#include <stdio.h>

int main(int argc, char **argv) {

    int num, max;
    
    scanf("%d", &max);
    
    for (int i = 0; i < 4; i++) {
        scanf("%d", &num);
        if (num > max) {
            max = num;
        }
    }
    
    printf("%d\n", max);

    return 0;
    
}
