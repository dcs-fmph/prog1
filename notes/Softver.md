---
title: Softvér
---

* TOC
{:toc}


## Úvod

V tomto dokumente popisujeme niektoré nástroje, ktoré môžete použiť na
programovanie v tomto semestri. Na cvičeniach a skúške odporúčame
používať **editor Kate** popísaný nižšie.

Môžete používať aj iné nástroje, ale

  - k iným prostrediam vám nemusíme vedieť poradiť, ako ich používať
  - na skúške budete môcť používať iba tie programy, ktoré sú k
    dispozícii v učebniach na fakulte v Linuxe, pričom nebude k
    dispozícii internet

## Prenášanie programov a odovzdávanie domácich úloh

  - Pri odovzdávaní domácich úloh odovzdávajte súbor .cpp s vašim
    programom (prípadne ďalšie súbory, ak to vyžaduje zadanie).
  - Ak pracujete na rôznych počítačoch v rámci FMFI učební, svoje
    projekty si ukladajte na sieťovom disku net
  - Dáta zo sieťového disku si môžete stiahnuť v učebni na USB kľúčik,
    alebo aj cez sieť z domu prihlásením sa na študentský Linuxový
    klaster [daVinci](http://www.st.fmph.uniba.sk/)
    (davinci.fmph.uniba.sk). Na prenos dát môžete použiť napríklad
    windowsovský program
    [winscp](http://winscp.net/eng/docs/introduction)
  - Odovzdané programy si môžete počas semestra stiahnuť z testovača, po
    začiatku ďalšieho semestra k ním stratíte prístup

## Kate

Kate je základný textový editor, ponúka však dostatok nastavení, aby sa
s v ňom pohodlne písali jednoduché programy (nie je však úplne vhodný na
väčšie projekty).

### Ako spustiť Kate v učebni

  - Prihláste sa do Linuxu rovnakým menom a heslom, aké používate v
    AISe.
  - Atlačte ALT+F2 a napíšte kate (alebo Kate nájdite v menu s ponukou
    programov v časti Utilities).
  - Odporúčame sedieť vždy pri tom istom počítači, máte uložené
    nastavenia.

### Vytvorenie nového programu

  - `File -> New` (Ctrl+N) vytvorí nový textový súbor
  - Uložte ho pomocou `File -> Save` (Ctrl+S), bude od vás žiadať nejaké
    meno a môžete si zvoliť, kam bude daný súbor umiestnený. Nazvať si
    ho môžeme napr. `prog.cpp`
  - Dôležité je pridať koncovku `.cpp` , vďaka nej Kate vie, že chcete
    programovať v C++ a mal by vám automaticky zapnúť C++ zvýrazňovanie
    (ktoré je veľmi praktické)

### Nastavenia editora

Na programovanie odporúčame spraviť / skontrolovať nasledujúce
nastavenia (keď máte otvorený .cpp súbor)

  - zobrazovanie terminálu
      - `Settings -> Configure Kate -> Plugins` a tam zaškrtnite Plugin
        s terminálom
      - `View -> Tool Views` a zaškrtnite `Show Terminal`
      - `Tools -> Synchronize Terminal with Current Document`
  - automatické zvýrazňovanie `Tools -> Highlighting -> Sources`, malo
    by byť zaškrtnuté C++
  - automatické C++ odsádzanie `Tools -> Indentation` malo by byť
    zaškrtnuté C Style
  - `Tools -> align` vám preformátuje vybranú časť programu

### Kompilovanie a spustenie programu

  - Kate nemá vstavané kompilovanie ani spúšťanie, preto na to treba
    používať **terminál** (textové príkazy)
  - V Kate viete mať priamo otvorenú lištu s terminálom, čo je veľmi
    praktické. Mala by sa nachádzať dole pod textovým oknom (prípade
    kliknite na malú ikonku Terminal)
  - Kliknite do okna s terminálom, aby sa stalo aktívnym
  - V termináli sa treba dostať do priečinku s vaším súborom
      - buď sa to stane automaticky vďaka nastaveniu `Tools ->
        Synchronize Terminal with Current Document`
      - alebo použite príkazy nižšie
  - Ak sa nachádzate v priečinku, v ktorom sa nachádza váš program napr.
    v súbore `prog.cpp`, môžete ho pomocou konzoly kompilovať a spúšťať
  - Príkaz `make prog` (slovo `prog` je meno súboru, ale bez koncovky),
    v tom istom priečinku sa vytvorí súbor *prog*, čo bude spustiteľný
    program (linuxový ekvivalent .exe)
  - Príkaz `g++ prog.cpp -o prog` - vytvorí to isté ako príkaz pred tým,
    akurát vieme nastavovať parametre kompilátora g++
  - Príkaz `./prog` - spustí daný program v priečinku, ak mal niečo
    vypísať, vypíše to do konzoly, ak mal niečo čítať, načítava to tiež
    z konzoly (ak nie je povedané inak)
  - Text `prog` v príkazoch vyššie nahraďte menom súboru, s ktorým
    pracujete.

### Ďalšia práca s teminálom

  - V termináli by ste mali vidieť svoje meno, nejaké ďalšie veci a
    potom `:~$` za ktorým kliká kurzor.
  - Časť za : vám hovorí, v ktorom priečinku sa nachádzate, `~` je
    domový priečinok.
  - Príkaz `ls` vypíše zoznam súborov a priečinkov v priečinku, v ktorom
    ste (skratka z list).
  - Príkaz `cd meno_priečinka` presuniete sa do priečinka s daným menom,
    ak sa taký priečinok nachádza v aktuálnom priečinku (skratka z
    change directory).
  - Príkaz `cd ..` presuniete sa o jeden priečinok vyššie.
  - Ak budete pri písaní mena priečinka/súboru stláčať klávesu Tab, bude
    sa vám snažiť automaticky doplniť hľadaný súbor. Ak je možností
    viac, doplní čo najviac znakov, ktoré sú rovnaké.
  - Šípkou hore a dole listujete v histórii príkazov a stlačením Enter
    ho môžete spustiť znovu.

Ak si v aktuálnom priečinku vytvoríte textový súbor so vstupom, môžete
ho poslať na vstup vášho programu pomocou presmerovania:

  - Namiesto `./prog` spustíte `./prog < my_input.txt`
  - Výsledok bude rovnaký ako keby ste obsah súboru `my_input.txt` ručne
    písali na konzolu.
  - Ak by ste si výsledok programu tiež chceli uložiť do súboru, použite
    opačné presmerovanie: `./prog < my_input.txt > my_output.txt`

### Práca v Kate s grafickou knižnicou SVGdraw

  - Knižnicu začneme používať od piatej prednášky
  - Stiahnite si
    [knižnicu](http://compbio.fmph.uniba.sk/vyuka/prog-data/svgdraw/)
      - Stiahnuté súbory `SVDdraw.cpp` a `SVGdraw.h` si uložte do
        priečinku, v ktorom máte svoje programy
  - do vlastného programu potom musíte na začiatok pridať riadok
    `#include "SVGdraw.h"`

**Kompilácia s grafickou knižnicou SVGdraw**

  - Kompilátor potrebuje vedieť, že váš program chce používať funkcie z
    iného súboru (`SVGdraw.cpp`) a preto mu musíte povedať, aby ich
    nalinkoval. Obyčajný make fungovať nebude.
  - Použite príkaz `g++ prog.cpp SVGdraw.cpp -o prog`
  - Vytvorí sa vám súbor `prog`, ktorý môžete normálne spustiť pomocou
    `./prog`
  - V priečinku s programom sa vytvorí súbor s príponou `.svg`, ktorý si
    môžete pozrieť napr. v internetových prehliadačoch firefox alebo
    chromium.

## Iné programátorské prostredia

Okrem jednoduchých editorov ako Kate existujú aj zložitejšie prostredia,
ktoré podporujú prácu programátora, najmä na väčších projektoch. Zvyknú
sa nazývať IDE (integrated development environment). Výhodu je napríklad
zabudovaný debugger, ktorý umožňuje krokovať program pri hľadaní chýb.

### Viacplatformové prostredia

Nasledovné prostredia by mali fungovať na Linuxových aj Windowsových
počítačoch, aj keď nie vždy je ľahké ich nainštalovať a môžu byť tiež
pomerne pomalé

  - [Visual Studio Code](https://code.visualstudio.com/) od firmy
    Microsoft ([návod na zapnutie
    C++](https://code.visualstudio.com/docs/languages/cpp))
  - [Netbeans](http://netbeans.apache.org/)
  - [Eclipse](https://www.eclipse.org/downloads/packages/release/2019-09/r/eclipse-ide-cc-developers)
  - [Code::Blocks](http://www.codeblocks.org/)
  - CLion, komerčný softvér so [študentskou licenciou
    zadarmo](https://www.jetbrains.com/student/)

Z nich v učebniach v Linuxe fungujú VS Code, Netbeans, Code::Blocks,
Eclipse

  - Tieto prostredia teda môžete použiť aj na skúške (vo VS Code ale
    nebudú pluginy pre C++)

### Windows

Pod Windows existuje pomerne veľké množstvo programátorských prostredí
podporujúcich C/C++. Možnosti sú napríklad nasledovné:

**1. Kompilátor GCC + textový editor**

  - Ide o najjednoduchšiu možnosť podobnú práci s Kate pod Linuxom.
  - GCC je pôvodom Linuxový kompilátor pre C/C++. Existuje však aj
    verzia pre Windows, ktorá je súčasťou prostredia
    [MinGW](https://sourceforge.net/projects/mingw/).
  - Programy možno písať v ľubovoľnom textovom editore, ideálne však v
    takom, ktorý podporuje zvýrazňovanie syntaxe pre C a C++, napríklad
    [Notepad++](https://notepad-plus-plus.org/),
    [PSPad](http://www.pspad.com/sk/) a mnohé ďalšie.
  - Programy potom kompilujeme z príkazového riadku: napríklad súbor
    `program.cpp` skompilujeme tak, že sa v príkazovom riadku nastavíme
    do adresára, ktorý ho obsahuje a následne zadáme príkaz ako

```bash
g++ -o prog prog.cpp
```

Tým sa vytvorí spustiteľný súbor `prog.exe`, ktorý možno spustiť z
príkazového riadku príkazom `prog`.

  - Viaceré textové editory podporujú aj integráciu s príkazovým
    riadkom, takže kompilovanie a spúštanie programov možno realizovať
    priamo z nich.

*Inštalácia MinGW:*

  - Stiahnite si inštálator zo [stránky
    projektu](https://sourceforge.net/projects/mingw/).
  - Zapamätajte si adresár na disku, do ktorého MinGW inštalujete.
  - Spustite inštaláciu, počas ktorej zvoľte obidva jazyky C a C++.
  - Po ukončení inštalácie pridajte cestu do adresára obsahujúceho
    spustiteľné súbory `gcc.exe` a `g++.exe` (typicky
    <cesta do koreňového adresára MinGW>`\bin`) do systémovej
    premennej `PATH`, aby bolo možné `g++` v príkazovom riadku volať z
    ľubovoľného adresára. Na internete je dostupných množstvo návodov
    na editovanie systémových premenných (kľúčové slová pre vyhľadávanie
    môžu byť napríklad *edit PATH environment variable* v kombinácii s
    vašou verziou Windows).

**2. NetBeans**

  - NetBeans je IDE určené najmä pre jazyk Java. Možno v ňom však
    vyvíjať aj aplikácie pre C a C++.
  - Je potrebné mať nainštalované MinGW (viď vyššie) a súčasne aj
    utilitu MSYS. Je možné nainštalovať aj [obidva tieto programy
    naraz](https://sourceforge.net/projects/mingwbundle/). Po ukončení
    inštalácie je potrebné okrem cesty na adresár obsahujúci `gcc.exe` a
    `g++.exe` do premennej `PATH` pridať aj adresár obsahujúci
    `make.exe`.
  - Podrobný návod na inštaláciu je k dispozícii
    [tu](https://netbeans.org/community/releases/80/cpp-setup-instructions.html),
    pričom odporúčame variant s MinGW.

**3. Dev-C++**

  - Iné IDE pre Windows s pomerne bezproblémovou inštaláciou
    (nepotrebuje MinGW).
  - Dostupné je [tu](https://sourceforge.net/projects/orwelldevcpp/).

**4. Code::Blocks**

  - Multiplatformové IDE.
  - Dostupné [tu](http://www.codeblocks.org/).

**5. Visual Studio 2015**

  - Profesionálne komerčné prostredie od firmy Microsoft, ktoré si ako
    študenti môžete na študijné účely nainštalovať podľa [pokynov na
    fakultnej
    stránke](http://zona.fmph.uniba.sk/sluzby-a-administrativa/it-sluzby/softver-dostupny-na-fakulte/)

**Ak máte na počítači operačný systém Windows, ale chceli by ste si
vyskúšať aj prácu v Linuxe:**

  - Môžete si nainštalovať Linux do virtuálneho počítača, napr. pomocou
    programu [VirtualBox](https://www.virtualbox.org/).
  - Alebo môžete štartovať Linux nainštalovaný na [USB
    kľúči](https://tutorials.ubuntu.com/tutorial/tutorial-create-a-usb-stick-on-windows#0).

### On-line prostredia

Ak máte problémy nainštalovať na svoj počítač vhodné prostredie na
programovanie, môžete skúsiť webstránky, ktoré vám umožňujú písať,
kompilovať a spúšťať jednoduché programy.

  - Základná jednoduchá stránka: <https://www.codechef.com/ide>
  - Mierne zložitejšia stránka, v ktorej sa dá program interaktívne
    spúšťať a dá sa robiť aj s SVGdraw:
    <http://www.tutorialspoint.com/compile_cpp11_online.php>

Tieto stránky nebudete môcť používať na skúške.

## Kontrola práce s pamäťou programom valgrind

V druhej polovici semestra budeme pracovať aj so smerníkmi a alokáciou
pamäte. Na odhalenie chýb, ktoré pri práci s pamäťou vznikajú, môžete
použiť program valgrind.

  - [Návod na použite programu valgrind](./Valgrind.md).

