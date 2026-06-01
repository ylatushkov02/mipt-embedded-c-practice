#include <stdio.h>

int f(int x) {
    if (x < -2) {
        return 4;
    } else if (x >= -2 && x < 2) {
        return x * x;
    } else {
        return x * x + 4 * x + 5;
    }
}

int main() {
    int x, max_val;
    scanf("%d", &x);
    
    max_val = f(x);
    
    while (1) {
        scanf("%d", &x);
        if (x == 0) {
            break;
        }
        int current = f(x);
        if (current > max_val) {
            max_val = current;
        }
    }
    
    printf("%d\n", max_val);
    
    return 0;
}
