#include <stdio.h>

int main(int argc, char **argv) {

    int max = 0, num;
    
    scanf("%d", &num);

    while (num > 0) {
        if (num % 10 > max) {
            max = num % 10;
        }
        num = num / 10;
    }
    
    printf("%d\n", max);

    return 0;
    
}
