#include "SVGdraw.h"

int main() {
  /* Vytvor obrázok s rozmermi 200x300 pixelov a
   * ulož ho do súboru domcek1.svg */
  SVGdraw drawing;
  SVGdraw_init(&drawing, 200, 300, "domcek1.svg");

  /* Nakresli obdĺžnik (štvorec) s ľavým horným rohom v 50, 150
   * a šírkou aj dĺžkou 100. */
  SVGdraw_drawRectangle(&drawing, 50, 150, 100, 100);

  /* Prečiarkni štvorec dvomi čiarami po uhlopriečke. */
  SVGdraw_drawLine(&drawing, 50, 250, 150, 150);
  SVGdraw_drawLine(&drawing, 50, 150, 150, 250);

  /* Nakresli strechu ako dve čiary. */
  SVGdraw_drawLine(&drawing, 50, 150, 100, 50);
  SVGdraw_drawLine(&drawing, 150, 150, 100, 50);

  /* Ukonči vypisovanie obrázka. */
  SVGdraw_finish(&drawing);
}
