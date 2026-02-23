#include <stdlib.h>
#include "sort_funcs.h"

#define SHRINK_STEP 1.247

void swap(void *a, void *b, size_t size) {
    char *p1 = (char *)a;
    char *p2 = (char *)b;
    char temp;

    while (size) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
        p1++;
        p2++;
        size--;
    }
}

void comb_sort(void *array, size_t len, size_t size, compare_func_t cmp) {
    size_t step = len;
    char *ptr = (char *)array;
    int swapped = 0;
    while (step > 1 || swapped) {
        swapped = 0;
        step /= SHRINK_STEP;
        if (step < 1) {
            step = 1;
        }
        for (int i = 0; i < len - step; ++i) {
            void *p1 = ptr + size * i;
            void *p2 = ptr + size * (i + step);
            if (cmp(p1, p2) > 0) {
                swap(p1, p2, size);
                swapped = 1;
            }
        }
    }
    return;
}

void selection_sort(void *array, size_t len, size_t size, compare_func_t cmp) {
    size_t left = 0, right = len - 1;
    
    char *ptr = (char *)array;

    void *p1 = NULL, *p_min = NULL, *p_max = NULL, *p_left = NULL, *p_right = NULL;

    while (left < right) {
        p_min = array + size * left;
        p_max = array + size * left;

        for (int i = left; i <= right; ++i) {
            p1 = array + size * i;

            if (cmp(p1, p_min) < 0) {
                p_min = p1;
            }
            else if (cmp(p1, p_max) > 0) {
                p_max = p1;
            }
        }
        p_left = array + size * left;
        p_right = array + size * right;
        
        if (p_min != p_left) {
            swap(p_min, p_left, size);
        }
        if (p_max == p_left) {
            p_max = p_min;
        }
        if (p_max != p_right) {
            swap(p_max, p_right, size);
        }
        left++;
        right--;
    }
    return;
}















