---
title: Program vyfarbovanie.c
---

[Súbor na stiahnutie](./vyfarbovanie.c)

```c
#include "SVGdraw.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

const char *farby[5] = {"white", "blue", "black", "yellow", "red"}; 

const int stvorcek = 40;    // velkost stvorceka v pixeloch
const int hrubkaCiary = 2;  // hrubka ciary v pixeloch
const double pauza = 0.3;   // pauza po kazdom kroku vyfarbovania v sekundach

/* Vytvori maticu s n riadkami a m stlpcami. */
int **vytvorMaticu(int m, int n) {
    int **a;
    a = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        a[i] = (int *)malloc(n * sizeof(int));
    }
    return a;
}

/* Uvolni pamat matice a s n riadkami a m stlpcami. */
void zmazMaticu(int **a, int m) {
    for (int i = 0; i < m; i++) {
        free(a[i]);
    }
    free(a);
}

/* Vykresli stvorcek v riadku i a stlpci j 
   s farbou vyplne farba a farbou ciary farbaCiary. */
void vykresliStvorcek(int i, int j, 
                      const char * farba, 
                      const char * farbaCiary, 
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

/* Nacita z textoveho suboru, na ktory ukazuje fr, 
   prvky matice a s n riadkami a m stlpcami. */
void nacitajMaticu(FILE *fr, int **a, int m, int n) {
    assert(fr != NULL);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fr, "%d", &a[i][j]);
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

int main() {
    FILE *fr = fopen("vyfarbovanie-vstup.txt", "r");
    assert(fr != NULL);

    // nacitanie rozmerov matice
    int m, n;
    fscanf(fr, "%d %d", &m, &n);  
    // vytvorenie matice a nacitanie jej prvkov  
    int **a = vytvorMaticu(m, n);
    nacitajMaticu(fr, a, m, n);
    // nacitanie suradnic pociatocneho stvorceka 
    int riadok, stlpec;
    fscanf(fr, "%d", &riadok);
    fscanf(fr, "%d", &stlpec);

    fclose(fr);
    
    Drawing drawing = drawingInit(n * stvorcek, m * stvorcek, "vyfarbovanie.svg");
    vykresliMaticu(a, m, n, drawing);


    vyfarbi(a, m, n, riadok, stlpec, 4, drawing);

    drawingFinish(drawing);
    zmazMaticu(a, m);
}
```
