#ifndef P_ARRAY_H
#define P_ARRAY_H

#include <iostream>
using namespace std;



template <typename T>
class pArray
{
    size_t pArraySize;  // size of list
    T *myArray;
    typedef T temp;

public:


/**
Constructor for generic array type T, and size s
*/
    pArray(size_t s)
    {
        pArraySize = s;
        myArray = new T [pArraySize];
    }

/**
Overloading '[]' operator for array element access
*/
    T &operator[] (int index)
    {
        if(index >= 0 && index < pArraySize)
            return myArray[index];
        else
        {
            cout<<"Array index out of bound!"<<endl;
            throw index;
        }
    }

/**
Returns array size
*/
    int arraySize()
    {
        return pArraySize;
    }
/**
Returns true if array is empty
*/
    bool isEmpty()
    {
        if(pArraySize == 0)
            return true;
        return false;
    }
/**
Returns element at the front of the array
*/
    T front()
    {
        if(pArraySize == 0)
            cout<<"Array is empty!"<<endl;
        return myArray[0];
    }
/**
Returns element at the back of the array
*/
    T back()
    {
        if(pArraySize == 0)
            cout<<"Array is empty!";
        return myArray[pArraySize-1];
    }
/**
Returns element at position 'index' of the array
*/
    T at(int index)
    {
        if(index >= 0 && index < pArraySize)
            return myArray[index];
        else
        {
            cout<<"Array index out of bound!"<<endl;
            throw index;
        }
    }

    void fillArray(T element)
    {
        for(int i = 0 ; i < pArraySize ; i++)
            myArray[i] = element;
    }

    void sortArray(bool ascending)
    {
        T temp;
        if(ascending)
        {
            for(int i = 0 ; i < pArraySize ; i++)
            {
                for(int j = i+1 ; j < pArraySize ; j++)
                {
                    if(myArray[i] > myArray[j])
                    {
                        temp = myArray[i];
                        myArray[i] = myArray[j];
                        myArray[j] = temp;
                    }
                }
            }
        }
        else
        {
            for(int i = pArraySize - 1 ; i >= 0 ; i--)
            {
                for(int j = i - 1 ; j >= 0 ; j--)
                {
                    if(myArray[i] > myArray[j])
                    {
                        temp = myArray[i];
                        myArray[i] = myArray[j];
                        myArray[j] = temp;
                    }
                }
            }
        }
    }


    void reverseArray()
    {
        int lower = 0;
        int upper = pArraySize - 1;
        T temp;
        for(; lower < upper ; lower++, upper--)
        {
            temp = myArray[lower];
            myArray[lower] = myArray[upper];
            myArray[upper] = temp;
        }
    }

    void printArray()
    {
        for(int i = 0 ; i < pArraySize ; i++)
            cout<<myArray[i]<<"  ";
        cout<<endl;
    }



    ~pArray()
    {
        free(myArray);
        cout<<"Array deleted!"<<endl;
    }

};




#endif /* P_ARRAY_H */
