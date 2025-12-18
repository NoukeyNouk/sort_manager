#ifndef CMP_FUNCS
#define CMP_FUNCS

typedef struct Car {
    char mark[17];
    char *owner;
    float mileage;
} Car;

int time_cmp(const void *a, const void *b);

int cmp_mark(const void *a, const void *b);
int cmp_mark_reversed(const void *a, const void *b);

int cmp_owner(const void *a, const void *b);
int cmp_owner_reversed(const void *a, const void *b);

int cmp_mileage(const void *a, const void *b);
int cmp_mileage_reversed(const void *a, const void *b);

#endif
