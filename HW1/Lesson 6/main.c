#include <stdio.h>

int main(int argc, char **argv) {

    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    printf("%.2f\n", (float) (a + b + c) / 3);
    return 0;
    
}
