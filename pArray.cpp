
#include <stdio.h>
#include <stdlib.h>
#include "pArray.h"


pArray* pArrayConstructor(size_t pArraySize)
{
    pArray* newArray = (pArray *)malloc(sizeof(pArray));
    return newArray;
}

void array_sort(pArray *ar, int (*cmp) (const void*, const void*))
{
    qsort(ar->buffer, ar->size, sizeof(void*), cmp);
}

void array_reverse(pArray *ar)
{
    size_t i;
    size_t j;
    for (i = 0, j = ar->size - 1; i < (ar->size - 1) / 2; i++, j--) {
        void *tmp = ar->buffer[i];
        ar->buffer[i] = ar->buffer[j];
        ar->buffer[j] = tmp;
    }
}
