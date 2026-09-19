---
title: Softvér
---

* TOC
{:toc}

## Úvod

V tomto dokumente popisujeme niektoré nástroje a postupy, ktoré môžete použiť
na písanie, kompilovanie a spúšťanie programov v tomto semestri.


## Písanie, kompilovanie a spúšťanie programov

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


### Ako na môj prvý program

Na [tejto stránke](/prog1/files/first-c-program.sk.html) nájdete návod na:

  - inštaláciu potrebného softvéru (textové editory, kompilátor, ...)
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


## Práca s počítačmi na fakulte

### Ako používať Linux v učebni

  - Prihláste sa do Linuxu rovnakým menom a heslom, aké používate v AISe.
  - Stlačte ALT+F2 a napíšte meno aplikácie, ktorú chcete spustiť alebo
    ju nájdite v menu s ponukou programov
      - Kate - v menu v časti Utilities
      - terminal (meno aplikácie je Konsole) - v menu v časti System
  - Odporúčame sedieť vždy pri tom istom počítači, keďže na ňom máte
    uložené nastavenia textového editor, ktorý používate.

### Práca s teminálom v linuxe

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
      - Namiesto `./prog` spustíte `./prog < my_input.txt`
      - Výsledok bude rovnaký ako keby ste obsah súboru `my_input.txt` ručne
        písali na konzolu.
  - Ak by ste si výsledok programu tiež chceli uložiť do súboru, použite
    opačné presmerovanie: `./prog < my_input.txt > my_output.txt`
  
### Ako prenášať súbory

  - Odporúčame ukladať si svoje programy na sieťovom disku net
  - Dáta zo sieťového disku máte prístupné na všetkých počítačoch
    v rámci FMFI učební
  - Dáta zo sieťového disku si kedykoľvek môžete stiahnuť v učebni
    na USB kľúčik alebo aj cez sieť odkiaľkoľvek prihlásením sa
    na študentský Linuxový klaster [daVinci](http://www.st.fmph.uniba.sk/)
    (davinci.fmph.uniba.sk) pomocou ssh.
  - Odovzdané programy si môžete počas semestra stiahnuť z testovača, po
    začiatku ďalšieho semestra k ním stratíte prístup

### Nastavenia editora Kate

Nasledujúce nastavenie by mali byť predvolené ak máte otvorený súbor
s koncovkou .c a postupovali ste podľa návodu vyššie. Tu ich uvádzame
len pre prípadné riešenie problémov.

  - zobrazovanie terminálu
      - `Settings -> Configure Kate -> Plugins` a tam zaškrtnite
        `Terminal tool view`
      - `View -> Tool Views` a zaškrtnite `Show Terminal` alebo
        stlačte `F4` alebo kliknite na ikonu terminálu
  - nastavenie terminálu do priečinka s aktuálne otvoreným súborom
    `Tools -> Synchronize Terminal with Current Document`
  - automatické zvýrazňovanie syntaxe `Tools -> Highlighting -> Sources -> C`
  - automatické C odsádzanie `Tools -> Indentation -> C style`


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

