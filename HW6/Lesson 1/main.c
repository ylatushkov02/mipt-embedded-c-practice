#include <stdio.h>

int abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int main() {
    int n;
    scanf("%d", &n);
    
    printf("%d\n", abs(n));
    
    return 0;
}
