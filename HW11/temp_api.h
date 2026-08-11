#ifndef TEMP_API_H
#define TEMP_API_H

#include <stddef.h>

#define TEMP_MIN (-99)
#define TEMP_MAX 99

typedef struct {
    int year;           /* yyyy — год, 4 цифры */
    char month[3];      /* mm — месяц, 2 символа */
    int day;            /* dd — день */
    int hour;           /* hh — часы */
    int minute;         /* mm — минуты */
    int temperature;    /* целое число от -99 до 99 */
} TempRecord;

/* Статистика за месяц */
void print_monthly_avg(const TempRecord *records, size_t count, int year, const char *month);
void print_monthly_min(const TempRecord *records, size_t count, int year, const char *month);
void print_monthly_max(const TempRecord *records, size_t count, int year, const char *month);

/* Статистика за год */
void print_yearly_avg(const TempRecord *records, size_t count, int year);
void print_yearly_min(const TempRecord *records, size_t count, int year);
void print_yearly_max(const TempRecord *records, size_t count, int year);

#endif /* TEMP_API_H */
