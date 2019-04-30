

#ifndef pListLock_h
#define pListLock_h

#include <iostream>
#include <unordered_set>
#include <vector>
#include <omp.h>

#define sentinalInt -99999999

using namespace std;

template <typename T>
struct pListLockNode
{
    T data;
    //omp_lock_t nodeLock;
    pListLockNode* next;
    pListLockNode* prev;

    pListLockNode(T element) : data(element), next(NULL), prev(NULL){}
};



template <typename T>
class pListLock
{
    size_t pListSize;
    pListLockNode<T> *pListHead;
    pListLockNode<T> *pListTail;
    omp_lock_t listLock;

public:

/**
Constructor for generic doubly linked list type T
*/
    pListLock()
    {
        pListSize = 0;
        pListHead = NULL;
        pListTail = NULL;
        pListHead = new pListLockNode<T>(sentinalInt);
        pListTail = new pListLockNode<T>(sentinalInt);
        omp_init_lock(&(listLock));
        pListHead->next = pListTail;
        pListTail->prev = pListHead;
    }

    bool isEmpty()
    {
        if(pListSize == 0)
            return true;
        return false;
    }

    int listSize()
    {
        return pListSize;
    }

    void acquireLock()
    {
        #pragma omp critical
        {
            omp_set_lock(&(listLock));
        }
    }

    void releaseLock()
    {
        omp_unset_lock(&(listLock));
    }

    void pushFront(T element)
    {
            //cout<<"Pushing new element at front "<<endl;
        pListLockNode<T>* p = new pListLockNode<T>(element);
        acquireLock();

        p->next = pListHead->next;
        p->prev = pListHead;
        pListHead->next->prev = p;
        pListHead->next = p;
        pListSize++;
        releaseLock();
    }

    void pushBack(T element)
    {
        acquireLock();
        //cout<<"Pushing new element at back "<<endl;
        pListLockNode<T>* p = new pListLockNode<T>(element);
        omp_init_lock(&(p->nodeLock));

        omp_set_lock(&(pListTail->prev->nodeLock));
        omp_set_lock(&(pListTail->nodeLock));


        p->prev = pListTail->prev;
        p->next = pListTail;
        pListTail->prev->next = p;
        pListTail->prev = p;
        pListSize++;
        releaseLock();

    }

    void popFront()
    {
        if(pListSize != 0)
        {
            acquireLock();
            if(pListHead->next->data != sentinalInt)
            {
                pListLockNode<T>* p = pListHead;
                pListHead = p->next;
                p->next->prev = NULL;
                pListHead->data = sentinalInt;

                free(p);
                pListSize--;

            }
            releaseLock();
        }
    }

    void popBack()
    {
        if(pListSize != 0)
        {
            acquireLock();
            if(pListTail->prev->data != sentinalInt)
            {
                pListLockNode<T>* p = pListTail;
                pListTail = p->prev;
                p->prev->next = NULL;
                pListTail->data = sentinalInt;
                free(p);
                pListSize--;
                omp_unset_lock(&(pListTail->nodeLock));
            }
            releaseLock();
        }
    }

    T front()
    {
        //cout<<"Front"<<endl;
        return pListHead->next->data;
    }

    T back()
    {
        //cout<<"Back"<<endl;
        return pListTail->prev->data;
    }

    bool searchElement(T element)
    {
        pListLockNode<T>* it = pListHead->next;
        while(it->data != sentinalInt)
        {
            if(it->data == element)
                return true;
        }
        return false;
    }

    T getIndex(int index)
    {

        if(pListSize == 0 || index < 0 || index >= pListSize)
        {
            //cout<<"Index out of bounds"<<endl;
            return dummy->data;
        }
        pListLockNode<T>* it = pListHead->next;
        while(index && it)
        {
            it = it->next;
            index--;
        }
        if(it)
            return it->data;
        return dummy->data;
    }

    void insertAt(T element, int index)
    {
        //cout<<"Inserting element at index "<<index<<endl;
        if(index < 0 || index  > pListSize)
        {
            //cout<<"Invalid index!"<<endl;
            return;
        }

        pListLockNode<T>* prev = pListHead;
        pListLockNode<T>* it = prev->next;

        while(index)
        {
            if(!it)
            {
                //cout<<"Invalid index"<<endl;
                return;
            }
            prev = it;
            it = it->next;
        }
        acquireLock();
        pListLockNode<T>* p = new pListLockNode<T>(element);
        p->next = it;
        p->prev = prev;
        prev->next = p;
        it->prev = p;
        pListSize++;
        releaseLock();
    }


    void eraseAt(int index)
    {
        //cout<<"Erase element"<<endl;
        if(index < 0 || index  >= pListSize)
        {
            //cout<<"Invalid index!"<<endl;
            return;
        }
        pListLockNode<T>* prev = pListHead;
        pListLockNode<T>* it = prev->next;

        index;
        while(index)
        {
            if(!it)
            {
                //cout<<"Invalid index"<<endl;
                return;
            }
            prev = it;
            it = it->next;
        }

        if(!it || it->data == sentinalInt)
        {
            //cout<<"Invalid index!"<<endl;
            return;
        }

        acquireLock();
        prev->next = it->next;
        it->next->prev = prev;
        free(it);
        pListSize--;
        releaseLock();
    }


    void sortList(bool ascending)
    {
        //cout<<"NOT READY. Sorting: "<<endl;
        //pListLockNode<T>* head = copyList(pListHead, NULL);
        return;
        if(ascending)
        {
            if(pListSize > 1)
            {
                for(int i = 0; i < pListSize - 1; i++)
                {
                    pListLockNode<T>* current = pListHead;
                    pListLockNode<T>* next = pListHead->next;
                    for(int j = 0; j < pListSize-i-1; j++)
                    {
                        if(current->data > next->data)
                        {
                            T temp = current->data;
                            current->data = next->data;
                            next->data = temp;
                        }
                        current = next;
                        next = next->next;
                    }
                }
            }
        }
        else
        {
            if(pListSize > 1)
            {
                for(int i = 0; i < pListSize-1; i++)
                {
                    pListLockNode<T>* current = pListHead;
                    pListLockNode<T>* next = pListHead->next;
                    for(int j = 0; j < pListSize-i-1; j++)
                    {
                        if(current->data < next->data)
                        {
                            T temp = current->data;
                            current->data = next->data;
                            next->data = temp;
                        }
                        current = next;
                        next = next->next;
                    }
                }
            }
        }
    }



    void reverseList()
    {
        //cout<<"NOT READY!"<<endl;
        pListLockNode<T>* it;
        pListLockNode<T>* prev;
        acquireLock();

        it = pListHead;
        prev = NULL;
        pListTail = it;

        while(it != NULL)
        {
            pListLockNode<T>* next = it->next;
            it->next = prev;
            it->prev = next;
            prev = it;
            it = next;
        }
        pListHead = prev;

        releaseLock();
        return reversedList;
    }

    unordered_set<T> uniqueList()
    {
        //cout<<"NOT READY!"<<endl;
        pListLockNode<T>* it;
        pListLockNode<T>* prev;
        unordered_set<T> hashSet;
        return hashSet;
        acquireLock();

        while(it != NULL)
        {
            prev = it;
            if(hashSet.find(it->data) == hashSet.end())
            {
                hashSet.insert(it->data);
            }
            it = it->next;
        }

        releaseLock();

        return hashSet;
    }


    void printList()
    {
        //cout<<"Printing Doubly linked list: "<<endl;
        pListLockNode<T>* it = pListHead->next;
        while(it->data != sentinalInt)
        {
            cout<<it->data<<" ";
            it = it->next;
        }
        cout<<endl;
    }

};

#endif // pListLock_h

