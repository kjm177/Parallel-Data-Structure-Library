
/**
Base Pager class for all types of paging algorithms
*/

#ifndef pList_h
#define pList_h

#include<iostream>
#include "LinkedList.h"
#include<vector>

using namespace std;

template <typename T>
class pList
{

public:

    size_t pListSize;  // size of list
    bool isEmpty;
    T *sll;
    pList();
   // pList(size_t);
   // virtual void sortpList(bool) = 0;
   // virtual void reversepList() = 0;

};
#endif
