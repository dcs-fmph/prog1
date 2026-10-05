---
title: Program domcek2.c
---

[Súbor na stiahnutie](./domcek2.c)

```c
#include "SVGdraw.h"
#include <math.h>

int main() {
  /* Vytvor korytnačku na súradniciach (50,250)
   * otočenú doprava na obrázku s rozmermi 200x300 pixelov,
   * ktorý bude uložený do súboru domcek2.svg. */
  Turtle turtle = turtleInit(200, 300, "domcek2.svg", 50, 250, 0);

  /* Nakresli dolnú čiaru a otoč sa smerom hore. */
  turtleForward(turtle, 100);
  turtleTurnLeft(turtle, 90);

  /* Nakresli pravú zvislú čiaru, hornú vodorovnú a ľavú zvislú. */
  turtleForward(turtle, 100);
  turtleTurnLeft(turtle, 90);
  turtleForward(turtle, 100);
  turtleTurnLeft(turtle, 90);
  turtleForward(turtle, 100);

  /* Otoč sa smerom na uhlopriečku.
     Dĺžku uhlopriečky vyrátame Pytagorovou vetou. */
  turtleTurnLeft(turtle, 135);
  double uhlopriecka = sqrt(100 * 100 + 100 * 100);
  turtleForward(turtle, uhlopriecka);

  /* Otoč sa smerom na pravú časť strechy.
   * Strecha bude rovnostranný trojuholník so stranou
   * dĺžky 100. */
  turtleTurnLeft(turtle, 75);
  turtleForward(turtle, 100);
  turtleTurnLeft(turtle, 120);
  turtleForward(turtle, 100);

  /* A posledná čiara - uhlopriečne prečiarknutie. */
  turtleTurnLeft(turtle, 75);
  turtleForward(turtle, uhlopriecka);

  /* Ukonči vypisovanie obrázka. */
  turtleFinish(turtle);
}
```
