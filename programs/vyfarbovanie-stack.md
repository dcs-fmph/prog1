---
title: Program vyfarbovanie-stack.cpp
---

[Súbor na stiahnutie](./vyfarbovanie-stack.cpp)

```cpp
/* Program Vyfarbovanie z prednášky 19, verzia so zásobníkom.
 *
 * Program načíta maticu zo súboru vyfarbovanie-vstup.txt
 * a animáciu uloží do súboru vyfarbovanie-stack.svg.
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

struct policko {
    int riadok, stlpec;
};

typedef policko dataType;

struct node {
    dataType data;
    node *next;
};

struct stack {
    // smerník na vrch zásobnika (začiatok zoznamu)
    // ak je zásobník prázdny, hodnota NULL.
    node *top;
};

/* Inicializuje prázdny zásobnik */
void init(stack &s) {
    s.top = NULL;
}

/* Zistí, či je zásobník prázdny */
bool isEmpty(const stack &s) {
    return s.top == NULL;
}

/* Pridá prvok item na vrch zásobníka */
void push(stack &s, dataType item) {
    node *tmp = new node;
    tmp->data = item;
    tmp->next = s.top;
    s.top = tmp;
}

/* Odoberie prvok z vrchu zásobníka a vráti jeho hodnotu */
dataType pop(stack &s) {
    assert(!isEmpty(s));
    dataType result = s.top->data;
    node *tmp = s.top->next;
    delete s.top;
    s.top = tmp;
    return result;
}

/* Vráti prvok na vrchu zásobníka, ale nechá ho tam */
dataType peek(const stack &s) {
    assert(!isEmpty(s));
    return s.top->data;
}

/* Uvoľní pamäť */
void destroy(stack &s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

const int deltaRiadok[4] = {0, 0, 1, -1};
const int deltaStlpec[4] = {1, -1, 0, 0};

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
    stack s;
    init(s);

    policko p = {riadok, stlpec};
    push(s, p);

    while (!isEmpty(s)) {
        p = pop(s);
        vykresliStvorcek(p.riadok, p.stlpec, farby[farba],
                         "lightgrey", drawing);
        drawingWait(drawing, pauza);

        for (int i = 0; i < 4; i++) {

            policko sused = {p.riadok + deltaRiadok[i],
                             p.stlpec + deltaStlpec[i]};

            if (sused.riadok >= 0 && sused.riadok < m
                    && sused.stlpec >= 0 && sused.stlpec < n
                    && a[sused.riadok][sused.stlpec] == staraFarba) {

                a[sused.riadok][sused.stlpec] = farba;
                push(s, sused);

                vykresliStvorcek(sused.riadok, sused.stlpec, farby[farba],
                                 "brown", drawing);
                drawingWait(drawing, pauza);
            }
        }
    }
    destroy(s);
}

int main() {
    FILE *fin = fopen("vyfarbovanie-vstup.txt", "r");
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
                                  "vyfarbovanie-stack.svg");
    vykresliMaticu(a, m, n, drawing);

    // vyfarbenie
    vyfarbi(a, m, n, riadok, stlpec, 4, drawing);

    // ukoncenie obrazku a uvolnenie pamate
    drawingFinish(drawing);
    zmazMaticu(a, m);
}
```
