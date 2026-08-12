#include <stdio.h>

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < 2; i++) {
        int t = a[i];
        a[i] = a[4 - i];
        a[4 - i] = t;
    }
    for (int i = 0; i < 2; i++) {
        int t = a[5 + i];
        a[5 + i] = a[9 - i];
        a[9 - i] = t;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d", a[i]);
        if (i < 9) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
