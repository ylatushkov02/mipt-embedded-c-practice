#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    char w1[101], w2[101];
    fscanf(in, "%100s %100s", w1, w2);
    int c1[26] = {0}, c2[26] = {0};
    for (int i = 0; w1[i]; i++) {
        c1[w1[i] - 'a']++;
    }
    for (int i = 0; w2[i]; i++) {
        c2[w2[i] - 'a']++;
    }
    int first = 1;
    for (int i = 0; i < 26; i++) {
        if (c1[i] == 1 && c2[i] == 1) {
            if (!first) {
                fprintf(out, " ");
            }
            fprintf(out, "%c", 'a' + i);
            first = 0;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
