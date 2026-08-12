#include <stdio.h>

int sum_1_to_n(int n) {
    if (n == 1) {
        return 1;
    }
    return n + sum_1_to_n(n - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", sum_1_to_n(n));
    return 0;
}
