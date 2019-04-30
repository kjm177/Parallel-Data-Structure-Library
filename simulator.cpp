#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <omp.h>
#include "ForwardListLock.h"
#include "pList.h"
#include "pArray.h"
#include "utility.h"

using namespace std;



int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout<<"ERROR! Missing program arguments. \n"<<endl;
        return 0;
    }
    char *fileName = argv[1];
    string inputFileName(fileName);

    int numOfThreads = atoi(argv[2]);

    printf("Parallel data structure simulator has begun!\n");

    struct testCase* t = readInput(inputFileName);


    //cout<<"DS: "<<t->dataStructure<<endl;
    //cout<<"NumOfOperations: "<<t->numOfOperations<<endl;
//for(int i = 0 ; i < t->numOfOperations ; i++)
   // {
     //   for(int j = 0 ; j < (t->operations[i]).size() ; j++)
            //cout<<t->operations[i][j]<<" ";
            //cout<<endl;
    //}

    if(t->dataStructure == 1)
        testArray(t, numOfThreads);
    else if(t->dataStructure == 2)
        testForwardList(t, numOfThreads);
    else if(t->dataStructure == 3)
        testList(t, numOfThreads);
   // else
   //     testListLock(t,numOfThreads);


    return 0;
}
