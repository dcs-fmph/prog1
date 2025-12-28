---
title: Zimný semester, semestrálny test
---

* TOC
{:toc}

  - Druhý semestrálny test sa bude konať v stredu **10.12. o 18:10** v
    posluchárňach A a B v trvaní 45 minút.
  - Z obidvoch testov spolu treba získať aspoň 50% bodov, inak známka
    Fx.
  - Opravný termín obidvoch testov bude 15.1.2026 doobeda.
  - Prineste si písacie potreby a preukaz študenta.
  - Rozsadenie bude na dverách posluchárne.
  - Vlastné papiere ani žiadne ďalšie pomôcky nie sú povolené. Mobily,
    hodinky a iné elektronické zariadenia musia byť vypnuté a odložené v
    taške.
  - Zákaz odpisovať od spolužiakov a komunikovať s inými osobami než
    vyučujúcimi.
  - Ak máte otázku k zadaniu prihláste sa, pokúsime sa vám pomôcť.
    Nebudeme vám ale radiť, ako riešiť úlohy.
  - Po opustení miestnosti nebude možné vrátiť sa a pokračovať v písaní
    testu.

<!-- end list -->

  - Ak máte problémy so slovenčinou, môžeme vám na teste a skúške
    poskytnúť strojový preklad zadaní. Prípadný záujem nahláste do
    pondelka 8.12. pomocou
    [formulára](https://forms.office.com/Pages/ResponsePage.aspx?id=jUcxznpu50yGcKW51RiE-fk1X-AjVvpHm_pTPiHlkYlURjBHTFY3R0dNVktGWlExTjhYTksyNFZCNS4u).
    Ak ste už formulár vyplnili pred prvým testom, nemusíte ho vypĺňať
    znovu.

Na semestrálnom teste budú podobné typy príkladov, aké poznáte z
teoretických cvičení, napríklad

  - napíšte funkciu, ktorá robí zadanú činnosť
  - doplňte chýbajúce časti funkcie
  - zistite, čo funkcia robí (pre daný vstup alebo všeobecne)

Vyskytne sa však aj nový typ príkladov, kde je úlohou napísať, ako bude
na nejakom vstupe fungovať algoritmus alebo dátová štruktúra z
prednášky. Nižšie sú ukážky takýchto príkladov. Svoje odpovede si
môžete skontrolovať na spodku stránky.

Na teste nebudú príklady na prácu so súbormi (treba ale ovládať základnú
prácu s konzolou pomocou cin a cout) a nebudú ani príklady používajúce
SVGdraw.

Môžete si pozrieť aj [ukážkový test pre
pokročilých](../files/Pisomka-pokrocili2020.pdf), ktorý má
podobné typy príkladov ako semestrálny test.

Príklady podobné na príklady 7, 8, 9 nižšie na riadnom termíne testu
nebudú, môžu sa však vyskytnúť na opravnom termíne.

## Ukážkové príklady z algoritmov na druhý semestrálny test

  - **Príklad 1** Ako bude vyzerať hašovacia tabuľka pri riešení kolízií
    pomocou spájaných zoznamov, ak hašovacia funkcia je |k| mod 5 a
    vkladáme prvky 13, -2, 0, 8, 10, 17?

<!-- end list -->

  - **Príklad 2:** Máme zásobník s a rad q, pričom obidve štruktúry
    uchovávajú dáta typu char. Aký bude ich obsah po nasledujúcej
    postupnosti príkazov?

<!-- end list -->

    init(s);
    init(q);
    push(s, 'A');
    push(s, 'B');
    push(s, 'C');
    enqueue(q, pop(s));
    enqueue(q, pop(s));
    push(s, 'D');
    push(s, dequeue(q));

  - **Príklad 3:** Strom nižšie má v každom uzle uložené jedno písmeno
    (dáta typu char). V akom poradí budú vypísané jednotlivé písmená, ak
    použijeme inorder, preorder a postorder prehľadávanie?

<!-- end list -->

``` 
         A
       /  \
      /    \
     B      C  
    / \    / \
   D   E  F   G
      / \
     H   I
```

  - **Príklad 4:** Máme binárny strom, v ktorom má každý vrchol buď dve
    deti a v dátovom poli uložený znak '\#' alebo nemá žiadne deti a v
    dátovom poli má uložený znak '\*'. Keď tento strom vypíšeme v
    preorder poradí, dostaneme postupnosť \#\#\*\#\*\*\* Nakreslite, ako
    vyzerá tento strom.

<!-- end list -->

  - **Príklad 5:** Prepíšte výraz 8 3 4 \* + 2 3 + / z postfixovej
    notácie do bežnej infixovej notácie. Aká je jeho hodnota?
    Nakreslite ho aj ako strom.

<!-- end list -->

  - **Príklad 6:** Prepíšte výraz ((2+4)/(3\*5))/(1-2) do postfixovej a
    prefixovej notácie.

<!-- end list -->

  - **Príklad 7:** Vyhodnocujeme výraz 8 3 4 \* + 2 3 - / v postfixovej
    notácii algoritmom z prednášky. Aký bude obsah zásobníka v čase, keď
    začneme spracovávať znamienko +?

<!-- end list -->

  - **Príklad 8:** Nakreslite binárny vyhľadávací strom, ktorý
    dostaneme, ak do prázdneho stromu postupne vkladáme záznamy s kľúčmi
    3, 4, 1, 2, 5, 6 (v tomto poradí).

<!-- end list -->

  - **Príklad 9:** Nakreslite prefixový strom s abecedou {a,b}, do
    ktorého sme vložili reťazce aba, aaab, baa, bab, ba. Vrcholy, ktoré
    zodpovedajú niektorému reťazcu zo vstupu, zvýraznite dvojitým
    krúžkom.

## Vzorové riešenia ukážkových príkladov na semestrálny test

  - **Príklad 1:**

Pre každý index tabuľky 0,...,4 uvádzame zoznam prvkov, ktoré sa do neho
zahašujú. Tieto budú pospájané v zozname v uvedenom poradí.

    0: 10, 0
    1:
    2: 17, -2
    3: 8, 13
    4:

  - **Príklad 2:** na zásobníku budú znaky A, D, C (A na spodku
    zásobníka), v rade bude písmeno B
  - **Príklad 3:**

<!-- end list -->

    Preorder:  ABDEHICFD
    Postorder: DHIEBFGCA
    Inorder:   DBHEIAFCG

  - **Príklad 4:**

<!-- end list -->

``` 
        #
       / \
      #   *
     /\
    *  #
      /\
     *  *
```

  - **Príklad 5:** (8+3\*4)/(2+3), hodnota 4, strom:

<!-- end list -->

``` 
         /
       /  \
      /    \
     +      +  
    / \    / \
   8   *  2   3
      / \
     3   4
```

  - **Príklad 6:** postfix 2 4 + 3 5 \* / 1 2 - / prefix: / / + 2 4 \* 3
    5 - 1 2
  - **Príklad 7:** na zásobníku budú čísla 8 a 12 (8 je na spodku
    zásobníka). Číslo 12 vzniklo vynásobením 3 a 4.
  - **Príklad 8:**

<!-- end list -->

``` 
        3
       / \
      1   4
      \    \
       2    5
             \
              6
```

  - **Príklad 9:** (namiesto dvojitého krúžku používame \*)

<!-- end list -->

``` 
          .
         / \
       a/   \b
       /     \ 
      .       .
    a/ \b    a/
    .   .   *
  a/  a/  a/ \b
  .   *   *   *
b/
*
```

