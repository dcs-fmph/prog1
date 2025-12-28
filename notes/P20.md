---
title: Prednáška 20
---

* TOC
{:toc}

## Oznamy

Oznamy z minulej prednášky

Prednášky

  - Tento týždeň a budúci pondelok ešte prednášky v normálnom režime.
  - Budúcu stredu 10.12. v prvej polovici prednášky informácie k skúške
    a rady k skúškovému všeobecne, potom doberieme posledné povinné
    učivo.
  - Posledný týždeň semestra v pondelok 15.12. nepovinná prednáška o
    nepreberaných črtách jazykov C a C++, v stredu 17.12. prednáška
    pravdepodobne nebude.

Cvičenia a úlohy

  - Cvičenia bežia normálne každý utorok, cvičenia v stredu už iba 2x.
  - Dnes bonusová rozcvička na stromy
  - Tretí miniprojekt treba odovzdať do zajtra (4.12.) 22:00.

Semestrálny test

  - Budúcu stredu o 18:10 v posluchárňach A a B, trvanie 45 minút.
  - Viac informácií na stránke [Zimný semester, semestrálny
    test](./Zimný_semester,_semestrálny_test.md).

## Opakovanie z minulej prednášky

Aritmetické výrazy

  - Bežná infixová notácia, napr. (65 – 3\*5)/(2 + 3)
  - Postfixová notácia 65 3 5 \* - 2 3 + /
  - Prefixová notácia / - 65 \* 3 5 + 2 3
  - Prefixová a postfixová notácia nepotrebujú zátvorky
  - Aritmetické výrazy uložené ako strom
      - Vyhodnotenie výrazu
      - Výpis vo všetkých troch notáciách

Plán na dnes

  - Predspracovanie reťazca do postupnosti tokenov (hociktorá notácia)
  - Vyhodnotenie výrazu v postfixovej notácii
  - Konverzia postfixovej notácie na strom
  - Konverzia infixovej notácie na postfixovú

## Unárne mínus

  - Operátory +, \* a / sú vždy **binárne**, čo znamená, že sa aplikujú
    sa na dva operandy.
  - Operátor - môže byť binárny aj **unárny** (unárny znamená, že sa
    aplikuje na jeden operand).
      - Príklad s binárnym mínus: `1 - 2`.
      - Príklad s unárnym mínus: `2 * -(2 + 3)`.
  - Nevýhodou postfixovej a prefixovej notácie je, že bez zátvoriek v
    nich nie je možné rozpoznať binárne a unárne mínus.
      - Prefixový výraz `- - 2 3` by napríklad mohol zodpovedať ako
        výrazu `-2 - 3` aj výrazu `-(2 - 3)`.
  - Na vyriešenie tohto problému budeme na unárne mínus používať
    znamienko `~` (iba interne v našom programe, nepoužíva sa tak
    všeobecne). V infixových výrazoch budú unárne mínus automaticky
    rozpoznané a nahradené `~`.
  - Na minulej prednáške sme unárne - neuvažovali. Ako by ste ho
    dorobili do stromu?

## Úvod do predspracovania výrazu

Používateľ zadá výraz ako text v niektorej notácii. Aby sa nám s ním
lepšie pracovalo, prevedieme ho najskôr na postupnosť symbolov (angl.
**token**), pričom každý symbol bude buď číslo reprezentované v
premennej typu `double` alebo znak reprezentujúci operátor alebo
zátvorku, podobne ako na minulej prednáške.

Jednotlivé symboly budeme ukladať do záznamov typu `token`

```cpp
struct token {
    char op;   
    double val;
};
```

  - Ak štruktúra obsahuje číslo, `op` bude medzera a samotné číslo bude
    v položke `val`.
  - Ak štruktúra reprezentuje iný symbol, tento symbol bude v položke
    `op` a položka `val` sa nebude používať.

Postupnosť symbolov uložíme do štruktúry `tokenSequence`, ktorá obsahuje
pole položiek typu `token` a tiež koľko položiek bolo do poľa uložených.

```cpp
struct tokenSequence {
    token * items;  // pole tokenov
    int size;       // veľkosť alokovaného poľa
    int length;     // počet tokenov uložených v poli
};
```

Napríklad pre výraz `"(2.1+ 3.9) / 3"` vznikne nasledujúca dátová
štruktúra:

    tokenSequence:
    length: 7
    size: nejaké číslo >= 7
    items: pole s nasledovnými položkami
    
    token items[0]: op '(', val ?
    token items[1]: op ' ', val 2.1
    token items[2]: op '+', val ?
    token items[3]: op ' ', val 3.9
    token items[4]: op ')', val ?
    token items[5]: op '/', val ?
    token items[6]: op ' ', val 3

Predspracovanie výrazu si ukážeme na konci prednášky, je to práca s
reťazcami.

## Vyhodnocovanie aritmetických výrazov v postfixovej notácii

  - Budeme používať **zásobník**, do ktorého budeme vkladať **čísla**
    čakajúce na spracovanie.
  - Operátor má v postfixovom zápise obidva operandy pred sebou. Keď
    narazíme na operátor, jeho operandy sme už prečítali a spracovali.
    Ide navyše o **posledné dve** prečítané alebo vypočítané hodnoty.

Výraz budeme postupne čítať zľava doprava:

  - Keď narazíme na číslo, vložíme ho na zásobník.
  - Keď narazíme na operátor:
      - Vyberieme zo zásobníka jeho dva operandy.
      - Prvé z týchto čísel je pritom druhým operandom a druhé z nich je
        prvým operandom.
      - Vykonáme s týmito operandmi danú operáciu a výsledok tejto
        operácie vložíme naspäť na zásobník.
  - Pri unárnom mínus vyberáme zo zásobníka iba jeden operand.
  - Tento postup opakujeme, až kým neprídeme na koniec výrazu. V tom
    okamihu by sme mali mať na zásobníku jediný prvok, výslednú hodnotu
    výrazu.

Technická poznámka:

  - Keďže vo [výslednom
    programe](./#program-na-prácu-s-výrazmi) budeme
    potrebovať zásobníky čísel aj znakov, používame v ňom zásobník
    položiek typu `token`. Ak by sme však robili čisto vyhodnocovanie
    postfixovej notácie, stačil by nám zásobník s prvkami typu `double`.

**Cvičenie:**

  - Odsimulujme činnosť tohto algoritmu na našom vstupe `65 3 5 * - 2 3
    + /`
  - Aké všelijaké prípady môžu nastať, keď na vstupe nemáme správny
    výraz v postfixovej notácii?

<!-- end list -->

```cpp
typedef token dataType;
// Nasleduje kód pre zásobník tokenov
// ...


/** Funkcia aplikuje operátor uložený v opToken na čísla
* uložené v num1 a num2, výsledok uloží ako číslo do result.
* Unárny operátor sa aplikuje iba na num1. */
void applyOp(token opToken, token num1, token num2, token & result) {
    result.op = ' ';
    switch (opToken.op) {
    case '~':
        result.val = -num1.val;
        break;
    case '+':
        result.val = num1.val + num2.val;
        break;
    case '-':
        result.val = num1.val - num2.val;
        break;
    case '*':
        result.val = num1.val * num2.val;
        break;
    case '/':
        result.val = num1.val / num2.val;
        break;
    default: // iné operátory nepovoľujeme.
        assert(false);
    }
}

/** Funkcia vyhodnotí a vráti hodnotou výrazu v postfixovom tvare. */
double evaluatePostfix(tokenSequence & tokens) {
    // zásobník, do ktorého ukladáme čísla
    stack numberStack;
    init(numberStack);

    for (int i = 0; i < tokens.length; i++) {
        // aktuálny token zo vstupu
        token curToken = tokens.items[i];
        if (curToken.op == ' ') {
            // čísla rovno ukladáme na zásobník
            push(numberStack, curToken);
        } else {
            // spracovanie operátora
            token num1, num2, result;
            // najskôr vyberieme 1 alebo 2 čísla zo zásobníka
            if (curToken.op == '~') {
                num1 = pop(numberStack);
            } else {
                num2 = pop(numberStack);
                num1 = pop(numberStack);
            }
            // na operandy aplikujeme operátor
            applyOp(curToken, num1, num2, result);
            // výsledné číslo uložíme na zásobník
            push(numberStack, result);
        }
    }
    // zo zásobníka vyberieme výsledné číslo
    token result = pop(numberStack);
    // skontrolujeme, že zásobník je prázdny a výsledok je číslo
    assert(isEmpty(numberStack) && result.op == ' ');
    // uvoľníme pamäť zásobníka
    destroy(numberStack);
    return result.val;
}
```

## Vytvorenie stromu z postfixového výrazu

  - Predchádzajúcu funkciu na vyhodnotenie postfixového výraz môžeme
    jednoducho prepísať tak, aby namiesto vyhodnocovania výrazu
    konštruovala zodpovedajúci aritmetický strom.
  - Namiesto hodnôt jednotlivých podvýrazov stačí na zásobníku uchovávať
    korene stromov, ktoré tieto podvýrazy reprezentujú.
  - Aplikácii aritmetickej operácie bude zodpovedať spojenie dvoch
    podstromov do jedného stromu.
  - V programe nižšie nájdete verziu tejto funkcie, v ktorej nepoužívame
    postupnosť symbolov (tokenov), ale priamo spracovávame postfixový
    výraz vo forme reťazca.
      - Podobne by sme mohli postupovať aj vo funkcii na vyhodnotenie
        postfixového výrazu.

<!-- end list -->

```cpp
typedef treeNode *dataType;

/* Sem príde definícia štruktúry pre zásobník 
 * a funkcií poskytovaných zásobníkom. */

treeNode * postfixToTree(char * str) {
    // zásobník, do ktorého ukladáme korene podstromov
    stack treeStack;
    init(treeStack);

    for (int i = 0; i < tokens.length; i++) {
        // aktuálny token zo vstupu
        token curToken = tokens.items[i];
        if (curToken.op == ' ') {
            // vytvoríme list a uložíme na zásobník
            push(treeStack, createNum(curToken.val));
        } else {
            // spracovanie operátora
            // najskôr vyberieme 2 podstromy zo zásobníka
            treeNode * right = pop(treeStack);
            treeNode * left = pop(treeStack);
            // vytvoríme nový koreň,
            // ktorý bude ich rodičom a vložíme na zásobník
        treeNode * newRoot = createOp(currentToken.op,
                      left, right);
        push(treeStack, newRoot);
        }
    }
    // zo zásobníka vyberieme výsledný strom
    treeNode * result = pop(treeStack);
    // skontrolujeme, že zásobník je prázdny
    assert(isEmpty(treeStack));
    // uvoľníme pamäť zásobníka
    destroy(treeStack);
    return result;
}
```

## Prevod výrazu z infixovej do postfixovej notácie

  - Pre bežnú prax je dôležitejšie vyhodnocovanie výrazov v klasickej
    infixovej notácii.
  - Túto úlohu teraz vyriešime tak, že napíšeme funkciu, ktorá preloží
    aritmetický výraz z infixovej do postfixovej notácie.
  - Následne ho môžeme vyhodnotiť algoritmom popísaným vyššie.

### Popis algoritmu

Uvažujme najprv výrazy bez zátvoriek a bez unárnych mínusov.

  - Pozostávajú teda z čísel a binárnych operátorov `+, -, *, /`, kde
    `*` a `/` majú vyššiu prioritu ako `+` a `-`.
  - Všetky tieto operátory sú navyše zľava asociatívne, t.j. napr. `30
    / 6 / 5` je to isté ako `(30 / 6) / 5`.

Na prevod takéhoto výrazu do postfixového tvaru ním stačí prejsť zľava
doprava a všimnúť si dve skutočnosti:

  - Poradie jednotlivých čísel v postfixovom výraze je rovnaké, ako v
    pôvodnom infixovom výraze.
  - Napríklad výraz `1 + 2 - 3 * 4 + 5` má postfixový tvar `1 2 + 3 4 *
    - 5 +`.
  - Pri prechádzaní vstupným infixovým výrazom budeme teda čísla priamo
    pridávať do výstupného postfixového výrazu.
  - Každý operátor treba presunúť spomedzi jeho dvoch operandov za jeho
    druhý operand.
  - Ak teda vo vstupnom infixovom výraze narazíme na operátor, nepridáme
    ho hneď do výstupného výrazu, ale uložíme ho pre neskoršie pridanie
    na správnej pozícii.
  - Uložený operátor treba vypísať za jeho druhým operandom. Ak pritom
    aj samotný operand obsahuje nejaké ďalšie operátory, určite musia
    byť vypísané skôr. Operátory teda budeme ukladať na zásobník.
  - Keď vo vstupnom infixovom výraze narazíme na operátor, je možné, že
    tesne pred ním končí operand jedného alebo niekoľkých operátorov
    uložených na zásobníku. Vďaka ľavej asociatívnosti pritom ide o
    práve všetky operátory na vrchu zásobníka, ktoré majú vyššiu alebo
    rovnakú prioritu, ako nájdený operátor. Všetky tieto operátory teda
    postupne vyberieme zo zásobníka a vypíšeme ich do výstupného
    reťazca. Až následne na zásobník vložíme nájdený operátor.
  - Na konci vstupného reťazca vypíšeme všetky operátory, ktoré zostali
    na zásobníku.

Z technických dôvodov budeme na spodku zásobníka uchovávať „umelé dno”
`#`, ktoré budeme chápať ako symbol s nižšou prioritou ako všetky
operátory.

  - Situáciu, keď pri vyberaní operátorov zo zásobníka narazíme na jeho
    dno tak budeme môcť riešiť konzistentne so situáciou, keď narazíme
    na operátor s nižšou prioritou: v oboch prípadoch chceme s vyberaním
    prestať.

Na vstupnom výraze `1 + 2 - 3 * 4 + 5` bude práve popísaný algoritmus
pracovať nasledovne:

    Vstupný symbol  Výstupný výraz    Zásobník (dno vľavo) 
    -------------------------------------------------------------------------------------------------------
               1                       #            vypíš 1 
                    1                  #
    
               +    1                  #            # má nižšiu prioritu ako +, nevyberaj ho
                    1                  # +          vlož + na zásobník
    
               2    1                  # +          vypíš 2
                    1 2                # + 
    
               -    1 2                # +          + má rovnakú prioritu ako -, vyber + a vypíš
                    1 2 +              #            # má nižšiu prioritu ako -, nevyberaj ho
                    1 2 +              #            vlož - na zásobník
                    1 2 +              # -   
    
               3    1 2 +              # -          vypíš 3
                    1 2 + 3            # - 
    
               *    1 2 + 3            # -          - má nižšiu prioritu ako *, nevyberaj ho
                    1 2 + 3            # - *        vlož * na zásobník
    
               4    1 2 + 3            # - *        vypíš 4
                    1 2 + 3 4          # - *                     
    
               +    1 2 + 3 4          # - *        * má vyššiu prioritu ako +, vyber * a vypíš
                    1 2 + 3 4 *        # -          - má rovnakú prioritu ako +, vyber - a vypíš
                    1 2 + 3 4 * -      #            # má nižšiu prioritu ako +, nevyberaj ho
                    1 2 + 3 4 * -      # +          vlož - na zásobník
    
               5    1 2 + 3 4 * -      # +          vypíš 5
                    1 2 + 3 4 * - 5    # +                 
    
        [koniec]    1 2 + 3 4 * - 5    # +          vyber operátory na zásobníku a vypíš
                    1 2 + 3 4 * - 5 +  #            <-- VÝSLEDNÝ POSTFIXOVÝ VÝRAZ

Pridanie zátvoriek:

  - Keď vo vstupnom infixovom reťazci narazíme na ľavú zátvorku, vložíme
    ju do zásobníka. Podobne ako pri `#` ju budeme považovať za symbol s
    nižšou prioritou, než všetky binárne operátory. To má dva dôsledky:
      - Pri vkladaní zátvorky teda nevyhadzujeme operátory zo zásobníka
      - Operátory vo vnútri zátvorky nespôsobia jej vyhodenie ani
        vyhodenie symbolov pod ňou
  - Keď narazíme na pravú zátvorku, potrebujeme vypísať všetky doposiaľ
    nevypísané operátory uzatvorené touto zátvorkou. Preto vyberieme a
    vypíšeme na výstup všetky operátory zo zásobníka až po prvú ľavú
    zátvorku (ktorú zo zásobníka taktiež vyberieme).

Pridanie unárneho mínus:

  - Unárne mínus má vyššiu prioritu ako binárne operátory.
    Predpokladáme, že ho máme zapísané ako `~`.
  - Je však sprava asociatívne, t.j. `--2` je to isté ako `-(-2)` a v
    postfixovom tvare to bude `2 ~ ~`.
  - Preto ak je aktuálny operátor unárne mínus `~`, nevyhadzujeme iné
    unárne mínus zo zásobníka. Toto je v programe dosiahnuté tak, že
    nové unárne mínus ("pravé") má vyššiu prioritu ako to, čo už je na
    zásobníku ("ľavé").

### Implementácia

```cpp
/** Pomocná funkcia, ktorá vráti prioritu operátora.
 * Argument right určuje, či ide o pravý z dvoch porovnávaných operátorov */
int priority(char op, bool right) {
    if (op == '#' || op == '(') return 0;
    if (op == '-' || op == '+') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '~' && !right) return 3;
    if (op == '~' && right) return 4;
    assert(false); // sem by sme sa nemali dostať
}

/** Skonvertuje infixový výraz infix do postfixovej formy */
void infixToPostfix(tokenSequence & infix, tokenSequence & postfix) {
    // inicializuje výslednú postupnosť tokenov
    init(postfix, infix.length);

    // vytvoríme zásobník operátorov a na spodok dáme #
    stack opStack;
    init(opStack);
    token curToken = {'#', 0};
    push(opStack, curToken);

    for (int i = 0; i < infix.length; i++) {
        // aktuálny token zo vstupu
        curToken = infix.items[i];
        if (curToken.op == ' ') {
            // čísla rovno skopírujeme do výstupu
            addToken(postfix, curToken);
        } else if (curToken.op == '(') {
            // začiatok zátvorky uložíme na zásobník
            push(opStack, curToken);
        } else if (curToken.op == ')') {
            // koniec zátvorky:
            // na výstup pridáme zo zásobníka operátory,
            // ktoré boli v zátvorke
            token popped = pop(opStack);
            while (popped.op != '(') {
                addToken(postfix, popped);
                popped = pop(opStack);
            }
        } else {
            // spracovanie operátora:
            // na výstup pridáme zo zásobníka operátory s vyššou prioritou
            int p = priority(curToken.op, true);
            while (priority(peek(opStack).op, false) >= p) {
                token popped = pop(opStack);
                addToken(postfix, popped);
            }
            // aktuálny operátor dáme na zásobník
            push(opStack, curToken);
        }
    }

    // zvyšné operátory presunieme zo zásobníka na výstup
    while (peek(opStack).op != '#') {
        token popped = pop(opStack);
        addToken(postfix, popped);
    }
    destroy(opStack);
}
```

*Cvičenie*: Rozšírte program vyššie o operáciu umocňovania `^` s
prioritou vyššou ako `*` (dajte pozor na fakt, že umocňovanie je na
rozdiel od operácií `+, -, *, /` sprava asociatívne).

## Predspracovanie výrazu

Preklad výrazu na postupnosť symbolov realizuje funkcia `tokenize`.

  - Na načítanie čísla používame funkciu `sscanf`, ktorá vyzerá podobne
    ako `scanf`, ale načítava zo zadaného reťazca.
      - Ako reťazec zadáme `&(str[strPos])`, čo spôsobí, že sa začne
        načítavať od pozície `strPos`, mohli by sme písať aj
        `str+strPos`.
      - Formátovací znak `%n` nám do premennej `skip` uloží počet
        znakov, ktoré sa pri načítaní čísla použili, o tento počet potom
        posunieme premennú `strPos`.
  - Kód token `newToken = {str[strPos], 0}` inicializuje položku `op` na
    znak `str[strPos]` a položku `val` na nulu.
  - Pomocné funkcie `init` a `addToken` pracujú s postupnosťou symbolov,
    nájdete ich v [programe na konci
    prednášky](./#program-na-prácu-s-výrazmi).

<!-- end list -->

```cpp
void tokenize(char * str, tokenSequence & tokens) {
    init(tokens, strlen(str));  // inicializujeme prázdnu postupnosť

    int strPos = 0;  // pozícia v rámci reťazca
    while (str[strPos] != 0) {  // kým nie sme na konci str
        if (isspace(str[strPos])) {  // preskakujeme biele znaky
            strPos++;
        } else if (isdigit(str[strPos]) || str[strPos] == '.') {
            // keď nájdeme cifru alebo bodku (začiatok čísla)
            double val;
            int skip;
            // načítame toto číslo pomocou sscanf, 
            // do skip uložíme počet znakov čísla
            sscanf(&(str[strPos]), "%lf%n", &val, &skip);
            // vytvoríme a uložíme token
            token newToken = {' ', val};
            addToken(tokens, newToken);
            // preskočíme všetky znaky čísla
            strPos += skip;
        } else {
            // spracovanie zátvoriek alebo operátora
            assert(strchr("+-/*()~", str[strPos]) != NULL);
            // vytvoríme a uložíme token
            token newToken = {str[strPos], 0};
            addToken(tokens, newToken);
            strPos++;
        }
    }
}
```

### Predspracovanie unárneho mínus

  - Pred prevodom infixového výrazu do postfixového tvaru potrebujeme v
    infixovom výraze nahradiť unárne mínus znakom `~`.
  - Robí to funkcia `fixUnaryMinus`.
  - Mínus je v korektnom infixovom výraze unárne práve vtedy, keď
    nenasleduje za číslom, ani za pravou zátvorkou, čo testuje pomocná
    funkcia `isOperand`.

<!-- end list -->

```cpp
/** Pomocná funkcia, ktorá vráti, či token je koncom operandu v infixovej notácii */
bool isOperand(token curToken) {
    return curToken.op == ' ' || curToken.op == ')';
}

/** Funkcia, ktorá v infixovom výraze zmení unárne mínus na ~ */
void fixUnaryMinus(tokenSequence & infix) {
    for (int i = 0; i < infix.length; i++) {
        if(infix.items[i].op == '-' 
           && (i == 0 || !isOperand(infix.items[i - 1]))) {
            infix.items[i].op = '~';
        }
    }
}
```

## Záverečné poznámky

  - Infixové výrazy vieme vyhodnotiť tak, že najskôr ich prevedieme na
    postfixové a tie potom vyhodnotíme.
      - Pri vyhodnocovaní postfixovej formy používame zásobník čísel
        (operandov).
      - Pri prevode z infixovej formy na postfixovú používame zásobník
        operátorov.
  - Obidva procesy sa dajú vykonávať aj súčasne (počas prechodu výrazom
    používame jeden zásobník čísel a jeden zásobník operátorov).
      - Toto je pre zaujímavosť implementované vo funkcii
        `evaluateInfix` v [priloženom
        programe](./#program-na-prácu-s-výrazmi).
  - Všeobecnejšie a elegantnejšie prístupy k analýze a vyhodnocovaniu
    výrazov ale aj celých programov uvidíte na predmete Kompilátory
    (Mgr. štúdium), ktorý využíva poznatky z predmetu Formálne jazyky a
    automaty (semester 2Z).
  - Videli sme aj algoritmus na konverziu postfixového výrazu na strom,
    ktorý pre zmenu potrebuje zásobník smerníkov na uzly stromu. Inak sa
    podobá na vyhodnocovanie postfixového výrazu.

### Typ dát na zásobníku

V našom programe, ktorý pracuje s infixovou a postfixovou notáciou,
potrebujeme zásobník čísel aj zásobník znakov.

  - Vyriešili sme to tým, že na zásobník dávame položky typu `token`,
    ktoré obsahujú znak aj číslo.
  - Nie je to však príliš elegantné a plytve pamäťou na nepotrebné
    údaje.
  - Druhá možnosť je dvakrát implementovať celý zásobník pre rôzne typy
    dát, kopírovanie a menenie kódu je však tiež niečo, čomu sa chceme
    vyhnúť.
  - Najlepšie by bolo použiť techniku generického programovania, ktorá
    je k dispozícii vo veľa jazykoch, vrátane C++, ale nie C. Touto
    technikou vieme zásobník implementovať raz a použiť s rôznymi typmi.
    Ukážku tejto techniky uvidíme na poslednej prednáške a viac sa
    dozviete na Programovaní (2) v letnom semestri.

Na konci prednášky sme ešte prebrali výšku stromov z [prednášky
19](./P19.md).

## Program na prácu s výrazmi

```cpp
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;

/** Štruktúra pre jednu súčasť výrazu: znamienko alebo číslo */
struct token {
    char op;     // znamienko alebo medzera, ak ide o číslo
    double val;  // číselná hodnota, ak je op medzera
};

/** Štruktúra pre postupnosť tokenov */
struct tokenSequence {
    token * items;  // pole tokenov
    int size;       // veľkosť alokovaného poľa
    int length;     // počet tokenov uložených v poli
};

/** Funkcia inicializuje prázdnu postupnosť tokenov
pričom alokuje pole požadovanej veľkosti. */
void init(tokenSequence & tokens, int size) {
    tokens.items = new token[size];
    tokens.size = size;
    tokens.length = 0;
}

/** Funkcia do postupnosti tokenov pridá nový token. */
void addToken(tokenSequence & tokens, token & newToken) {
    assert(tokens.length < tokens.size);
    tokens.items[tokens.length] = newToken;
    tokens.length++;
}

/** Funkcia odalokuje pamäť alokovanú pre postupnosť tokenov */
void destroy(tokenSequence & tokens) {
    delete[] tokens.items;
}

/** Funkcia vypíše postupnosť tokenov, každý v hranatých zátvorkách. */
void printTokens(tokenSequence & tokens) {
    for (int i = 0; i < tokens.length; i++) {
        token curToken = tokens.items[i];
        if (curToken.op == ' ') {
            printf(" [val %g]", curToken.val);
        } else {
            printf(" [op %c]", curToken.op);
        }
    }
    printf("\n");
}

/** Funkcia vypíše postupnosť tokenov ako aritmetický výraz. */
void printTokenExpression(tokenSequence & tokens) {
    for (int i = 0; i < tokens.length; i++) {
        token curToken = tokens.items[i];
        if (curToken.op == ' ') {
            printf(" %g", curToken.val);
        } else {
            printf(" %c", curToken.op);
        }
    }
    printf("\n");
}

/** Funkcia konvertuje výraz z reťazca na postupnosť tokenov. */
void tokenize(char * str, tokenSequence & tokens) {
    init(tokens, strlen(str));  // inicializujeme prázdnu postupnosť

    int strPos = 0;  // pozícia v rámci reťazca
    while (str[strPos] != 0) {  // kým nie sme na konci str
        if (isspace(str[strPos])) {  // preskakujeme biele znaky
            strPos++;
        } else if (isdigit(str[strPos]) || str[strPos] == '.') {
            // keď nájdeme cifru alebo bodku (začiatok čísla)
            double val;
            int skip;
            // načítame toto číslo pomocou sscanf, do skip uložíme počet znakov čísla
            sscanf(&(str[strPos]), "%lf%n", &val, &skip);
            // vytvoríme a uložíme token
            token newToken = {' ', val};
            addToken(tokens, newToken);
            // preskočíme všetky znaky čísla
            strPos += skip;
        } else {
            // spracovanie zátvoriek alebo operátora
            assert(strchr("+-/*()~", str[strPos]) != NULL);
            // vytvoríme a uložíme token
            token newToken = {str[strPos], 0};
            addToken(tokens, newToken);
            strPos++;
        }
    }
}

// Nasleduje kód pre zásobník tokenov
typedef token dataType;

/** Uzol spájaného zoznamu pre zásobník */
struct node {
    dataType data; // dáta uložené v uzle
    node * next;   // smerník na ďalší uzol zoznamu
};

/** Štruktúra pre zásobník implementovaný pomocou zoznamu*/
struct stack {
    node * top; // Smernik na vrch zasobníka  alebo NULL
};

/** Funkcia inicializuje prázdny zásobník */
void init(stack & s) {
    s.top = NULL;
}

/** Funkcia zistí, či je zásobník prázdny */
bool isEmpty(stack & s) {
    return s.top == NULL;
}

/** Funkcia pridá prvok item na vrch zásobníka */
void push(stack & s, dataType item) {
    node * tmp = new node;
    tmp->data = item;
    tmp->next = s.top;
    s.top = tmp;
}

/** Funkcia odoberie prvok z vrchu zasobnika a vráti ho */
dataType pop(stack & s) {
    assert(!isEmpty(s));
    dataType result = s.top->data;
    node * tmp = s.top->next;
    delete s.top;
    s.top = tmp;
    return result;
}

/** Funkcia vráti prvok na vrchu zásobníka, ale nechá ho v zásobníku */
dataType peek(stack & s) {
    assert(!isEmpty(s));
    return s.top->data;
}

/** Funkcia uvoľní pamäť zásobníka */
void destroy(stack & s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

/** Funkcia aplikuje operátor uložený v opToken na čísla
* uložené v num1 a num2, výsledok uloží ako číslo do result.
* Unárny operátor sa aplikuje iba na num1. */
void applyOp(token opToken, token num1, token num2, token & result) {
    result.op = ' ';
    switch (opToken.op) {
    case '~':
        result.val = -num1.val;
        break;
    case '+':
        result.val = num1.val + num2.val;
        break;
    case '-':
        result.val = num1.val - num2.val;
        break;
    case '*':
        result.val = num1.val * num2.val;
        break;
    case '/':
        result.val = num1.val / num2.val;
        break;
    default: // iné operátory nepovoľujeme.
        assert(false);
    }
}

/** Funkcia vyhodnotí a vráti hodnotou výrazu v postfixovom tvare. */
double evaluatePostfix(tokenSequence & tokens) {
    // zásobník, do ktorého ukladáme čísla
    stack numberStack;
    init(numberStack);

    for (int i = 0; i < tokens.length; i++) {
        // aktuálny token zo vstupu
        token curToken = tokens.items[i];
        if (curToken.op == ' ') {
            // čísla rovno ukladáme na zásobník
            push(numberStack, curToken);
        } else {
            // spracovanie operátora
            token num1, num2, result;
            // najskôr vyberieme 1 alebo 2 čísla zo zásobníka
            if (curToken.op == '~') {
                num1 = pop(numberStack);
            } else {
                num2 = pop(numberStack);
                num1 = pop(numberStack);
            }
            // na operandy aplikujeme operátor
            applyOp(curToken, num1, num2, result);
            // výsledné číslo uložíme na zásobník
            push(numberStack, result);
        }
    }
    // zo zásobníka vyberieme výsledné číslo
    token result = pop(numberStack);
    // skontrolujeme, že zásobník je prázdny a výsledok je číslo
    assert(isEmpty(numberStack) && result.op == ' ');
    // uvoľníme pamäť zásobníka
    destroy(numberStack);
    return result.val;
}

/** Pomocná funkcia, ktorá vráti prioritu operátora.
* Argument right určuje, či ide o pravý z dvoch porovnávaných operátorov */
int priority(char op, bool right) {
    if (op == '#' || op == '(') return 0;
    if (op == '-' || op == '+') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '~' && !right) return 3;
    if (op == '~' && right) return 4;
    assert(false); // sem by sme sa nemali dostať
}

/** Skonvertuje infixový výraz infix do postfixovej formy */
void infixToPostfix(tokenSequence & infix, tokenSequence & postfix) {
    // inicializuje výslednú postupnosť tokenov
    init(postfix, infix.length);

    // vytvoríme zásobník operátorov a na spodok dáme #
    stack opStack;
    init(opStack);
    token curToken = {'#', 0};
    push(opStack, curToken);

    for (int i = 0; i < infix.length; i++) {
        // aktuálny token zo vstupu
        curToken = infix.items[i];
        if (curToken.op == ' ') {
            // čísla rovno skopírujeme do výstupu
            addToken(postfix, curToken);
        } else if (curToken.op == '(') {
            // začiatok zátvorky uložíme na zásobník
            push(opStack, curToken);
        } else if (curToken.op == ')') {
            // koniec zátvorky:
            // na výstup pridáme zo zásobníka operátory,
            // ktoré boli v zátvorke
            token popped = pop(opStack);
            while (popped.op != '(') {
                addToken(postfix, popped);
                popped = pop(opStack);
            }
        } else {
            // spracovanie operátora:
            // na výstup pridáme zo zásobníka operátory s vyššou prioritou
            int p = priority(curToken.op, true);
            while (priority(peek(opStack).op, false) >= p) {
                token popped = pop(opStack);
                addToken(postfix, popped);
            }
            // aktuálny operátor dáme na zásobník
            push(opStack, curToken);
        }
    }

    // zvyšné operátory presunieme zo zásobníka na výstup
    while (peek(opStack).op != '#') {
        token popped = pop(opStack);
        addToken(postfix, popped);
    }
    destroy(opStack);
}

/** Pomocná funkcia, ktorá zo zásobníka vyberie
* jedno alebo dve čísla, aplikuje na nich operátor a výsledok uloží na zásobník. */
void processOp(stack & numberStack, token curToken) {
    token num1, num2, result;
    // najskôr vyberieme 1 alebo 2 čísla zo zásobníka
    if (curToken.op == '~') {
        num1 = pop(numberStack);
    } else {
        num2 = pop(numberStack);
        num1 = pop(numberStack);
    }
    // na operandy aplikujeme operátor
    applyOp(curToken, num1, num2, result);
    // výsledné číslo uložíme na zásobník
    push(numberStack, result);
}

/** Spočíta hodnotu výrau v infixovej forme,
 * kombinuje infixToPostfix a evaluatePostfix */
double evaluateInfix(tokenSequence & infix) {
    // zásobník, do ktorého ukladáme čísla
    stack numberStack;
    init(numberStack);

    // vytvoríme zásobník operátorov a na spodok dáme #
    stack opStack;
    init(opStack);
    token curToken = {'#', 0};
    push(opStack, curToken);

    for (int i = 0; i < infix.length; i++) {
        // aktuálny token zo vstupu
        curToken = infix.items[i];
        if (curToken.op == ' ') {
            // čísla ukladáme na zásobník
            push(numberStack, curToken);
        } else if (curToken.op == '(') {
            // začiatok zátvorky uložíme na zásobník
            push(opStack, curToken);
        } else if (curToken.op == ')') {
            // koniec zátvorky:
            // spracujeme zo zásobníka operátory,
            // ktoré boli v zátvorke
            token popped = pop(opStack);
            while (popped.op != '(') {
                processOp(numberStack, popped);
                popped = pop(opStack);
            }
        } else {
            // spracovanie operátora:
            // spracujeme zo zásobníka operátory s vyššou prioritou
            int p = priority(curToken.op, true);
            while (priority(peek(opStack).op, false) >= p) {
                token popped = pop(opStack);
                processOp(numberStack, popped);
            }
            // aktuálny operátor dáme na zásobník
            push(opStack, curToken);
        }
    }

    // spracujeme zvyšné operátory zo zásobníka
    while (peek(opStack).op != '#') {
        token popped = pop(opStack);
        processOp(numberStack, popped);
    }
    destroy(opStack);

    // zo zásobníka vyberieme výsledné číslo
    token result = pop(numberStack);
    // skontrolujeme, že ásobník je prázdny a výsledok je číslo
    assert(isEmpty(numberStack) && result.op == ' ');
    // uvoľníme pamäť zásobníka čísel
    destroy(numberStack);
    return result.val;
}

/** Pomocná funkcia, ktorá vráti, či token je koncom operandu v infixovej notácii */
bool isOperand(token curToken) {
    return curToken.op == ' ' || curToken.op == ')';
}

/** Funkcia, ktorá v infixovom výraze zmení unárne mínus na ~ */
void fixUnaryMinus(tokenSequence & infix) {
    for (int i = 0; i < infix.length; i++) {
        if (infix.items[i].op == '-'
                && (i == 0 || !isOperand(infix.items[i - 1]))) {
            infix.items[i].op = '~';
        }
    }
}

/** Hlavný program načítava a vykonáva postupnosť príkazov tokenize, postfix, infix a end.
 * Príkaz tokenize tokenizuje a vypíše vstupný výraz.
 * Príkaz postfix načíta výraz v postfixovom formáte a vypíše jeho hodnotu.
 * Príkaz infix načíta výraz v infixovom formáte, upraví v ňom unárne - na ~.
 * prevedie ho do postfixového formátu, vyhodnotí postfixový výraz a naopokon
 * vyhodnotí aj priamo infixovú formu výrazu.  */
int main() {
    const int maxLine = 100;
    char command[maxLine];
    char expression[maxLine];

    while (true) {
        int ret = scanf("%s", command);
        if (ret < 1 || strcmp(command, "end") == 0) {
            break;
        } else if (strcmp(command, "tokenize") == 0) {
            fgets(expression, maxLine, stdin);
            tokenSequence tokens;
            tokenize(expression, tokens);
            printf(" tokens:");
            printTokens(tokens);
            destroy(tokens);
        } else if (strcmp(command, "postfix") == 0) {
            fgets(expression, maxLine, stdin);
            tokenSequence postfix;
            tokenize(expression, postfix);
            double value = evaluatePostfix(postfix);
            printf(" value: %g\n", value);
            destroy(postfix);
        }
        if (strcmp(command, "infix") == 0) {
            fgets(expression, maxLine, stdin);
            tokenSequence infix;
            tokenize(expression, infix);
            fixUnaryMinus(infix);
            printf(" infix:");
            printTokenExpression(infix);
            tokenSequence postfix;
            infixToPostfix(infix, postfix);
            printf(" postfix:");
            printTokenExpression(postfix);
            double value = evaluatePostfix(postfix);
            printf(" value of postfix: %g\n", value);
            double value2 = evaluateInfix(infix);
            printf(" value of infix: %g\n", value2);
            destroy(infix);
            destroy(postfix);
        }
    }
}
```

## Program pre aritmetické výrazy ako stromy

  - Rozlišujeme `treeDataType` (`token`) a `stackDataType` (`treeNode`).
  - Načíta výraz v postfixovej notácii, konvertuje na strom, ten potom
    vyhodnotí a vypíše vo všetkých troch notáciách.
  - Nepodporuje unárne mínus, ale dalo by sa dorobiť.

<!-- end list -->

```cpp
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;

struct token {
  char op;      // operátor alebo medzera
  double val;   // hodnota ak op je medzera
};
// typ pre dáta uložené v uzloch stromu
typedef token treeDataType;


// uzol binárneho stromu
struct treeNode {

    // data uložené v uzle
    treeDataType data;

    // smerníky na podstromy
    treeNode * left, * right;
};

/** Funkcia vráti nový uzol pre operátor */
treeNode * createOp(char op, treeNode * left, treeNode * right) {
    treeNode * v = new treeNode;
    v->left = left;
    v->right = right;
    v->data.op = op;
    return v;
}

/** Funkcia vráti nový uzol pre číslo */
treeNode * createNum(double val) {
    treeNode * v = new treeNode;
    v->left = NULL;
    v->right = NULL;
    v->data.op = ' ';
    v->data.val = val;
    return v;
}


// Nasleduje kód pre zásobník uzlov stromu
typedef treeNode * stackDataType;

/** Uzol spájaného zoznamu pre zásobník */
struct node {
    stackDataType data; // dáta uložené v uzle
    node * next;   // smerník na ďalší uzol zoznamu
};

/** Štruktúra pre zásobník implementovaný pomocou zoznamu*/
struct stack {
    node * top; // Smernik na vrch zasobníka  alebo NULL
};

/** Funkcia inicializuje prázdny zásobník */
void init(stack & s) {
    s.top = NULL;
}

/** Funkcia zistí, či je zásobník prázdny */
bool isEmpty(stack & s) {
    return s.top == NULL;
}

/** Funkcia pridá prvok item na vrch zásobníka */
void push(stack & s, stackDataType item) {
    node * tmp = new node;
    tmp->data = item;
    tmp->next = s.top;
    s.top = tmp;
}

/** Funkcia odoberie prvok z vrchu zasobnika a vráti ho */
stackDataType pop(stack & s) {
    assert(!isEmpty(s));
    stackDataType result = s.top->data;
    node * tmp = s.top->next;
    delete s.top;
    s.top = tmp;
    return result;
}

/** Funkcia vráti prvok na vrchu zásobníka, ale nechá ho v zásobníku */
stackDataType peek(stack & s) {
    assert(!isEmpty(s));
    return s.top->data;
}

/** Funkcia uvoľní pamäť zásobníka */
void destroy(stack & s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

/** Funkcia konvertuje výraz v postfixovom tvare na strom */
treeNode * postfixToTree(char * str) {
    // zásobník, do ktorého ukladáme korene podstromov
    stack treeStack;
    init(treeStack);

    int strPos = 0;  // pozícia v rámci reťazca
    while (str[strPos] != 0) {  // kým nie sme na konci str
        if (isspace(str[strPos])) {  // preskakujeme biele znaky
            strPos++;
        } else if (isdigit(str[strPos]) || str[strPos] == '.') {
            // keď nájdeme cifru alebo bodku (začiatok čísla)
            double val;
            int skip;
            // načítame toto číslo pomocou sscanf,
            // do skip uložíme počet znakov čísla
            sscanf(&(str[strPos]), "%lf%n", &val, &skip);
            // preskočíme všetky znaky čísla
            strPos += skip;

            // vytvoríme list a uložíme na zásobník
            push(treeStack, createNum(val));
        } else {
            // spracovanie operátora
            assert(strchr("+-/*", str[strPos]) != NULL);
            treeNode * left, * right;
            // najskôr vyberieme 2 podstromy zo zásobníka
            // vytvoríme nový koreň,
            // ktorý bude ich rodičom a vložíme na zásobník
            right = pop(treeStack);
            left = pop(treeStack);
            push(treeStack, createOp(str[strPos], left, right));
            strPos++;
        }
    }
    // zo zásobníka vyberieme výsledný strom
    treeNode * result = pop(treeStack);
    // skontrolujeme, že zásobník je prázdny
    assert(isEmpty(treeStack));
    // uvoľníme pamäť zásobníka
    destroy(treeStack);
    return result;
}

/** Funkcia spočíta hodnotu výrazu reprezentovaného stromom */
double evaluateTree(treeNode * root) {
    assert(root != NULL);
    if (root->data.op == ' ') {
        return root->data.val;
    } else {
        double valLeft = evaluateTree(root->left);
        double valRight = evaluateTree(root->right);
        switch (root->data.op) {
        case '+':
            return valLeft + valRight;
            break;
        case '-':
            return valLeft - valRight;
            break;
        case '*':
            return valLeft * valRight;
            break;
        case '/':
            return valLeft / valRight;
            break;
        default:
            assert(false);
            break;
        }
    }
    return 0; // realne nedosiahnutelny prikaz
}

/** Funkcia uvoľní pamäť daného stromu */
void destroyTree(treeNode * root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

/** Funkcia vypíše aritmetický výraz v inorder poradí */
void printInorder(treeNode * root) {
    if (root->data.op == ' ') {
        printf("%g", root->data.val);
    } else {
        printf("(");
        printInorder(root->left);
        printf(" %c ", root->data.op);
        printInorder(root->right);
        printf(")");
    }
}

/** Funkcia vypíše aritmetický výraz v preorder poradí */
void printPreorder(treeNode * root) {
    if (root->data.op == ' ') {
        printf("%g ", root->data.val);
    } else {
        printf("%c ", root->data.op);
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

/** Funkcia vypíše aritmetický výraz v postorder poradí */
void printPostorder(treeNode * root) {
    if (root->data.op == ' ') {
        printf("%g ", root->data.val);
    } else {
        printPostorder(root->left);
        printPostorder(root->right);
        printf("%c ", root->data.op);
    }
}


int main() {
    // načítame postfixový výraz do reťazca
    const int maxLine = 100;
    char postfix[maxLine];
    fgets(postfix, maxLine, stdin);
    // výraz konvertujeme na strom
    treeNode * root = postfixToTree(postfix);
    // spočítame hodnotu výrazu
    double value = evaluateTree(root);
    printf(" value: %g\n", value);
    // vypíšeme vo všetkých troch notáciách
    printf(" inorder: ");
    printInorder(root);
    printf("\n preorder: ");
    printPreorder(root);
    printf("\n postorder: ");
    printPostorder(root);
    printf("\n");
    // uvoľníme pamäť
    destroyTree(root);
}
```

