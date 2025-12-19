#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "sort_funcs.h"
#include "cmp_funcs.h"

#define MARK_LETTERS "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM- "

typedef void (*sort_t)(void *, size_t, size_t, compare_func_t);

Car *Car_random();
int rand_int(int, int);
float rand_float(float, float);
sort_t sort_selection(int);
compare_func_t cmp_selection(int, int);

int main(int argc, char **argv) {
    srand(time(NULL));

    int opt = 0;
    int reverse_flag = 0, sort_flag = 0;
    int field_flag = 0, elements_flag = 0;
    int arrays_flag = 0, print_flag = 0;
    int important_flag = 0, medium_flag = 0;
    
    int field_number = 2;
    int elements_len = 10;
    int arrays_len = 10;
    int sort_number = 0;

    double *times = NULL;

    // parsing flags
    while ((opt = getopt(argc, argv, "mpris:f:e:a:")) != -1) {
        switch (opt) {
            case 'p':
                print_flag = 1;
                break;

            case 'r':
                reverse_flag = 1;
                break;

            case 's':
                sort_flag = 1;
                sort_number = atoi(optarg);
                break;

            case 'f':
                field_flag = 1;
                field_number = atoi(optarg);
                break;

            case 'e':
                elements_flag = 1;
                elements_len = atoi(optarg);
                break;

            case 'a':
                arrays_flag = 1;
                arrays_len = atoi(optarg);
                break;
            
            case 'i':
                important_flag = 1;
                break;

            case 'm':
                medium_flag = 1;
                break;

            default:
                printf("Usage: %s [FLAGS]\n", argv[0]);
                printf("\nFLAGS:\n");
                printf("\n-p\n\tprint sorted arrays\n");
                printf("\n-r\n\treverse sort algorithm\n");
                printf("\n-i\n\tshow only important info\n");
                printf("\n-m\n\tcount medium instead of average time\n");
                printf("\n-f [FIELD_NUMBER]\n\tselect field used for sort (0 - Mark, 1 - owner, 2 - mileage)\n");
                printf("\n-s [SORT_NUMBER]\n\tselect sort algorithm (0 - comb_sort, 1 - selection_sort, 2 - qsort)\n");
                printf("\n-a [ARRAYS_COUNT]\n\tselect count of sorting arrays\n");
                printf("\n-e [ELEMENTS_COUNT]\n\tselect count of elements in each array\n");
                return 1;
                break;
        }
    }
    
    printf("SELECTED OPTIONS:\n");
    printf("Print:     %d\n", print_flag);
    printf("Sort:      %d\n", sort_number);
    printf("Field:     %d\n", field_number);
    printf("Arrays:    %d\n", arrays_len);
    printf("Elements:  %d\n", elements_len);
    printf("Reverse:   %d\n", reverse_flag);
    printf("Important: %d\n\n", important_flag);

    //initializing arrays of Cars
    Car ***arrays = malloc(arrays_len * sizeof(Car **));
    if (!arrays) {
        return 1;
    }

    for (int i = 0; i < arrays_len; ++i) {
        arrays[i] = malloc(elements_len * sizeof(Car *));
        if (!(arrays[i])) {
            goto cleanup;
        }

        for (int j = 0; j < elements_len; ++j) {
            arrays[i][j] = Car_random();
            if (!(arrays[i][j])) {
                goto cleanup;
            }
        }
    }
    
    //finding preferred cmp_func
    compare_func_t cmp_func = cmp_selection(field_number, reverse_flag);
    
    //finding preferred sort_func
    sort_t sort_func = sort_selection(sort_number);

    //timing of the sort
    struct timespec start, end;
    times = malloc(arrays_len * sizeof(double));
    if (!times) {
        goto cleanup;
    }

    for (int i = 0; i < arrays_len; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        sort_func(arrays[i], elements_len, sizeof(Car *), cmp_func);
        clock_gettime(CLOCK_MONOTONIC, &end);
 
        times[i] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    }
    
    if (print_flag && !important_flag) {
        for (int i = 0; i < arrays_len; ++i) {
            printf("\n\n==================\n");
            printf("    ARRAY %d\n", i);
            printf("==================\n");
            for (int j = 0; j < elements_len; ++j) {
                printf("Mark:    %s\n", arrays[i][j]->mark);
                printf("Owner:   %s\n", arrays[i][j]->owner);
                printf("Mileage: %f\n\n", arrays[i][j]->mileage);
            }
        }
    }

    if (!important_flag) {
        printf("timed:\n");
        for (int i = 0; i < arrays_len; ++i) {
            printf("%lf\n", times[i]);
        }
    }

    double all_time = 0;
    if (medium_flag) {
        qsort(times, arrays_len, sizeof(double), time_cmp);
        all_time = times[arrays_len / 2];
    }
    else {
        double time_sum = 0;
        for (int i = 0; i < arrays_len; ++i) {
            time_sum += times[i];
        }
        all_time = time_sum / arrays_len;
    }

    printf("Average:  %lf\n", all_time);
    printf("Elements: %d\n", elements_len);

    //free all
cleanup:
    if (times) {
        free(times);
    }
    if (arrays) {
        for (int i = 0; i < arrays_len; ++i) {
            if (arrays[i]) {
                for (int j = 0; j < elements_len; ++j) {
                    if (arrays[i][j]) {
                        if (arrays[i][j]->owner) {
                            free(arrays[i][j]->owner);
                        }
                    }                
                    free(arrays[i][j]);
                }
                free(arrays[i]);
            }
        }
        free(arrays);
    }
    return 0;
}

Car *Car_random() {
    Car *car = malloc(sizeof(Car));
    if (!car) {
        return NULL;
    }
    char letter = (char)rand_int(0, 53);

    for (int i = 0; i < 16; ++i) {
        letter = (char)rand_int(0, 53);
        car->mark[i] = MARK_LETTERS[letter];
    }
    car->mark[16] = 0;

    int len = rand_int(30, 100);

    car->owner = calloc(len + 1, sizeof(char));
    if (!car->owner) {
        free(car);
        return NULL;
    }

    for (int i = 0; i < len; ++i) {
        letter = (char)rand_int(32, 126);

        car->owner[i] = letter;
    }
    car->mileage = rand_float(0.0, 1000.0);

    return car;
}

int rand_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

float rand_float(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

sort_t sort_selection(int sort_number) {
    if (sort_number == 0) {
        return comb_sort;
    }
    else if (sort_number == 1) {
        return selection_sort;
    }
    return qsort;
}

compare_func_t cmp_selection(int field_number, int reverse_flag) {
    if (field_number == 0) {
        if (!reverse_flag) {
            return cmp_mark;
        }
        return cmp_mark_reversed;
    }
    else if (field_number == 1) {
        if (!reverse_flag) {
            return cmp_owner;
        }
        return cmp_owner_reversed;
    }
    else if (field_number == 2) {
        if (!reverse_flag) {
            return cmp_mileage;
        }
        return cmp_mileage_reversed;
    }
    return cmp_mileage;
}
