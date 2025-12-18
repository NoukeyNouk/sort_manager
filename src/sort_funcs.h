#ifndef SORT_LIB
#define SORT_LIB

typedef int (*compare_func_t)(const void *, const void *);

void comb_sort(void *array, size_t len, size_t size, compare_func_t cmp);
void selection_sort(void *array, size_t len, size_t size, compare_func_t cmp);

#endif
