---
title: Prednáška 15
---

* TOC
{:toc}

## Oznamy

  - Miniprojekt odovzdávajte do budúceho štvrtka 22:00, posledný
    miniprojekt bude zverejnený budúci týždeň.
  - Úlohy z tohto týždňa majú termín odovzdania až utorok večer, lebo v
    pondelok je rektorské voľno. V utorok na cvičeniach však pribudnú
    nové úlohy, takže odporúčame tie z tohto týždňa dokončiť skôr.
  - Na dnešných cvičeniach bude rozcvička za jeden bonusový bod.
  - Nerobte zbytočné zmeny v poskytnutej kostre, stratíte za to body.
  - Pri práci so smerníkmi odporúčame nakresliť si obrázok.

## Smerníková aritmetika

Na smerníkoch možno vykonávať určité operácie, ktoré sa zvyknú nazývať
smerníková aritmetika. Uvažujme číslo `n` typu `int` a smerníky `p` a
`q` na nejaký typ `T`.

```cpp
int n;
T * p, * q;
```

  - `p + n` je smerník na `n`-té políčko za adresou `p`, pričom veľkosť
    políčka je daná typom `T`
      - `p + n` je teda to isté ako `&(p[n])` a `*(p+n)` je to isté ako
        `p[n]`.
      - `p++` je skratkou pre `p = p + 1`, posunie nám teda smerník `p`
        o políčko doprava v rámci poľa.
      - Výraz `p[n]` je len skratkou pre `*(p+n)`.
      - `p[n]` aj `p + n` teda chceme používať iba ak `p` ukazuje na
        prvok poľa, za ktorým v poli ide ešte aspoň `n` ďalších políčok
  - Podobne `p - n` je smerník na `n`-té políčko pred adresou `p`.
      - `p - n` teda chceme používať iba ak `p` ukazuje na prvok poľa,
        pred ktorým v poli ide ešte aspoň `n` ďalších políčok
  - Ak `p` a `q` sú adresami prvkov v tom istom poli, `p - q` je celé
    číslo `k` také, že `p == q + k`, t.j. o koľko políčok je `p` ďalej
    vpravo od `q`.
  - Ak `p` a `q` sú adresami prvkov v tom istom poli, môžeme ich tiež
    porovnávať pomocou `<, >, <=, >=`
  - Ľubovoľné dva smerníky toho istého typu vieme porovnávať pomocou
    `==, !=`.

Tu je napr. zvláštny spôsob ako vypísať pole `a`:

```cpp
const int n = 4;
int a[n] = {4, 3, 2, 1};
for (int * smernik = a; smernik < a + n; smernik++) {
     cout << "Prvok " << smernik - a << " je " << *smernik << endl;
}
```

Podobný kód sa ale občas používa na prechádzanie reťazcov. Napríklad
nasledujúca funkcia spočíta počet medzier v reťazci:

```cpp
int zratajMedzery(char str[]) { // mohli by sme dať aj char *str
  int pocet = 0;
  while(*str != 0) {   // kým nenájdeme ukončovaciu nulu
     if(*str == ' ') { // skontroluj znak, na ktorý ukazuje str
         pocet++; 
     }
     str++;           // posuň str na ďalší znak 
  }
  return pocet;
}
```

### Funkcie z knižnice cstring so smerníkovou aritmetikou

  - `strstr(text, vzorka)` vracia smerník na `char`
      - `NULL` ak sa vzorka nenachádza v texte, smerník na začiatok
        prvého výskytu inak
      - pozíciu výskytu zistíme smerníkovou aritmetikou:

<!-- end list -->

    char * text = "Hello world!";
    char * vzorka = "or";
    char * where = strstr(text, vzorka);
    if(where != NULL) {
      int position = where - text;
    }

  - Ako by ste pomocou volaní `strstr` spočítali počet výskytov vzorky v
    texte?
  - Podobne `strchr` hľadá prvý výskyt znaku v texte.

## Práca s konzolou na spôsob jazyka C: `printf` a `scanf`

  - Doposiaľ sme s konzolou pracovali prostredníctvom knižnice
    [`iostream`](http://www.cplusplus.com/reference/iostream/), ktorá
    patrí medzi štandardné knižnice jazyka C++ a v ktorej sú definované
    prúdy `cin` a `cout`.
  - Dnes si ukážeme alternatívny prístup k práci s konzolou založený na
    knižnici [`cstdio`](http://www.cplusplus.com/reference/cstdio/),
    ktorá je štandardnou knižnicou jazyka C.

### Výpis formátovaných dát na konzolu: `printf`

  - S použitím knižnice `cstdio` možno na konzolu písať pomocou funkcie
    [`printf`](http://www.cplusplus.com/reference/cstdio/printf/).
  - Tu sú príklady jej použitia:

<!-- end list -->

```cpp
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    int x = 10;
    double y = sqrt(x);
    printf("Ahoj svet, este raz!\n");
    printf("Odmocnina cisla %d je %f.\n", x, y);
}
```

Tento program vypíše:

```cpp
Ahoj svet, este raz!
Odmocnina cisla 10 je 3.162278.
```

Vo všeobecnosti vyzerá volanie `printf` nasledovne:

```cpp
printf(format, hodnota1, hodnota2, ...)
```

  - Prvý argument je **formátovací reťazec**, za ním môže nasledovať
    niekoľko ďalších argumentov.
  - Bežné znaky z formátovacieho reťazca sa priamo vypíšu na výstup.
  - Koniec riadku sa píše pomocou `"\n"`.
  - Symbol `%` začína takzvanú **špecifikáciu konverzie** a má za
    následok vypísanie ďalšieho argumentu funkcie (prvého, ktorý sa
    nepoužil).
  - V jednoduchých príkladoch za znakom `%` nasleduje znak
    reprezentujúci typ vypísanej hodnoty.
  - Pozor, typy jednotlivých argumentov musia byť v súlade s
    formátovacím reťazcom.

<!-- end list -->

  - `%d`: celé číslo (typ `int`).
  - `%ld`: dlhé celé číslo (typ `long int`).
  - `%f`: reálne číslo (typ `double`).
  - `%e`: reálne číslo vo vedeckej notácii, napr. `5.4e7` (typ
    `double`).
  - `%c`: znak (typ `char`).
  - `%s`: reťazec (typ `char *`).
  - `%%`: vypíše samotný znak `%`.

### Formátovanie výstupu

  - Formát vypísania daného argumentu možno upraviť nepovinnými
    parametrami medzi symbolom `%` a znakom konverzie.
  - Napríklad:
      - `%.2f`: vypíše reálne číslo na 2 desatinné miesta,
      - `%4d`: ak má celé číslo menej ako 4 cifry, doplní vľavo medzery,
      - `%04d`: podobne, ale dopĺňa nuly.

Nasledujúci program vo vhodnom formáte vypíše hodnoty faktoriálu
prirodzených čísel od 1 po 20 použitím typu `long long int`, ktorý
garantuje aspoň 64 bitové číslo:

```cpp
#include <cstdio>
using namespace std;

long long int factorial(int n) {                      
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

int main() {
    for (int i = 1; i <= 20; i++) {                   
        printf("%2d! = %22lld\n", i, factorial(i));
    }
}
```

```cpp
 1! =                      1
 2! =                      2
 3! =                      6
 4! =                     24
 5! =                    120
 6! =                    720
 7! =                   5040
 8! =                  40320
 9! =                 362880
10! =                3628800
11! =               39916800
12! =              479001600
13! =             6227020800
14! =            87178291200
15! =          1307674368000
16! =         20922789888000
17! =        355687428096000
18! =       6402373705728000
19! =     121645100408832000
20! =    2432902008176640000
```

Nasledujúci program vypíše zadaný dátum vo formáte typu 02.01.2019:

```cpp
#include <cstdio>
using namespace std;

void vypisDatum(int d, int m, int r) {
    printf("%02d.%02d.%04d\n", d, m, r);
}

int main() {
    vypisDatum(2, 1, 2019);
}
```

Celá špecifikácia konverzie pozostáva z nasledujúcich častí:

  - Z povinného úvodného znaku `%`.
  - Z nepovinných *príznakov*, napríklad `-`, ktorého použitie vyústi v
    zarovnanie vypisovaného textu vľavo (bez jeho použitia sa text
    zarovná vpravo). Ďalšími príznakmi sú napríklad `0` (dopĺňanie núl
    naľavo), `+` (vypíše znamienko *+* pri kladných číslach), atď.
  - Z nepovinného celého čísla udávajúceho minimálnu *šírku* výpisu
    (minimálny počet „políčok”, do ktorých sa text vypíše).
  - Z nepovinnej bodky nasledovanej celým číslom udávajúcim *presnosť*
    výpisu (pri reálnych číslach napríklad počet desatinných miest;
    presnosť má však svoju interpretáciu aj pri iných typoch dát).
  - Z nepovinného modifikátora `l`, `ll`, alebo `h` pre `long`, `long
    long`, resp. `short`.
  - Z povinného *symbolu konverzie* (napr. `d`, `f`, `s`, ...).

### Načítanie formátovaných dát z konzoly: `scanf`

Vstup z konzoly sa dá načítať funkciou
[`scanf`](http://www.cplusplus.com/reference/cstdio/scanf/) s typickým
volaním

```cpp
scanf(format, adresa1, adresa2, ...) 
```

  - Napríklad `scanf("%d", &x)` načíta celočíselnú hodnotu do premennej
    `x`.
  - Zatiaľ čo argumentmi `printf` sú priamo hodnoty, `scanf` potrebuje
    adresy premenných, pretože ich modifikuje.

Pomocou `scanf` možno načítať aj viacero premenných naraz:

```cpp
#include <cstdio>
using namespace std;

void vypisDatum(int d, int m, int r) {
    printf("%02d.%02d.%04d\n", d, m, r);
}

int main() {
    int d, m, r;
    printf("Zadaj den, mesiac a rok: ");  
    scanf("%d %d %d", &d, &m, &r);        
    vypisDatum(d, m, r);                    
}
```

Formátovací reťazec sa v `scanf` interpretuje nasledovne:

  - Špecifikácia typu načítavaných premenných je podobná ako pri funkcii
    `printf`.
      - `%d` načíta `int`
      - `%lf` načíta `double` (pozor, tu je rozdiel od `printf`, kde sa
        double vypisuje pomocou `%f`)
      - `%s` načíta reťazec, konkrétne jedno slovo, t.j. postupnosť
        nebielych znakov. Ako argument sa zadá hodnota typu `char*`,
        ktorá má ukazovať na dostatočne veľké pole.
      - `%100s` načíta slovo, ale najviac 100 znakov. Pole má mať
        veľkosť aspoň 101.
      - `%c` načíta jeden znak. Na rozdiel od všetkých predchádzajúcich
        typov, tu sa nepreskakujú biele znaky pred prvým nebielym.
  - Biele znaky (angl. *whitespace*, t.j. medzery, konce riadkov,
    tabulátory) vo formátovacom reťazci spôsobia, že funkcia `scanf`
    číta a ignoruje všetky biele znaky pred ďalším nebielym znakom.
    Jeden biely znak vo formátovacom reťazci tak umožní ľubovoľný počet
    bielych znakov na vstupe.
  - Ostatné znaky formátovacieho reťazca musia presne zodpovedať vstupu.

Nasledujúci príkaz tak napríklad načíta dátum vo formáte
`deň.mesiac.rok`:

```cpp
scanf("%d.%d.%d", &d, &m, &r);
```

### Kontrola správnosti vstupu

Funkcia `scanf` vracia počet úspešne načítaných hodnôt zo vstupu.

  - V prípade chyby hneď na začiatku vstupu tak napríklad vráti `0`.
  - Ak hneď na začiatku narazí na koniec vstupu, vráti hodnotu `EOF`
    (typicky -1).
  - Vstup z konzoly sa dá ukončiť pod Linuxom ako `Ctrl+D` resp. pod
    Windowsom ako `Ctrl+Z` a `Enter`

Príklad: zadávanie dátumu vo formáte `deň.mesiac.rok` s kontrolou
vstupu:

```cpp
#include <cstdio>
using namespace std;

void vypisDatum(int d, int m, int r) {
    printf("%02d.%02d.%04d\n", d, m, r);
}

int main() {
    int d, m, r;
    printf("Zadaj datum: ");
    int uspech = scanf("%d.%d.%d", &d, &m, &r);
    if (uspech == 3) {
        printf("Datum je ");
        vypisDatum(d, m, r);
    } else {
        printf("Nebol zadany korektny datum.\n");
        printf("Pocet uspesne nacitanych poloziek: %d.\n", uspech);
    }
}
```

Ďalší program počíta súčet postupne zadávaných čísel, až kým je zadané
nekorektné číslo alebo koniec súboru:

```cpp
#include <cstdio>
using namespace std;

int main() {
    double sum = 0;
    double x;
    while (scanf("%lf", &x) == 1) {
         sum += x;
    }
    printf("Sucet je %.2f\n", sum);
}
```

## Textové súbory

Na načítavanie a vypisovanie dát sme doposiaľ používali výhradne
konzolu. V praxi však často potrebujeme spracovávať dáta uložené v
súboroch.

  - Zameriame sa na súbory v textovom formáte, s ktorými sa pracuje
    podobne ako s konzolou.
  - V C++ existujú ekvivalenty `cin >>` a `cout <<` aj pre súbory,
    nájdete ich v knižnici
    [fstream](http://www.cplusplus.com/reference/fstream/fstream/).

### Základy: typ `FILE *` a funkcie `fopen`, `fclose`, `fprintf`, `fscanf`

So súbormi sa pri použití knižnice `cstdio` pracuje pomocou typu `FILE
*` (veľkými písmenami).

  - Je to smerník na štruktúru typu `FILE`, ktorá obsahuje informácie o
    súbore, s ktorým sa práve pracuje.
  - Premenné pre prácu so súbormi tak možno definovať napríklad takto:

<!-- end list -->

```cpp
FILE *fr, *fw;
```

**Otvorenie súboru pre čítanie**

  - `fr = fopen("vstup.txt", "r");`
  - Otvorí súbor s názvom `vstup.txt` (prípadne možno zadať kompletnú
    cestu k súboru).
  - Ak taký súbor neexistuje alebo sa nedá otvoriť, do `fr` priradí
    `NULL`.
  - Z otvoreného súboru môžeme čítať napríklad pomocou `fscanf`, ktorá
    je analógiou k `scanf`.
  - Napríklad `fscanf(fr, "%d", &x);`

**Otvorenie súboru pre zápis**

  - `fw = fopen("vystup.txt", "w");`
  - Vytvorí súbor s názvom `vystup.txt`. Ak už existoval, zmaže jeho
    obsah (keby sme vo volaní `fopen` namiesto `"w"` použili `"a"`,
    pridávalo by sa na koniec existujúceho súboru).
  - Ak sa nepodarí súbor otvoriť, do `fw` priradí `NULL`.
  - Do otvoreného súboru môžeme zapisovať napr. pomocou funkcie
    `fprintf`, ktorá je analógiou k `printf`.
  - Napr. `fprintf(fw, "%d", x);`

**Zatvorenie súboru**

  - Po ukončení práce so súborom je ho potrebné zavrieť pomocou
    `fclose(f);`
  - Počet súčasne otvorených súborov je obmedzený.

### Príklad

Nasledujúci program načíta číslo *n* a následne *n* celých čísel zo
súboru `vstup.txt`. Do súboru `vystup.txt` vypíše vstupné čísla v
opačnom poradí.

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

int main() {
    // otvorime vstupny subor a skontrolujeme, ze sa podarilo
    FILE *fr = fopen("vstup.txt", "r");   
    assert(fr != NULL);
    
    // nacitame pocet cisel
    int n, uspech;
    uspech = fscanf(fr, "%d", &n);
    assert(uspech == 1 && n >= 0);

    // alokujeme pole a nacitame cisla
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        uspech = fscanf(fr, "%d", &a[i]);
        assert(uspech == 1);
    }
    fclose(fr);

    // otvorime vystupny subor a skontrolujeme, ze sa podarilo
    FILE *fw = fopen("vystup.txt", "w");
    assert(fw != NULL);

    // vypiseme cisla odzadu
    for (int i = n-1; i >= 0; i--) {
        fprintf(fw, "%d ", a[i]);
    }
    fclose(fw);
    delete[] a;    
}
```

### Štandardný vstup a výstup ako súbor

So štandardným vstupom a výstupom sa pracuje rovnako ako so súborom. V
`cstdio` sú definované dva konštantné smerníky

```cpp
FILE *stdin, *stdout;
```

pre štandardný vstupný a výstupný prúd. Tie tak môžu byť použité v
ľubovoľnom kontexte, v ktorom sa očakáva súbor. Napríklad volanie
`fscanf(stdin, "%d", &x)` je ekvivalentné volaniu `scanf("%d", &x)`.

Ten istý kód sa tak dá použiť na prácu so súbormi aj so štandardným
vstupom resp. výstupom – stačí len podľa potreby nastaviť premennú typu
`FILE *`. Typické použitie je napríklad nasledovné:

```cpp
    // do retazca str nacitame z konzoly meno suboru alebo pomlcku
    char str[101];
    scanf("%100s", str);
    // do fw otvorime subor alebo pouzijeme konzolu
    FILE *fw;    
    if (strcmp(str, "-") == 0) {
        fw = stdout;
    } else {
        fw = fopen(str, "w");
    }
    // zapiseme nieco do fw
    fprintf(fw, "Hello world!\n");
    // ak treba, zatvorime subor
    if (strcmp(str, "-") != 0) {
        fclose(fw);
    }
```

### Testovanie konca súboru

Existujú dve možnosti testovania, či sme dosiahli koniec súboru:

  - V knižnici `cstdio` je definovaná symbolická konštanta `EOF`, ktorá
    má väčšinou hodnotu -1. Ak sa funkcii `fscanf` nepodarí načítať
    žiadnu hodnotu, pretože načítavanie dospelo ku koncu súboru, vráti
    konštantu `EOF` ako svoj výstup.
  - Funkcia `feof(subor)` vráti `true` práve vtedy, keď sa funkcia
    `fscanf` (alebo nejaká iná funkcia) už niekedy pokúšala čítať za
    koncom súboru `subor`.

## Spracovanie vstupu pozostávajúceho z postupnosti čísel

Často na vstupe očakávame postupnosť číselných hodnôt oddelených bielymi
znakmi. Pozrime sa na tri obvyklé možnosti, ako môže byť takýto vstup
zadaný a spracovaný pomocou funkcie `fscanf`.

*Formát 1*: `N` (počet čísel) a následne `N` ďalších čísel.

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

int main() {
    FILE *f;
    const int MAXN = 100;
    int a[MAXN], N, uspech;

    f = fopen("vstup.txt", "r");
    assert(f != NULL);

    uspech = fscanf(f, "%d ", &N);
    assert(uspech == 1 && N >= 0 && N <= MAXN);

    for (int i = 0; i < N; i++) {
        uspech = fscanf(f, "%d ", &a[i]);
        assert(uspech == 1);
    }
    fclose(f);

    // tu pride spracovanie dat v poli a
}
```

*Formát 2*: postupnosť čísel ukončená číslom -1 alebo inou špeciálnou
hodnotu.

```cpp
    // otvorime subor f ako vyssie
    N = 0;
    int x;
    uspech = fscanf(f, "%d ", &x);
    assert(uspech == 1);
    while (x != -1) {
        assert(N < MAXN);
        a[N] = x;
        N++;
        uspech = fscanf(f, "%d ", &x);
        assert(uspech == 1);
    }
    // zatvorime subor a spracujeme data
```

*Formát 3*: čísla, až kým neskončí súbor (najtypickejší prípad v praxi).

Priamočiary prístup **nefunguje vždy správne**:

```cpp
    // otvorime subor f ako vyssie
    N = 0;
    while (!feof(f)) {
        assert(N < MAXN);
        uspech = fscanf(f, "%d", &a[N]);
        assert(uspech == 1); // bude tu padat
        N++;
    }
    // zatvorime subor a spracujeme data
```

  - Tento program nefunguje, ak po poslednom čísle v súbore nasleduje
    ešte koniec riadku (čo je obvyklé).
  - Pri načítaní tohto čísla skončíme na symbole konca riadku, `fscanf`
    sa teda nepokúsi čítať za koncom súboru.
  - Spustí sa teda ďalšie opakovanie cyklu, v ktorom sa už ale nepodarí
    ďalšie číslo načítať a `assert` ukončí program s chybovou hláškou.
  - Aj bez príkazu `assert` by sme mali problém, že do poľa by sa
    uložila nezmyselná hodnota.

Tento nedostatok môžeme napraviť napríklad tak, že vo volaní funkcie
`fscanf` dáme vo formátovacom reťazci za `%d` medzeru. Tá sa bude
pokúšať preskočiť všetky biele znaky až po najbližší nebiely; pritom
natrafí na koniec súboru a `feof(f)` už bude vracať `true`.

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

int main() {
    FILE *f;
    const int MAXN = 100;
    int a[MAXN], N, uspech;

    f = fopen("vstup.txt", "r");
    assert(f != NULL);

    N = 0;
    while (!feof(f)) {
        assert(N < MAXN);
        uspech = fscanf(f, "%d ", &a[N]);
        assert(uspech == 1);
        N++;
    }
    fclose(f);

    // tu pride spracovanie dat v poli a
}
```

Cvičenie: upravte úryvky programu vyššie tak, aby pracoval s číslami
typu `double` alebo so slovami.

## Zhrnutie

  - Doteraz sme s konzolou pracovali pomocou `cin` a `cout` z knižnice
    `iostream`, ktorá patrí do C++.
  - V jazyku C sa na načítavanie čísel a slov používajú funkcie `scanf`
    a `printf` z knižnice `cstdio`.
      - Funkcia `scanf` umožňuje tiež testovať koniec vstupu a správnosť
        prečítaných hodnôt.
      - Funkcia `printf` umožňuje pohodlne vypísať viacero hodnôt aj s
        nastavením formátovania ako napr. počet desatinných miest alebo
        zarovnávanie.
  - Nekombinujte v jednom programe prácu s konzolou pomocou `iostream` a
    `cstdio`. Každá knižnica si časť vstupu alebo výstupu ukladá do
    svojich interných premenných a môže dôjsť k strate alebo
    preusporiadaniu dát.
  - Pri práci so súbormi súbor typu `FILE *` otvoríme funkciou `fopen`,
    zatvoríme `fclose`.
  - Namiesto `scanf`, `printf` pri súboroch použijeme `fprintf`,
    `fscanf`.

