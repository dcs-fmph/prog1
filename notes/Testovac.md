---
title: Návod k testovaču
---


Príklady z cvičení, domácich úloh, ale aj na záverečnej skúške budete
odovzdávať na stránke **<https://prog.dcs.fmph.uniba.sk/>**, ktorá
bude súčasne mnohé z vašich riešení aj testovať.

  - Na stránku sa prihláste heslom, ktoré dostanete na prvých
    cvičeniach, po prihlásení si ho zmeňte.
  - Na testovači uvidíte zoznam príkladov, spolu s ich zadaniami v pdf
    formáte a s ďalšími potrebnými súbormi (napr. kostra programu,
    príklady vstupu)
  - Vaše programy môžete odovzdať buď zvolením súboru s programom (.cpp)
    z disku alebo nakopírovaním programu do textového poľa.
  - Váš program sa uloží na testovači a môžete si neskôr skontrolovať,
    či ste odovzdali správnu verziu.
  - Testovač váš program skompiluje a spustí na niekoľkých vstupoch.
    Výsledok testovania vám zobrazí.
  - V závislosti od zaťaženia servera zobrazenie výsledku môže nejaký
    čas trvať.
  - V ideálnom prípade dostanete výsledok OK, ak váš program vypísal na
    všetkých vstupoch správnu odpoveď.
  - Môže však dôjsť k rôznym chybám:
      - CE (compile error): chyba pri kompilácii, testovač vypíše výstup
        kompilátora. Odporúčame pred odovzdaním program skompilovať na
        vašom počítači.
      - WA (wrong answer): na niektorom vstupe váš program vypísal zlú
        odpoveď. Môže ísť o závažnú chybu v programe, ale aj len o malý
        problém vo formáte výstupu. Testovač väčšinou porovnáva váš
        výsledok znak po znaku so správnym výsledkom a každý rozdiel,
        ako napríklad medzera navyše, považuje za chybu. Pozrite si
        detaily testovania, či nezbadáte rozdiely vo formáte.
      - TO (time limit exceeded): program na príslušnom vstupe bežal
        príliš dlho. Nakoľko dávame pomerne veľké časové limity,
        pravdepodobne váš program sa "zacyklil", t.j. beží do nekonečna.
      - SG (segmentation fault): váš program spadol na chybu pri behu,
        napr. delenie nulou, prístup mimo hraníc poľa, prípadne priveľká
        spotreba pamäte.
      - Kód WAITING znamená, že váš program ešte čaká na spustenie a
        RUNNING znamená, že prebieha jeho testovanie.
  - Pri týchto problémoch skúste program spúšťať na viacerých vstupoch
    na vašom počítači a chybu objaviť. Niekedy vám poskytneme aj vstupy
    a výstupy použité na testovači, ktoré vám pomôžu pri hľadaní chyby.
    V opačnom prípade si skúste nejaké vstupy vymyslieť sami.
  - Program opravujte až kým nedostanete OK na všetkých vstupoch.
  - Testovač vám dovolí odovzdať program aj po termíne, ale takéto
    pokusy už nebudú brané do úvahy pri bodovaní, pokiaľ nemáte
    dohodnuté individuálne predĺženie termínu s vyučujúcimi.
  - Ak testovač nefunguje alebo ak nájdete chybu v zadaní, **dajte nám
    vedieť** na adrese {% include email.html %}. Takisto na
    túto adresu posielajte otázky k zadaniam alebo prosby o pomoc s
    konkrétnou úlohou.

## Poznámka o vstupe a výstupe

  - Ak v zadaní nie je povedané inak, všetok vstup načítavajte z konzoly
    príkazmi `cin` (prípadne `scanf` a pod.) a vypisujte na konzolu príkazmi
    `cout` (prípadne `printf` a pod.)
  - Vstup uvedený v zadaní má testovač v súbore a [presmeruje
    ho](https://cs.wikipedia.org/wiki/P%C5%99esm%C4%9Brov%C3%A1n%C3%AD)
    vášmu programu na konzolu, t.j. správa sa podobne, ako keby niekto
    zadával príslušné hodnoty ručne počas behu vášho programu
  - Naopak testovač zachytí do súboru všetko, čo váš program vypíše na
    konzolu. Tento súbor potom porovnáva so správnou odpoveďou.
  - Napr. [program na sčítanie čísel z prvej prednášky](./P1#sčítanie-čísel)
    by mohol mať nasledovný vstup a výstup na testovači:

```
10
3
```
```
Please enter the first number: Please enter the second number: 10+3=13
```

  - V príkladoch na testovači väčšinou vynecháme interaktívne časti,
    program si teda nebude pýtať čísla od užívateľa, predpokladá, že ten
    ich sám od seba zadá.

## Nastavenia kompilátora

  - Vaše programy kompilujeme pomocou gcc 9.4.0 s nastaveniami `g++
    -static -std=gnu++17 -O2 -Wall -Wextra`
