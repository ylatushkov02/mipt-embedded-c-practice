#include <stdio.h>

int main() {
    int a[12];
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    printf("%.2f\n", sum / 12.0);
    return 0;
}
