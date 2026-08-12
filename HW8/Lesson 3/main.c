#include <stdio.h>

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    int max_i = 0, min_i = 0;
    for (int i = 1; i < 10; i++) {
        if (a[i] > a[max_i]) {
            max_i = i;
        }
        if (a[i] < a[min_i]) {
            min_i = i;
        }
    }
    printf("%d %d %d %d\n", max_i + 1, a[max_i], min_i + 1, a[min_i]);
    return 0;
}
