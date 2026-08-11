#include "temp_functions.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 1024

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

static int temp_array_add(TempArray *array, TempRecord record)
{
    if (array->count == array->capacity && temp_array_grow(array) != 0) {
        return -1;
    }

    array->records[array->count++] = record;
    return 0;
}

static int is_header_line(const char *line)
{
    char lower[256];
    size_t i = 0;

    while (line[i] != '\0' && i + 1 < sizeof(lower)) {
        lower[i] = (char)tolower((unsigned char)line[i]);
        ++i;
    }
    lower[i] = '\0';

    return strstr(lower, "year") != NULL;
}

static int parse_int_field(const char *field, int *value)
{
    char *end = NULL;
    long parsed;

    while (*field != '\0' && isspace((unsigned char)*field)) {
        ++field;
    }

    if (*field == '\0') {
        return -1;
    }

    parsed = strtol(field, &end, 10);
    if (end == field) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

static int parse_csv_line(const char *line, TempRecord *record)
{
    char buffer[256];
    char *fields[6];
    char *token;
    char *saveptr = NULL;
    int field_count = 0;
    size_t len;

    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    len = strlen(buffer);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[--len] = '\0';
    }

    if (len == 0) {
        return -1;
    }

    token = strtok_r(buffer, ";", &saveptr);
    while (token != NULL && field_count < 6) {
        fields[field_count++] = token;
        token = strtok_r(NULL, ";", &saveptr);
    }

    if (field_count != 6 || token != NULL) {
        return -1;
    }

    if (parse_int_field(fields[0], &record->year) != 0 ||
        parse_int_field(fields[1], &record->month) != 0 ||
        parse_int_field(fields[2], &record->day) != 0 ||
        parse_int_field(fields[3], &record->hour) != 0 ||
        parse_int_field(fields[4], &record->minute) != 0 ||
        parse_int_field(fields[5], &record->temperature) != 0) {
        return -1;
    }

    if (record->year < 1000 || record->year > 9999 ||
        record->month < 1 || record->month > 12 ||
        record->day < 1 || record->day > 31 ||
        record->hour < 0 || record->hour > 23 ||
        record->minute < 0 || record->minute > 59 ||
        record->temperature < TEMP_MIN || record->temperature > TEMP_MAX) {
        return -1;
    }

    return 0;
}

static int record_compare(const void *left_ptr, const void *right_ptr)
{
    const TempRecord *left = left_ptr;
    const TempRecord *right = right_ptr;

    if (left->year != right->year) {
        return left->year - right->year;
    }
    if (left->month != right->month) {
        return left->month - right->month;
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

int temp_array_load_csv(TempArray *array, const char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    size_t line_number = 0;
    int loaded = 0;

    if (file == NULL || array == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        TempRecord record;

        ++line_number;

        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
            continue;
        }

        if (line_number == 1 && is_header_line(line)) {
            continue;
        }

        if (parse_csv_line(line, &record) != 0) {
            fprintf(stderr, "Ошибка в строке %zu: неверный формат данных\n", line_number);
            continue;
        }

        if (temp_array_add(array, record) != 0) {
            fclose(file);
            return -1;
        }

        ++loaded;
    }

    fclose(file);
    return loaded > 0 ? 0 : -1;
}

void temp_array_sort(TempArray *array)
{
    if (array == NULL || array->count < 2) {
        return;
    }

    qsort(array->records, array->count, sizeof(TempRecord), record_compare);
}

void print_help(const char *program_name)
{
    printf("Консольное приложение — статистика температуры\n\n");
    printf("Использование: %s [ключи]\n\n", program_name);
    printf("Поддерживаемые ключи:\n");
    printf("  -h                 Описание функционала приложения и список ключей\n");
    printf("  -f <filename.csv>  Входной CSV-файл для обработки\n");
    printf("  -m <номер месяца>  Вывести только статистику за указанный месяц (1-12)\n");
    printf("\nБез параметров выводится эта справка.\n");
    printf("Формат CSV: YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE\n");
    printf("Некорректные строки пропускаются с указанием номера строки.\n");
}

static int collect_month_stats(const TempRecord *records, size_t count, int year, int month,
                               long *sum, size_t *matched, int *min_temp, int *max_temp)
{
    *sum = 0;
    *matched = 0;

    for (size_t i = 0; i < count; ++i) {
        if (records[i].year != year || records[i].month != month) {
            continue;
        }

        if (*matched == 0) {
            *min_temp = records[i].temperature;
            *max_temp = records[i].temperature;
        } else {
            if (records[i].temperature < *min_temp) {
                *min_temp = records[i].temperature;
            }
            if (records[i].temperature > *max_temp) {
                *max_temp = records[i].temperature;
            }
        }

        *sum += records[i].temperature;
        ++(*matched);
    }

    return *matched > 0;
}

static int collect_year_stats(const TempRecord *records, size_t count, int year,
                              long *sum, size_t *matched, int *min_temp, int *max_temp)
{
    *sum = 0;
    *matched = 0;

    for (size_t i = 0; i < count; ++i) {
        if (records[i].year != year) {
            continue;
        }

        if (*matched == 0) {
            *min_temp = records[i].temperature;
            *max_temp = records[i].temperature;
        } else {
            if (records[i].temperature < *min_temp) {
                *min_temp = records[i].temperature;
            }
            if (records[i].temperature > *max_temp) {
                *max_temp = records[i].temperature;
            }
        }

        *sum += records[i].temperature;
        ++(*matched);
    }

    return *matched > 0;
}

void print_monthly_stats(const TempRecord *records, size_t count, int year, int month)
{
    long sum = 0;
    size_t matched = 0;
    int min_temp = 0;
    int max_temp = 0;

    printf("=== Статистика за месяц %02d.%04d ===\n", month, year);

    if (!collect_month_stats(records, count, year, month, &sum, &matched, &min_temp, &max_temp)) {
        printf("Нет данных за указанный месяц\n");
        return;
    }

    printf("Среднемесячная температура: %.2f\n", (double)sum / (double)matched);
    printf("Минимальная температура: %d\n", min_temp);
    printf("Максимальная температура: %d\n", max_temp);
}

void print_yearly_stats(const TempRecord *records, size_t count, int year)
{
    long sum = 0;
    size_t matched = 0;
    int min_temp = 0;
    int max_temp = 0;

    printf("=== Статистика за %04d год ===\n", year);

    if (!collect_year_stats(records, count, year, &sum, &matched, &min_temp, &max_temp)) {
        printf("Нет данных за указанный год\n");
        return;
    }

    printf("Среднегодовая температура: %.2f\n", (double)sum / (double)matched);
    printf("Минимальная температура: %d\n", min_temp);
    printf("Максимальная температура: %d\n", max_temp);
}

void print_all_monthly_stats(const TempRecord *records, size_t count, int year)
{
    for (int month = 1; month <= 12; ++month) {
        long sum = 0;
        size_t matched = 0;
        int min_temp = 0;
        int max_temp = 0;

        if (!collect_month_stats(records, count, year, month, &sum, &matched, &min_temp, &max_temp)) {
            continue;
        }

        print_monthly_stats(records, count, year, month);
        printf("\n");
    }
}
