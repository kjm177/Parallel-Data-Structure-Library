
#ifndef pList_h
#define pList_h

#include <iostream>
#include <unordered_set>
#include <omp.h>

#define sentinalInt -9999999

using namespace std;

template <typename T>
struct pListNode
{
    T data;
    omp_lock_t nodeLock;
    pListNode* next;
    pListNode* prev;

    pListNode(T element) : data(element), next(NULL), prev(NULL){}
};



template <typename T>
class pList
{
    size_t pListSize;
    pListNode<T> *pListHead;
    pListNode<T> *pListTail;
    pListNode<T> *dummy;

public:

/**
Constructor for generic doubly linked list type T
*/
    pList()
    {
        pListSize = 0;
        pListHead = NULL;
        pListTail = NULL;
        dummy = new pListNode<T>(sentinalInt);
        pListHead = new pListNode<T>(sentinalInt);
        omp_init_lock(&(pListHead->nodeLock));
        pListTail = new pListNode<T>(sentinalInt);
        omp_init_lock(&(pListTail->nodeLock));
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

    void pushFront(T element)
    {
        #pragma omp critical
        {
            cout<<"Pushing new element at front "<<endl;
            pListNode<T>* p = new pListNode<T>(element);
            omp_init_lock(&(p->nodeLock));

            omp_set_lock(&(pListHead->nodeLock));
            omp_set_lock(&(pListHead->next->nodeLock));

            p->next = pListHead->next;
            p->prev = pListHead;
            pListHead->next->prev = p;
            pListHead->next = p;
            pListSize++;

            omp_unset_lock(&(pListHead->nodeLock));
            omp_unset_lock(&(p->next->nodeLock));
        }
    }

    void pushBack(T element)
    {
        #pragma omp critical
        {
            cout<<"Pushing new element at back "<<endl;
            pListNode<T>* p = new pListNode<T>(element);
            omp_init_lock(&(p->nodeLock));

            omp_set_lock(&(pListTail->prev->nodeLock));
            omp_set_lock(&(pListTail->nodeLock));


            p->prev = pListTail->prev;
            p->next = pListTail;
            pListTail->prev->next = p;
            pListTail->prev = p;
            pListSize++;

            omp_unset_lock(&(p->prev->nodeLock));
            omp_unset_lock(&(pListTail->nodeLock));

        }
    }

    void popFront()
    {
        if(pListSize == 0)
        {
            cout<<"ERROR! List is empty!"<<endl;
            return;
        }

        omp_set_lock(&(pListHead->nodeLock));
        omp_set_lock(&(pListHead->next->nodeLock));
        omp_set_lock(&(pListHead->next->next->nodeLock));

        pListNode<T>* p = pListHead->next;
        pListHead->next = p->next;
        p->next->prev = pListHead;

        free(p);
        pListSize--;

        omp_unset_lock(&(pListHead->nodeLock));
        omp_unset_lock(&(pListHead->next->nodeLock));


    }

    void popBack()
    {
        if(pListSize == 0)
        {
            cout<<"ERROR! List is empty!"<<endl;
            return;
        }


        omp_set_lock(&(pListTail->prev->prev->nodeLock));
        omp_set_lock(&(pListTail->prev->nodeLock));
        omp_set_lock(&(pListTail->nodeLock));

        pListNode<T>* p = pListTail->prev;
        pListTail->prev = p->prev;
        p->prev->next = pListTail;

        omp_unset_lock(&(pListTail->nodeLock));
        omp_unset_lock(&(pListTail->prev->nodeLock));

        free(p);
        pListSize--;
    }

    T front()
    {
        cout<<"Front"<<endl;
        return pListHead->next->data;
    }

    T back()
    {
        cout<<"Back"<<endl;
        return pListTail->prev->data;
    }

    bool searchElement(T element)
    {
        pListNode<T>* it = pListHead->next;
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
            cout<<"Index out of bounds"<<endl;
            return dummy->data;
        }
        pListNode<T>* it = pListHead->next;
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
        cout<<"Inserting element at index "<<index<<endl;
        if(index < 0 || index  > pListSize)
        {
            cout<<"Invalid index!"<<endl;
            return;
        }
        if(index == 0)
        {
            pushFront(element);
            return;
        }
        pListNode<T>* it = pListHead;
        omp_set_lock(&(it->nodeLock));
        pListNode<T>* next = it->next;

        while(index && it)
        {
            if(next == NULL)
            {
                cout<<"Invalid index"<<endl;
                return;
            }
            omp_set_lock(&(next->nodeLock));
            it = next;
            omp_unset_lock(&(it->nodeLock));
            next = it->next;
        }
        if(!it || it->data == sentinalInt)
        {
            if(it)
                omp_unset_lock(&(it->nodeLock));
            return;
        }
        omp_set_lock(&(next->nodeLock));

        pListNode<T>* p = new pListNode<T>(element);
        omp_init_lock(&(p->nodeLock));
        p->next = next;
        p->prev = it;
        it->next = p;
        next->prev = p;

        omp_unset_lock(&(it->nodeLock));
        omp_unset_lock(&(next->nodeLock));
    }


    void eraseAt(int index)
    {
        cout<<"Erase element"<<endl;
        if(index < 0 || index  >= pListSize)
        {
            cout<<"Invalid index!"<<endl;
            return;
        }
        pListNode<T>* prev = pListHead;
        omp_set_lock(&(prev->nodeLock));
        pListNode<T>* next = prev->next;

        index--;
        while(index && next)
        {
            omp_set_lock(&(next->nodeLock));
            prev = next;
            omp_unset_lock(&(prev->nodeLock));
            next = prev->next;
        }

        if(!next || next->data == sentinalInt)
        {
            cout<<"Invalid index!"<<endl;
            return;
        }
        omp_set_lock(&(next->nodeLock));
        omp_set_lock(&(next->next->nodeLock));
        pListNode<T>* p = next;
        next = next->next;
        prev->next = next;
        next->prev = prev;
        free(p);
        pListSize--;
        omp_unset_lock(&(prev->nodeLock));
        omp_unset_lock(&(next->nodeLock));
    }

    void sortList(bool ascending)
    {
        cout<<"NOT READY. Sorting: "<<endl;
        return;
        if(ascending)
        {
            if(pListSize > 1)
            {
                for(int i = 0; i < pListSize - 1; i++)
                {
                    pListNode<T>* current = pListHead;
                    pListNode<T>* next = pListHead->next;
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
                    pListNode<T>* current = pListHead;
                    pListNode<T>* next = pListHead->next;
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
        cout<<"NOT READY!"<<endl;
        return;
        pListNode<T>* temp = NULL;
        pListNode<T>* it = pListHead;
        pListTail = it;

        while(it != NULL)
        {
            temp = it->prev;
            it->prev = it->next;
            it->next = temp;
            it = it->prev;
        }

        if(temp != NULL)
            pListHead = temp->prev;
    }

    void uniqueList()
    {
        cout<<"NOT READY. Making list unique: "<<endl;
        return;
        unordered_set<T> s;
        pListNode<T>* it = pListHead;
        pListNode<T>* temp = NULL;
        while(it)
        {
            pListNode<T>* next = it->next;
            if(s.find(it->data) != s.end())
            {
                if(!temp)
                {
                    if(it->next)
                    {
                        pListHead = it->next;
                        it->next->prev = NULL;
                    }
                    else
                    {
                        pListTail = NULL;
                        pListTail = NULL;
                    }
                }
                else
                {
                    temp->next = it->next;
                    if(temp->next)
                        temp->next->prev = temp;
                    else
                        pListTail = temp;
                }
                free(it);
            }
            else
            {
                s.insert(it->data);
            }
            if(next)
                temp = next->prev;
            it = next;
        }
    }


    void printList()
    {
        cout<<"Printing Doubly linked list: "<<endl;
        pListNode<T>* it = pListHead->next;
        while(it->data != sentinalInt)
        {
            cout<<it->data<<" ";
            it = it->next;
        }
        cout<<endl;
    }

};

#endif // pList_h

