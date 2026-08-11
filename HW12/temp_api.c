#include "temp_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 8

static int month_matches(const TempRecord *record, int year, const char *month)
{
    return record->year == year && strcmp(record->month, month) == 0;
}

static int year_matches(const TempRecord *record, int year)
{
    return record->year == year;
}

static int temp_array_grow(TempArray *array)
{
    size_t new_capacity = array->capacity == 0 ? INITIAL_CAPACITY : array->capacity * 2;
    TempRecord *new_records = realloc(array->records, new_capacity * sizeof(TempRecord));

    if (new_records == NULL) {
        return -1;
    }

    array->records = new_records;
    array->capacity = new_capacity;
    return 0;
}

static int parse_record(TempRecord *record, int year, int month, int day, int hour, int minute, int temperature)
{
    if (month < 1 || month > 12 || day < 1 || day > 31 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 ||
        temperature < TEMP_MIN || temperature > TEMP_MAX) {
        return -1;
    }

    record->year = year;
    snprintf(record->month, sizeof(record->month), "%02d", month);
    record->day = day;
    record->hour = hour;
    record->minute = minute;
    record->temperature = temperature;
    return 0;
}

static int record_compare(const TempRecord *left, const TempRecord *right)
{
    if (left->year != right->year) {
        return left->year - right->year;
    }
    if (strcmp(left->month, right->month) != 0) {
        return strcmp(left->month, right->month);
    }
    if (left->day != right->day) {
        return left->day - right->day;
    }
    if (left->hour != right->hour) {
        return left->hour - right->hour;
    }
    if (left->minute != right->minute) {
        return left->minute - right->minute;
    }
    return left->temperature - right->temperature;
}

TempArray *temp_array_create(void)
{
    TempArray *array = malloc(sizeof(TempArray));
    if (array == NULL) {
        return NULL;
    }

    array->records = NULL;
    array->count = 0;
    array->capacity = 0;
    return array;
}

void temp_array_free(TempArray *array)
{
    if (array == NULL) {
        return;
    }

    free(array->records);
    free(array);
}

int temp_array_add(TempArray *array, TempRecord record)
{
    if (array == NULL) {
        return -1;
    }

    if (array->count == array->capacity && temp_array_grow(array) != 0) {
        return -1;
    }

    array->records[array->count++] = record;
    return 0;
}

int temp_array_delete(TempArray *array, size_t index)
{
    if (array == NULL || index >= array->count) {
        return -1;
    }

    for (size_t i = index; i + 1 < array->count; ++i) {
        array->records[i] = array->records[i + 1];
    }

    --array->count;
    return 0;
}

void temp_array_sort(TempArray *array)
{
    if (array == NULL || array->count < 2) {
        return;
    }

    for (size_t i = 0; i + 1 < array->count; ++i) {
        for (size_t j = 0; j + 1 < array->count - i; ++j) {
            if (record_compare(&array->records[j], &array->records[j + 1]) > 0) {
                TempRecord tmp = array->records[j];
                array->records[j] = array->records[j + 1];
                array->records[j + 1] = tmp;
            }
        }
    }
}

void temp_array_print(const TempArray *array)
{
    if (array == NULL) {
        return;
    }

    printf("year,month,day,hour,minute,temperature\n");
    for (size_t i = 0; i < array->count; ++i) {
        const TempRecord *record = &array->records[i];
        printf("%04d,%s,%02d,%02d,%02d,%d\n",
               record->year,
               record->month,
               record->day,
               record->hour,
               record->minute,
               record->temperature);
    }
}

int temp_array_load_csv(TempArray *array, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL || array == NULL) {
        return -1;
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        ++line_number;

        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        if (line_number == 1 && strstr(line, "year") != NULL) {
            continue;
        }

        TempRecord record;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int temperature;

        if (sscanf(line, "%d,%d,%d,%d,%d,%d",
                   &year, &month, &day, &hour, &minute, &temperature) != 6) {
            fclose(file);
            return -1;
        }

        if (parse_record(&record, year, month, day, hour, minute, temperature) != 0) {
            fclose(file);
            return -1;
        }

        if (temp_array_add(array, record) != 0) {
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

void print_help(const char *program_name)
{
    printf("Приложение для обработки температурных данных.\n\n");
    printf("Использование: %s [ключи]\n\n", program_name);
    printf("Поддерживаемые ключи:\n");
    printf("  -h                 Описание функционала приложения и список ключей\n");
    printf("  -f <файл.csv>      Входной CSV-файл для обработки\n");
    printf("  -m <номер месяца>  Вывести только статистику за указанный месяц (1-12)\n");
    printf("\nФормат CSV: year,month,day,hour,minute,temperature\n");
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
