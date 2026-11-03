  - Pre jednoduchosť napíšeme iba verziu dynamického poľa pre typ `int`.
    Analogicky by sme postupovali pre iné typy.

Dynamické pole celých čísel budeme reprezentovať ako štruktúru typu
`dynArray`, ktorá bude pozostávať z nasledujúcich troch zložiek:

  - Zo smerníku `items` ukazujúceho na nultý prvok poľa (čiže vlastne
    pole samotné).
  - Z celočíselnej premennej `length`, v ktorej bude počet prvkov, ktoré
    sú aktuálne v poli.
  - Z celočíselnej premennej `size`, v ktorej bude veľkosť alokovanej
    pamäte pre pole `items`.

Štruktúra `dynArray` teda v sebe združuje pole aj jeho dĺžku, stačí
posielať jeden parameter.

Napíšeme niekoľko funkcií, pomocou ktorých budeme s dynamickými poľami
manipulovať.

  - Funkcia `void init(dynArray &a)` inicializuje dynamické pole `a`, v
    ktorom je nula prvkov. Funkcia ale alokuje nejaký malý objem pamäte
    (u nás dva prvky).
  - Funkcia `void add(dynArray &a, int x)` pridá do dynamického poľa `a`
    prvok s hodnotou `x`, čím počet prvkov vzrastie o jedna. V prípade
    potreby ešte predtým realokuje pamäť.
  - Funkcia `int get(dynArray a, int index)` vráti prvok dynamického
    poľa `a` na pozícii `index`. V prípade, že `index` nereprezentuje
    korektnú pozíciu prvku poľa (teda je menší ako `0` alebo väčší, než
    `a.length - 1`), ukončí vykonávanie programu pomocou `assert`.
  - Funkcia `void set(dynArray &a, int index, int x)` nastaví prvok
    dynamického poľa na pozícii `index` na hodnotou `x`. Ak `index`
    nereprezentuje korektnú pozíciu prvku poľa, ukončí vykonávanie
    programu pomocou `assert`.
  - Funkcia `int length(dynArray a)` vráti počet prvkov aktuálne
    uložených v dynamickom poli `a`.
  - Funkcia `void destroy(dynArray &a)` zlikviduje dynamické pole `a`
    (uvoľní pamäť).

Bez ohľadu na implementáciu samotného dynamického poľa už teda vieme
napísať kostru programu, ktorý ho využíva, napríklad na výpis vstupu
odzadu.
