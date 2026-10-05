---
title: Program SVGukazka.c
---

[Súbor na stiahnutie](./SVGukazka.c)

```c
#include "SVGdraw.h"

int main() {
    /* Vytvor obrázok s rozmermi 200x300 pixelov a
     * ulož ho do súboru SVGukazka.svg */
    Drawing drawing = drawingInit(200, 300, "SVGukazka.svg");

    setFillColor(drawing, "yellow"); /* Nastav farbu výplne na žltú */
    setLineColor(drawing, "orange"); /* Nastav farbu čiar na oranžovú */
    setLineWidth(drawing, 5); /* Nastav hrúbku čiar na 5 */

    /* Nakresli mnohouholník. */
    drawPolygonStart(drawing, 50, 150);
    drawPolygonAddPoint(drawing, 100, 50);
    drawPolygonAddPoint(drawing, 150, 150);
    drawPolygonAddPoint(drawing, 150, 250);
    drawPolygonAddPoint(drawing, 50, 250);
    drawPolygonFinish(drawing);

    /* Nakresli elipsu (kruh) so stredom v 170, 70 a polomermi 20. */
    drawEllipse(drawing, 170, 70, 20, 20);

    setNoFill(drawing); /* Nastav výplň na priesvitnú */
    setLineColorRGB(drawing, 0, 0, 0); /* Nastav farbu čiar na čiernu */
    setLineWidth(drawing, 1); /* Nastav hrúbku čiar na 1 */

    /* Nakresli obdĺžnik (štvorec) s ľavým horným rohom v 50, 150
     * a šírkou aj dĺžkou 100. */
    drawRectangle(drawing, 50, 150, 100, 100);

    /* Prečiarkni štvorec dvomi čiarami po uhlopriečke. */
    drawLine(drawing, 50, 250, 150, 150);
    drawLine(drawing, 50, 150, 150, 250);

    /* Vypíš text prednastaveným fontom zarovnaný vľavo (left) a hore (top). */
    drawText(drawing, 50, 255, "SVGdraw example", "lt");
    /* Zmeniť veľkosť písma na 15. */
    setFontSize(drawing, 15);
    /* Vypíš text novým fontom zarovnaný na sted v oboch smeroch. */
    drawText(drawing, 100, 25, "SVGdraw example", "");

    /* Ukonči vypisovanie obrázka. */
    drawingFinish(drawing);
}
```
