#include "temp_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *csv_file = NULL;
    int filter_month = 0;
    int has_month_filter = 0;
    TempArray *array = NULL;
    int year;

    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

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

    array = temp_array_create();
    if (array == NULL) {
        fprintf(stderr, "Ошибка: не удалось создать массив\n");
        return 1;
    }

    if (temp_array_load_csv(array, csv_file) != 0) {
        fprintf(stderr, "Ошибка: не удалось загрузить корректные данные из файла %s\n", csv_file);
        temp_array_free(array);
        return 1;
    }

    temp_array_sort(array);
    year = array->records[0].year;

    if (has_month_filter) {
        print_monthly_stats(array->records, array->count, year, filter_month);
    } else {
        print_all_monthly_stats(array->records, array->count, year);
        print_yearly_stats(array->records, array->count, year);
    }

    temp_array_free(array);
    return 0;
}
