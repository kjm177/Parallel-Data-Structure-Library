#include <iostream>
#include <set>
#include <omp.h>

#ifndef pForwardList_h
#define pForwardList_h

using namespace std;

template <typename T>
struct pSListNode
{
    T data;
    pSListNode* next;
    pSListNode (T element) : data(element), next(NULL) {}
};


template <typename T>
class pSList {
  size_t List_Size;
  pSListNode<T> *Head;

public:
  /**
  Constructor for singly linked list with HEAD -> NULL
  */
    pSList() {
      List_Size = 0;
      Head = NULL;
      cout<<"Created a new list a"<<endl;
    }

    /**
    Returns list size/length
    */
    int listSize() {
      return List_Size;
    }

    /**
    Returns true if list is empty
    */
    bool isEmpty() {
      if(List_Size == 0)
        return true;
      return false;
    }

    /**
    Adds element of type T to front of the list
    */
    void pushFront(T element) {
      pSListNode<T>* node = new pSListNode<T>(element);
      node->next = Head;
      Head = node;
      List_Size++;
    }

    /**
    Deletes element at the front of the list
    */
    void popFront() {
      if(List_Size == 0)
        cout<<"List is empty!";
      else {
        List_Size--;
        pSListNode<T>* node = Head;
        Head = Head->next;
        free(node);
      }
    }

    /**
    Adds element of type T at position 'index'
    */
    void insertAfter(int index, T element) {
          if(index >= 0 && index <= List_Size) {
            if(index == 0) pushFront(element);
            else {
              pSListNode<T>* it = Head;
              pSListNode<T>* temp;
              int i = 0;
              while(it && i < index) {
                temp = it;
                it = it->next;
                i++;
              }
              pSListNode<T>* node = new pSListNode<T>(element);
              temp->next = node;
              node->next = it;
              List_Size++;
            }
          }
          else
          {
              cout<<"List index out of bound!"<<endl;
              throw index;
          }
    }

    /**
    Returns element at position 'index'
    */
    T getIndex(int index) {
      if(index >= 0 && index < List_Size) {
        pSListNode<T>* it = Head;
        int i = 0;
        while(it && i < index) {
          it = it->next;
          i++;
        }
        return it->data;
      }
      else
      {
          cout<<"List index out of bound!"<<endl;
          throw index;
      }
    }

    /**
    Returns element at the front of the list
    */
    T front() {
      if(List_Size > 0)
          return Head->data;
      else
      {
          cout<<"List is empty!"<<endl;
          throw 0;
      }
    }

    /**
    Reverses the list
    */
    void reverse() {
      pSListNode<T>* curr = Head;
      pSListNode<T>* prev = NULL;
      pSListNode<T>* next = NULL;
      while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
      }
      Head = prev;
    }

    /**
    Erases element at position 'index'
    */
    void erase(int index) {
      if(index >= 0 && index < List_Size) {
        if(index == 0) popFront();
        else {
          pSListNode<T>* it = Head;
          pSListNode<T>* temp;
          int i = 0;
          while(it && i < index) {
            temp = it;
            it = it->next;
            i++;
          }
          free(temp->next);
          temp->next = it->next;
          List_Size--;
        }
      }
      else
      {
          cout<<"List index out of bound!"<<endl;
          throw index;
      }
    }

    /**
    Removes duplicate elements from a list by keeping only the first occurence of the element
    */
    void unique() {
      if(List_Size > 0) {
        set<T> s;
        pSListNode<T>* it = Head;
        int i = 0;
        while(it && i < List_Size) {
          if(s.find(it->data) != s.end())
            erase(i);
          else
            s.insert(it->data);
          it = it->next;
          i++;
        }
      }
      else
      {
          cout<<"List is empty!"<<endl;
          throw 0;
      }
    }

    /**
    Sorts list in ascending on descending order specified by argument passed to it
    */
    void sort(bool ascending) {
      if(ascending) {
        if(List_Size > 1) {
          int i,j;
          for(i = 0; i < List_Size-1; i++ ) {
            pSListNode<T>* current = Head;
            pSListNode<T>* next = Head->next;
            for(j = 0; j < List_Size-i-1; j++ ) {
              if(current->data > next->data) {
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
      else {
        if(List_Size > 1) {
          int i,j;
          for(i = 0; i < List_Size-1; i++ ) {
            pSListNode<T>* current = Head;
            pSListNode<T>* next = Head->next;
            for(j = 0; j < List_Size-i-1; j++ ) {
              if(current->data < next->data) {
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

    /**
    Prints the contents of the list
    */
    void printList() {
      pSListNode<T>* it = Head;
      cout<<"List: ";
      while(it) {
        cout<<it->data<<" ";
        it = it->next;
      }
      cout<<endl;
    }

};

#endif
