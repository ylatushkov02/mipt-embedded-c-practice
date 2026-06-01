#include <stdio.h>

int sumN(int n) {
    return n * (n + 1) / 2;
}

int main() {
    int n;
    scanf("%d", &n);
    
    printf("%d\n", sumN(n));
    
    return 0;
}
