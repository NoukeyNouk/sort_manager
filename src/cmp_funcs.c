#include <string.h>
#include "cmp_funcs.h"

int time_cmp(const void *a, const void *b) {
    double num1 = *(double *)a;
    double num2 = *(double *)b;
    if (num1 - num2 > 0) {
        return 1;
    }
    else if (num1 == num2) {
        return 0;
    }
    return -1;
}

int cmp_mark(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;
    return strcmp(car1->mark, car2->mark);
}

int cmp_mark_reversed(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;
    return strcmp(car1->mark, car2->mark) * -1;
}

int cmp_owner(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;
    return strcmp(car1->owner, car2->owner);
}

int cmp_owner_reversed(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;
    return strcmp(car1->owner, car2->owner) * -1;
}

int cmp_mileage(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;

    float mileage1 = car1->mileage;
    float mileage2 = car2->mileage;
    if (mileage1 - mileage2 > 0) {
        return 1;
    }
    else if (mileage1 - mileage2 < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

int cmp_mileage_reversed(const void *a, const void *b) {
    const Car *car1 = *(const Car **)a;
    const Car *car2 = *(const Car **)b;

    float mileage1 = car1->mileage;
    float mileage2 = car2->mileage;
    if (mileage1 - mileage2 > 0) {
        return -1;
    }
    else if (mileage1 - mileage2 < 0) {
        return 1;
    }
    else {
        return 0;
    }
}
