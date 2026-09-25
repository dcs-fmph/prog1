#include "SVGdraw.h"
#include <math.h>

int main(void) {
  /* Vytvor korytnačku na súradniciach (50,250)
   * otočenú doprava na obrázku s rozmermi 200x300 pixelov,
   * ktorý bude uložený do súboru domcek2.svg. */
  Turtle turtle;
  Turtle_init(&turtle, 200, 300, "domcek2.svg", 50, 250, 0);

  /* Nakresli dolnú čiaru a otoč sa smerom hore. */
  Turtle_forward(&turtle, 100);
  Turtle_turnLeft(&turtle, 90);

  /* Nakresli pravú zvislú čiaru, hornú vodorovnú a ľavú zvislú. */
  Turtle_forward(&turtle, 100);
  Turtle_turnLeft(&turtle, 90);
  Turtle_forward(&turtle, 100);
  Turtle_turnLeft(&turtle, 90);
  Turtle_forward(&turtle, 100);

  /* Otoč sa smerom na uhlopriečku.
     Dĺžku uhlopriečky vyrátame Pytagorovou vetou. */
  Turtle_turnLeft(&turtle, 135);
  Turtle_forward(&turtle, sqrt(100 * 100 + 100 * 100));

  /* Otoč sa smerom na pravú časť strechy.
   * Strecha bude rovnostranný trojuholník so stranou
   * dĺžky 100. */
  Turtle_turnLeft(&turtle, 75);
  Turtle_forward(&turtle, 100);
  Turtle_turnLeft(&turtle, 120);
  Turtle_forward(&turtle, 100);

  /* A posledná čiara - uhlopriečne prečiarknutie. */
  Turtle_turnLeft(&turtle, 75);
  Turtle_forward(&turtle, sqrt(100 * 100 + 100 * 100));

  /* Ukonči vypisovanie obrázka. */
  Turtle_finish(&turtle);

  return 0;
}
