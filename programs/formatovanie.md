---
title: Program formatovanie.c
---

[Súbor na stiahnutie](./formatovanie.c)

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

void simplify(char A[]) {
    /* V retazci A nahradi kazdy suvisly usek bielych znakov prave jednou medzerou.
     * Na zaciatku a konci retazca nebudu medzery. */

    /* prepis hocijake biele znaky na medzeru */
    for (int i = 0; A[i] != 0; i++) {
        if (isspace(A[i])) {
            A[i] = ' ';
        }
    }

    int kam = 0; /* prve este neobsadene miesto */
    char prev = ' '; /* predchadzajuci znak */

    for (int i = 0; A[i] != 0; i++) {
        /* ak nemame viac medzier po sebe, skopirujeme znak */
        if (A[i] != ' ' || prev != ' ') {
            A[kam] = A[i];
            kam++;
        }
        /* zapamatame si posledny znak */
        prev = A[i];
    }

    /* zrusime pripadnu medzeru na konci */
    if (kam > 0 && A[kam - 1] == ' ') {
        kam--;
    }

    /* retazec ukoncime nulou */
    A[kam] = 0;
}

bool breakLines(char A[], int width) {
    /* Preformatuje odstavec na sirku riadku width, vyhodi zbytocne medzery.
     * Dlzka kazdeho slova musi byt najviac width, inak funkcia vrati false */

    simplify(A);
    int n = strlen(A);

    int zac = 0;  /* index prveho pismena v riadku */
    while (zac < n) {
        int kon = zac + width;  /* potencialny koniec riadku */
        /* ak uz nemame dost pismen na cely riadok */
        if (kon > n) {
            kon = n;
        }
        /* ak sme na konci, pridame koniec riadku za koniec retazca */
        if (kon == n) {
            A[kon] = '\n';
            A[kon + 1] = 0;
            n++;
        } else {
            /* ideme späť, kým nenájdeme medzeru */
            while (kon > zac && A[kon] != ' ') {
                kon--;
            }
            /* nenašli sme medzeru: slovo bolo príliš dlhé. */
            if (kon == zac) {
                return false;
            }
            /* medzeru prepíšeme na koniec riadku */
            assert(A[kon] == ' ');
            A[kon] = '\n';
        }
        /* za koncom riadku bude novy zaciatok */
        zac = kon + 1;
    }
    return true;
}

#define NMAX 2000

int main(void) {
    char A[NMAX];
    A[0] = 0;

    printf("Zadavaj text ukonceny prazdnym riadkom.\n");
    while (true) {
        /* nacitame jeden riadok */
        char tmp[NMAX];
        fgets(tmp, NMAX, stdin);
        /* ak je prazdny, koncime nacitavanie */
        if (strcmp(tmp, "\n") == 0) {
            break;
        }
        /* ak je miesto v poli A, pridame do neho novy riadok */
        if (strlen(A) + strlen(tmp) + 1 < NMAX) {
            strcat(A, tmp);
        } else {
            printf("Text je prilis dlhy.\n");
            return 1;
        }
    }

    printf("Zadaj sirku riadku:\n");
    int width;
    scanf("%d", &width);

    breakLines(A, width);
    printf("Sformatovany odstavec:\n");
    fputs(A, stdout);
}
```
