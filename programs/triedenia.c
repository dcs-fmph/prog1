/* Program s triedeniami z prednášky 6. */
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

int readArray(int a[], int maxSize) {
    /* Od užívateľa načíta počet vstupných čísel.
     * Potom načíta zadaný počet celých čísel a uloží ich do poľa a,
     * Hodnota maxSize je veľkosť poľa,
     * ktorú nemožno prekročiť.
     * Funkcia vráti počet načítaných čísel. */

    int n;
    scanf("%d", &n);
    assert(n <= maxSize);
    for (int i = 0; i < n; i++) {
        scanf("%d", &(a[i]));
    }
    return n;
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
}


void swap(int a[], int i, int j) {
    /* Vymeň hodnoty prvkov v poli a na pozíciách i a j. */
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}


void bubbleSort(int a[], int n) {
    /* usporiadaj prvky v poli a od najmenšieho po najväčší */

    bool hotovo = false;
    while (!hotovo) {
        bool vymenil = false;
        /* porovnávaj všetky dvojice susedov,
           vymeň ak menší za väčším */
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                swap(a, i - 1, i);
                vymenil = true;
            }
        }
        /* ak sme žiadnu dvojicu nevymenili,
           môžeme skončiť. */
        if (!vymenil) {
            hotovo = true;
        }
    }
}

int maxIndex(int a[], int n) {
    /* vráť index, na ktorom je najväčší prvok z prvkov a[0]...a[n-1] */
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[index]) {
            index = i;
        }
        /* invariant: a[j]<=a[index] pre všetky j=0,...,i*/
    }
    return index;
}

void selectionSort(int a[], int n) {
    /* usporiadaj prvky v poli a od najmenšieho po najväčší */

    for (int kam = n - 1; kam >= 1; kam--) {
        /* invariant: a[kam+1]...a[n-1] sú utriedené
         * a pre každé i,j také že 0<=i<=kam, kam<j<n platí a[i]<=a[j] */
        int index = maxIndex(a, kam + 1);
        swap(a, index, kam);
    }
}

void insertionSort(int a[], int n) {
    /* usporiadaj prvky v poli a od najmenšieho po najväčší */

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

#define NMax 100

int main(void) {
    int a[NMax];

    int n = readArray(a, NMax);
    
    printArray(a, n);
    //insertionSort(a, n);
    //bubbleSort(a, n);
    selectionSort(a, n);
    printArray(a, n);
}
