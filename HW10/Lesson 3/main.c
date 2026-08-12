#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    char s[1001];
    fgets(s, sizeof(s), in);
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
    if (len == 0) {
        fclose(in);
        fclose(out);
        return 0;
    }
    char last = s[len - 1];
    int first = 1;
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == last) {
            if (!first) {
                fprintf(out, " ");
            }
            fprintf(out, "%d", i);
            first = 0;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
