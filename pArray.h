#include <stdio.h>
#include <stdlib.h>

#ifndef P_ARRAY_H
#define P_ARRAY_H

typedef struct
{
    size_t size;
    void** buffer;
} pArray;

void array_reverse(pArray *ar);
void array_sort(pArray *ar, int (*cmp) (const void*, const void*));
pArray* pArrayConstructor(size_t pArraySize);



#endif /* P_ARRAY_H */
