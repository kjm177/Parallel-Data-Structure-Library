#ifndef utility_h
#define utility_h


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <omp.h>
#include "ForwardListLock.h"
#include "pList.h"
#include "pArray.h"

using namespace std;

struct testCase
{
    int dataStructure;
    int numOfOperations;
    vector<vector<int>> operations;
};

int convertStringToInteger(string s)
{
    stringstream convert(s);
    int ans;
    convert >> ans;
    return(ans);
}

vector<string> tokenizer(string input)
{
    vector <string> tokens;
    stringstream check1(input);
    string intermediate;
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

struct testCase* readInput(string inputFileName)
{
    struct testCase* newTestCase = new testCase();
    newTestCase->numOfOperations = 0;
    ifstream inputFile;
    inputFile.open(inputFileName);
    if(!inputFile.is_open())
        cout<<"ERROR! Unable to open file!";
    else
    {
        string token;
        getline(inputFile, token);
        newTestCase->dataStructure = convertStringToInteger(token);
        getline(inputFile, token);
        int numOps = convertStringToInteger(token);
        newTestCase->numOfOperations = numOps;

        for(int i = 0 ; i < numOps ; i++)
        {
            vector<int> currentOperation;
            getline(inputFile, token);
            vector<string> tokens = tokenizer(token);
            for(int j = 0 ; j < tokens.size() ; j++)
                currentOperation.push_back(convertStringToInteger(tokens[j]));
            (newTestCase->operations).push_back(currentOperation);
        }
    }
    return newTestCase;
}

void testList(struct testCase* t, int numThreads)
{
    if(t->numOfOperations < 1)
    {
        cout<<"ERROR! No operations in test case!"<<endl;
        return;
    }

    //cout<<t->operations[0][1];
    pList <int> dll;
    dll.printList();

#pragma omp parallel for num_threads(numThreads)
    for(int i = 1 ; i < t->numOfOperations ; i++)
    {
        //cout<<i<<" ";
        switch(t->operations[i][0])
        {
        case 1:
            {
                int s = dll.listSize();
                break;
            }
        case 2:
            {
                bool check = dll.isEmpty();
                break;
            }
        case 3:
            {
                dll.pushFront(t->operations[i][1]);
                break;
            }
        case 4:
            {
                dll.pushBack(t->operations[i][1]);
                break;
            }
        case 5:
            {
                dll.popFront();
                break;
            }
        case 6:
            {
                dll.popBack();
                break;
            }
        case 7:
            {
                dll.insertAt(t->operations[i][1], t->operations[i][2]);
                break;
            }
        case 8:
            {
                dll.getIndex(t->operations[i][1]);
                break;
            }
        case 9:
            {
                int element = dll.front();
                break;
            }
        case 10:
            {
                int element = dll.back();
                break;
            }
        case 11:
            {
                vector <int> dllCopy = dll.reverseList();
                break;
            }
        case 12:
            {
                dll.eraseAt(t->operations[i][1]);
                break;
            }
        case 13:
            {
                dll.uniqueList();
                break;
            }
        case 14:
            {
                dll.sortList(t->operations[i][1]);
                break;
            }
        default:
            {
                cout<<"default";
            }
        }
        //dll.printList();
    }
    cout<<endl;
    cout<<"Final Doubly linked list size: "<<dll.listSize()<<endl;

}

void testArray(struct testCase* t, int numThreads)
{
    if(t->numOfOperations < 1)
    {
        cout<<"ERROR! No operations in test case!"<<endl;
        return;
    }

    cout<<t->operations[0][1];
    pArray <int> arr(t->operations[0][1]);
    arr.printArray();

    for(int i = 1 ; i < t->numOfOperations ; i++)
    {
        cout<<i<<" ";
        switch(t->operations[i][0])
        {
        case 1:
            {
                arr[t->operations[i][1]] = t->operations[i][2];
                break;
            }
        case 2:
            {
                int s = arr.arraySize();
                break;
            }
        case 3:
            {
                bool isEmpty = arr.isEmpty();
                break;
            }
        case 4:
            {
                int arrayFront = arr.front();
                break;
            }
        case 5:
            {
                int arrayBack = arr.back();
                break;
            }
        case 6:
            {
                int num = arr.at(t->operations[i][1]);
                break;
            }
        case 7:
            {
                arr.fillArray(t->operations[i][1]);
                break;
            }
        case 8:
            {
                arr.sortArray(t->operations[i][1]);
                break;
            }
        case 9:
            {
                arr.reverseArray();
                break;
            }
        default:
            {
                cout<<"default";
            }
        }
        arr.printArray();
    }

}

void testForwardList(struct testCase* t, int numThreads)
{
    if(t->numOfOperations < 1)
    {
        cout<<"ERROR! No operations in test case!"<<endl;
        return;
    }

    pSList <int> sll;

#pragma omp parallel for num_threads(numThreads)
    for(int i = 1 ; i < t->numOfOperations ; i++)
    {
        switch(t->operations[i][0])
        {
        case 1:
            {
                int s = sll.listSize();
                cout<<"List size is "<<s<<endl;
                break;
            }
        case 2:
            {
                bool check = sll.isEmpty();
                if(check) cout<<"List is empty!"<<endl;
                else cout<<"List is not empty!"<<endl;
                break;
            }
        case 3:
            {
                sll.pushFront(t->operations[i][1]);
                sll.printList();
                break;
            }
        case 4:
            {
                sll.popFront();
                sll.printList();
                break;
            }
        case 5:
            {
                sll.insertAfter(t->operations[i][1], t->operations[i][2]);
                break;
            }
        case 6:
            {
                int element = sll.getIndex(t->operations[i][1]);
		cout<<"Element at index is: "<<element<<endl;
		break;
            }
        case 7:
            {
                int element = sll.front();
                cout<<"Element at front is "<<element<<endl;
		break;
            }
        case 8:
            {
                sll.reverse();
                break;
            }
        case 9:
            {
                sll.erase(t->operations[i][1]);
                break;
            }
        case 10:
            {
              sll.unique();
              break;
            }
        case 11:
            {
              sll.sort(t->operations[i][1]);
              break;
            }
        default:
            {
                cout<<"default";
            }
        }
    }

}


#endif // utility_h
