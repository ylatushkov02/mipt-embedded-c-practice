#include <stdio.h>

int pow(int n, int p) {
    int result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    
    printf("%d\n", pow(n, p));
    
    return 0;
}
