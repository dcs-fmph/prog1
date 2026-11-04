/* Program s triedeniami z prednášky 13. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NMAX 100000

// ------- Pomocné funkcie ----------

void generateRandomArray(int a[], int n) {
    /* Vygeneruje n náhodných čísel a uloží ich do poľa a */
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000;
    }
}

void readArray(int a[], int n) {
    /* Od užívateľa načíta n čísel a uloží ich do poľa a */
    for (int i = 0; i < n; i++) {
        scanf("%d", &(a[i]));
    }
}

void copyArray(int src[], int dest[], int n) {
    /* Skopíruje n prvkov z poľa src do poľa dest */
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void printArray(int a[], int n) {
    /* Vypíše všetky prvky poľa a dĺžky n */
    for (int i = 0; i < n; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
}

// ------- Triedenie vkladaním ----------

void insertionsort(int a[], int n) {
    /* Triedenie vkladaním */
    for (int i = 1; i < n; i++) {
        int prvok = a[i];
        int kam = i;
        while (kam > 0 && a[kam - 1] > prvok) {
            a[kam] = a[kam - 1];
            kam--;
        }
        a[kam] = prvok;
    }
}

// ------- Triedenie zločovaním ----------

void merge(int a[], int left, int middle, int right) {
    /* Zlúčenie dvoch usporiadaných častí poľa a.
     * Prvá časť je od indexu left po middle, druhá od middle + 1 po right */

    int aux[NMAX];      // pomocné pole
    int i = left;       // index v prvej časti
    int j = middle + 1; // index v druhej časti
    int k = 0;          // index v pomocnom poli

    while ((i <= middle) && (j <= right)) {
        // Kým sú a[i..middle] aj a[j..right] neprázdne,
        // menší z prvkov a[i], a[j] ulož do aux[k] a posuň indexy
        if (a[i] <= a[j]) {
            aux[k] = a[i];
            i++;
            k++;
        } else {
            aux[k] = a[j];
            j++;
            k++;
        }
    }

    // ak ešte zostali prvky v prvej časti, vložíme ich do aux
    while (i <= middle) {
        aux[k] = a[i];
        i++;
        k++;
    }

    // ak ešte zostali prvky v druhej časti, vložíme ich do aux
    while (j <= right) {
        aux[k] = a[j];
        j++;
        k++;
    }

    // nakoniec skopírujeme zlúčené prvky z aux späť do a
    // pozícia 0 v aux pôjde na pozíciu left v a
    for (int k = left; k <= right; k++) {
        a[k] = aux[k - left];
    }
}

void mergesort(int a[], int left, int right) {
    /* Triedenie zlučovaním od pozície left
     * po pozíciu right (vrátane) */

    // triviálny prípad: pole má najviac jeden prvok
    if (left >= right) {
        return;
    }

    // rozdeľuj: spočítame stred poľa
    int middle = (left + right) / 2;

    // rekurzívne vyriešime podproblémy
    mergesort(a, left, middle);
    mergesort(a, middle + 1, right);

    // panuj: zlúčime obe usporiadané časti
    merge(a, left, middle, right);
}

// ------- Quick Sort ----------

void swap(int a[], int i, int j) {
    /* Vymení hodnoty prvkov v poli a na pozíciách i a j. */
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int a[], int left, int right) {
    /* Rozdelí pole a od pozície left po pozíciu right okolo pivotu.
     * Prvky menšie ako pivot budú naľavo, potom
     * nasleduje pivot a prvky rovné alebo väčšie ako pivot.
     * Vráti index pivotu po rozdelení. */

    int pivot = a[left];
    int lastSmaller = left;

    for (int unknown = left + 1; unknown <= right; unknown++) {
        if (a[unknown] < pivot) {
            lastSmaller++;
            swap(a, unknown, lastSmaller);
        }
    }
    swap(a, left, lastSmaller);
    return lastSmaller;
}

void quicksort(int a[], int left, int right) {
    /* Triedenie QuickSort od pozície left
       po pozíciu right  (vrátane)*/

    // triviálny prípad: ak má pole najviac jeden prvok
    if (left >= right) {
        return;
    }

    // rozdelíme pole okolo pivotu
    int middle = partition(a, left, right);
    // Po vykonaní funkcie:
    // a[left..middle-1] sú menšie ako pivot
    // a[middle] je pivot
    // a[middle+1..right] sú väčšie ako pivot

    // rekurzívne utrieď a[left..middle-1], a[middle+1..right]
    quicksort(a, left, middle - 1);
    quicksort(a, middle + 1, right);
}

// ------- Funkcia main ----------

int main() {
    /* načítame alebo vygenerujeme dáta na triedenie */
    int n;
    int a1[NMAX];
    int a2[NMAX];
    int a3[NMAX];

    printf("Zadaj pocet cisel v poli: ");
    scanf("%d", &n);

    printf("Maju byt vygenerovane nahodne? (zadaj A alebo N): ");
    char odpoved;
    scanf(" %c", &odpoved);

    if (odpoved == 'A') {
        generateRandomArray(a1, n);
    } else {
        printf("Zadaj %d cisel: ", n);
        readArray(a1, n);
    }
    /* budeme triediť tri kópie toho istého poľa */
    copyArray(a1, a2, n);
    copyArray(a1, a3, n);

    /* premenné na ukladanie časov začiatku a konca triedenia */
    clock_t start1, end1, start2, end2, start3, end3;

    /* triedime a meriame čas */
    start1 = clock();
    insertionsort(a1, n);
    end1 = clock();

    start2 = clock();
    mergesort(a2, 0, n - 1);
    end2 = clock();

    start3 = clock();
    quicksort(a3, 0, n - 1);
    end3 = clock();

    /* výpis výsledkov */
    printf("Insertion sort: %f CPU sekund\n", (end1 - start1) * 1.0 / CLOCKS_PER_SEC);
    printf("Merge sort: %f CPU sekund\n", (end2 - start2) * 1.0 / CLOCKS_PER_SEC);
    printf("Quick sort: %f CPU sekund\n", (end3 - start3) * 1.0 / CLOCKS_PER_SEC);

    /* výpis zoradeného poľa */
    if (odpoved == 'N') {
        printf("Zoradene pole: ");
        printArray(a1, n);
    }

    /* kontrola, či sú všetky polia rovnaké */
    for (int i = 0; i < n; i++) {
        assert(a1[i] == a2[i] && a1[i] == a3[i]);
    }

}
