#include <iostream>
#include "pArray.h"

pArray<T>::pArray(size_t s)
{
    pArraySize = s;
    myArray = new T [pArraySize];
}


