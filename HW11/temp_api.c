#include "temp_api.h"

#include <stdio.h>
#include <string.h>

static int month_matches(const TempRecord *record, int year, const char *month)
{
    return record->year == year && strcmp(record->month, month) == 0;
}

static int year_matches(const TempRecord *record, int year)
{
    return record->year == year;
}

void print_monthly_avg(const TempRecord *records, size_t count, int year, const char *month)
{
    long sum = 0;
    size_t matched = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!month_matches(&records[i], year, month)) {
            continue;
        }

        sum += records[i].temperature;
        ++matched;
    }

    if (matched == 0) {
        printf("Среднемесячная температура (%04d-%s): нет данных\n", year, month);
        return;
    }

    printf("Среднемесячная температура (%04d-%s): %ld\n", year, month, sum / (long)matched);
}

void print_monthly_min(const TempRecord *records, size_t count, int year, const char *month)
{
    int has_value = 0;
    int min_temp = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!month_matches(&records[i], year, month)) {
            continue;
        }

        if (!has_value || records[i].temperature < min_temp) {
            min_temp = records[i].temperature;
            has_value = 1;
        }
    }

    if (!has_value) {
        printf("Минимальная температура в месяце (%04d-%s): нет данных\n", year, month);
        return;
    }

    printf("Минимальная температура в месяце (%04d-%s): %d\n", year, month, min_temp);
}

void print_monthly_max(const TempRecord *records, size_t count, int year, const char *month)
{
    int has_value = 0;
    int max_temp = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!month_matches(&records[i], year, month)) {
            continue;
        }

        if (!has_value || records[i].temperature > max_temp) {
            max_temp = records[i].temperature;
            has_value = 1;
        }
    }

    if (!has_value) {
        printf("Максимальная температура в месяце (%04d-%s): нет данных\n", year, month);
        return;
    }

    printf("Максимальная температура в месяце (%04d-%s): %d\n", year, month, max_temp);
}

void print_yearly_avg(const TempRecord *records, size_t count, int year)
{
    long sum = 0;
    size_t matched = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!year_matches(&records[i], year)) {
            continue;
        }

        sum += records[i].temperature;
        ++matched;
    }

    if (matched == 0) {
        printf("Среднегодовая температура (%04d): нет данных\n", year);
        return;
    }

    printf("Среднегодовая температура (%04d): %ld\n", year, sum / (long)matched);
}

void print_yearly_min(const TempRecord *records, size_t count, int year)
{
    int has_value = 0;
    int min_temp = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!year_matches(&records[i], year)) {
            continue;
        }

        if (!has_value || records[i].temperature < min_temp) {
            min_temp = records[i].temperature;
            has_value = 1;
        }
    }

    if (!has_value) {
        printf("Минимальная температура за год (%04d): нет данных\n", year);
        return;
    }

    printf("Минимальная температура за год (%04d): %d\n", year, min_temp);
}

void print_yearly_max(const TempRecord *records, size_t count, int year)
{
    int has_value = 0;
    int max_temp = 0;

    for (size_t i = 0; i < count; ++i) {
        if (!year_matches(&records[i], year)) {
            continue;
        }

        if (!has_value || records[i].temperature > max_temp) {
            max_temp = records[i].temperature;
            has_value = 1;
        }
    }

    if (!has_value) {
        printf("Максимальная температура за год (%04d): нет данных\n", year);
        return;
    }

    printf("Максимальная температура за год (%04d): %d\n", year, max_temp);
}
