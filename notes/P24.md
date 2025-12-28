---
title: Prednáška 24
---

* TOC
{:toc}

## Nepreberané črty jazykov C a C++

Dnešná prednáška bude venovaná (pomerne plytkému) prehľadu rôznych čŕt
jazykov C a C++, ktoré sa počas semestra nepreberali. Tento prehľad by
mal poslúžiť ako pomôcka pri štúdiu existujúcich programov, resp. ako
inšpirácia pre ďalšie samoštúdium.

Znalosť materiálu z tejto prednášky *nebude* vyžadovaná na skúške.
Rovnako *nie je* odporúčané na skúške tento materiál využívať bez
dôkladného samostatného oboznámenia sa s ním.

Táto prednáška nepokrýva objektovo-orientované programovanie v jazyku
C++. Objektovo-orientované programovanie (v jazyku Java) bude hlavnou
náplňou druhého semestra programovania.

## Rozdiely medzi jazykmi C a C++

Jazyk C vznikol okolo roku 1972 na podporu vývoja operačného systému
Unix; jazyk C++ okolo roku 1985. Programy v jazyku C sú väčšinou súčasne
aj korektnými programami v jazyku C++ (ide ale o isté zjednodušenie).
Obidva tieto jazyky existujú vo viacerých štandardoch, v ktorých sa
postupne pridávali nové črty.

V priebehu semestra sme programovali v jazyku C++. Veľká časť
konštrukcií, ktoré sme v programoch využívali, však pochádza už z
jazyka C. Výnimkami sú však napríklad nasledujúce črty jazyka C++, ktoré
v jazyku C nie sú k dispozícii:

  - V jazyku C nie je možné predávanie parametrov funkcií referenciou.
    Namiesto toho je potrebné používať smerníky.
  - V jazyku C nefungujú operátory `new` a `delete`. Namiesto nich treba
    použiť funkcie popísané nižšie.
  - Na používanie typu `bool` a konštánt `true` a `false` je potrebná
    knižnica `stdbool` (t. j. `#include <stdbool.h>`). Zabudovaný
    booleovský typ má názov `_Bool` a nadobúda hodnoty `0` a `1`.
  - Štandardnými knižnicami jazyka C sú spomedzi štandardných knižníc
    jazyka C++ v zásade tie začínajúce písmenom `c`, napríklad `cstdio`.
    Namiesto ` #include  `<cstdio> potom v C píšeme `#include
    <stdio.h>`.
      - V jazyku C špeciálne nie je možné používať knižnicu `iostream` a
        v nej definované štandardné vstupno-výstupné prúdy `cin` a
        `cout`.
  - V jazyku C je potrebné pri deklarácii premennej typu `struct
    struktura` písať aj kľúčové slovo `struct`.
  - V starších verziách jazyka C nefungujú mnohé konštrukcie jazyka C++,
    ktoré sme bežne používali – napríklad komentáre vo forme `//`,
    deklarácie premenných inde ako na začiatku funkcie, atď.

## Nepreberané črty jazyka C (použiteľné aj v C++)

### Enumerované typy

Enumerované typy pozostávajú z vymenovania niekoľkých hodnôt, ktoré sa
stanú celočíselnými konštantami. To je občas užitočné na sprehľadnenie
zdrojového kódu.

*Príklad*:

```cpp
#include <iostream>
using namespace std;

int main(void) {
    enum farba {biela, modra, cervena, zelena, cierna};  // definicia enumerovaneho typu farba
    farba f = biela;                                     // definicia premennej typu farba     
    f = zelena;                                          // priradenie do premennej typu farba  
    cout << f << endl;                                   // vypise 3
    return 0;
}
```

### Zložený typ (`union`)

Zložený typ umožňuje na jednom mieste pamäte uchovávať hodnotu, ktorá
môže byť viacerých dátových typov (narozdiel od štruktúr však vždy ide
o práve jednu hodnotu). Definuje sa podobne ako štruktúra, avšak s
použitím kľúčového slova `union` namiesto `struct`.

*Príklad*:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

union zlozenyTyp {
    int n;
    char s[100];
};

int main() {
    zlozenyTyp z;
    z.n = 10;
    cout << z.n << endl;  // vypise 10
    strcpy(z.s, "abcd");
    cout << z.s << endl;  // vypise abcd
    cout << z.n << endl;  // vypise nejaky nezmysel
}
```

Napríklad pri aritmetických stromoch by použitie zloženého typu umožnilo
ušetriť trochu pamäte tým, že by sme si v každom uzle pamätali *buď*
jeho hodnotu, *alebo* operátor, pričom typ uzla by sme rozlišovali podľa
toho, či sú smerníky na oboch synov rovné `NULL`.

### Operátory

Okrem operátorov, ktoré sme používali, existuje niekoľko ďalších, ako
napríklad nasledujúce:

  - *Bitové operátory* pracujú s celým číslom ako s poľom bitov
    (vhodnejšie sú `unsigned` typy):
      - `<<` a `>>` posúvajú bity doľava a doprava, zodpovedajú
        násobeniu a deleniu mocninami dvojky.
      - `&` (*and* po bitoch), | (*or* po bitoch), ^ (*xor* po bitoch),
        \~ (negácia po bitoch).
  - *Ternárny operátor* `?` s použitím `(podmienka)?(hodnota pre
    true):(hodnota pre false)`, napríklad `cout << x << " je " <<
    ((x%2==0) ? "parne" : "neparne") << endl;`

### Cyklus `do-while`

Cyklus `do-while` je obdobou cyklu `while` s vyhodnocovaním podmienky na
konci iterácie. Nasledujúce dva spôsoby písania cyklu sú viac-menej
ekvivalentné:

```cpp
do { 
    prikazy;
} while(podmienka);

while (true) {
    prikazy;
    if (!podmienka) break;
}
```

### Makrá a konštanty

Konštantu možno zadefinovať napríklad aj takto:

```cpp
#define MAXN 100
```

Narozdiel od konštanty s definíciou

```cpp
const int maxN = 100;
```

sa tu konštantná premenná `MAXN` reálne nevytvára (nevyhradzuje sa pre
ňu pamäťové miesto); všetky výskyty `MAXN` sú preprocesorom kompilátora
nahradené „ešte v zdrojovom kóde” konštantou `100`.

Okrem konštánt možno definovať aj zložitejšie makrá s parametrami:

```cpp
/* Definicia makra: */
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

/* Priklad pouzitia: */
cout << MIN(a*a, b+5);

/* Preprocesor vykona substituciu za MIN, ktorou dostane: */
cout << ((a*a) < (b+5) ? (a*a) : (b+5));
```

  - Bez dostatočného množstva zátvoriek by pri použití makra `MIN` mohlo
    dôjsť k „interakcii s okolím”.
  - Vo všeobecnosti je odporúčané vyvarovať sa použitia makier.

### Delenie programu na súbory

Väčšie programy je zvyčajne žiadúce rozdeliť na viacero zdrojových
súborov. Často sa tiež môže zísť vytvorenie vlastnej knižnice.

Kompilátory, ako napríklad `g++`, spravidla umožňujú skompilovať viacero
zdrojových súborov naraz. Pri volaní `g++` z príkazového riadku môžeme
písať napríklad

    g++ -o program subor1.cpp subor2.cpp subor3.cpp

Takéto volanie ale môže byť úspešné len za dvoch podmienok:

  - Funkciu `main` musí obsahovať *práve jeden* z kompilovaných
    zdrojových súborov.
  - Ak sa v niektorom súbore `suborA.cpp` využíva funkcia `f` z iného
    súboru `suborB.cpp`, musí byť funkcia `f` v súbore `suborA.cpp`
    *zadeklarovaná* (t. j. uvedie sa hlavička funkcie `f` nasledovaná
    bodkočiarkou, bez samotného tela – čiže definície – funkcie `f`).

V súbore `lib.cpp` môžeme mať napríklad definície dvoch funkcií `f` a
`g`:

```cpp
/* Subor lib.cpp */

int f(int n) {
    return n + 1;
}

int g(int n) {
    return n*2;
}
```

Môžeme teraz do súboru `prog.cpp` napísať program, ktorý tieto funkcie
deklaruje a následne využíva:

```cpp
/* Subor prog.cpp */

#include <iostream>
using namespace std;

int f(int n);
int g(int n);

int main(void) {
    int n;
    cin >> n;
    cout << f(n) << " " << g(n) << endl;
    return 0;
}
```

Program potom možno skompilovať volaním

    g++ -o prog prog.cpp lib.cpp

Manuálne deklarovanie všetkých funkcií môže byť obzvlášť pri veľkých
knižniciach a programoch pozostávajúcich z veľkého množstva súborov
ťažkopádne. Typickým riešením je preto presunutie všetkých deklarácií
do špeciálneho *hlavičkového súboru* (angl. *header file*), v našom
prípade napríklad `lib.h`. Direktíva `#include "lib.h"` potom
prekopíruje do súboru, ktorý ju obsahuje, kompletný obsah súboru
`lib.h`, čím sa vlastne deklarujú všetky funkcie z knižnice `lib.cpp`.

Pre náš príklad vyššie tak teraz máme 3 súbory. Súbor `lib.cpp` je
rovnaký ako vyššie, súbor `lib.h` obsahuje

```cpp
/* Subor lib.h */

int f(int n);
int g(int n);
```

a súbor `prog.cpp` obsahuje

```cpp
/* Subor prog.cpp */

#include "lib.h"
#include <iostream>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    cout << f(n) << " " << g(n) << endl;
    return 0;
}
```

Program skompilujeme rovnako ako vyššie:

    g++ -o prog prog.cpp lib.cpp

Rozdiel medzi direktívami `#include "lib.h"` a `#include <lib.h>`
spočíva v tom, že kým v prvom prípade sa hlavičkový súbor hľadá najprv
v aktuálnom adresári, v druhom prípade sa prehľadávajú iba adresáre,
ktoré sú na danom systéme predvolené (typicky ide o adresáre obsahujúce
hlavičky štandardných knižníc).

### Zopár užitočných funkcií

**Alokácia pamäte**

  - V jazyku C nie sú definované operátory `new` a `delete`, resp.
    `new[]` a `delete[]`.
  - Pamäť sa alokuje funkciou `malloc`, ktorá alokuje kus pamäte s daným
    počtom bajtov.
      - V prípade neúspechu vráti `NULL`.
      - V prípade úspechu vráti smerník na `void`, ktorý je následne
        nutné pretypovať.
  - Uvoľnenie pamäte realizuje funkcia `free`.
  - Pri výpočte veľkosti potrebnej pamäte sa zvyčajne používa operátor
    `sizeof`.

<!-- end list -->

```cpp
#include <cstdlib>   // resp. #include <stdlib.h> v C

/* vytvorime pole 100 int-ov */
int *a = (int *)malloc(sizeof(int) * 100);
/* odalokujeme pole a */
free(a);
```

**Triedenie**

  - Funkcia `qsort` z knižnice `stdlib.h`.
  - Dostane pole, počet jeho prvkov, veľkosť každého prvku a funkciu,
    ktorá porovná dva prvky.
      - Funkciu teda posielame ako parameter.
      - Táto porovnávacia funkcia dostane dva smerníky typu `void *` (na
        dva prvky poľa).
      - Vráti záporné číslo, ak prvý prvok je menší, nulu, ak sú rovnaké
        a kladné číslo, ak je prvý väčší.
  - Ak si napíšeme porovnávaciu funkciu, môžeme triediť prvky hocijakého
    typu.

<!-- end list -->

```cpp
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int a[] = {5, 3, 2, 4, 1};
qsort(a, 5, sizeof(int), compare);
```

  - Existuje napríklad aj funkcia `bsearch` na binárne vyhľadávanie v
    utriedenom poli.

## Nepreberané črty jazyka C++

### Generické funkcie

Občas sa zíde napísať algoritmus, ktorý by mohol pracovať na dátach
rôznych typov. Napríklad triediť môžeme celé alebo desatinné čísla,
reťazce, zložitejšie štruktúry s určitým kľúčom a pod.

V C++ sa dajú písať takzvané *generické funkcie*, ktoré možno
„parametrizovať” podľa typu:

```cpp
#include <iostream>
using namespace std;

template <typename T> 
T vratPrvok(T *a, int k) {
    T result = a[k];
    return result;
} 

int main() {
    int a[5] = {1,2,3,4,5};
    cout << vratPrvok(a, 1) << endl;  // vypise 2
}
```

  - Viac v letnom semestri.

### Preťaženie operátorov

Pre novovytvorené typy je možné štadardným operátorom jazyka C++
priradiť novú sémantiku pomocou tzv. *preťaženia*. Napríklad v
nasledujúcom príklade definujeme operátor `<` na menách, ktorý najprv
porovnáva podľa priezviska a následne podľa krstného mena.

```cpp
struct meno {
    char *krstne, *priezvisko;
};

bool operator < (const meno &x, const meno &y) {
    return strcmp(x.priezvisko, y.priezvisko) < 0
            || strcmp(x.priezvisko, y.priezvisko) == 0
            && strcmp(x.krstne, y.krstne) < 0;
}
```

  - Podobne môžeme zadefinovať napríklad operátory `+` a `*` pre
    štruktúry reprezentujúce polynómy alebo komplexné čísla...
  - `cout << "Hello"` používa preťažený operátor `<<` pre výstupný prúd
    na ľavej strane a reťazec na pravej strane.

### Reťazce typu `string`

  - V C++ je možné okrem klasických C-čkových reťazcov použiť aj typ
    `string` z C++.
  - Jeho použitie je elegantnejšie, sám si určuje potrebnú veľkosť
    pamäte.
  - Reťazce tohto typu sú objekty, do funkcií ich odovzdávame väčšinou
    referenciou.
  - K jednotlivým znakom pristupujeme pomocou `[]` (ako u polí) alebo
    pomocou metódy `at`.

<!-- end list -->

```cpp
#include <string>
#include <iostream>
using namespace std;

int main() {
    char cstr[100] = "Ahoj\n";
    string str = "Ako sa mas?\n";
    string str2;

    /* Do str mozno pomocou operatora = korektne priradit konstantne retazce,
       C-ckove retazce (polia znakov), aj ine premenne typu string. */
    str2 = "Ahoj\n";
    str2 = cstr;
    str2 = str;

    /* Meranie dlzky retazca: */
    cout << "Dlzka je: " << str.length() << endl;

    /* Funguje porovnanie pomocou ==, !=, <, ...
     * (bud dvoch C++ stringov, alebo C++ stringu a C stringu)
     * Pomocou operatora + mozno realizovat zretazenie. */
    str2 = cstr + str;
    str2.push_back('X');   // prida jeden symbol na koniec retazca
    str2.push_back('\n');
    cout << str2 << endl;

    if (str < str2) {
        cout << "Prvy je mensi" << endl;
    } else if (str == str2) {
        cout << "Rovnaju sa" << endl;
    } else {
        cout << "Druhy je mensi" << endl;
    }
}
```

  - Pomocou metódy `c_str()` možno získať z reťazca typu `string`
    premennú typu `const char*`.

### Dátová štruktúra `vector`

Súčasťou štandardnej knižnice jazyka C++ je viacero rôznych [dátových
štruktúr](http://www.cplusplus.com/reference/stl/). Ide pritom o
generické štruktúry, ktoré môžu uchovávať dáta rôznych typov (čo je o
poznanie elegantnejšie riešenie, ako to naše s `dataType`; v jednom
programe napríklad môžeme mať štruktúry uchovávajúce rôzne typy).

Na tomto mieste spomeňme dátovú štruktúru `vector`
[1](http://www.cplusplus.com/reference/vector/vector/):

  - O niečo podarenejšia verzia dynamických polí z prednášky.
  - Deklarovať ho možno jedným z nasledujúcich spôsobov:

<!-- end list -->

```cpp
vector<int> a;       // vytvori pole celych cisel
vector<int> a(10);   // vytvori pole 10 celych cisel, ktore vsetky nastavi na vychodziu hodnotu
vector<int> a(5,1);  // vytvori pole 5 celych cisel, ktore nastavi na 1
```

  - Prístup k prvkom `vector`-u je možný dvoma spôsobmi:
      - Klasicky pomocou `a[index]` – podobne ako pri poliach sa ale v
        takom prípade nekontroluje rozsah.
      - Alternatívne možno použiť `a.at(index)` – v prípade indexu mimo
        rozsahu program hneď spadne (presnejšie vyhodí výnimku) a
        nenarobí chaos v pamäti.
  - V obidvoch prípadoch môžeme aj priraďovať: `a[index] = value;
    a.at(index) = value;`

<!-- end list -->

  - Ďalšie metódy na prácu s `vector`-mi:
      - `a.push_back(x)` vloží hodnotu `x` ako nový prvok na koniec
        poľa, podľa potreby pritom pole realokuje a pod.
      - `a.size()` vráti počet prvkov v poli.
      - `a.resize(n)` alebo `a.resize(n, value)` zmení počet prvkov v
        poli na `n`, pričom buď zahodí nadbytočné prvky alebo pridá nové
        – tie budú mať hodnotu `value` alebo východziu hodnotu.

<!-- end list -->

```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> a;
    for (int i = 0; i <= 10; i++) {
        a.push_back(i);
    }
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << endl;  // alebo a.at(i)
    }
}
```

Algoritmus na **triedenie**:

  - V knižnici <algorithm>

<!-- end list -->

```cpp
//triedime normalne pole
int A[6] = {1, 4, 2, 8, 5, 7};
sort(A, A + 6);

//triedime vektor
vector <int> A;
sort(A.begin(), A.end());

//triedime podla nasej porovnavacej funkcie, napr. podla absolutnej hodnoty
struct cmp {
    bool operator()(int x, int y) { return abs(x) < abs(y); }
};
cmp c;
sort(A.begin(), A.end(), c);
```

### Range-based for loop

  - Špeciálny cyklus cez prvky vektora a pod.
      - nepotrebujeme zavádzať premennú pre index
      - podobný for cyklus uvidíte podrobnejšie v Jave

<!-- end list -->

```cpp
#include <iostream>
#include <vector>
using namespace std; 

void vypis(const vector<int> &a) {
  // vypise vsetky prvky vektora a
  for (const int &value : a) { 
    cout << value << ' ';
  }
  cout << '\n';  
}

int main() {
  vector<int> a;

  // do vektora a vlozi prvky 0,..,5
  for(int value : {0,1,2,3,4,5}) {
    a.push_back(value);
  }

  vypis(a);  // vypise 0 1 2 3 4 5
 
  // zvysi kazdy prvok vektora o 1
  for (int &value : a) { 
    value++;
  }

  vypis(a); // vypise 1 2 3 4 5 6
}
```

