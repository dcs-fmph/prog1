---
title: Program vyfarbovanie-queue.cpp
---

[Súbor na stiahnutie](./vyfarbovanie-queue.cpp)

```cpp
/* Program Vyfarbovanie z prednášky 19, verzia s radom.
 *
 * Program načíta maticu zo súboru vyfarbovanie-vstup.txt
 * a animáciu uloží do súboru vyfarbovanie-queue.svg.
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

struct queue {
    // Smerník na prvý uzol
    // Ak je rad prázdny, hodnota NULL
    node *first;
    // Smerník na posledný uzol.
    // Ak je rad prázdny, hodnota NULL
    node *last;
};

/* Inicializuje prázdny rad */
void init(queue &q) {
    q.first = NULL;
    q.last = NULL;
}

/* Zistí, či je rad prázdny */
bool isEmpty(const queue &q) {
    return q.first == NULL;
}

/* Pridá prvok item na koniec radu */
void enqueue(queue &q, dataType item) {
    node *tmp = new node;
    tmp->data = item;
    tmp->next = NULL;
    if (isEmpty(q)) {
        q.first = tmp;
        q.last = tmp;
    } else {
        q.last->next = tmp;
        q.last = tmp;
    }
}

/* Odoberie prvok zo začiatku radu a vráti jeho hodnotu */
dataType dequeue(queue &q) {
    assert(!isEmpty(q));
    dataType result = q.first->data;
    node *tmp = q.first->next;
    delete q.first;
    if (tmp == NULL) {
        q.first = NULL;
        q.last = NULL;
    } else {
        q.first = tmp;
    }
    return result;
}

/* Vráti prvok zo začiatku radu, ale nechá ho tam */
dataType peek(const queue &q) {
    assert(!isEmpty(q));
    return q.first->data;
}

/* Uvoľní pamäť */
void destroy(queue &q) {
    while (!isEmpty(q)) {
        dequeue(q);
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
    queue q;
    init(q);

    policko p = {riadok, stlpec};
    enqueue(q, p);

    while (!isEmpty(q)) {
        p = dequeue(q);
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
                enqueue(q, sused);

                vykresliStvorcek(sused.riadok, sused.stlpec, farby[farba],
                                 "brown", drawing);
                drawingWait(drawing, pauza);
            }
        }
    }
    destroy(q);
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
                                  "vyfarbovanie-queue.svg");
    vykresliMaticu(a, m, n, drawing);

    // vyfarbenie
    vyfarbi(a, m, n, riadok, stlpec, 4, drawing);

    // ukoncenie obrazku a uvolnenie pamate
    drawingFinish(drawing);
    zmazMaticu(a, m);
}
```
