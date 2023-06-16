#ifndef List_h
#define List_h

typedef struct Node Node;
typedef struct List List;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};


List * createList(void);

void * firstList(List * list);

void * nextList(List * list);

void * lastList(List * list);

void * prevList(List * list);

void pushBack(List * list, void * data);

void * popFront(List * list);

void * popBack(List * list);

void * popCurrent(List * list);

void cleanList(List * list);

void display(List* list);

void replace(List * list, void * data);

#endif /* List_h */


