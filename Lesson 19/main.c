#include <stdio.h>

int main() {
    
    int a, b;

    scanf("%d %d", &a, &b);
    
    printf("%s\n", (a > b) ? "Above" : (a < b) ? "Less" : "Equal");
    
    return 0;

}
