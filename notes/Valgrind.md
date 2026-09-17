---
title: Valgrind
---

* TOC
{:toc}

  - Jazyk C pri použití polí a smerníkov nekontroluje, či ich používame
    správne
  - Chybou v programe sa nám teda ľahko môže stať, že čítame alebo
    píšeme mimo alokovanej pamäte
  - Takéto chyby sa niekedy ťažko hľadajú
  - V Linuxe nám na hľadanie takýchto chýb pomôže nástroj
    [valgrind](http://valgrind.org/), ktorý môžete použiť aj na skúške
  - Vo Windows môžete použiť [Dr. Memory](http://drmemory.org/)

## Spustenie programu v nástroji valgrind pri použití Kate

  - Na príkazovom riadku v editore Kate spúšťate váš program príkazom
    typu `./prog`, kde `prog.c` je meno vášho súboru
  - Namiesto toho napíšete `valgrind ./prog`
  - Nástroj valgrind bude náš program pozorne sledovať a keď robí divné
    veci v pamäti, vypíše nám o tom správu
  - Aby boli tieto správy zrozumiteľnejšie (obsahovali čísla riadkov),
    lepšie je skompilovať program s prepínačom -g
  - Namiesto `make prog` teda napíšete 
      - `gcc -g -Wall prog.c -o prog`

## Ukážky chýb a výsledok z valgrind

### Neinicializovaná premenná

Nasledujúci program vypisuje neinicializovanú premennú *i*

```c
#include <stdio.h>

int main(void) {
    int i; printf("%d\n", i);
}
```    

Valgrind vypíše okrem iného
```
==569288== Conditional jump or move depends on uninitialised value(s)
==569288==    at 0x48DA0CB: __printf_buffer (vfprintf-process-arg.c:58)
==569288==    by 0x48DB73A: __vfprintf_internal (vfprintf-internal.c:1544)
==569288==    by 0x48D01B2: printf (printf.c:33)
==569288==    by 0x10916D: main (prog.c:4)
```

Dôležitá informácia je, že chyba nastala na riadku 4 v programe prog.c

### Neinicializovaný smerník

Nasledujúci program zapisuje do pamäte, na ktorú ukazuje smerník s
neinicializovanou hodnotou

```c
#include <stdio.h>
int main() {
    int *p; 
    *p = 7; 
    printf("%d\n", *p);
}
```

```
==569398== Use of uninitialised value of size 8
==569398==    at 0x109159: main (prog.c:4)
==569398== 
==569398== Use of uninitialised value of size 8
==569398==    at 0x109163: main (prog.c:5)
==569398== 
```

### Chybné odalokovanie

Tento program sa pokúša odalokovať pamäť, ktorá nebola alokovaná

```c
#include <stdlib.h>
int main() {
    int i = 7; 
    int *p = &i; 
    free(p);
}
```

```
==569510== Invalid free() / delete / delete[] / realloc()
==569510==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==569510==    by 0x10919E: main (prog.c:5)
==569510==  Address 0x1fff00033c is on thread 1's stack
==569510==  in frame #1, created by main (prog.c:2)
```

### Písanie za koniec alokovaného poľa

```c
#include <stdlib.h>
int main(void) {
    int *p = (int*)malloc(4 * sizeof(int));
    for(int i = 0; i <= 4; i++) {
        p[i] = 100;
    }
    free(p);
}
```

Priraďujeme na index 4 v poli, ktoré má iba indexy 0 až 3. Valgrind
vypíše:

```
==570167== Invalid write of size 4
==570167==    at 0x1091A0: main (prog.c:5)
==570167==  Address 0x4a86050 is 0 bytes after a block of size 16 alloc'd
==570167==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==570167==    by 0x10917E: main (prog.c:3)
```

### Písanie za koniec lokálneho poľa

Ani valgrind nemusí nájsť všetky chyby, napr. píšeme za koniec poľa,
ktoré je lokálne vo funkcii, ale valgrind si to nevšimne:

```c
#include <stdio.h>

int main(void) {
    int a[4] = {10, 20, 30, 40};
    int *p = a;
    for(int i = 0; i <= 4; i++) {
        p[i] = 100;
    }
}
```

Ak index 4 nahradíme 200, program padne, ale valgrind nevie presne určiť
kde...

  - Celkovo valgrind lepšie deteguje chyby týkajúce sa dynamicky
    alokovanej pamäte (pomocou `malloc`)

## Hľadanie neodalokovanej pamäte

Valgrind nám tiež môže pomôcť nájsť pamäť, ktorú sme alokovali cez `malloc`,
ale zabudli odalokovať cez `free`.
  - V programe nižšie máme dve volania `malloc`, ku ktorým chýba odalokovanie

```c
#include <stdlib.h>
int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    double *b = (double*)malloc(sizeof(double));
    for(int i = 0; i<n; i++) {
        a[i] = i;
    }
}
```

Valgrind vypíše
```
==569679== HEAP SUMMARY:
==569679==     in use at exit: 408 bytes in 2 blocks
==569679==   total heap usage: 2 allocs, 0 frees, 408 bytes allocated
==569679== 
==569679== LEAK SUMMARY:
==569679==    definitely lost: 408 bytes in 2 blocks
==569679==    indirectly lost: 0 bytes in 0 blocks
==569679==      possibly lost: 0 bytes in 0 blocks
==569679==    still reachable: 0 bytes in 0 blocks
==569679==         suppressed: 0 bytes in 0 blocks
==569679== Rerun with --leak-check=full to see details of leaked memory
```

  - Vidíme teda, že počas beho programu sa alokovali 2 kusy pamäte ale žiaden sa neodalokoval
  - Podľa pokynov programu spustíme `valgrind --leak-check=full ./prog`
  - Pribudne podrobnejší rozbor neodalokovanej pamäte

```
==569728== HEAP SUMMARY:
==569728==     in use at exit: 408 bytes in 2 blocks
==569728==   total heap usage: 2 allocs, 0 frees, 408 bytes allocated
==569728== 
==569728== 8 bytes in 1 blocks are definitely lost in loss record 1 of 2
==569728==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==569728==    by 0x10917A: main (prog.c:5)
==569728== 
==569728== 400 bytes in 1 blocks are definitely lost in loss record 2 of 2
==569728==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==569728==    by 0x10916C: main (prog.c:4)
```



  - valgrind nám teraz vypísal, na ktorom riadku je `malloc`, ku ktorému
    nebol volaný `free` (riadky 4 a 5 v súbore `prog.c`)
  - tu to vidíme ľahko aj bez valgrind, ale vo väčšom programe vám táto
    informácia môže pomôcť

## Cvičenie

Nasledujúci program by mal správne vypísať text `AhojAhojAhojAhoj`, ale
je v ňom zopár chýb. Skúste nájsť a opraviť chyby čítaním programu,
použitím debugera, programu valgrind, prípadne si pridajte nejaké
pomocné výpisy premenných.

  - v programe valgrind je vždy dobré začať od prvej vypísanej chyby,
    opraviť ju a spustiť valgrind znovu


```c
#include <stdio.h>
#include <string.h>

void opakuj(char kam[], char co[], char kolko) {
    /* Funkcia dostane na vstupe retazec co a cislo kolko a nakopiruje ho tolkokrat
     * za sebou do retazca kam. */

    int i = 0; // pozicia v kam
    for (int opakovanie = 0; opakovanie < kolko; opakovanie++) { // opakuj kopirovanie
        for (int j = 0; co[j] != 0; j++) { // prechod cez znaky retazca co
            kam[i] = co[j];
            i++;
        }
    }
}

int main(void) {
    char ahoj[4] = {'A', 'h', 'o', 'j'};
    char vysledok[16];
    opakuj(vysledok, ahoj, 4);
    printf("%s\n", vysledok);
}
```
