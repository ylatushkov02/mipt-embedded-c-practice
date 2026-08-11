#include "temp_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_monthly_stats(const TempRecord *records, size_t count, int year, int month)
{
    char month_str[3];

    snprintf(month_str, sizeof(month_str), "%02d", month);

    printf("=== Статистика за месяц %02d %04d ===\n", month, year);
    print_monthly_avg(records, count, year, month_str);
    print_monthly_min(records, count, year, month_str);
    print_monthly_max(records, count, year, month_str);
}

static void print_yearly_stats(const TempRecord *records, size_t count, int year)
{
    printf("=== Статистика за %04d год ===\n", year);
    print_yearly_avg(records, count, year);
    print_yearly_min(records, count, year);
    print_yearly_max(records, count, year);
}

static int record_matches_month(const TempRecord *record, int year, int month)
{
    char month_str[3];

    snprintf(month_str, sizeof(month_str), "%02d", month);
    return record->year == year && strcmp(record->month, month_str) == 0;
}

static int year_has_month(const TempRecord *records, size_t count, int year, int month)
{
    for (size_t i = 0; i < count; ++i) {
        if (record_matches_month(&records[i], year, month)) {
            return 1;
        }
    }

    return 0;
}

static void collect_years(const TempRecord *records, size_t count, int *years, size_t *years_count)
{
    *years_count = 0;

    for (size_t i = 0; i < count; ++i) {
        int year = records[i].year;
        int found = 0;

        for (size_t j = 0; j < *years_count; ++j) {
            if (years[j] == year) {
                found = 1;
                break;
            }
        }

        if (!found && *years_count < 32) {
            years[(*years_count)++] = year;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *csv_file = NULL;
    int filter_month = 0;
    int has_month_filter = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
            return 0;
        }

        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Ошибка: для ключа -f нужно указать файл\n");
                return 1;
            }
            csv_file = argv[++i];
            continue;
        }

        if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Ошибка: для ключа -m нужно указать номер месяца\n");
                return 1;
            }
            filter_month = atoi(argv[++i]);
            if (filter_month < 1 || filter_month > 12) {
                fprintf(stderr, "Ошибка: номер месяца должен быть от 1 до 12\n");
                return 1;
            }
            has_month_filter = 1;
            continue;
        }

        fprintf(stderr, "Ошибка: неизвестный ключ %s\n", argv[i]);
        print_help(argv[0]);
        return 1;
    }

    if (csv_file == NULL) {
        fprintf(stderr, "Ошибка: укажите входной файл через ключ -f\n");
        print_help(argv[0]);
        return 1;
    }

    TempArray *array = temp_array_create();
    if (array == NULL) {
        fprintf(stderr, "Ошибка: не удалось создать массив\n");
        return 1;
    }

    if (temp_array_load_csv(array, csv_file) != 0) {
        fprintf(stderr, "Ошибка: не удалось прочитать файл %s\n", csv_file);
        temp_array_free(array);
        return 1;
    }

    temp_array_sort(array);

    if (array->count == 0) {
        fprintf(stderr, "Ошибка: файл не содержит записей\n");
        temp_array_free(array);
        return 1;
    }

    int years[32];
    size_t years_count = 0;

    collect_years(array->records, array->count, years, &years_count);

    if (has_month_filter) {
        for (size_t i = 0; i < years_count; ++i) {
            if (year_has_month(array->records, array->count, years[i], filter_month)) {
                print_monthly_stats(array->records, array->count, years[i], filter_month);
                printf("\n");
            }
        }
    } else {
        for (size_t i = 0; i < years_count; ++i) {
            print_yearly_stats(array->records, array->count, years[i]);
            printf("\n");
        }
    }

    temp_array_free(array);
    return 0;
}
