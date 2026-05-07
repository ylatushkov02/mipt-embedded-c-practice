#include <stdio.h>

int main(int argc, char **argv) {

    int sum = 0, num;
    
    scanf("%d", &num);

    while (num > 0) {
        sum = sum + num % 10;
        num = num / 10;
    }
    
    printf("%d\n", sum);

    return 0;
    
}
