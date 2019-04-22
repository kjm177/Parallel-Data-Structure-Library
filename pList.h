
#ifndef pList_h
#define pList_h

#include <iostream>
#include <unordered_set>
using namespace std;

template <typename T>
struct pListNode
{
    T data;
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

public:

/**
Constructor for generic doubly linked list type T
*/
    pList()
    {
        pListSize = 0;
        pListHead = NULL;
        pListTail = NULL;
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

    pushFront(T element)
    {
        cout<<"Pushing new element at front "<<endl;
        pListNode<T>* p = new pListNode<T>(element);

        p->next = pListHead;
        if(pListHead)
            pListHead->prev = p;
        else
            pListTail = p;
        pListHead = p;
        pListSize++;
    }

    pushBack(T element)
    {
        cout<<"Pushing new element at back "<<endl;
        pListNode<T>* p = new pListNode<T>(element);
        p->prev = pListTail;

        if(pListTail)
            pListTail->next = p;
        else
            pListHead = p;
        pListTail = p;
        pListSize++;
    }

    popFront()
    {
        if(pListSize == 0)
        {
            cout<<"ERROR! List is empty!"<<endl;
        }
        pListNode<T>* p = pListHead;
        pListHead = pListHead->next;
        if(pListHead)
            pListHead->prev = NULL;
        else
            pListTail = NULL;

        free(p);

        pListSize--;
    }

    popBack()
    {
        if(pListSize == 0)
        {
            cout<<"ERROR! List is empty!"<<endl;
        }
        pListNode<T>* p = pListTail;
        pListTail = pListTail->prev;
        if(pListTail)
            pListTail->next = NULL;
        else
            pListHead = NULL;

        free(p);
        pListSize--;
    }

    T front()
    {
        if(pListSize == 0)
        {
            cout<<"List is empty"<<endl;
            throw 0;
        }
        return pListHead->data;
    }

    T back()
    {
        if(pListSize == 0)
        {
            cout<<"List is empty"<<endl;
            throw 0;
        }
        return pListTail->data;
    }

    T getIndex(int index)
    {
        if(pListSize == 0 || index < 0 || index >= pListSize)
        {
            cout<<"Index out of bounds"<<endl;
            throw 0;
        }
        pListNode<T>* it = pListHead;
        while(index)
        {
            it = it->next;
            index--;
        }
        return it->data;
    }

    void insertAt(T element, int index)
    {
        if(index < 0 || index  > pListSize)
        {
            cout<<"Invalid index!"<<endl;
            return;
        }

        pListNode<T>* it = pListHead;
        pListNode<T>* temp = pListHead;

        while(index--)
        {
            if(index == 0)
            {
                pListNode<T>* p = new pListNode<T>(element);
                p->prev = temp;
                p->next = it;
                p->next->next = p;
            }
            else
            {
                temp = it;
                it = it->next;
            }
        }
    }


    void eraseAt(int index)
    {
        cout<<"Erase element"<<endl;
        if(index < 0 || index  >= pListSize)
        {
            cout<<"Invalid index!"<<endl;
            return;
        }

        pListNode<T>* it = pListHead;
        pListNode<T>* temp = NULL;

        while(index)
        {
            temp = it;
            it = it->next;
            index--;
        }

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

    void sortList(bool ascending)
    {
        cout<<"Sorting: "<<endl;
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
        cout<<"Making list unique: "<<endl;
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
        pListNode<T>* it = pListHead;
        while(it)
        {
            cout<<it->data<<" ";
            it = it->next;
        }
        cout<<endl;
    }

};

#endif // pList_h

