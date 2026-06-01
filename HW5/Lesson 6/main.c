#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, prev, current;
    scanf("%d", &n);
    
    if (n < 0) {
        n = abs(n);
    }
    
    if (n < 10) {
        printf("NO\n");
        return 0;
    }
    
    prev = n % 10;
    n /= 10;
    
    while (n > 0) {
        current = n % 10;
        if (current == prev) {
            printf("YES\n");
            return 0;
        }
        prev = current;
        n /= 10;
    }
    
    printf("NO\n");
    return 0;
}
