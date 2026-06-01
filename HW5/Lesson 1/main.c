#include <stdio.h>

int main(int argc, char **argv) {

    int num = 0;
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) {
        printf("%d %d %d\n", i, i*i, i*i*i);
    }

    return 0;
}
