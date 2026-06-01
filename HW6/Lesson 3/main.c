#include <stdio.h>

int avr(int a, int b) {
    return (a + b) / 2;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    printf("%d\n", avr(a, b));
    
    return 0;
}
