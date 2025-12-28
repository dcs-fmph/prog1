---
title: Zimný semester, skúška
---

* TOC
{:toc}

Odporúčame tiež si preštudovať **[pravidlá predmetu](./Pravidla.md)**.

## Termíny, prihlasovanie

Termíny skúšok

  - Piatok 19.12. 13:10 (predtermín)
  - Štvrtok 22.1. 13:00
  - Štvrtok 29.1. 13:00, hlavne 1. opravný termín
  - Štvrtok 12.2. 13:00, hlavne 2. opravný termín

Ak zistíte konflikt našej skúšky s hromadnou skúškou alebo písomkou
iného predmetu, dajte nám vedieť čím skôr. Na poslednú chvíľu už
nedokážeme nájsť riešenie. Trvanie skúšky je 2,5 hodiny.

Prihlasovanie

  - Prihlasovanie je v AIS2/Votr otvorené od pondelka 1.12. 19:00
  - Na termín sa prihlasujte / odhlasujte najneskôr 24 hodín pred
    začiatkom termínu.
  - Na skúšku môžete ísť iba ak ste úspešne absolvovali semestrálny test
    aspoň na 50% bodov.
  - Celkovo budú iba uvedené štyri termíny. Každý sa môže zúčastniť na
    najviac troch z nich.

Špeciálne pravidlá pre predtermín

  - Ak sa zúčastňujete predtermínu, body za tréningové príklady môžete
    dostať iba ak ich vyriešite do 19.12. 11:30 (toto neplatí, ak po
    predtermíne ešte idete na opravný termín skúšky).

<!-- end list -->

  - Ak máte problémy so slovenčinou, môžeme vám na teste a skúške
    poskytnúť strojový preklad zadaní.
      - Záujem je potrebné záujem do 8.12., bolo spomínané pred obidvoma
        testami

## Praktická skúška

  - 2.5 hodiny práca pri počítači v halách H3, H6, prípadne F1-248
  - Počas skúšky vám nebudeme pomáhať hľadať chyby vo vašom programe.
    Môžete sa však spýtať na nejasnosti v zadaní. Dajte nám tiež
    vedieť v prípade technických problémov alebo ak si myslíte, že v
    zadaní / kostre / vstupoch je chyba.

Ďalšie detaily

  - Nebudeme používať SVGdraw
  - Môžete používať aj črty C/C++, ktoré sme nebrali. Používajte len
    štandardné súčasti jazyka. Vaše programy by mali fungovať na
    testovači bez zvláštnych nastavení kompilátora a pod.
  - Odporúčame používať iba tie časti jazyka, s ktorými máte dostatočné
    skúsenosti.
  - Skúška bude v Linuxe, rovnaké prostredie ako na cvičeniach.
  - Odovzdávanie prostredníctvom špeciálnej verzie testovača.
  - Okrem testovača nebude k dispozícii internet.
  - Bude k dispozícii kópia poznámok z predmetu, ktoré vidíte na tejto
    stránke.
  - Budete používať špeciálne skúškové konto, takže nebudete mať k
    dispozícii žiadne svoje súbory alebo nastavenia.
  - Môžete použiť Kate, valgrind, ale aj iné nástroje, ktoré bežia v
    Linuxe v učebniach a nepotrebujú internet. Prípadné problémy s
    použitím iného softvéru vám však nebudeme pomáhať riešiť.
      - Nemôžete použiť online prostredia.
      - VS Code nemá pluginy
  - Môžete použiť pero alebo ceruzku na robenie poznámok (odporúčame).
  - Prineste si aj preukaz študenta.
  - Zakázané sú akékoľvek ďalšie pomôcky (mobily a elektronické
    zariadenia, poznámky a iné papierové materiály atď), komunikácia s
    inými osobami než s vyučujúcimi predmetu ako aj pokusy o narušenie
    riadneho chodu testovača.
  - Pri reštarte počítača sa stratia všetky súbory, používajte testovač
    ako zálohu (odovzdajte aj nedokončený program).
  - Každých cca 20 minút vás vyučujúci vyzvú, aby ste v najbližších
    minútach odovzdali svoj program na testovač. Ak práve nerobíte na
    žiadnom programe, odovzdajte krátku správu, napr. "rozmyslam"

## Príklady

Na skúške budete riešiť dva príklady za rovnaký počet bodov

**Prvý príklad**

  - V prvom príklade budete mať za úlohu samostatne napísať celý
    program, ktorý rieši zadanú úlohu. Typicky bude treba načítať dáta,
    spracovať ich a vypísať výsledok.
  - V tomto príklade môžete použiť ľubovoľný postup.
  - Budú však zakázané polia pevných veľkostí. Polia alokujte dynamicky
    cez `new`, alebo použite štruktúry, ktoré menia veľkosť podľa
    potreby (napr. `string`, `vector`). Alokovanú pamäť odalokujte.
  - Predtým ako začnete programovať, si poriadne rozmyslite, aké dátové
    štruktúry (polia, matice, struct-y a pod.) chcete v programe
    použiť.

**Druhý príklad**

  - V druhom príklade dostanete kostru programu, pričom vašou úlohou
    bude doprogramovať niektoré funkcie.
  - V tomto príklade môžete mať v zadaní predpísaný spôsob, ako máte
    niektoré časti naprogramovať.
  - Budú sa vyžadovať aj zložitejšie časti učiva, ako napríklad zoznamy,
    stromy a rekurzia.

**Ukážkové príklady**

Niektoré ukážkové príklady na skúšku budú k dispozícii na
[testovači](https://prog.dcs.fmph.uniba.sk/), môžete si ich v rámci
tréningu vyriešiť a odovzdať. Pre realistickejší tréning si vždy
prečítajte zadanie tesne predtým, ako príklad začnete riešiť, aby ste
odhadli, koľko času vám príklad zaberie vrátane čítania zadania a
rozmýšľania nad riešením.

**Techniky hľadania chýb**

Pre niektorých študentov nie je ani tak problém napísať takmer kompletný
program, ale skôr nájsť v ňom chyby, kvôli ktorým nefunguje.

  - Pozrite si rady k hľadaniu chýb na [prednáške
    5](./P5#hľadanie-chýb-v-programe) a
    návod na použitie programu [Valgrind](./Valgrind.md).

## Hodnotenie

Aby ste mali šancu úspešne ukončiť predmet, **aspoň jeden z príkladov
vám musí prejsť všetky testy na testovači**

  - Túto podmienku nebudeme považovať za splnenú, ak váš program nerieši
    zadanú úlohu (t.j. jeho myšlienka nie je v zásade správna).
  - Podmienku však považujeme za splnenú, ak váš program prejde všetky
    vstupy, má v zásade správnu myšlienku, ale nedostane plný počet
    bodov napríklad kvôli chýbajúcemu uvoľneniu pamäte, statickým
    poliam, menšej chybe, ktorá sa neprejavila na daných vstupoch a pod.
  - Dobre si rozmyslite, s ktorým príkladom chcete začať a snažte sa ho
    dokončiť, kým nedostanete OK na testovači. Potom ho môžete ešte
    vylepšovať alebo sa snažiť vyriešiť aspoň časť príkladu, ktorý ste
    ešte neriešili.

**Bodové hodnotenie**

  - V prvom rade budeme hodnotiť správnosť myšlienky vášho programu.
    Predtým, ako začnete programovať, si dobre prečítajte zadanie a
    rozmyslite, ako budete úlohu riešiť.
  - Ďalej je veľmi dôležité, aby sa program dal skompilovať (v
    štandardnom prostredí) a aby správne fungoval na všetkých vstupoch
    spĺňajúcich podmienky v zadaní.
  - V druhej úlohe budeme jednotlivé funkcie hodnotiť zvlášť, takže
    môžete získať čiastočné body, ak ste niekoľko funkcií napísali
    správne.
  - Na hodnotenie môže mať menší vplyv aj úprava a štýl programu
    (komentáre, mená premenných, odsadzovanie, členenie dlhšieho
    programu na funkcie,...)
  - Na tejto skúške nezáleží na rýchlosti vášho programu (pokiaľ zbehne
    v časovom limite, ktorý však nie je prísny). Radšej napíšte
    jednoduchý, prehľadný a hlavne správny pomalší program, než
    rýchlejší, ale zbytočne zložitý, či nesprávny.

## Opravné termíny

  - Opakovanie praktickej skúšky sa riadi študijným poriadkom fakulty.
    Máte nárok na dva opravné termíny (ale len v rámci termínov, ktoré
    sme určili).
  - Ak po skúške máte nárok na známku E alebo lepšiu, ale chceli by ste
    si známku ešte opraviť, musíte sa dohodnúť so skúšajúcimi.
  - Ak sa zo závažných dôvodov (napr. zdravotných, alebo konflikt s inou
    skúškou) nemôžete zúčastniť termínu skúšky alebo písomky, dajte o
    tom vyučujúcim vedieť čím skôr.

