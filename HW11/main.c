#include "temp_api.h"

#include <stdio.h>

int main(void)
{
    TempRecord records[] = {
        {2025, "01", 15, 10, 30, -5},
        {2025, "01", 20, 14,  0, -12},
        {2025, "01", 25, 18, 45,  2},
        {2025, "02",  3,  9, 15, -3},
        {2025, "02", 14, 12,  0,  5},
        {2025, "02", 28, 20, 10,  8},
        {2025, "03",  1,  8,  0,  0},
        {2025, "03", 15, 16, 30, 12},
        {2024, "12", 31, 23, 59, -20},
    };

    size_t count = sizeof(records) / sizeof(records[0]);

    printf("=== Статистика за январь 2025 ===\n");
    print_monthly_avg(records, count, 2025, "01");
    print_monthly_min(records, count, 2025, "01");
    print_monthly_max(records, count, 2025, "01");

    printf("\n=== Статистика за 2025 год ===\n");
    print_yearly_avg(records, count, 2025);
    print_yearly_min(records, count, 2025);
    print_yearly_max(records, count, 2025);

    return 0;
}
