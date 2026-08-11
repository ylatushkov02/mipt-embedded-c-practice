#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stddef.h>

#define TEMP_MIN (-99)
#define TEMP_MAX 99

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int temperature;
} TempRecord;

typedef struct {
    TempRecord *records;
    size_t count;
    size_t capacity;
} TempArray;

TempArray *temp_array_create(void);
void temp_array_free(TempArray *array);
int temp_array_load_csv(TempArray *array, const char *filename);
void temp_array_sort(TempArray *array);

void print_help(const char *program_name);

void print_monthly_stats(const TempRecord *records, size_t count, int year, int month);
void print_yearly_stats(const TempRecord *records, size_t count, int year);
void print_all_monthly_stats(const TempRecord *records, size_t count, int year);

#endif /* TEMP_FUNCTIONS_H */
