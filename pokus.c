#include <stdio.h>



int main() {
  int N;
    printf("Zadaj pocet cisel: ");
    scanf("%d", &N);
    int p[N];
    for(int i=0; i<N; i++) {
      p[i] = i;
    }
    for(int i=0; i<N; i++) {
      printf("%d", p[i]);
    }
    
}
