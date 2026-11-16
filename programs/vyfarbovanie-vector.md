---
title: Program vyfarbovanie-vector.cpp
---

[Súbor na stiahnutie](./vyfarbovanie-vector.cpp)

```cpp
/* Program Vyfarbovanie z prednášky 19, verzia s vectormi */
#include "SVGdraw.h"
#include <cstdio>
#include <cassert>
#include <vector>

const char *farby[5] = {"white", "blue", "black", "yellow", "red"};

const int stvorcek = 40;    // velkost stvorceka v pixeloch
const int hrubkaCiary = 2;  // hrubka ciary v pixeloch
const double pauza = 0.3;   // pauza po kazdom kroku vyfarbovania v sekundach

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
void vykresliMaticu(const std::vector<std::vector<int>> &a,
                    Drawing drawing) {
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)a[i].size(); j++) {
            vykresliStvorcek(i, j, farby[a[i][j]], "lightgray", drawing);
        }
    }
}

/* Nacita z textoveho suboru, na ktory ukazuje fin,
   prvky matice a, ktora uz je vytvorena. */
void nacitajMaticu(FILE *fin, std::vector<std::vector<int>> &a) {
    assert(fin != NULL);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)a[i].size(); j++) {
            int x;
            fscanf(fin, "%d", &x);
            a[i][j] = x;
        }
    }
}

/* Prefarbi suvislu jednofarebnu oblast obsahujucu
 * poziciu (riadok,stlpec) na farbu s cislom farba. */
void vyfarbi(std::vector<std::vector<int>> &a,
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
        vyfarbi(a, riadok - 1, stlpec, farba, drawing);
    }
    if (riadok + 1 < (int)a.size() && a[riadok + 1][stlpec] == staraFarba) {
        vyfarbi(a, riadok + 1, stlpec, farba, drawing);
    }
    if (stlpec - 1 >= 0 && a[riadok][stlpec - 1] == staraFarba) {
        vyfarbi(a, riadok, stlpec - 1, farba, drawing);
    }
    if (stlpec + 1 < (int)a[riadok].size() && a[riadok][stlpec + 1] == staraFarba) {
        vyfarbi(a, riadok, stlpec + 1, farba, drawing);
    }
    vykresliStvorcek(riadok, stlpec, farby[farba],
                     "lightgray", drawing);
    drawingWait(drawing, pauza);
}

int main() {
    FILE *fin = fopen("vyfarbovanie-vstup.txt", "r");
    assert(fin != NULL);

    // nacitanie rozmerov matice
    int m, n;
    fscanf(fin, "%d %d", &m, &n);
    // vytvorenie matice a nacitanie jej prvkov
    std::vector<std::vector<int>> a(m, std::vector<int>(n));
    nacitajMaticu(fin, a);
    // nacitanie suradnic pociatocneho stvorceka
    int riadok, stlpec;
    fscanf(fin, "%d", &riadok);
    fscanf(fin, "%d", &stlpec);
    fclose(fin);

    // vykreslenie povodnej matice
    Drawing drawing = drawingInit(n * stvorcek, m * stvorcek,
                                  "vyfarbovanie.svg");
    vykresliMaticu(a, drawing);

    // vyfarbenie
    vyfarbi(a, riadok, stlpec, 4, drawing);

    // ukoncenie obrazku
    drawingFinish(drawing);
}
```
