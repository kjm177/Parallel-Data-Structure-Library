
#ifndef LinkedListNode_h
#define LinkedListNode_h

template <typename T>
struct sLinkedList
{
    T data;
    sLinkedList* next;
};

template <typename T>
struct dLinkedList
{
    T data;
    dLinkedList* next;
    dLinkedList* prev;
};

#endif // LinkedListNode_h
