#ifndef TEMP_API_H
#define TEMP_API_H

#include <stddef.h>

#define TEMP_MIN (-99)
#define TEMP_MAX 99

typedef struct {
    int year;
    char month[3];
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
int temp_array_add(TempArray *array, TempRecord record);
int temp_array_delete(TempArray *array, size_t index);
void temp_array_sort(TempArray *array);
void temp_array_print(const TempArray *array);

void print_monthly_avg(const TempRecord *records, size_t count, int year, const char *month);
void print_monthly_min(const TempRecord *records, size_t count, int year, const char *month);
void print_monthly_max(const TempRecord *records, size_t count, int year, const char *month);

void print_yearly_avg(const TempRecord *records, size_t count, int year);
void print_yearly_min(const TempRecord *records, size_t count, int year);
void print_yearly_max(const TempRecord *records, size_t count, int year);

void print_help(const char *program_name);

#endif /* TEMP_API_H */
