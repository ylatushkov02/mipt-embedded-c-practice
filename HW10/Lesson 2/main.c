#include <stdio.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    char even_digits[] = {'2', '4', '6', '8'};
    int letter = 0;
    int digit = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            fputc('A' + letter, out);
            letter++;
        } else {
            fputc(even_digits[digit % 4], out);
            digit++;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
