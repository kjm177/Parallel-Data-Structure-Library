#include <iostream>
#include "pArray.h"

using namespace std;


int main(int argc, char* argv[])
{
    printf("Parallel data structure simulator has begun!\n");
    pArray* p = pArrayConstructor(10);

    int i;
    for(i = 0 ; i < 10 ; i++)
        p[i] = i;
    for(i = 0 ; i < 10 ; i++)
        cout<<p[i]<<endl;



    return 0;
}
