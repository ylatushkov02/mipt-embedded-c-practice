#include <stdio.h>

int convertP(int n, int p) {
    int result = 0;
    int mult = 1;
    
    if (n == 0) {
        return 0;
    }
    
    while (n > 0) {
        result += (n % p) * mult;
        n /= p;
        mult *= 10;
    }
    
    return result;
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    
    printf("%d\n", convertP(n, p));
    
    return 0;
}
