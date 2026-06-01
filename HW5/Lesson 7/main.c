#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, digit;
    int digits[10] = {0};
    scanf("%d", &n);
    
    if (n < 0) {
        n = abs(n);
    }
    
    if (n == 0) {
        printf("NO\n");
        return 0;
    }
    
    while (n > 0) {
        digit = n % 10;
        if (digits[digit] == 1) {
            printf("YES\n");
            return 0;
        }
        digits[digit] = 1;
        n /= 10;
    }
    
    printf("NO\n");
    return 0;
}
