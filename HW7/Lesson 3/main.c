#include <stdio.h>

void print_digits_rev(int n) {
    printf("%d", n % 10);
    if (n / 10 > 0) {
        printf(" ");
        print_digits_rev(n / 10);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    print_digits_rev(n);
    printf("\n");
    return 0;
}
