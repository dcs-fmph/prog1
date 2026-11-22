/* Program Počítanie ostrovov z prednášky 19
 *
 * Program načíta maticu zo súboru ostrovy-vstup.txt
 * a animáciu uloží do súboru ostrovy.svg.
 */

#include "SVGdraw.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>

const char *farby[5] = {"white", "blue", "black", "yellow", "red"};

const int stvorcek = 40;    // velkost stvorceka v pixeloch
const int hrubkaCiary = 2;  // hrubka ciary v pixeloch
const double pauza = 0.3;   // pauza po kazdom kroku vyfarbovania v sekundach

/* Vytvori maticu s m riadkami a n stlpcami. */
int **vytvorMaticu(int m, int n) {
    int **a = new int *[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
    }
    return a;
}

/* Uvolni pamat matice a s m riadkami. */
void zmazMaticu(int **a, int m) {
    for (int i = 0; i < m; i++) {
        delete[] a[i];
    }
    delete[] a;
}

/* Vykresli stvorcek v riadku i a stlpci j
   s farbou vyplne farba a farbou ciary farbaCiary. */
void vykresliStvorcek(int i, int j,
                      const char *farba,
                      const char *farbaCiary,
                      Drawing drawing) {
    setLineColor(drawing, farbaCiary);
    setLineWidth(drawing, hrubkaCiary);
    setFillColor(drawing, farba);
    drawRectangle(drawing, j * stvorcek, i * stvorcek,
                  stvorcek, stvorcek);
}

/* Vykresli maticu a s n riadkami a m stlpcami. */
void vykresliMaticu(int **a, int m, int n, Drawing drawing) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            vykresliStvorcek(i, j, farby[a[i][j]], "lightgray", drawing);
        }
    }
}

/* Nacita z textoveho suboru, na ktory ukazuje fin,
   prvky matice a s n riadkami a m stlpcami. */
void nacitajMaticu(FILE *fin, int **a, int m, int n) {
    assert(fin != NULL);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fin, "%d", &a[i][j]);
        }
    }
}

/* Prefarbi suvislu jednofarebnu oblast obsahujucu
 * poziciu (riadok,stlpec) na farbu s cislom farba. */
void vyfarbi(int **a, int m, int n,
             int riadok, int stlpec, int farba,
             Drawing drawing) {
    int staraFarba = a[riadok][stlpec];
    if (staraFarba == farba) {
        return;
    }
    a[riadok][stlpec] = farba;
    vykresliStvorcek(riadok, stlpec, farby[farba],
                     "brown", drawing);
    drawingWait(drawing, pauza);
    if (riadok - 1 >= 0 && a[riadok - 1][stlpec] == staraFarba) {
        vyfarbi(a, m, n, riadok - 1, stlpec, farba, drawing);
    }
    if (riadok + 1 < m && a[riadok + 1][stlpec] == staraFarba) {
        vyfarbi(a, m, n, riadok + 1, stlpec, farba, drawing);
    }
    if (stlpec - 1 >= 0 && a[riadok][stlpec - 1] == staraFarba) {
        vyfarbi(a, m, n, riadok, stlpec - 1, farba, drawing);
    }
    if (stlpec + 1 < n && a[riadok][stlpec + 1] == staraFarba) {
        vyfarbi(a, m, n, riadok, stlpec + 1, farba, drawing);
    }
    vykresliStvorcek(riadok, stlpec, farby[farba],
                     "lightgray", drawing);
    drawingWait(drawing, pauza);
}

int najdiOstrovy(int **a, int m, int n, Drawing drawing) {
    int ostrovov = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 3) {
                ostrovov++;
                vyfarbi(a, m, n, i, j, 4, drawing);
            }
        }
    }
    return ostrovov;
}


int main() {
    FILE *fin = fopen("ostrovy-vstup.txt", "r");
    assert(fin != NULL);

    // nacitanie rozmerov matice
    int m, n;
    fscanf(fin, "%d %d", &m, &n);
    // vytvorenie matice a nacitanie jej prvkov
    int **a = vytvorMaticu(m, n);
    nacitajMaticu(fin, a, m, n);
    // nacitanie suradnic pociatocneho stvorceka
    int riadok, stlpec;
    fscanf(fin, "%d", &riadok);
    fscanf(fin, "%d", &stlpec);
    fclose(fin);

    // vykreslenie povodnej matice
    Drawing drawing = drawingInit(n * stvorcek, m * stvorcek,
                                  "ostrovy.svg");
    vykresliMaticu(a, m, n, drawing);

    int pocetOstrovov = najdiOstrovy(a, m, n, drawing);
    std::printf("Pocet ostrovov je %d.\n", pocetOstrovov);

    // ukoncenie obrazku a uvolnenie pamate
    drawingFinish(drawing);
    zmazMaticu(a, m);
}
