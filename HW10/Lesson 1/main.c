#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    char s[101];
    fgets(s, sizeof(s), in);
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
    fprintf(out, "%s, %s, %s %d", s, s, s, len);
    fclose(in);
    fclose(out);
    return 0;
}
