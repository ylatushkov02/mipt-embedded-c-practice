#include <stdio.h>

int main(int argc, char **argv) {

    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    printf("%d+%d+%d=%d\n", a, b, c, a + b + c);
    printf("%d*%d*%d=%d\n", a, b, c, a * b * c);
    return 0;
    
}
