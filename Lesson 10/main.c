#include <stdio.h>

int main(int argc, char **argv) {

    int num, min;
    
    scanf("%d", &min);
    
    for (int i = 0; i < 4; i++) {
        scanf("%d", &num);
        if (num < min) {
            min = num;
        }
    }
    
    printf("%d\n", min);

    return 0;
    
}
