---
title: Prednáška 4
---

* TOC
{:toc}

## Oznamy

Čo nás čaká v najbližších dňoch


### Kontrola vstupov

- Nasledujúca funkcia počíta súčet všetkých deliteľov čísla `n`.
- Funguje správne, ak `n` je *kladné* celé číslo.
- Pre záporné `n` vráti nulu, čo nie je ideálne.

```cpp
#include <iostream>
using namespace std;

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
    cout << "Zadaj kladne cele cislo: ";
    cin >> n;
        
    cout << "Sucet delitelov " << n << ": " 
         << sumOfDivisors(n) << "." << endl;
}
```

Ako by sme mohli funkciu zlepšiť?
- Preprogramovať ju tak, aby vrátila napr. súčet kladných deliteľov aj pre záporné čísla, čo však `n=0`?
- Vrátiť samotný výsledok ale aj logickú hodnotu, či bol vstup správny, t.j. výsledok je zmyspluplný
  - Momentálne však nevieme z funkcie vrátiť viac ako jednu hodnotu
- V prípade nesprávneho vstupu do funkcie ukončiť beh programu s nejakou správou o chybe
  - Uvidíme nižšie
- Mnohé jazyky na ošetrovanie podobných chýb používajú mechanizmus výnimiek, uvidíte v letnom semestri 

### Použitie funkcie `assert`

- Na ukončenie celého programu v prípade zlého vstupu, môžeme použiť
funkciu `assert` (treba ` #include  `<assert.h>).
- Táto funkcia kontroluje platnosť nejakej podmienky, jej vstupom je teda logická hodnota
- Ak je podmienka splnená, program normálne pokračuje
- V opačnom prípade sa program zastaví s chybovou hláškou

Okrem toho, že `assert` ukončí program, je to aj odkaz pre čitateľa kódu, aké máme na danom mieste programu predpoklady.

```cpp
#include <iostream>
#include <cassert>
using namespace std;

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
    cout << "Zadaj kladne cele cislo: ";
    cin >> n;
        
    cout << "Sucet delitelov " << n << ": " 
         << sumOfDivisors(n) << "." << endl;
}
```


## Záznam typu struct

V príklade s dĺžkou úsečky sme funkcii
posielali veľa parametrov (súradnice x a y):

```c
double dlzka(double x1, double y1, 
            double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2; 
    return sqrt(dx * dx + dy * dy);
}
```

Program bude krajší, ak si údaje o jednom bode spojíme do jedného
záznamu

```c
struct bod {
    double x, y;
};
```

  - Pomocou `struct` vytvoríme nový dátový typ `struct bod`, ktorý má zložky
    `x` a `y`
  - V jednom struct-e môžu byť aj položky rôznych typov, napr.

```c
struct bod { 
   double x,y; 
   int id; 
   bool visible; 
};
```

  - Môžeme vytvárať premenné typu `bod`, napr. `struct bod a, b;`
  - K položkám bodu pristupujeme pomocou bodky, napr. `a.x = 4.0;`

Nasledujúci program načíta súradnice troch bodov, spočíta obvod
trojuholníka a stredy všetkých troch strán.

```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct bod {
    double x, y;  // suradnice bodu v rovine
};

double dlzka(bod &bod1, bod &bod2) {
    // funkcia vrati dlzku usecky z bodu 1 do bodu 2
    double dx = bod1.x - bod2.x;
    double dy = bod1.y - bod2.y;
    return sqrt(dx * dx + dy * dy);
}

void stred(bod &bod1, bod &bod2, bod &stred) {
    // funkcia do bodu stred spocita stred usecky z bodu 1 do bodu 2
    stred.x = (bod1.x + bod2.x) / 2;
    stred.y = (bod1.y + bod2.y) / 2;
}

void vypisBod(bod &b) {
    // funkcia vypise suradnice bodu v zatvorke a koniec riadku
    cout << "(" << b.x << "," << b.y << ")" << endl;
}

int main() {
    // nacitame suradnice vrcholov trojuholnika
    bod A, B, C;
    cout << "Zadaj suradnice vrcholu A oddelene medzerou: ";
    cin >> A.x >> A.y;
    cout << "Zadaj suradnice vrcholu B oddelene medzerou: ";
    cin >> B.x >> B.y;
    cout << "Zadaj suradnice vrcholu C oddelene medzerou: ";
    cin >> C.x >> C.y;
    // spocitame dlzky stran
    double da = dlzka(B, C);
    double db = dlzka(A, C);
    double dc = dlzka(A, B);
    // vypiseme obvod
    cout << "Obvod trojuholnika ABC: " << da + db + dc << endl;

    // spocitame stredy stran
    bod stredAB;
    stred(A, B, stredAB);
    bod stredAC;
    stred(A, C, stredAC);
    bod stredBC;
    stred(B, C, stredBC);

    // vypiseme stredy stran
    cout << "Stred strany AB: ";
    vypisBod(stredAB);
    cout << "Stred strany AC: ";
    vypisBod(stredAC);
    cout << "Stred strany BC: ";
    vypisBod(stredBC);
}
```

Príklad behu programu:

    Zadaj suradnice vrcholu A oddelene medzerou: 0 0
    Zadaj suradnice vrcholu B oddelene medzerou: 0 3
    Zadaj suradnice vrcholu C oddelene medzerou: 4 0
    Obvod trojuholnika ABC: 12
    Stred strany AB: (0,1.5)
    Stred strany AC: (2,0)
    Stred strany BC: (2,1.5)
