#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *listaEnlazada = (List *) malloc(sizeof(List));
  if (listaEnlazada == NULL)
      return NULL;
  
  listaEnlazada->head = NULL;
  listaEnlazada->tail = NULL;
  listaEnlazada->current = NULL;
  
  return listaEnlazada;
}

void * firstList(List * list) {
  if (list->head == NULL)
    return NULL;
  
  list->current = list->head;
  
  return list->current->data;
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL)
    return NULL;
  
  list->current = list->current->next;
  
  return list->current->data;
}

void * lastList(List * list) {
  if (list->tail == NULL)
    return NULL;
  
  list->current = list->tail;
  
    return list->current->data;
}

void * prevList(List * list) {
  if (list->current == NULL || list->current->prev == NULL)
    return NULL;

  list->current = list->current->prev;
  
  return list->current->data;
}

void pushBack(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    
    if (list->head == NULL)
    {
        nuevoNodo->next = nuevoNodo;
        nuevoNodo->prev = nuevoNodo;
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
    }
    else
    {
        list->current = list->tail;
        list->tail->next = nuevoNodo;
        list->tail = nuevoNodo;
        nuevoNodo->prev = list->current;
    }
    list->current = nuevoNodo;
    nuevoNodo->next = NULL;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->head == NULL)
    return NULL;
  
  void *dato = NULL;
  dato = list->current->data;
  
  if (list->current == list->tail)
  {
    list->tail = list->tail->prev;
    list->tail->next = NULL;
  }
  else if (list->current == list->head)
  {
    list->head = list->head->next;
    list->head->prev = NULL;
  }
  else
  {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
  }
  
  free(list->current);
  
  list->current = list->head;
  
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}

/*void display(List* list) {

    Node* current = list->head;

    while(current != NULL) {
        printf("");
        current = current->next;
    }

} */


void replace(List * list, void * data){
    Node *nuevoNodo = createNode(data);
    list->current->prev->next = nuevoNodo;
    list->current->next->prev = nuevoNodo;
    nuevoNodo->prev = list->current->prev;
    nuevoNodo->next = list->current->next;
    list->current = nuevoNodo;
    
}

unsigned short get_size_list(List* list)
{
    unsigned short cont = 0;
    if (list->head == NULL)    return 0;
    
    list->current = list->head;
    while (list->current != NULL)
    {
        cont++;
        list->current = list->current->next;
    }
    return cont;
}
