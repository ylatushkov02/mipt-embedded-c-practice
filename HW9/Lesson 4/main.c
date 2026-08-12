#include <stdio.h>

void print_digit(char s[]) {
    int cnt[10] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            cnt[s[i] - '0']++;
        }
    }
    for (int d = 0; d <= 9; d++) {
        if (cnt[d] > 0) {
            printf("%d %d\n", d, cnt[d]);
        }
    }
}
