---
title: Prednáška 16
---

* TOC
{:toc}

## Oznamy

  - Druhý miniprojekt odovzdávajte do zajtra 22:00, posledný miniprojekt
    bude zverejnený po dnešnej prednáške.
  - Na dnešných cvičeniach bude bonusová rozcvička za jeden bonusový
    bod.
  - Budúcu stredu bude rektorské voľno kvôli konferencii [Matfyz
    Connections](https://fmph.uniba.sk/microsites/connections-fmfi/connections/uvod/).

## Príklad na prácu s textovými súbormi

  - Prácu s textovými súbormi si zopakujeme na nasledujúcom príklade.
  - Hlavný vstupný súbor `vstup.txt` má na prvom riadku názov výstupného
    súboru.
  - Každý z niekoľkých ďalších riadkov obsahuje názov jedného vstupného
    súboru nasledovaný počtom čísel, ktoré z neho chceme načítať.
  - Úlohou je prekopírovať z každého súboru zadaný počet čísel.

Napríklad `vstup.txt`

    vystup.txt
    a.txt 2
    b.txt 1
    a.txt 3

Súbor `a.txt`

    1 2 3 4 5 6 7 8 9

Súbor `b.txt`

    10 20 30 40 50 60 70 80 90

Výsledný súboru `vystup.txt`

    1 2 10 1 2 3

Program uvedený nižšie pracuje v nasledujúcich krokoch:

  - Otvorí hlavný vstupný súbor `vstup.txt` a prečíta z neho názov
    výstupného súboru.
  - Otvorí výstupný súbor.
  - Následne opakovane prečíta názov súboru a počet čísel *N*.
  - Otvorí súbor s práve načítaným názvom, prekopíruje z neho *N* čísel
    do výstupného súboru a následne tento súbor zatvorí.
  - Zatvorí hlavný vstupný súbor aj výstupný súbor.

Dĺžka načítavaných reťazcov bude vo volaniach funkcie `fscanf` obmedzená
na 19 znakov

  - to teda je maximálna dĺžka názvu súboru, s ktorou bude program
    vedieť pracovať

<!-- end list -->

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

int main() {
    FILE *fr_main, *fr_part, *fw;
    int N, success, num;
    fr_main = fopen("vstup.txt", "r");
    assert(fr_main != NULL);
    
    char filename[20];
    success = fscanf(fr_main, "%19s", filename);
    assert(success == 1); 
    
    fw = fopen(filename, "w");
    assert(fw != NULL);
    while (!feof(fr_main)) {
        success = fscanf(fr_main, "%19s %d ", filename, &N);
        assert(success == 2);
        fr_part = fopen(filename, "r");
        assert(fr_part != NULL);
        for (int i = 0; i < N; i++) {
            success = fscanf(fr_part, "%d ", &num);
            assert(success == 1);
            fprintf(fw, "%d ", num);
        }
        fclose(fr_part);
    }
    fclose(fw);
    fclose(fr_main); 
}
```

## Čítanie a zapisovanie po znakoch

Knižnica `cstdio` obsahuje aj funkcie na čítanie a zapisovanie súboru po
znakoch.

  - Funkcia `int getc(FILE *f)` načíta a vráti jeden znak zo súboru
      - Ak načítanie neprebehne úspešne, výsledkom je špeciálna
        konštanta `EOF`, ktorá je vždy rôzna od ľubovoľnej hodnoty typu
        `char`
      - Neukladajte výstupnú hodnotu funkcie `getc` do premennej typu
        `char`, lebo nebudete vedieť rozoznať koniec súboru.
  - Funkcia `int getchar()` je skratka pre `getc(stdin)`, načíta teda
    jeden znak z konzoly
      - Avšak rovnako ako pri `scanf` sa vstup začne spracovávať až
        potom, ako používateľ stlačí `Enter`, nie je takto možné
        reagovať priamo na stlačenie nejakej klávesy.

<!-- end list -->

  - Funkcia `int putc(int c, FILE *f)` zapíše znak `c` do súboru.
  - Funkcia `int putchar(int c)` je skratkou pre `putc(c, stdout)`,
    vypíše teda daný znak na konzolu.

### Príklad: kopírovanie súboru

Nasledujúci program skopíruje obsah súboru `original.txt` do súboru
`kopia.txt`.

```cpp
#include <cstdio>
using namespace std;

int main() {
    FILE *fr = fopen("original.txt", "r");
    FILE *fw = fopen("kopia.txt", "w");

    int c = getc(fr);
    while (c != EOF) {
        putc(c, fw);
        c = getc(fr);
    }

    fclose(fr);
    fclose(fw);
}
```

*Cvičenie:* čo robí nasledujúci program?

  - výsledkom priradenia `c = getc(fr)` je hodnota priradená do
    premennej `c`

<!-- end list -->

```cpp
#include <cstdio>
using namespace std;

int main() {
    FILE *fr;
    int c;

    fr = fopen("vstup.txt", "r");
    while ((c = getc(fr)) != '\n') {
        putchar(c);
    }
    putchar(c);         
    fclose(fr);
}
```

### Funkcia `ungetc`

  - Často sa stáva, že pri načítavaní znakov nájdeme koniec práve
    načítavaného úseku až po načítaní znaku, ktorý už nie je žiadúce
    prečítať.
  - Vtedy je užitočné posunúť sa v načítavaní o jeden krok nazad.
  - Túto úlohu realizuje funkcia `int ungetc(int c, FILE * f)`.
  - Väčšinou ako `c` použijeme posledne načítaný znak zo súboru `f`.
  - Môžeme však použiť aj iný znak, ktorý bude virtuálne pridaný na
    začiatok neprečítanej časti súboru. Súbor sa reálne nemení, ale pri
    nasledujúcom čítaní z neho sa ako prvý prečíta znak `c`.
  - V prípade úspechu `ungetc(c,f)` vráti hodnotu `c`; v prípade
    neúspechu je výstupom `EOF`.
  - Takéto správanie funkcie `ungetc` je však garantované len ak sa táto
    funkcia nevolá viackrát za sebou.

**Príklad č. 1:** Nasledujúci kus programu skonvertuje reťazec
pozostávajúci zo znakov `'0'` až `'9'` na zodpovedajúcu číselnú
hodnotu. Keď narazí na prvý znak, ktorý nie je cifra, vráti ho, aby sa
dal použiť pri ďalšom spracovávaní.

```cpp
    int hodnota = 0;
    int c = getchar();
    while (c >= '0' && c <= '9') {
        hodnota = hodnota * 10 + (c - '0');
        c = getchar();
    }
    ungetc(c, stdin);
```

**Príklad č. 2:** Nasledujúci program prečíta číslo pomocou funkcie
`fscanf`, predtým však musí prečítať neznámy počet znakov `'$'`.

```cpp
#include <cstdio>
using namespace std;

int main() {
    FILE *fr = fopen("vstup.txt", "r");
    int c = getc(fr);
    while (c == '$') {
        c = getc(fr);
    }
    ungetc(c, fr);

    int hodnota;
    fscanf(fr, "%d", &hodnota);
    printf("%d\n", hodnota);
   
    fclose(fr);
}
```

## Čítanie a zapisovanie po riadkoch

Riadok vieme načítať zo súboru nasledujúcou funkciou

```cpp
char *fgets(char *str, int n, FILE * f);
```

Jej argumenty sú

  - Pole znakov `str`, do ktorého sa v prípade úspechu riadok načíta.
  - Číslo `n` je typicky dĺžka poľa `str`
      - Funkcia do poľa `str` z daného riadku súboru načíta a uloží
        najviac `n-1` znakov a reťazec `str` následne ukončí znakom `0`.
  - Smerník `f` na súbor, z ktorého sa má riadok prečítať.

<!-- end list -->

  - Funkcia `fgets` teda načítava znaky dovtedy, kým narazí na koniec
    riadku (`\n`) alebo koniec súboru alebo kým zo súboru neprečíta
    `n-1` znakov.
  - Prípadný znak `\n` na konci riadku sa nezahodí, ale pridá sa na
    koniec reťazca `str` (pokiaľ nebolo načítaných príliš veľa znakov).
  - Výstupom funkcie je v prípade načítania aspoň jedného znaku načítaný
    reťazec `str`; inak je výstupom `NULL` a reťazec `str` ostáva
    nezmenený.

Funkcia `int fputs(const char *str, FILE *f)` vypíše reťazec `str` do
súboru

  - `str` môže obsahovať hocikoľko koncov riadkov (aj nula)
  - pri chybe vráti `EOF`, inak vráti nezáporné celé číslo

**Príklad:** nasledujúci program načítava riadky v súbore `vstup.txt` a
vypíše ich na konzolu, pričom na začiatok každého riadku pridá jeho
poradové číslo. Funguje správne za predpokladu, že žiaden z riadkov nie
je dlhší ako 100 znakov vrátane znaku `'\n'` na konci riadku.

```cpp
#include <cstdio>
using namespace std;

const int maxN = 101;

int main() {
    char str[maxN];
    int num = 0;
    
    FILE *fr = fopen("vstup.txt", "r");
    while (fgets(str, maxN, fr) != NULL) {
        printf("%d: ", num);  // výpis čísla riadku
        fputs(str, stdout);   // výpis samotného riadku
        num++;
    }
    fclose(fr);
}
```

**Cvičenie:**

  - Zistite, ako sa správa uvedený program, keď posledným znakom v
    súbore je resp. nie je znak `'\n'`.
  - Zistite, čo program vypíše na výstup pre súbor, ktorý obsahuje
    jediný riadok o 200 znakoch.

## Prístupy k spracovaniu textového vstupu

Časté schémy spracovania textového súboru:

  - Pomocou `fscanf` načítavame jednotlivé čísla, slová a pod. (vhodné,
    keď všetky biele znaky považujeme za ekvivalentné oddeľovače)
  - Čítame po znakoch pomocou `getc` (pomerne univerzálne, ale niekedy
    prácne)
  - Čítame po riadkoch pomocou `fgets` do reťazca, potom reťazec
    spracovávame (vhodné, keď riadok je ucelená časť súboru, ktorá nás
    zaujíma)

Niekedy je užitočné tieto prístupy aj kombinovať.

**Príklad:** chceme nájsť dĺžku najdlhšieho riadku v súbore

  - Prvá možnosť je čítanie riadkov do reťazca a ich spracovanie
    (problém, ak je riadok príliš dlhý)
  - Druhá možnosť je čítať súbor po znakoch, pričom si potrebujeme
    udržiavať "stav": koľko písmen sme už videli v aktuálnom riadku

<!-- end list -->

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

const int maxN = 100;

int main() {
    FILE *fr = fopen("vstup.txt", "r");
    int maxDlzka = 0;
    char str[maxN];
    while (fgets(str, maxN, fr) != NULL) {
        int dlzka = strlen(str);
        if (dlzka > maxDlzka) {
            maxDlzka = dlzka;
        }
    }
    fclose(fr);
    printf("Najdlhsi riadok ma dlzku %d\n", maxDlzka);
}
```

```cpp
#include <cstdio>
using namespace std;

int main() {
    FILE *fr = fopen("vstup.txt", "r");
    int maxDlzka = 0;
    int dlzka = 0;
    int c = getc(fr);
    while (c != EOF) {
        dlzka++;
        if (c == '\n') {
            if (dlzka > maxDlzka) {
                maxDlzka = dlzka;
            }
            dlzka = 0;
        }
        c = getc(fr);
    }
    if (dlzka > maxDlzka) { // Posledny riadok nemusi koncit symbolom \n.
        maxDlzka = dlzka;
    }
    fclose(fr);
    printf("Najdlhsi riadok ma dlzku %d\n", maxDlzka);
}
```

Cvičenie: čo ak chceme zistiť, koľký riadok v súbore bol ten najdlhší?

**Príklad 2:** máme súbor s číslami oddelenými bielymi znakmi (medzery,
tabulátory, konce riadkov,...), pričom medzi dvoma číslami môže byť aj
viac ako jeden oddeľovač. Chceme spočítať súčet čísel na každom riadku.

  - Nepríjemná kombinácia rozlišovania koncov riadku od iných bielych
    znakov a čítania formátovaných hodnôt (čísel)
  - Môžeme prečítať riadok do reťazca a rozložiť na čísla (napr.
    funkciou [`sscanf`](https://en.cppreference.com/w/c/io/fscanf) a so
    špecifikáciou konverzie `%n`, ktorá uloží počet načítaných znakov).
  - Program nižšie však používa kombináciu `getc`, `ungetc` a `fscanf`
      - Biele znaky spracúva pomocou funkcie `getc`. Ak je niektorý z
        týchto znakov koncom riadku, vypíše zistený súčet čísel.
      - Po nájdení nebieleho znaku ho vráti do vstupného prúdu funkciou
        `ungetc`, prečíta číslo pomocou funkcie `fscanf` a aktualizuje
        súčet.
      - Na zistenie, či je prečítaný znak biely, využíva program funkciu
        `isspace` z knižnice `cctype`.
      - Program predpokladá, že aj posledný riadok vstupného súboru je
        ukončený symbolom `\n`.

<!-- end list -->

```cpp
#include <cstdio>
#include <cctype>
using namespace std;

int main(void) {
    FILE *fr = fopen("vstup.txt", "r");
    int sucet = 0;
    int hodnota;
    while (!feof(fr)) {
        int c = getc(fr);
        // Precitaj biele znaky po najblizsi nebiely.
        while (c != EOF && isspace(c)) { 
            if (c == '\n') {   // Na konci riadku vypis sucet.
                printf("Sucet %d\n", sucet);
                sucet = 0;
            }
            c = getc(fr);
        }
        if (c == EOF) { // Koniec suboru
            break;
        }                
        ungetc(c, fr);    
        fscanf(fr, "%d", &hodnota);
        sucet += hodnota;
    }
    fclose(fr);
}
```

**Cvičenia:**

  - Čo program spraví, ak vstup obsahuje aj prázdne riadky?
  - Upravte program, aby pracoval správne aj v prípade, že posledný
    riadok nie je ukončený symbolom `\n`.
      - Čo vlastne chceme považovať za posledný riadok?
  - Upravte program, aby na výstupe vypisoval aj čísla na riadkoch
    oddelené medzerami.

## Jednoduché šifrovanie

Prácu so súbormi si teraz precvičíme na dvoch jednoduchých šifrách.

### Caesarova šifra

[Caesarova šifra](https://en.wikipedia.org/wiki/Caesar_cipher) je šifra,
pri ktorej sa každé písmeno vstupného reťazca posunie cyklicky o *K*
miest v abecednom poradí, kde *K* je zadaný parameter šifry.

  - Napríklad pre *K=2* sa písmeno `A` zmení na `C`, písmeno `b` sa
    zmení na `d` a písmeno `Z` sa zmení na `B`.
  - Ukážeme si jej použitie pre anglickú abecedu (t. j. znaky `'a'` až
    `'z'` a `'A'` až `'Z'` bez diakritiky); je ju ale možné upraviť
    napríklad aj tak, aby pracovala s ASCII kódmi.

Napríklad pre *K=3*:

    Pôvodný text:   HelloWorld
    Šifrovaný text: KhoorZruog

Nasledujúci program zašifruje súbor.

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

void encryptCaesar(FILE *fr, FILE *fw, int shift) {
    assert(shift >= 0 && shift <= 25);
    int c;
    while ((c = getc(fr)) != EOF) {
        if ((c >= 'A') && (c <= 'Z')) {
            c = c + shift;
            if (c > 'Z') {
                c -= 26;
            }
        } else if ((c >= 'a') && (c <= 'z')) {
            c = c + shift;
            if (c > 'z') {
                c -= 26;
            }
        }
        putc(c, fw);
    }
}

int main() {
    int shift;
    scanf("%d", &shift);  // nacitame parameter o kolko posuvat pismena
    
    FILE *fr = fopen("plaintext.txt", "r");
    FILE *fw = fopen("ciphertext.txt", "w");
    
    encryptCaesar(fr, fw, shift);
    
    fclose(fr);
    fclose(fw);
}
```

  - Čo program spraví so znakmi, ktoré nie sú písmená?
  - Dešifrovanie by fungovalo podobne, akurát by sa posun odpočítaval a
    ako špeciálny prípad by sa riešilo, keď nový znak má kód menší ako
    'a'. Môžeme ale tiež použiť program na šifrovanie a posun 26-K, kde
    K je posun použitý na šifrovanie.

### Vigenèrova šifra

[Vigenèrova šifra](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)
je veľmi podobná Caesarovej; posun však nie je konštantný, ale podľa
kľúča.

  - Kľúč je reťazec zložený z písmen `A` až `Z`, pričom tieto
    predstavujú posuny o `0` až `25` pozícií v abecede.
  - Prvý symbol otvoreného textu je zašifrovaný podľa prvého symbolu
    kľúča, druhý symbol podľa druhého symbolu kľúča, atď. Po
    vyčerpaní celého kľúča sa pokračuje cyklicky, opäť od jeho
    začiatku.

Napríklad pre heslo AHOJ:

    Pôvodný text:   HelloWorld
    Heslo:          AHOJAHOJAH
    Šifrovaný text: HlzuoDcalk

Očíslované písmená abecedy:

``` 
 0:A,  1:B,  2:C,  3:D,  4:E,  5:F,  6:G
 7:H,  8:I,  9:J, 10:K, 11:L, 12:M, 13:N
14:O, 15:P, 16:Q, 17:R, 18:S, 19:T, 20:U
21:V, 22:W, 23:X, 24:Y, 25:Z
```

Nasledujúci program zašifruje súbor.

```cpp
#include <cstdio>
using namespace std;

const int maxKeyLength = 100;

void encryptVigenere(FILE *fr, FILE *fw, char *key) {
    int c;
    int i = 0;
    while ((c = getc(fr)) != EOF) {
        if ((c >= 'A') && (c <= 'Z')) {
            c = c + (key[i] - 'A');
            if (c > 'Z') {
                c -= 26;
            }
            i++;
        } else if ((c >= 'a') && (c <= 'z')) {
            c = c + (key[i] - 'A');
            if (c > 'z') {
                c -= 26;
            }
            i++;
        }
        if (key[i] == 0) {
            i = 0;
        }
        putc(c, fw);
    }
}

int main() {
    // nacitame kluc z konzoly
    char key[maxKeyLength];
    scanf("%s", key);
    
    // otvorime subory
    FILE *fr = fopen("plaintext.txt", "r");
    FILE *fw = fopen("ciphertext.txt", "w");
    
    // sifrujeme 
    encryptVigenere(fr, fw, key);
    
    // zatvorime subory
    fclose(fr);
    fclose(fw);
}
```

Nasledujúci program potom dešifruje súbor.

```cpp
#include <cstdio>
#include <cassert>
using namespace std;

const int maxKeyLength = 100;

void decryptVigenere(FILE *fr, FILE *fw, char *key) {
    int c;
    int i = 0;
    while ((c = getc(fr)) != EOF) {
        if ((c >= 'A') && (c <= 'Z')) {
            c = c - (key[i] - 'A');
            if (c < 'A') {
                c += 26;
            }
            i++;
        } else if ((c >= 'a') && (c <= 'z')) {
            c = c - (key[i] - 'A');
            if (c < 'a') {
                c += 26;
            }
            i++;
        }
        if (key[i] == 0) {
            i = 0;
        }
        putc(c, fw);
    }
}

int main() {
    char key[maxKeyLength];
    scanf("%s", key);
    
    FILE *fr = fopen("ciphertext.txt", "r");
    FILE *fw = fopen("plaintext2.txt", "w");
    
    decryptVigenere(fr, fw, key);
    
    fclose(fr);
    fclose(fw);
}
```

  - Caesarova aj Vigenèrova šifra s krátkym kľúčom sa dajú ľahko
    prelomiť.
  - O šifrách, ktoré sa v súčasnosti používajú, sa môžete dozvedieť vo
    vyšších ročníkoch na predmete Kryptológia.

## Zhrnutie práce so súbormi

  - Ukázali sme si prácu so súbormi pomocou knižnice `cstdio` z jazyka
    C.
  - Súbor je reprezentovaný smerníkom typu `FILE *`.
  - Na otváranie a zatváranie súborov slúžia funkcie `fopen`, `fclose`.
  - Na vypísanie kombinácie čísel a textov slúži funkcia `fprintf`,
    čísla a slová načítavame pomocou `fscanf`.
  - Po znakoch pracujeme funkciami `putc` a `getc`, niekedy sa zíde aj
    `ungetc`.
  - Po riadkoch pracujeme pomocou `fgets` a `fputs`.
  - V programoch, ktoré sa majú reálne používať, je vhodné kontrolovať,
    či tieto operácie úspešne zbehli. Tiež pozor na to, aby pri
    načítaní reťazcov nenastalo pretečenie poľa.
  - K niektorým funkciám existujú aj verzie pre konzolu, napr. `printf`
    a `scanf`, `putchar`, `getchar`.
  - S konzolou tiež môžeme pracovať pomocou premenných `stdin`,
    `stdout`.

Ďalšie možnosti

  - Okrem textových súborov existujú aj binárne, kde nie je číslo
    zapísané ako postupnosť cifier, ale priamo ako bajty.
      - Binárne súbory majú často menšiu veľkosť a rýchlejšie sa s nimi
        pracuje, ťažšie však ručne skontrolujete, čo v súbore je.
      - V knižnici `cstdio` existujú na prácu s binárnymi súbormi
        funkcie `fwrite` a `fread`.
  - V C++ sa dá so súbormi pracovať podobne, ako sme používali `cin` a
    `cout`. Potrebné funkcie nájdete v knižnici `fstream`.
  - V jednom programe **nekombinujte** prácu s konzolou pomocou `cstdio`
    a `iostream`, môže dôjsť k strate dát.
  - V mnohých programovacích jazykoch existujú knižnice na načítavanie a
    zapisovanie často používaných formátov súborov.

