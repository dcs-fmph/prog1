---
title: Valgrind
---

* TOC
{:toc}

  - C-čko pri použití polí a smerníkov nekontroluje, či ich používame
    správne
  - Chybou v programe sa nám teda ľahko môže stať, že čítame alebo
    píšeme mimo alokovanej pamäte
  - Takéto chyby sa niekedy ťažko hľadajú
  - V Linuxe nám na hľadanie takýchto chýb pomôže nástroj
    [valgrind](http://valgrind.org/), ktorý môžete použiť aj na skúške
  - Vo Windows môžete použiť [Dr. Memory](http://drmemory.org/)

## Spustenie programu v nástroji valgrind pri použití Kate

  - Na príkazovom riadku v editore Kate spúšťate váš program príkazom
    typu `./prog`, kde `prog.cpp` je meno vášho súboru
  - Namiesto toho napíšete `valgrind ./prog`
  - Nástroj valgrind bude náš program pozorne sledovať a keď robí divné
    veci v pamäti, vypíše nám o tom správu
  - Aby boli tieto správy zrozumiteľnejšie (obsahovali čísla riadkov),
    lepšie je skompilovať program s prepínačom -g
  - Namiesto `make prog` teda napíšete `g++ -g prog.cpp -o prog` alebo
    ešte lepšie je zapnúť si aj varovania kompilátora

<!-- end list -->

  - 
    
      -   
        `g++ -g -Wall prog.cpp -o prog`

## Spustenie programu v nástroji valgrind pri použití Netbeans

  - Keď v Netbeans spustíme nástroj Build (ikonka kladivka; spúšťa sa
    tiež automaticky pred spustením programu), Netbeans zavolá
    kompilátor a vytvorí spustiteľný súbor
  - Tento spustiteľný súbor nájdeme v adresári typu
    `NetBeansProjects/meno_projektu/dist/Debug/GNU-Linux-x86/`, volá sa
    rovnako ako projekt
  - V Linuxe si ho môžeme na príkazovom riadku spustiť aj mimo
    prostredia Netbeans, stačí napísať
    `NetBeansProjects/meno_projektu/dist/Debug/GNU-Linux-x86/meno_projektu`
  - Namiesto toho ho môžeme spustiť `valgrind
    NetBeansProjects/meno_projektu/dist/Debug/GNU-Linux-x86/meno_projektu`
  - Nástroj valgrind bude náš program pozorne sledovať a keď robí divné
    veci v pamäti, vypíše nám o tom správu

## Ukážky chýb a výsledok z valgrind

### Neinicializovaná premenná

Nasledujúci program vypisuje neinicializovanú premennú *i*

    #include <iostream>
    using namespace std;
    int main(void) {
        int i; cout << i << endl;
    }

Valgrind vypíše okrem iného

    ==25895== Conditional jump or move depends on uninitialised value(s)
    ==25895==    at 0x4F3CCAE: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x4F3CEDC: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x4F493F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x40082C: main (prog.cpp:4)
    ==25895== 
    ==25895== Use of uninitialised value of size 8
    ==25895==    at 0x4F3BB13: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x4F3CCD9: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x4F3CEDC: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x4F493F9: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
    ==25895==    by 0x40082C: main (prog.cpp:4)

Dôležitá informácia je, že chyba nastala na riadku 4 v programe prog.cpp

### Neinicializovaný smerník

Nasledujúci program zapisuje do pamäte, na ktorú ukazuje smerník s
neinicializovanou hodnotou

    #include <iostream>
    using namespace std;
    int main(void) {
        int *p; 
        *p = 7; 
        cout << *p << endl;
    }

    ==25923== Use of uninitialised value of size 8
    ==25923==    at 0x400822: main (prog.cpp:5)
    ==25923== 
    ==25923== Invalid write of size 4
    ==25923==    at 0x400822: main (prog.cpp:5)
    ==25923==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ==25923== 
    ==25923== 
    ==25923== Process terminating with default action of signal 11 (SIGSEGV)
    ==25923==  Access not within mapped region at address 0x0
    ==25923==    at 0x400822: main (prog.cpp:5)
    ==25923==  If you believe this happened as a result of a stack
    ==25923==  overflow in your program's main thread (unlikely but
    ==25923==  possible), you can try to increase the size of the
    ==25923==  main thread stack using the --main-stacksize= flag.
    ==25923==  The main thread stack size used in this run was 8388608.

### Chybné odalokovanie

Tento program sa pokúša odalokovať pamäť, ktorá nebola alokovaná

    #include <iostream>
    using namespace std;
    int main(void) {
        int i = 7; 
        int *p = &i; 
        delete p;
    }

    ==25952== Invalid free() / delete / delete[] / realloc()
    ==25952==    at 0x4C2F24B: operator delete(void*) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==25952==    by 0x4007A7: main (prog.cpp:6)
    ==25952==  Address 0xfff0002bc is on thread 1's stack
    ==25952==  in frame #1, created by main (prog.cpp:3)

### Písanie za koniec alokovaného poľa

    #include <iostream>
    using namespace std;
    int main(void) {
        int *p = new int[4];
        for(int i = 0; i <= 4; i++) {
            p[i] = 100;
        }
        delete[] p;
    }

Priraďujeme na index 4 v poli, ktoré má iba indexy 0 až 3. Valgrind
vypíše:

    ==149928== Invalid write of size 4
    ==149928==    at 0x1091C4: main (prog.cpp:6)
    ==149928==  Address 0x4db3c90 is 0 bytes after a block of size 16 alloc'd
    ==149928==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==149928==    by 0x10919E: main (prog.cpp:4)

### Písanie za koniec lokálneho poľa

Ani valgrind nemusí nájsť všetky chyby, napr. píšeme za koniec poľa,
ktoré je lokálne vo funkcii, ale valgrind si to nevšimne:

    #include <iostream>
    using namespace std;
    int main(void) {
        int a[4] = {10, 20, 30, 40};
        int *p = a;
        for(int i = 0; i <= 4; i++) {
            p[i] = 100;
        }
    }

Ak index 4 nahradíme 200, program padne, ale valgrind nevie presne určiť
kde...

  - Celkovo valgrind lepšie deteguje chyby týkajúce sa dynamicky
    alokovanej pamäte (pomocou `new`)

## Hľadanie neodalokovanej pamäte

Valgrind nám tiež môže pomôcť nájsť pamäť, ktorú sme alokovali cez new,
ale zabudli odalokovať cez delete alebo delete\[\].

  - V programe nižšie máme dve volania new, ku ktorým chýba odalokovanie

<!-- end list -->

    #include <iostream>
    using namespace std;
    int main(void) {
      int n = 100;
      int *a = new int[n];
      double *b = new double;
      for(int i = 0; i<n; i++) {
        a[i] = i;
      }
    }

Valgrind vypíše

    ==149385== Memcheck, a memory error detector
    ==149385== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==149385== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==149385== Command: ./prog
    ==149385== 
    ==149385== 
    ==149385== HEAP SUMMARY:
    ==149385==     in use at exit: 408 bytes in 2 blocks
    ==149385==   total heap usage: 3 allocs, 1 frees, 73,112 bytes allocated
    ==149385== 
    ==149385== LEAK SUMMARY:
    ==149385==    definitely lost: 408 bytes in 2 blocks
    ==149385==    indirectly lost: 0 bytes in 0 blocks
    ==149385==      possibly lost: 0 bytes in 0 blocks
    ==149385==    still reachable: 0 bytes in 0 blocks
    ==149385==         suppressed: 0 bytes in 0 blocks
    ==149385== Rerun with --leak-check=full to see details of leaked memory
    ==149385== 
    ==149385== For lists of detected and suppressed errors, rerun with: -s
    ==149385== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

  - Vidíme teda, že počas beho programu sa alokovali 3 kusy pamäte a iba
    jeden sa odalokoval
  - Z toho jedno alokovanie bolo v štandardnej knižnici, ale tie ďalšie
    dve sú naše a bolo by pekné ich odalokovať

<!-- end list -->

  - Podľa pokynov programu spustíme `valgrind --leak-check=full ./prog`
  - Pribudne podrobnejší rozbor neodalokovanej pamäte

<!-- end list -->

    ==149568== HEAP SUMMARY:
    ==149568==     in use at exit: 408 bytes in 2 blocks
    ==149568==   total heap usage: 3 allocs, 1 frees, 73,112 bytes allocated
    ==149568== 
    ==149568== 8 bytes in 1 blocks are definitely lost in loss record 1 of 2
    ==149568==    at 0x483BE63: operator new(unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==149568==    by 0x109209: main (prog.cpp:6)
    ==149568== 
    ==149568== 400 bytes in 1 blocks are definitely lost in loss record 2 of 2
    ==149568==    at 0x483C583: operator new[](unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==149568==    by 0x1091FB: main (prog.cpp:5)

  - valgrind nám teraz vypísal, na ktorom riadku je new, ku ktorému
    nebol volaný delete (riadky 5 a 6 v súbore prog.cpp)
  - tu to vidíme ľahko aj bez valgrind, ale vo väčšom programe vám táto
    informácia môže pomôcť

## Cvičenie

Nasledujúci program by mal správne vypísať text "AhojAhojAhojAhoj", ale
je v ňom zopár chýb. Skúste nájsť a opraviť chyby čítaním programu,
použitím debugera, programu valgrind, prípadne si pridajte nejaké
pomocné výpisy premenných.

  - v programe valgrind je vždy dobré začať od prvej vypísanej chyby,
    opraviť ju a spustiť valgrind znovu

<!-- end list -->

    #include <iostream>
    using namespace std;
    
    void opakuj(char kam[], char co[], char kolko) {
        /* Funkcia dostane na vstupe retazec co a cislo kolko a nakopiruje ho tolkokrat
         * za sebou do retazca kam. */
    
        int i=0; // pozicia v kam
        for(int opakovanie=0; opakovanie<kolko; opakovanie++) {  // opakuj kopirovanie
            for(int j=0; co[j]!=0; j++) {  // prechod cez znaky retazca co
                kam[i] = co[j];
                i++;
            }        
        }
    }
    
    int main(void) {
        char ahoj[4] = {'A', 'h', 'o', 'j'};
        char vysledok[16];  
        opakuj(vysledok, ahoj, 4);
        cout << vysledok << endl;
    }

