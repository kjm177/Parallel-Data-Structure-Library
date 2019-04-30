#include <iostream>
#include <set>
#include <omp.h>

#ifndef pForwardList_h
#define pForwardList_h

#define sentinalInt -9999999

using namespace std;

template <typename T>
struct pSListNode
{
    T data;
    pSListNode* next;
    omp_lock_t nodeLock;
    pSListNode (T element) : data(element), next(NULL) {}
};


template <typename T>
class pSList {
  size_t List_Size;
  pSListNode<T> *Head;
  pSListNode<T> *dummy;

public:
  /**
  Constructor for singly linked list with HEAD -> NULL
  */
    pSList() {
      List_Size = 0;
      Head = new pSListNode<T>(sentinalInt);
      omp_init_lock(&(Head->nodeLock));
      dummy = new pSListNode<T>(sentinalInt);
      Head->next = dummy;
      cout<<"Created a new list"<<endl;
    }

    /**
    Returns pointer to a copy of the list
    */

    pSListNode<T>* copyList(pSListNode<T>* list) {
      if (list->next == NULL) return NULL;
      pSListNode<T>* newHead = new pSListNode<T>(0);
      newHead->data = list->data;
      newHead->next = copyList(list->next);
      return newHead;
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
      if(List_Size == 0) return true;
      return false;
    }

    /**
    Adds element of type T to front of the list
    */
    void pushFront(T element) {
      #pragma omp critical
      {
        cout<<"Pushing new element at front "<<element<<endl;
        pSListNode<T>* p = new pSListNode<T>(element);
        omp_init_lock(&(p->nodeLock));

        omp_set_lock(&(Head->nodeLock));
        omp_set_lock(&(Head->next->nodeLock));

        p->next = Head->next;
        Head->next = p;
        List_Size++;

        omp_unset_lock(&(Head->nodeLock));
        omp_unset_lock(&(p->next->nodeLock));
      }
    }

    /**
    Deletes element at the front of the list
    */
    void popFront() {
      if(List_Size == 0) {
        cout<<"List is empty!"<<endl;
        return;
      }
      else {
        omp_set_lock(&(Head->nodeLock));
        omp_set_lock(&(Head->next->nodeLock));

        // omp_set_lock(&(Head->next->next->nodeLock));
        if(Head->next->data != sentinalInt) {

          cout<<"Popped "<<Head->next->data<<endl;

          pSListNode<T>* node = Head;
          Head = node->next;
          Head->data = sentinalInt;
          free(node);
          List_Size--;

          omp_unset_lock(&(Head->nodeLock));
        }
      }
    }

    /**
    Returns element at the front of the list
    */
    T front() {
      return Head->next->data;
    }

    /**
    Returns element at position 'index'
    */
    T getIndex(int index) {

      if(List_Size == 0 || index < 0 || index >= List_Size) {
        return dummy->data;
      }
      pSListNode<T>* it = Head->next;
      while(index && it) {
        it = it->next;
        index--;
      }
      if(it) return it->data;

      return dummy->data;
    }


    /**
    Adds element of type T at position 'index'
    */
    void insertAt(T element, int index) {

      if(index < 0 || index > List_Size) return;

      pSListNode<T>* prev = Head;
      pSListNode<T>* it = prev->next;

      while(index) {
        if(!it) return;
        prev = it;
        it = it->next;
        index--;
      }
      #pragma omp critical
      {
        omp_set_lock(&(prev->nodeLock));
        omp_set_lock(&(it->nodeLock));
      }
      pSListNode<T>* p = new pSListNode<T>(element);
      omp_init_lock(&(p->nodeLock));
      p->next = it;
      prev->next = p;
      List_Size++;
      omp_unset_lock(&(prev->nodeLock));
      omp_unset_lock(&(it->nodeLock));
    }


    /**
    Erases element at position 'index'
    */
    void eraseAt(int index) {
      if(index >= 0 && index < List_Size) {
        pSListNode<T>* prev = Head;
        pSListNode<T>* it = prev->next;

        while(index) {
          if(!it) return;
          prev = it;
          it = it->next;
          index--;
        }

        if(!it || it->data == sentinalInt) return;

        #pragma omp critical
        {
          omp_set_lock(&(prev->nodeLock));
          omp_set_lock(&(it->nodeLock));
          omp_set_lock(&(it->next->nodeLock));
        }

        prev->next = it->next;
        free(it);
        List_Size--;
        omp_unset_lock(&(prev->nodeLock));
        omp_unset_lock(&(prev->next->nodeLock));
      }
      else return;
    }

    /**
    Reverses the list
    */
    void reverse() {
      return;
      if(List_Size > 0) {
        pSListNode<T>* newHead = copyList(Head->next);
        pSListNode<T>* it;
        pSListNode<T>* curr = newHead;
        pSListNode<T>* prev = NULL;
        pSListNode<T>* next = NULL;
        while(curr != NULL) {
          next = curr->next;
          curr->next = prev;
          prev = curr;
          curr = next;
        }
        newHead = prev;
        cout<<"Reversed list: ";
        while(newHead != NULL) {
          cout<<newHead->data<<" ";
          it = newHead;
          newHead = newHead->next;
          free(it);
        }
      }
      else cout<<"List is empty!"<<endl;
    }


    /**
    Removes duplicate elements from a list by keeping only the first occurence of the element
    */
    void unique() {
      return;
      if(List_Size > 0) {
        pSListNode<T>* newHead = copyList(Head->next);
        set<T> s;
        pSListNode<T>* it = newHead;
        pSListNode<T>* prev;
        int i = 0;
        while(it && i < List_Size) {
          if(s.find(it->data) != s.end()) {
            prev->next = it->next;
            pSListNode<T>* temp = it;
            free(temp);
          }
          else s.insert(it->data);
          prev = it;
          it = it->next;
          i++;
        }
        cout<<"Unique list: ";
        while(newHead != NULL) {
          cout<<newHead->data<<" ";
          it = newHead;
          newHead = newHead->next;
          free(it);
        }
      }
      else cout<<"List is empty!"<<endl;
    }

    /**
    Sorts list in ascending on descending order specified by argument passed to it
    */
    void sort(bool ascending) {
      return;
      if(List_Size > 1) {
        pSListNode<T>* newHead = copyList(Head->next);
        if(ascending) {
          int i,j;
          for(i = 0; i < List_Size-1; i++ ) {
            pSListNode<T>* current = newHead;
            pSListNode<T>* next = newHead->next;
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
        else {
          int i,j;
          for(i = 0; i < List_Size-1; i++ ) {
            pSListNode<T>* current = newHead;
            pSListNode<T>* next = newHead->next;
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
        cout<<"Sorted list: ";
        pSListNode<T>* it;
        while(newHead != NULL) {
          cout<<newHead->data<<" ";
          it = newHead;
          newHead = newHead->next;
          free(it);
        }
      }
    }

    /**
    Prints the contents of the list
    */
    void printList() {
      pSListNode<T>* it = Head->next;
      while(it->next != NULL) {
        cout<<it->data<<" ";
        it = it->next;
      }
      cout<<endl;
    }

};

#endif
