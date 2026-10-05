---
title: Program domcek1.c
---

[Súbor na stiahnutie](./domcek1.c)

```c
#include "SVGdraw.h"

int main() {
  /* Vytvor obrázok s rozmermi 200x300 pixelov a
   * ulož ho do súboru domcek1.svg */
  Drawing drawing = drawingInit(200, 300, "domcek1.svg");

  /* Nakresli obdĺžnik (štvorec) s ľavým horným rohom v 50, 150
   * a šírkou aj dĺžkou 100. */
  drawRectangle(drawing, 50, 150, 100, 100);

  /* Prečiarkni štvorec dvomi čiarami po uhlopriečke. */
  drawLine(drawing, 50, 250, 150, 150);
  drawLine(drawing, 50, 150, 150, 250);

  /* Nakresli strechu ako dve čiary. */
  drawLine(drawing, 50, 150, 100, 50);
  drawLine(drawing, 150, 150, 100, 50);

  /* Ukonči vypisovanie obrázka. */
  drawingFinish(drawing);
}
```
