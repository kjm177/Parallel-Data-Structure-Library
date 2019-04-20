#include <iostream>
#include "pArray.h"

using namespace std;


int main(int argc, char* argv[])
{
    printf("Parallel data structure simulator has begun!\n");


    pArray < int > a(10);


    int temp = -1;
    for(int i = 0 ; i < 10 ; i++, temp *= -1)
        a[i] = i*temp;

    a.printArray();


    a.sortArray(true);
    a.printArray();


    a.sortArray(false);
    a.printArray();
    //a.reverseArray();
    //a.printArray();

//    a.~pArray();




    return 0;
}
