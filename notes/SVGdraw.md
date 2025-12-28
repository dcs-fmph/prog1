---
title: SVGdraw
---

* TOC
{:toc}

Knižnica SVGdraw umožňuje vytvoriť obrázok v SVG formáte a vykresľovať
do neho rôzne geometrické útvary, animovať ich a používať korytnačiu
grafiku.

  - Návod na použitie knižnice [v prostredí
    Kate](./Softver.md#práca-v-kate-s-grafickou-knižnicou-svgdraw)
  - [Stiahnutie
    knižnice](https://compbio.fmph.uniba.sk/vyuka/prog-data/svgdraw/)
  - Príklady programov na [prednáške 5](./P5.md)

## Vykresľovanie v SVG formáte

  - Ako prvé musíme vytvoriť súbor s obrázkom v SVG formáte s určitými
    rozmermi príkazom typu `SVGdraw drawing(150, 100, "hello.svg");`
  - Do obrázku môžeme kresliť príkazmi `drawRectangle`, `drawEllipse`,
    `drawLine`, `drawText`.
  - Ak chceme vykresľovať mnohouholníky, použijeme skupinu príkazov
    `startPolygon`, `addPolygonPoint` a `drawPolygon`. Pomocou
    `startPolygon` a `addPolygonPoint` postupne vymenujeme vrcholy a
    pomocou `drawPolygon` mnohouholník uzavrieme a vykreslíme.
  - Pomocou príkazov `setLineColor`, `setFillColor`, `setNoFill`
    nastavujeme farbu čiar a vyfarbovania. Farby zadávame buď troma
    číslami od 0 do 255 určujúcimi intenzitu červenej, zelenej a
    modrej, alebo názvom, napr. `"red"` ([zoznam mien
    farieb](https://www.w3.org/TR/SVG/types.html#ColorKeywords)). Príkaz
    `setFontSize` nastavuje veľkosť písma a `setLineWidth` nastavuje
    hrúbku čiary.
  - Po vykreslení všetkých útvarov ukončíme vykresľovanie príkazom
    `drawing.finish();`
  - Po spustení programu by mal vzniknúť súbor `hello.svg`, ktorý si
    môžete prezrieť napríklad v internetovom prehliadači.

## Animácie

  - Príkaz `wait` umožní pozastaviť vykresľovanie SVG súboru o zadaný
    čas v sekundách, takže jednotlivé útvary sa objavujú postupne.
  - Príkaz `clear` schová všetky vykreslené útvary, takže môžeme kresliť
    znova na prázdnu plochu. Pred príkazom `clear` je vhodné použiť
    `wait`.
  - Príkaz `hideItem` schová objekt (napr. čiaru) so zadaným číslom.
    Každý kresliaci príkaz vráti číslo práve vykresleného objektu,
    takže si ho stačí uložiť v nejakej premennej pre neskoršie mazanie.

## Príkazy pre korytnačiu grafiku

Namiesto vykresľovania obdĺžnikov, čiar a pod na zadané súradnice môžeme
obrázok vytvoriť aj korytnačou grafikou. Na obrázku bude pohyb
korytnačky znázornený ako červený trojuholník a za sebou bude nechávať
čiernu čiaru.

  - Príkazom typu `Turtle turtle(200, 300, "domcek2.svg", 50, 250, 0);`
    vytvoríme SVG obrázok určitej veľkosti a s určitým menom súboru.
    Posledné tri čísla udávajú počiatočnú polohu korytnačky a jej
    natočenie.
  - Korytnačka si pamätá svoju polohu a natočenie na ploche. Príkaz
    `forward` posunie korytnačku dopredu, príkazy `turnLeft` a
    `turnRight` ju otočia.
  - Príkaz `setSpeed` umožňuje zmeniť rýchlosť korytnačky, aby sme
    lepšie videli, ako sa postupne hýbe.
