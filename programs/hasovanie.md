---
title: Program hasovanie.cpp
---

[Súbor na stiahnutie](./hasovanie.cpp)

```cpp
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

/* hašovacia funkcia */
int h(int x, int m) {
    return abs(x) % m;
}

/* štruktúra reprezentujúca jeden prvok spájaného zoznamu */
struct node {
    int data;
    node *next;
};

/* štruktúra implementujúca dynamickú množinu hašovaním */
struct set {
    node **table;  // pole smerníkov na začiatky zoznamov
    int m;         // veľkost hašovacej tabuľky
};

/* Funkcia vytvorí prázdnu dynamickú množinu. */
void init(set &s, int m) {
    // veľkosť tabuľky je parametrom funkcie init
    s.m = m;
    s.table = new node *[m];
    for (int i = 0; i < m; i++) {
        s.table[i] = NULL;
    }
}

/* Funkcia zistí, či prvok x patrí do množiny s. */
bool contains(set &s, int x) {
    // spočítame políčko tabuľky
    int index = h(x, s.m);
    node *p = s.table[index];
    // p ukazuje na začiatok zoznamu
    while (p != NULL) {
        // prechádzame zoznam, hľadáme x
        if (p->data == x) {
            return true;
        }
        p = p->next;
    }
    return false;
}

/* Funkcia pridá prvok x do množiny s. */
void add(set &s, int x) {
    // spočítame políčko tabuľky
    int index = h(x, s.m);
    // vytvoríme nový uzol
    node *p = new node;
    p->data = x;
    // uzol vložíme na začiatok zoznamu
    p->next = s.table[index];
    s.table[index] = p;
}

/* Funkcia uvoľní množinu s z pamäte. */
void destroy(set &s) {
    for (int i = 0; i < s.m; i++) {
        // uvoľníme zoznam s.table[i]
        node *p = s.table[i];
        while (p != NULL) {
            node *p2 = p->next;
            delete p;
            p = p2;
        }
    }
    delete[] s.table;
}

int main() {
    // množina s m=13
    set A;
    init(A, 13);

    while (true) {
        // načítame jeden z príkazov add, contains, end
        // za add a contains načítame aj prvok x
        std::string prikaz;
        std::cin >> prikaz;
        if (prikaz == "contains") {
            int x;
            std::cin >> x;
            if (contains(A, x)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else if (prikaz == "add") {
            int x;
            std::cin >> x;
            add(A, x);
        } else if (prikaz == "end") {
            break;
        } else {
            std::cout << "Bad command\n";
        }
    }

    // uvoľníme pamäť množiny A
    destroy(A);
}
```
