#include <stdio.h>

int main(int argc, char **argv) {

    int num, min, max;
    
    scanf("%d", &min);

    max = min;

    for (int i = 0; i < 4; i++) {
        scanf("%d", &num);
        if (num < min) {
            min = num;
        }
        if (num > max) {
            max = num;
        }
    }
    
    printf("%d\n", min + max);

    return 0;
    
}
