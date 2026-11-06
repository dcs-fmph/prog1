/* Program Hra Life z prednášky 15 */

#include "SVGdraw.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/* velkost stvorceka */
#define SIZE 15

bool **vytvorMaticu(int m, int n) {
    /* vytvor maticu s m riadkami a n stlpcami */
    bool **a;
    a = malloc(sizeof(bool *) * m);
    for (int i = 0; i < m; i++) {
        a[i] = malloc(sizeof(bool) * n);
    }
    return a;
}

void zmazMaticu(int m, bool **a) {
    /* uvolni pamat matice s m riadkami */
    for (int i = 0; i < m; i++) {
        free(a[i]);
    }
    free(a);
}

void nacitajMaticu(int m, int n, bool **a) {
    /* matica je vytvorena, velkosti m krat n, vyplnime ju cislami zo vstupu */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c", &c);  // nacitaj znak, preskoc biele znaky, ak nejake su
            assert(c == '0' || c == '1');  // kontrola, ci je znak 0 alebo 1
            a[i][j] = (c == '1');
        }
    }
}

void zobrazStvorcek(int i, int j, bool hodnota, Drawing drawing) {
    /* zobraz stvorcek v riadku i a stlpci j */
    setLineColor(drawing, "white");
    if (hodnota) {
        setFillColor(drawing, "black");
    } else {
        setFillColor(drawing, "white");
    }
    drawRectangle(drawing, j * SIZE, i * SIZE, SIZE, SIZE);
}

void zobrazMaticu(int m, int n, bool **a, Drawing drawing) {
    /* zobraz prvky true ciernymi stvorcekmi */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            /* nastavenie farby podla hodnoty */
            if (a[i][j]) {
                zobrazStvorcek(i, j, true, drawing);
            }
        }
    }
}

void zobrazZmeny(int m, int n, bool **a, bool **b, Drawing drawing) {
    /* zobraz nove stvorceky na miestach, kde bola zmena */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) {
                zobrazStvorcek(i, j, b[i][j], drawing);
            }
        }
    }
}

int zratajOkolie(int m, int n, bool **a, int riadok, int stlpec) {
    /* pocet zivych prvkov v okoli */
    int sucet = 0;
    for (int i = riadok - 1; i <= riadok + 1; i++) {
        for (int j = stlpec - 1; j <= stlpec + 1; j++) {
            /* treba osetrit okraje matice */
            if (i >= 0 && i < m && j >= 0 && j < n && a[i][j]) {
                sucet++;
            }
        }
    }
    /* samotny stvorcek nechceme zaratat */
    if (a[riadok][stlpec]) {
        sucet--;
    }
    return sucet;
}

void prepocitajMaticu(int m, int n, bool **a, bool **b) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int pocet = zratajOkolie(m, n, a, i, j);
            /* prirad do b[i][j] hodnotu podla okolia a[i][j] */
            b[i][j] = (pocet == 3 || (pocet == 2 && a[i][j]));
        }
    }
}

int main(void) {
    /* nacitaj rozmery matice */
    int m, n;
    scanf("%d %d", &m, &n);

    /* vytvor a nacitaj maticu */
    bool **a = vytvorMaticu(m, n);
    nacitajMaticu(m, n, a);

    /* zobraz maticu */
    Drawing drawing = drawingInit(m * SIZE, n * SIZE, "life.svg");
    zobrazMaticu(m, n, a, drawing);
    drawingWait(drawing, 1);

    /* pomocna matica na vypocty */
    bool **b = vytvorMaticu(m, n);

    /* simuluj 10 krokov hry life */
    for (int i = 0; i < 10; i++) {
        /* podla a spocitaj maticu do b */
        prepocitajMaticu(m, n, a, b);
        /* prekresli, co sa zmenilo */
        zobrazZmeny(m, n, a, b, drawing);
        drawingWait(drawing, 1);
        /* vymen smerniky, aby v a bola nova matica */
        bool **tmp = b;
        b = a;
        a = tmp;
    }

    /* uvolni pamat matic */
    zmazMaticu(m, a);
    zmazMaticu(m, b);
    drawingFinish(drawing);
}

