---
title: Prednáška 4b
---

* TOC
{:toc}

## Oznamy

Čo nás čaká v najbližších dňoch

## Opakovanie

Na minulej prednáške sme videli funkcie, ako napríklad túto:

```c
double dlzka(double x1, double y1, 
            double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2; 
    return sqrt(dx * dx + dy * dy);
}
```

Všeobecná schéma funkcie

```c
typ_navratovej_hodnoty identifikator_funkcie(zoznam_vstupnych_argumentov) {
    telo_funkcie // Môže obsahovať príkazy return
}
```


## Kontrola vstupov

- Nasledujúca funkcia počíta súčet všetkých deliteľov čísla `n`.
- Funguje správne, ak `n` je kladné celé číslo.
- Pre záporné `n` vráti nulu, čo nie je ideálne.

```c
#include <stdio.h>

int sumOfDivisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += i;    
        }        
    }   
    return sum;  
}

int main() {
    int n;
    printf("Zadaj kladne cele cislo: ");
    scanf("%d", &n);
        
    printf("Sucet delitelov %d: %d.\n", n, sumOfDivisors(n));
}
```

Ako by sme mohli funkciu zlepšiť?
- Preprogramovať ju tak, aby vrátila napr. súčet kladných deliteľov aj pre záporné čísla, čo však pre `n=0`?
- Vrátiť samotný výsledok ale aj logickú hodnotu, či bol vstup správny, t.j. výsledok je zmyspluplný.
  - Momentálne však ešte nevieme z funkcie vrátiť viac ako jednu hodnotu.
- V prípade nesprávneho vstupu do funkcie ukončiť beh programu s nejakou správou o chybe
  - Uvidíme nižšie
- Mnohé jazyky na ošetrovanie podobných chýb používajú mechanizmus výnimiek, uvidíte v letnom semestri.

### Použitie funkcie `assert`

- Na ukončenie celého programu v prípade zlého vstupu, môžeme použiť
funkciu `assert` (treba ` #include  `<assert.h>).
- Táto funkcia kontroluje platnosť nejakej podmienky, jej vstupom je teda logická hodnota.
- Ak je podmienka splnená, program normálne pokračuje.
- V opačnom prípade sa program zastaví s chybovou hláškou.

Okrem toho, že `assert` ukončí program, je to aj odkaz pre čitateľa kódu, aké máme na danom mieste programu predpoklady.

```c
#include <stdio.h>
#include <assert.h>

int sumOfDivisors(int n) {
    assert(n > 0);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += i;    
        }        
    }   
    return sum;  
}

int main() {
    int n;
    printf("Zadaj kladne cele cislo: ");
    scanf("%d", &n);
        
    printf("Sucet delitelov %d: %d.\n", n, sumOfDivisors(n));
}
```

Príklad behu programu:
```
Zadaj kladne cele cislo: -10
pokus: pokus.c:5: sumOfDivisors: Assertion `n > 0' failed.
Aborted (core dumped)
```


## Záznam typu `struct`

V príklade s dĺžkou úsečky sme funkcii posielali veľa parametrov (súradnice x a y):

```c
double dlzka(double x1, double y1, 
            double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2; 
    return sqrt(dx * dx + dy * dy);
}
```

Program bude krajší, ak si údaje o jednom bode spojíme do jedného záznamu

```c
struct bod {
    double x, y;
};
```

- Pomocou `struct` vytvoríme nový dátový typ `struct bod`, ktorý má zložky `x` a `y`
- V jednom `struct`-e môžu byť aj položky rôznych typov, napr.

```c
struct rozsireny_bod { 
   double x,y; 
   int id; 
   bool visible; 
};
```

- Môžeme vytvárať premenné typu `struct bod`, napr. `struct bod a, b;`
- K položkám bodu pristupujeme pomocou bodky, napr. `a.x = 4.0;`
- Súradnice bodov môžeme posielať do funkcií ako jeden parameter a tiež môžeme funkcie vracať záznamy typu `struct`, ako vidíme v nasledujúcom príklade.

Nasledujúci program načíta súradnice troch bodov, spočíta obvod
trojuholníka a stredy všetkých troch strán.

```c
#include <stdio.h>
#include <math.h>

struct bod {
    double x, y;  // suradnice bodu v rovine
};

double dlzka(struct bod bod1, struct bod bod2) {
    // funkcia vrati dlzku usecky z bodu 1 do bodu 2
    double dx = bod1.x - bod2.x;
    double dy = bod1.y - bod2.y;
    return sqrt(dx * dx + dy * dy);
}

struct bod stred(struct bod bod1, struct bod bod2) {
    struct bod stred;
    // funkcia vrati bod, ktory je stredom usecky z bodu 1 do bodu 2
    stred.x = (bod1.x + bod2.x) / 2;
    stred.y = (bod1.y + bod2.y) / 2;
    return stred;
}

void vypisBod(struct bod b) {
    // funkcia vypise suradnice bodu v zatvorke a koniec riadku
    printf("(%lf,%lf)\n", b.x, b.y);
}

int main() {
    // nacitame suradnice vrcholov trojuholnika
    struct bod A, B, C;
    printf("Zadaj suradnice vrcholu A oddelene medzerou: ");
    scanf("%lf %lf", &A.x, &A.y);
    printf("Zadaj suradnice vrcholu B oddelene medzerou: ");
    scanf("%lf %lf", &B.x, &B.y);
    printf("Zadaj suradnice vrcholu C oddelene medzerou: ");
    scanf("%lf %lf", &C.x, &C.y);
    // spocitame dlzky stran
    double da = dlzka(B, C);
    double db = dlzka(A, C);
    double dc = dlzka(A, B);
    // vypiseme obvod
    printf("Obvod trojuholnika ABC: %lf\n", da + db + dc);

    // spocitame stredy stran
    struct bod stredAB = stred(A, B);
    struct bod stredAC = stred(A, C);
    struct bod stredBC = stred(B, C);

    // vypiseme stredy stran
    printf("Stred strany AB: ");
    vypisBod(stredAB);
    printf("Stred strany AC: ");
    vypisBod(stredAC);
    printf("Stred strany BC: ");
    vypisBod(stredBC);
}
```

Príklad behu programu:

```
Zadaj suradnice vrcholu A oddelene medzerou: 0 0
Zadaj suradnice vrcholu B oddelene medzerou: 0 3
Zadaj suradnice vrcholu C oddelene medzerou: 4 0
Obvod trojuholnika ABC: 12
Stred strany AB: (0,1.5)
Stred strany AC: (2,0)
Stred strany BC: (2,1.5)
```

## Spracovanie väčšieho množstva dát

Naše programy doteraz spracovávali len malý počet vstupných dát
načítaných od užívateľa (napr. súradnice troch bodov). Často však
chceme pracovať s väčším množstvom dát

  - Na ďalšej prednáške si ukážeme, ako uložiť väčšie množstvo dát do poľa
  - Na niektoré úlohy však pole nepotrebujeme - údaje môžeme spracovávať
    rovno ako ich používateľ zadáva

V nasledujúcich príkladoch užívateľ zadá číslo *N* a potom *N* celých
čísel
  - Predstavme si napríklad, že učiteľ zadá body, ktoré študenti dostali
    na písomke (napr. celé čísla v rozsahu 0..10)
  - Z týchto bodov chceme spočítať nejaké štatistiky

### Priemer

```c
#include <stdio.h>

int main() {
    int N;
    printf("Zadaj pocet cisel: ");
    scanf("%d", &N);

    int sucet = 0;
    printf("Zadavaj cisla: ");
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        sucet += x;
    }

    double priemer = sucet / (double) N;
    printf("Priemer je %lf.\n", priemer);
}
```

  - Čo by sa stalo, keby sme vo výpočte priemeru vynechali `(double)`?

### Maximum

```c
#include <stdio.h>

int main() {
    int max, x, N;

    printf("Zadaj pocet cisel: ");
    scanf("%d", &N);

    printf("Zadavajte cisla: ");

    max = ?
    for (int i = 0; i < N; i++) {
        scanf("%d", &x);
        if (x > max) {
            max = x;
        }
    }

    printf("Maximum je %d\n", max);
}
```

Ako ale začať? Ako nastaviť maximum na začiatok?

  - Jedna možnosť je nastaviť ho na nejakú veľmi malú hodnotu, aby sa
    iste neskôr zmenila. Ale čo ak používateľ dá všetky čísla ešte
    menšie?
  - Riešením je použiť najmenšie možné číslo. Ale to je príliš viazané
    na konkrétny rozsah, nebude fungovať po zmene typu premenných.
  - Ďalšia možnosť je si pamätať, že ešte nemáme správne nastavené
    maximum a po načítaní prvého čísla ho nastaviť alebo spracovať prvé
    číslo zvlášť (mimo cyklu).


```c
#include <stdio.h>

int main() {
    int max, x, N;

    printf("Zadaj pocet cisel: ");
    scanf("%d", &N);

    printf("Zadavajte cisla: ");
    scanf("%d", &x);   // načítanie prvého čísla
    max = x;

    for (int i = 1; i < N; i++) {  // cyklus cez N-1 ďalších čísel 
        scanf("%d", &x);
        if (x > max) {
            max = x;
        }
    }

    printf("Maximum je %d\n", max);
}
```

**Cvičenie:**

  - Ako by sme program rozšírili tak, aby vedel vypísať aj koľké číslo v
    poradí bolo najväčšie?
  - Čo treba v programe zmeniť, ak chceme hľadať minimum namiesto
    maxima?
