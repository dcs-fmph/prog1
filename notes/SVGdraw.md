---
title: SVGdraw
---

* TOC
{:toc}

Knižnica SVGdraw umožňuje vytvoriť obrázok v SVG formáte a vykresľovať
do neho rôzne geometrické útvary, animovať ich a používať korytnačiu
grafiku.

## Stiahnutie a použitie knižnice

Stiahnite si nasledujúce dva súbory (kliknite na linku pravým tlačidlom a zvoľte Save Link As):
- [SVGdraw.c](/prog1/programs/SVGdraw.c)
- [SVGdraw.h](/prog1/programs/SVGdraw.h)

Použitie knižnice
- na začiatok programu pridajte riadok `#include "SVGdraw.h"`
- váš program a obidva súbory knižnice uložte do jedného priečinka, aby ich kompilátor našiel
- kompilujte program spolu s knižnicou, napríklad príkazom `gcc program.c SVGdraw.c -lm -o program` (pridajte prepínač `-lm`, pretože knižnica používa `math.h`)
- spustite program príkazom `./program` ako obvykle
- program v priečinku vytvorí súbor s obrázkom v SVG formáte, napríklad `program.svg`
- súbor s príponou `.svg` si môžete pozrieť napríklad v internetových prehliadačoch (Firefox, Edge,  Chromium a pod.).


## Ukážkové programy

Ukážkové programy: 
- [domček čiarami](/prog1/programs/domcek1.html) (vytvorí obrázok [`domcek1.svg`](/prog1/programs/domcek1.svg))
- [domček korytnačou grafikou](/prog1/programs/domcek2.html) (vytvorí obrázok [`domcek2.svg`](/prog1/programs/domcek2.svg))
- [ďalšia ukážka](/prog1/programs/SVGukazka.html) (vytvorí obrázok [`SVGukazka.svg`](/prog1/programs/SVGukazka.svg) s rôznymi geometrickými útvarmi a textom)
- príklady programov na [prednáške 5](./P5)

## Vykresľovanie v SVG formáte

  - Ako prvé musíme vytvoriť súbor s obrázkom v SVG formáte s určitými
    rozmermi príkazom typu `Drawing drawing = drawingInit(150, 100, "hello.svg");`
  - Do obrázku môžeme kresliť príkazmi `drawRectangle`, `drawEllipse`,
    `drawLine`, `drawText`. Všetky tieto príkazy majú ako prvý parameter 
    premennú `drawing`, ktorá určuje, do ktorého obrázku sa má kresliť.
  - Ak chceme vykresľovať mnohouholníky, použijeme skupinu príkazov
    `drawPolygonStart`, `drawPolygonAddPoint` a `drawPolygonFinish`. Pomocou
    `drawPolygonStart` a `drawPolygonAddPoint` postupne vymenujeme vrcholy a
    pomocou `drawPolygonFinish` mnohouholník uzavrieme a vykreslíme.
  - Pomocou príkazov `setLineColorRGB` a `setFillColorRGB`
    nastavujeme farbu čiar a vyfarbovania. Farby zadávame troma
    číslami od 0 do 255 určujúcimi intenzitu červenej, zelenej a
    modrej. Príkazy `setLineColor` a `setFillColor` umožňujú nastaviť farbu
    názvom, napr. `"red"` ([zoznam mien
    farieb](https://www.w3.org/TR/SVG/types.html#ColorKeywords)). Príkaz `setNoFill` vypína 
    vyfarbovanie útvarov. Príkaz
    `setFontSize` nastavuje veľkosť písma a `setLineWidth` nastavuje
    hrúbku čiary.
  - Po vykreslení všetkých útvarov ukončíme vykresľovanie príkazom
    `drawingFinish(drawing);`. 

## Animácie

  - Príkaz `drawingWait` umožní pozastaviť vykresľovanie SVG súboru o zadaný
    čas v sekundách, takže jednotlivé útvary sa objavujú postupne.
  - Príkaz `drawingClear` schová všetky vykreslené útvary, takže môžeme kresliť
    znova na prázdnu plochu. Pred príkazom `drawingClear` je vhodné použiť
    `drawingWait`.
  - Príkaz `drawingHideItem` schová objekt (napr. čiaru) so zadaným číslom.
    Každý kresliaci príkaz vráti číslo práve vykresleného objektu,
    takže si ho stačí uložiť v nejakej premennej pre neskoršie mazanie.

## Príkazy pre korytnačiu grafiku

Namiesto vykresľovania obdĺžnikov, čiar a podobne na zadané súradnice môžeme
obrázok vytvoriť aj korytnačou grafikou. Na obrázku bude pohyb
korytnačky znázornený ako červený trojuholník a za sebou bude nechávať
čiernu čiaru.

  - Príkazom typu `Turtle turtle = turtleInit(200, 300, "domcek2.svg", 50, 250, 0);`
    vytvoríme SVG obrázok určitej veľkosti a s určitým menom súboru.
    Posledné tri čísla udávajú počiatočnú polohu korytnačky a jej
    natočenie.
  - Korytnačka si pamätá svoju polohu a natočenie na ploche. Príkaz
    `turtleForward` posunie korytnačku dopredu, príkazy `turtleTurnLeft` a
    `turtleTurnRight` ju otočia.
  - Príkaz `turtleSetSpeed` umožňuje zmeniť rýchlosť korytnačky, aby sme
    lepšie videli, ako sa postupne hýbe.
