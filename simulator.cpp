#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <omp.h>
#include "ForwardListLock.h"
#include "pList.h"
#include "pArray.h"
#include "utility.h"

using namespace std;



int main(int argc, char* argv[])
{
    printf("Parallel data structure simulator has begun!\n");
    string inputFileName = "test_list_15.txt";

    struct testCase* t = readInput(inputFileName);


    cout<<"DS: "<<t->dataStructure<<endl;
    cout<<"NumOfOperations: "<<t->numOfOperations<<endl;
    for(int i = 0 ; i < t->numOfOperations ; i++)
    {
        for(int j = 0 ; j < (t->operations[i]).size() ; j++)
            cout<<t->operations[i][j]<<" ";
            cout<<endl;
    }

    if(t->dataStructure == 1)
        testArray(t);
    else if(t->dataStructure == 2)
        testForwardList(t);
    else
        testList(t);


    return 0;
}
