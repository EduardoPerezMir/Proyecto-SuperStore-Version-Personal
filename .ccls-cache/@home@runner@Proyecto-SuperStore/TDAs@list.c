#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    if (new == NULL)    exit(EXIT_FAILURE);
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
    nuevoNodo->next = NULL;

    if (list->head == NULL) {
        nuevoNodo->prev = NULL;
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
    } else {
        list->tail->next = nuevoNodo;
        nuevoNodo->prev = list->tail;
        list->tail = nuevoNodo;
    }

    list->current = nuevoNodo;
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

    if (list->current == list->tail && list->current == list->head)
    {
        list->head=NULL;
        list->tail=NULL;
        list->current = NULL;
        free(list->current);
        return dato;
    }
  
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
    
  list->current = NULL;
    
  free(list->current);
  
  return dato;
}

void cleanList(List * list) {
    Node *current = list->head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
}

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

int isListEmpty(List* lista)
{
    if (lista->head == NULL)    return 1;
    else     return 0;    
}

int get_size(List* lista)
{
    if (lista->head == NULL)
        return 0;
    
    lista->current = lista->head;
    int cont = 0;
    while (lista->current != NULL)
    {
         cont++;
        lista->current = lista->current->next;
    }
    return cont;
}


void destroyList(List* list)
{
    if (list == NULL) {
        return;
    }
    
    Node* current = list->head;
    
    if (list->head == NULL)
    {
        free(list);
        return;
    }
    
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL; // Para evitar el acceso a una dirección de memoria ya liberada
    
    free(list);
    list = NULL;
}