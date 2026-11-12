---
title: Prednáška 17
---

* TOC
{:toc}

## Oznamy

  - Dnešná prednáška je špeciálna z dvoch dôvodov:
      - Hostia zo stredných škôl z programu Minierasmus
      - V stredu prednáška nebude - fakultná konferencia [Matfyz
        Connections](https://fmph.uniba.sk/microsites/connections-fmfi/connections/uvod/)
      - Ukážeme si teda hrozienka z dvoch prednášok, zvyšok si pozrite
        vo videu
  - Zajtra na cvičeniach rozcvička z minulej prednášky - čítanie súboru
    po riadkoch
      - V stredu cvičenia nebudú
      - Zverejníme aj jeden príklad z budúcich cvičení, môžete si
        spraviť v predstihu
  - Tretí miniprojekt do budúceho štvrtka 4.12.
  - Druhý semestrálny test streda 10.12. o 18:10, viac informácií o
    týždeň

### Linky na videá k častiam prednášky 17 a 18, ktoré sa tento rok neprednášali

  - Implementácia zásobníka a radu pomocou polí a spájaných zoznamov
      - [Video](https://liveuniba-my.sharepoint.com/:v:/g/personal/brejova2_uniba_sk/IQAshOlsq6vdQ5dtXhco_FDGAafjISRvWUNVtY9Y82kpNLw),
        [poznámky](./P17.md#implement%C3%A1cia-z%C3%A1sobn%C3%ADka-a-radu)
      - Obidve implementácie sú jednoduché a rýchle, každá operácia je
        len pomocou zopár jednoduchých operácií
      - Avšak obsahujú niektoré pekné triky, najmä implementácia radu
        pomocou poľa
  - Použitie zásobníka na kontrolu zátvoriek
      - [Video](https://liveuniba-my.sharepoint.com/:v:/g/personal/brejova2_uniba_sk/IQB8_AuNy7X7SZJj1bXOTy4GATn3dA-MS1QXvhRmAiu4uy8?e=MnSeTm&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D),
        [poznámky](./P17.md#príklad-kontrola-uzátvorkovania)
  - Použitie zásobníka alebo radu na nerekurzívny QuickSort
      - [Video](https://liveuniba-my.sharepoint.com/:v:/g/personal/brejova2_uniba_sk/IQAfDGLy3HJLSo0KXU1QMAv3AbqJ4G_VbFqfzAo8itvfrLU?e=dt4WM3&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D),
        [poznámky](./P18.md#použitie-zásobníka-a-radu-nerekurzívny-quick-sort)
  - Nerekurzívna verzia vyfarbovania s použitím zásobníka a radu
      - [Video](https://liveuniba-my.sharepoint.com/:v:/g/personal/brejova2_uniba_sk/IQA0M8Dg5paJQaPHP1XIK11vAfBpLLLl2c3LzNkdX2gE-nI?e=CZQ0e3&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D),
        [poznámky](./P18#nerekurzívne-vyfarbovanie)
  - Na pozeranie videí sa musíte prihlásiť do univerzitého systému

## Opakovanie: Abstraktný dátový typ

*Abstraktný dátový typ* (ADT) je abstrakcia dátovej štruktúry nezávislá
od samotnej implementácie.

  - Býva zadaný pomocou množiny operácií (hlavičiek funkcií), ktoré
    poskytuje
  - Jeden abstraktný dátový typ môže byť implementovaný pomocou
    viacerých dátových štruktúr.

Témou [prednášky 14](./P14.md) bol napríklad abstraktný
dátový typ *dynamická množina*, ktorý poskytuje tri základné operácie:

  - Zistenie či prvok patrí do množiny (`contains`).
  - Pridanie prvku do množiny (`add`).
  - Odobranie prvky z množiny (`remove`).

Videli sme implementácie pomocou neutriedeného poľa, utriedeného poľa,
spájaného zoznamu, priameho adresovania a hašovania (pre jednoduchosť
bez operácie `remove`).

Podobne za ADT môžeme považovať dynamické pole s operáciami `add`,
`length`, `get` a `set`.

Výhodou abstraktných dátových typov je oddelenie implementácie dátovej
štruktúry od programu, ktorý ju používa.

  - Napríklad program pracujúci s dynamickou množinou prostredníctvom
    funkcií `contains`, `add` a `remove` možno rovnako dobre použiť pri
    implementácii množiny pomocou neutriedených polí, ako pri jeho
    implementácii pomocou hašovania.

## Rad a zásobník

Dnes si ukážeme dva nové abstraktné dátové typy, zásobník a rad.

  - Rad aj zásobník udržiavajú postupnosť nejakých prvkov.
  - Typicky ide o úlohy alebo dáta čakajúce na spracovanie.
  - Obidva poskytujú funkciu, ktorá vkladá nový prvok.
  - Druhou základnou funkciou je výber jedného prvku, pričom rad sa od
    zásobníka líši tým, ktorý prvok sa vyberá.

Prvky radu a zásobníka môžu byť ľubovoľného typu. Namiesto konkrétneho
typu (ako napríklad `int` alebo `char`) dnes budeme pracovať so
všeobecným typom, ktorý nazveme `dataType`. Za ten možno dosadiť
ľubovoľný konkrétny typ. Napríklad `int` dosadíme za `dataType` takto:

```cpp
typedef int dataType;
```

  - Pri využití tohto prístupu tak napríklad bude možné získať z radu
    prvkov typu `int` rad prvkov typu `char` zmenou v jedinom riadku
    programu.
  - Taká istá úprava by sa dala spraviť aj pri ADT množina a dynamické
    pole.

### Rad (queue)

Niekedy sa nazýva aj front(a).

  - Z radu sa zakaždým vyberie ten jeho prvok, ktorý doň bol vložený ako
    prvý spomedzi jeho aktuálnych prvkov.
  - Možno ho tak pripodobniť k radu pri pokladni v obchode.
  - Takáto metóda manipulácie s dátami sa v angličtine označuje skratkou
    FIFO, podľa *first in, first out*.

Abstraktný dátový typ pre rad poskytuje tieto operácie (kde `queue` je
názov štruktúry reprezentujúcej rad):

```cpp
/* Inicializuje prázdny rad */
void init(queue &q);

/* Zistí, či je rad prázdny */
bool isEmpty(queue &q);

/* Pridá prvok item na koniec radu */
void enqueue(queue &q, dataType item);

/* Odoberie prvok zo začiatku radu a vráti jeho hodnotu */
dataType dequeue(queue &q);

/* Vráti prvok zo začiatku radu, ale nechá ho v rade */
dataType peek(queue &q);

/* Uvoľní pamäť */
void destroy(queue &q);
```

### Zásobník (stack)

  - Zo zásobníka sa naopak zakaždým vyberie ten prvok, ktorý doň bol
    vložený ako posledný.
  - Môžeme si ho predstaviť ako stĺpec tanierov, kde umyté taniere
    dávame na vrch stĺpca a tiež z vrchu aj berieme taniere na
    použitie.
  - Táto metóda manipulácie s dátami sa v angličtine označuje skratkou
    LIFO, podľa *last in, first out*.

Abstraktný dátový typ pre zásobník poskytuje tieto operácie (`stack` je
názov štruktúry reprezentujúcej zásobník):

```cpp
/* Inicializuje prázdny zásobník */
void init(stack &s);

/* Zistí, či je zásobník prázdny */
bool isEmpty(stack &s);

/* Pridá prvok item na vrch zásobníka */
void push(stack &s, dataType item);

/* Odoberie prvok z vrchu zásobníka a vráti jeho hodnotu */
dataType pop(stack &s);

/* Vráti prvok na vrchu zásobníka, ale nechá ho v zásobníku */
dataType peek(stack &s);

/* Uvoľní pamäť */
void destroy(stack &s);
```

### Programy využívajúce rad a zásobník

Bez ohľadu na samotnú implementáciu vyššie uvedených funkcií vieme písať
programy, ktoré ich využívajú. Napríklad nasledujúci program pracuje s
radom:

```cpp
#include <iostream>
using namespace std;

typedef int dataType;


/* Sem príde definícia štruktúry queue a potrebných funkcií. */


int main() {
    queue q;
    init(q);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    cout << dequeue(q) << endl;  // Vypíše 1
    cout << dequeue(q) << endl;  // Vypíše 2
    cout << dequeue(q) << endl;  // Vypíše 3
    destroy(q);
}
```

Podobne nasledujúci program pracuje so zásobníkom:

```cpp
#include <iostream>
using namespace std;

typedef int dataType;

/* Sem príde definícia štruktúry stack a potrebných funkcií. */

int main() {
    stack s;
    init(s);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    cout << pop(s) << endl;  // Vypíše 3
    cout << pop(s) << endl;  // Vypíše 2
    cout << pop(s) << endl;  // Vypíše 1
    destroy(s);
}
```

Poznámka:

  - V objektovo-orientovanom programovaní (budúci semester) sa namiesto
    napr. `push(s,10)` píše niečo ako `s.push(10)`

## Implementácia zásobníka a radu

### Zásobník pomocou poľa

  - Na úvod implementujeme zásobník pomocou poľa `items`, ktoré budeme
    alokovať na fixnú dĺžku `maxN` (ešte lepšie by bolo použiť dynamické
    pole).
  - Spodok zásobníka pritom bude v tomto poli uložený na pozícii `0` a
    jeho vrch na pozícii `top`.
  - Keď je zásobník prázdny, bude v premennej `top` hodnota `-1`.

<!-- end list -->

```cpp
#include <cassert>

typedef int dataType;
const int maxN = 1000;

struct stack {
    // Alokované pole prvkov zásobníka
    dataType *items; 
    // Index vrchu zasobníka v poli items, -1 ak prázdny
    int top;         
};

/* Inicializuje prázdny zásobník */
void init(stack &s) {
    s.items = new dataType[maxN];
    s.top = -1; 
}

/* Zistí, či je zásobník prázdny */
bool isEmpty(stack &s) {
    return s.top == -1;
}

/* Pridá prvok item na vrch zásobníka */
void push(stack &s, dataType item) {
    assert(s.top <= maxN - 2);
    s.top++;
    s.items[s.top] = item;
} 

/* Odoberie prvok z vrchu zasobníka a vráti jeho hodnotu */
dataType pop(stack &s) {
    assert(!isEmpty(s));
    s.top--;
    return s.items[s.top + 1];
}

/* Vráti prvok na vrchu zásobníka, ale nechá ho tam */          
dataType peek(stack &s) {
    assert(!isEmpty(s));
    return s.items[s.top];
}

/* Uvoľní pamäť */
void destroy(stack &s) {
    delete[] s.items;
}
```

### Rad pomocou poľa

  - Rad sa od zásobníka líši tým, že prvky sa z neho vyberajú z opačnej
    strany, než sa doň vkladajú.
  - Keby sa prvý prvok radu udržiaval na pozícii `0`, museli by sa po
    každom výbere prvku tie zvyšné posunúť o jednu pozíciu doľava, čo
    je časovo neefektívne.
  - Rad teda implementujeme tak, aby jeho začiatok mohol byť na
    ľubovoľnej pozícii `first` poľa `items`.
  - Pole `items` pritom budeme chápať ako cyklické. Prvky s indexom
    menším ako `first` budeme chápať ako nasledujúce za posledným
    prvkom poľa.

<!-- end list -->

```cpp
#include <cassert>

typedef int dataType;

const int maxN = 1000;

struct queue {
    dataType *items; // Alokované pole obsahujúce prvky radu
    int first;       // Index prvého prvku radu v poli items
    int count;       // Počet prvkov v rade
};

/* Inicializuje prázdny rad */
void init(queue &q) {
    q.items = new dataType[maxN];
    q.first = 0;
    q.count = 0;
}

/* Zistí, či je rad prázdny */
bool isEmpty(queue &q) {
    return q.count == 0;
}

/* Pridá prvok item na koniec radu */
void enqueue(queue &q, dataType item) {
    assert(q.count < maxN);
    int index = (q.first + q.count) % maxN;
    q.items[index] = item;
    q.count++;
} 

/* Odoberie prvok zo začiatku radu a vráti jeho hodnotu */
dataType dequeue(queue &q) {
    assert(!isEmpty(q));
    dataType result = q.items[q.first];
    q.first = (q.first + 1) % maxN;
    q.count--;
    return result;
}

/* Vráti prvok zo začiatku radu, ale nechá ho tam */
dataType peek(queue &q) {
    assert(!isEmpty(q));
    return q.items[q.first];
}         

/* Uvoľní pamäť */
void destroy(queue &q) {
    delete[] q.items;
}
```

### Zásobník pomocou spájaného zoznamu

  - Zásobník teraz implementujeme pomocou spájaného zoznamu.
  - Na rozdiel od implementácie pomocou poľa bude výhodnejšie uchovávať
    vrch zásobníka ako *prvý* prvok zoznamu.
  - Pri jednosmerne spájaných zoznamoch je totiž jednoduchšie vkladať a
    odoberať prvky na jeho začiatku.

<!-- end list -->

  - Výhoda tohto prístupu oproti implementácii pomocou poľa je v tom, že
    maximálny počet prvkov v zásobníku nebude obmedzený konštantou
    `maxN`. Podobný efekt je možné docieliť aj pomocou dynamického poľa,
    tam však dochádza k realokácii.

<!-- end list -->

```cpp
#include <cassert>

typedef int dataType;

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
bool isEmpty(stack &s) {
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
dataType peek(stack &s) {
    assert(!isEmpty(s));
    return s.top->data;
}

/* Uvoľní pamäť */
void destroy(stack &s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}
```

### Rad pomocou spájaného zoznamu

  - Pri implementácii radu pomocou spájaného zoznamu rozšírime spájané
    zoznamy zo [14.
    prednášky](./P14.md#spájané-zoznamy) o
    smerník `last` na posledný prvok zoznamu.
  - Bude tak možné efektívne vkladať prvky na koniec zoznamu, ako aj
    odoberať prvky zo začiatku zoznamu.
  - Výhodou oproti implementácii radu pomocou poľa je, podobne ako pri
    zásobníkoch, eliminácia obmedzenia na maximálny počet prvkov v
    rade.

```cpp
#include <cassert>

typedef int dataType;

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
bool isEmpty(queue &q) {
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
dataType peek(queue &q) {
    assert(!isEmpty(q));
    return q.first->data;
}         

/* Uvoľní pamäť */
void destroy(queue &q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}
```

## Použitie zásobníka a radu

Zásobník aj rad často uchovávajú dáta určené na spracovanie, zoznamy
úloh, atď. Rad sa zvyčajne používa v prípadoch, keď je žiadúce zachovať
ich poradie. Môže ísť o situácie, keď jeden proces generuje úlohy
spracúvané iným procesom, napríklad:

  - Textový procesor pripravuje strany na tlač a vkladá ich do radu, z
    ktorého ich tlačiareň (resp. jej ovládač) postupne vyberá.
  - Sekvenčne vykonávané výpočtové úlohy čakajú v rade na spustenie.
  - Zákazníci čakajú na zákazníckej linke na voľného operátora.
  - Pasažieri na standby čakajú na voľné miesto v lietadle.

Zásobník sa zvyčajne používa v situáciách, keď na poradí spracúvania
nezáleží, alebo keď je žiadúce vstupné poradie obrátiť. Najvýznamnejší
príklad situácie druhého typu je nasledujúci:

  - Operačný systém ukladá lokálne premenné volaných funkcií na tzv.
    *zásobníku volaní* (angl. *call stack*), čo umožňuje používanie
    rekurzie.
  - Rekurzívne programy sa dajú prepísať na nerekurzívne pomocou „ručne
    vytvoreného” zásobníka (neskôr si ukážeme nerekurzívnu verziu
    triedenia *Quick Sort*).

### Príklad: kontrola uzátvorkovania

Ako jednoduchý príklad na použitie zásobníka uvažujme nasledujúci
problém: na vstupe je daný reťazec pozostávajúci (okrem prípadných
ďalších znakov, ktoré budeme ignorovať) zo zátvoriek `(,),[,],{,}`.
Úlohou je zistiť, či je tento reťazec dobre uzátvorkovaný. To znamená,
že:

  - Pre každú uzatváraciu zátvorku musí byť posledná dosiaľ neuzavretá
    otváracia zátvorka rovnakého typu, pričom musí existovať aspoň jedna
    dosiaľ neuzavretá zátvorka.
  - Každá otváracia zátvorka musí byť niekedy neskôr uzavretá.

Príklady očakávaného vstupu a výstupu:

    ()
    Retazec je dobre uzatvorkovany
    
    nejaky text bez zatvoriek
    Retazec je dobre uzatvorkovany
    
    [((({}[])[]))]()
    Retazec je dobre uzatvorkovany
    
    [[#))
    Retazec nie je dobre uzatvorkovany
    
    ())(
    Retazec nie je dobre uzatvorkovany
    
    ((
    Retazec nie je dobre uzatvorkovany
    
    ((cokolvek
    Retazec nie je dobre uzatvorkovany

  - Nasledujúci program postupne prechádza cez vstupný reťazec, pričom
    pre každú otváraciu zátvorku si na zásobník pridá uzatváraciu
    zátvorku rovnakého typu.
  - Ak narazí na uzatváraciu zátvorku, výraz môže byť dobre
    uzátvorkovaný len v prípade, že je na zásobníku aspoň jedna
    zátvorka, pričom zátvorka na vrchu zásobníka sa zhoduje so
    zátvorkou na vstupe.
  - V prípade úspešného prechodu cez celý vstup je reťazec dobre
    uzátvorkovaný práve vtedy, keď na zásobníku nezostala žiadna
    zátvorka.

<!-- end list -->

```cpp
#include <iostream>
#include <cassert>
using namespace std;

typedef char dataType;

/* Sem pride definicia struktury stack a vsetkych potrebnych funkcii. */

int main() {
    char vyraz[100];
    cin.getline(vyraz, 100);
    
    stack s;
    init(s);
    
    bool dobre = true;
    
    for (int i = 0; vyraz[i] != 0; i++) {
        switch (vyraz[i]) {
            case '(':
                push(s, ')');
                break;
            case '[':
                push(s, ']');
                break;
            case '{':
                push(s, '}');
                break;
            case ')':
            case ']':
            case '}':
                if (isEmpty(s)) {
                    dobre = false;
                } else {
                    char c = pop(s);
                    if (c != vyraz[i]) {
                        dobre = false;
                    }
                }
                break;
        }
    }
    
    dobre = dobre && isEmpty(s);
        
    destroy(s);
    
    if (dobre) {
        cout << "Retazec je dobre uzatvorkovany." << endl;
    } else {
        cout << "Retazec nie je dobre uzatvorkovany." << endl;
    }

}
```

*Cvičenie:* Prepíšte program na kontrolu zátvoriek do rekurzívnej
podoby. Použite pritom iba premenné typu `char`; špeciálne nepoužívajte
žiadne polia. Reťazec načítavajte pomocou funkcií `getc` a `ungetc`.
Môžete predpokladať, že je ukončený koncom riadku.

## Zhrnutie

  - Videli sme abstraktné dátové štruktúry zásobník a rad, ktoré vedia
    uchovávať postupnosť prvkov a pridávať a uberať prvky podľa určitých
    pravidiel.
  - Implementovali sme ich pomocou polí aj spájaných zoznamov.
    Implementácie všetkých funkcií sú rýchle a jednoduché (okrem
    `destroy` pre neprázdnu štruktúru).
  - Implementácia radu pomocou poľa používa pekný trik s cyklickým
    poľom.
  - Na budúcej prednáške vďaka zásobníku a radu prerobíme niektoré
    rekurzívne programy na nerekurzívne.

Ak zostáva čas, ukážeme si ešte jeden [rekurzívny
program](./P18.md#vyfarbovanie-súvislých-oblastí),
viac na budúcej prednáške.

