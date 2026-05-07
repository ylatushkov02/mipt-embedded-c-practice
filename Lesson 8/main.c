#include <stdio.h>

int main(int argc, char **argv) {

    int a = 0;
    int b = 0;
    int c = 0;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    if (a > b) {
        if (a > c) {
            printf("%d\n", a);
        } else {
            printf("%d\n", c);
        }
    } else {
        if (b > c) {
            printf("%d\n", b);
        } else {
            printf("%d\n", c);
        }
    }
    
    return 0;
    
}
