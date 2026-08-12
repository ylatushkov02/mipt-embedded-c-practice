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
    for (int i = 0; i < len; i++) {
        if (s[i] == 'a') {
            s[i] = 'b';
        } else if (s[i] == 'b') {
            s[i] = 'a';
        } else if (s[i] == 'A') {
            s[i] = 'B';
        } else if (s[i] == 'B') {
            s[i] = 'A';
        }
    }
    fprintf(out, "%s", s);
    fclose(in);
    fclose(out);
    return 0;
}
