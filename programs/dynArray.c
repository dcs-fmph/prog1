#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Dynamicke pole celych cisel */
typedef struct {
    int *items;     // smerník na prvý prvok poľa
    int size;       // veľkosť alokovaného poľa
    int length;     // počet prvkov pridaných do poľa
} dynArray;

void init(dynArray *a) {
    /* Inicializuje dynamické pole veľkosti 2 */
    a->size = 2;
    a->length = 0;
    a->items = malloc(sizeof(int) * a->size);
}

void reallocate(dynArray *a, int newSize) {
    /* Pomocna funkcia, ktora sa pouziva vo funkcii add.
     * Zmeni velkost pola zo size na newSize,
     * prekopiruje vsetky prvky do noveho pola. */

    assert(a->length <= newSize);
    a->size = newSize;
    // alokujeme nove pole
    int *newItems = malloc(sizeof(int) * a->size);
    // prekopirujeme stare pole do noveho
    for (int i = 0; i < a->length; i++) {
        newItems[i] = a->items[i];
    }
    // uvolnime stare pole
    free(a->items);
    a->items = newItems;  // a->items teraz ukazuje na nove pole
}

void add(dynArray *a, int x) {
    /* Prida na koniec dynamickeho pola prvok x
     * a v pripade potreby realokuje pole */

    // ak uz sa x do pola nevojde
    if (a->length == a->size) {
        // zdvojnasobime velkost pola items
        reallocate(a, a->size * 2);
    }
    // teraz je pole urcite dost velke
    // pridame x a zvysime pocet prvkov
    a->items[a->length] = x;
    a->length++;
}

int get(dynArray *a, int index) {
    /* Vrati prvok dynamickeho pola a na pozicii index
     * (ak ide o korektnu poziciu)*/
    assert(index >= 0 && index <= a->length - 1);
    return a->items[index];
}

void set(dynArray *a, int index, int x) {
    /* Ulozi na poziciu index dynamickeho pola a hodnotu x
     * (ak ide o korektnu poziciu)*/
    assert(index >= 0 && index <= a->length - 1);
    a->items[index] = x;
}

int length(dynArray *a) {
    /* Vrati pocet prvkov v dynamickom poli a */
    return a->length;
}

void destroy(dynArray *a) {
    /* Uvolni alokovanu pamat pre pole a */
    free(a->items);
}

int main(void) {
    dynArray a;
    init(&a);  // inicializuje a

    int x;
    scanf("%d", &x);
    // pridavame prvky, kym su nezaporne
    while (x >= 0) {
        add(&a, x);
        scanf("%d", &x);
    }
    // vypise prvky pola od konca
    for (int i = length(&a) - 1; i >= 0; i--) {
        printf(" %d", get(&a, i));
    }
    printf("\n");

    // ukazka pouzitia get a set
    set(&a, 0, 42);
    printf(" %d\n", get(&a, 0));

    destroy(&a);  // uvolni pamat
}
