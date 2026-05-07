#include <stdio.h>

int main() {

    char *seasons[] = {
        "winter", "winter", 
        "spring", "spring", "spring", 
        "summer", "summer", "summer", 
        "autumn", "autumn", "autumn", 
        "winter"
    };

    int month;
    
    scanf("%d", &month);

    printf("%s\n", seasons[month - 1]);
    
    return 0;

}
