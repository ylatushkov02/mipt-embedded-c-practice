#include "temp_api.h"

#include <stdio.h>

int main(void)
{
    TempRecord records[] = {
        {2026, "08",  1,  8,  0, 18},
        {2026, "08",  5, 14, 30, 24},
        {2026, "08", 11, 10, 15, 22},
        {2026, "08", 15, 18, 45, 26},
        {2026, "08", 20, 12,  0, 19},
        {2026, "07", 28, 20, 10, 21},
        {2026, "07", 14, 12,  0, 17},
        {2026, "06",  1,  8,  0, 15},
        {2025, "12", 31, 23, 59, -5},
    };

    size_t count = sizeof(records) / sizeof(records[0]);

    printf("=== Статистика за август 2026 ===\n");
    print_monthly_avg(records, count, 2026, "08");
    print_monthly_min(records, count, 2026, "08");
    print_monthly_max(records, count, 2026, "08");

    printf("\n=== Статистика за 2026 год ===\n");
    print_yearly_avg(records, count, 2026);
    print_yearly_min(records, count, 2026);
    print_yearly_max(records, count, 2026);

    return 0;
}
