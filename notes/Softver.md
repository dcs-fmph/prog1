---
title: Softvér
---

* TOC
{:toc}



## Základná práca s editorom Kate v učebni

Toto sú úplné základy vhodné na prvé cvičenia. Ďalšie vysvetlenia, detaily a možnosti nájdete nižšie, odporúčame preštudovať.

### Ako používať Linux v učebni, spustenie Kate

  - Pri štarte počítače zvoľte Linux
  - Prihláste sa rovnakým menom a heslom, aké používate v AISe.
  - Stlačte ALT+F2 a napíšte meno aplikácie, ktorú chcete spustiť alebo
    ju nájdite v menu s ponukou programov
      - `Kate` - v menu v časti Utilities
  - Odporúčame sedieť vždy pri tom istom počítači, keďže na ňom máte
    uložené nastavenia Kate a iných programov, ktoré používate.

### Vytvorenie súboru v Kate

- Vytvorte nový súbor a uložte ho napríklad ako `program.c`.
- Meno súboru môžete zvoliť aj iné, ale koncovku použite `.c`
- Na základe koncovky `.c` bude Kate správne zvýrazňovať syntax.

Pre začiatok môžete použiť napríklad [program na sčítanie dvoch čísel z prednášky 1](./P1.html#sčítanie-čísel).

### Spustenie terminálu v editore Kate

Na kompiláciu a spúšťanie programu budeme používať príkazový riadok, ktorý sa v Kate volá terminál, niekedy ho budeme volať aj konzola.

Zobrazovanie terminálu

- `Settings -> Configure Kate -> Plugins` a tam zaškrtnite `Terminal tool view`
- `View -> Tool Views` a zaškrtnite `Show Terminal` alebo
   stlačte `F4` alebo kliknite na ikonu terminálu
- nastavenie terminálu do priečinka s aktuálne otvoreným súborom
  `Tools -> Synchronize Terminal with Current Document`

### Kompilovanie a spustenie programu v termináli

- V editore nezabudnite uložiť aktuálny stav do súboru (napr. pomocou `Ctrl S` alebo cez menu)
- Kliknite do okna terminálu a môžete písať príkazy
- Príkaz `ls` vypíše zoznam súborov v aktuálnom priečinku, mali by ste vidieť okrem iného `program.c`
- Spustite kompilátor
  `gcc -Wall program.c -o program`
- Ak kompilátor vypísal chybu alebo varovanie, pokúste sa ju pochopiť a opraviť, potom spustie kompilátor znovu
- Ak kompilátor nevypísal nič, zrejme úspešne vytvoril spustiteľný súbor `program`
- Svoj program môžete spustiť takto:
  `./program`
- Keď program funguje správne, môžete ho odovzdať na testovač
- Na testovač odovzdajte vždy súbor s koncovkou `.c`, nie spustiteľný súbor.

## Ďalšie detaily

Po zvládnutí základnej práce vyššie odporúčame preštudovať si ďalšie vysvetlenia uvedené nižšie.

### Práca s teminálom v linuxe

  - Terminál (príkazový riadok} môžete otvoriť priamo v Kate alebo aj ako zvláštne okno
    - V učebni ho nájdete pod menom Konsole medzi aplikáciami v časti System 
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
  - Ak si v aktuálnom priečinku vytvoríte textový súbor so vstupom
    `my_input.txt`, môžete ho poslať na vstup vášho programu pomocou
    presmerovania.
      - Namiesto `./program` spustíte `./program < my_input.txt`
      - Výsledok bude rovnaký ako keby ste obsah súboru `my_input.txt` ručne
        písali na konzolu.
  - Ak by ste si výsledok programu tiež chceli uložiť do súboru, použite
    opačné presmerovanie: `./program < my_input.txt > my_output.txt`
  - Beh programu prerušíte stlačením `Ctrl C`
  
### Ako prenášať súbory

  - Odporúčame ukladať si svoje programy na sieťovom disku `net`
  - Dáta zo sieťového disku máte prístupné na všetkých počítačoch
    v rámci FMFI učební
  - Dáta zo sieťového disku si kedykoľvek môžete stiahnuť v učebni
    na USB kľúčik alebo aj cez sieť odkiaľkoľvek prihlásením sa
    na študentský Linuxový klaster [daVinci](http://www.st.fmph.uniba.sk/)
    (davinci.fmph.uniba.sk) pomocou ssh.
  - Odovzdané programy si môžete počas semestra stiahnuť z testovača, po
    začiatku ďalšieho semestra k ním stratíte prístup

### Vysvetlenie práce s kompilátorom

V príkaze `gcc program.c -o program`:
  - `program.c`: zdrojový súbor na preklad, zmeňte podľa potreby
  - `-o program`: určuje názov výstupného súboru; bez `-o` je predvolený názov `a.out`
  - Môžete pridať aj ďalšie nastavenia, napríklad pomocou prepínačov 
    `-Wall` a `-Wextra` zapnete viac varovaní prekladača o potenciálnych chybách vo vašom programe

## Alternatívne možnosti, práca na vlastnom počítači

### Písanie programov
    
Počas semestra na cvičeniach aj na škúške budete písať programy v jednoduchých
textových editoroch. Odporúčame používať editor **Kate**, ktorý ponúka dostatok
nastavení, aby sa s v ňom pohodlne písali jednoduché programy. Funguje na oboch
operačných systémoch Linux aj Windows (na počítačoch na fakulte sa nachádza len
na Linuxe). Iné textové editory, ktoré môžete použiť:

  - Linux: vim, nano
  - Windows: notepad++, pspad

### Kompilovanie a spúšťanie programov

Na kompilovanie a spúšťanie programov budeme používať terminál (v Linuxe)
respektíve powershell (vo Windows). Ak používate editor Kate, je možné
otvoriť terminál/powershell priamo v okne editora, čo vie byť veľmi
praktické.

### Ako nainštalovať potrebné nástroje

Na [tejto stránke](/prog1/files/first-c-program.sk.html) nájdete návod na:

  - inštaláciu potrebného softvéru na váš počítač (textové editory, kompilátor, ...)
      - Na počítačoch na fakulte je samozrejme už všetko potrebné nainštalované.
  - napísanie prvého programu
  - jeho kompiláciu a spustenie


### Použitie iných nástrojov

Môžete používať aj iné nástroje, ale silno odporúčame používať nejaký jednoduchý textový editor, ktorý nebude programovať takpovediac za vás. A kompilovanie a spúšťanie vašich programov robiť manuálne s použitím konzoly. Výhodami takéhoto prístupu je:

  - Núti vás lepšie porozumieť tomu, ako program vzniká, prekladá sa
    a spúšťa, čo sa pri použití komplexného IDE skryje za kliknutie
    jedného tlačidla.
  - Automatizovať má zmysel iba činnosť, ktorú už človek sám úplne ovláda.
    Najskôr preto musíte získať vlastné znalosti a skúsenosti, až potom
    vám môžu pokročilé nástroje pomáhať pracovať rýchlejšie a efektívnejšie.
  - Cieľom predmetu nie je iba odovzdať funkčný program, ale porozumieť
    jeho fungovaniu a vybudovať si pevné základy.
  - Na skúške budete môcť používať iba jednoduché textové editory,
    ktoré sú k dispozícii v učebniach na fakulte v Linuxe, pričom
    nebude k dispozícii internet, preto odporúčame rovnako pracovať
    počas cvičení, aby ste si to vyskúšali

Okrem jednoduchých editorov ako Kate existujú aj zložitejšie prostredia,
ktoré podporujú prácu programátora, najmä na väčších projektoch. Zvyknú
sa nazývať IDE (integrated development environment). Ak sa chcete
pozrieť aj na niektoré z nich, môžete si vyskúšať napríklad jednu
z nasledovných možností: Visual Studio Code, Netbeans, Eclipse, CLion
(so študentskou licenciou zadarmo).

Ak chcete bežať Linux na počítači s nainštalovaným Windows, môžete ho spúšťať vo virtuálnom počítači. Návod nájdete na [tejto stránke](/prog1/files/debian-vm.sk.html).
