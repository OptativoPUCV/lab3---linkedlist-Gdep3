#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *lista = (List *)malloc(sizeof(List));
  lista->head = NULL;
  lista->current = NULL;
  lista->tail = NULL;
  return lista;
}

void *firstList(List *list) {
  if(list->head == NULL){
    return NULL;
  }
  list->current = list->head;
  return list->head->data;
}

void *nextList(List *list) {
  if(list->current == NULL){
    return NULL;
  }
  if(list->current->next == NULL){
    return NULL;
  }
  list->current = list->current->next;
  return list->current->data;
}

void *lastList(List *list) {
  if(list->tail == NULL){
    return NULL;
  }
  list->current = list->tail;
  return list->current->data;
}

void *prevList(List *list) {
  if(list->current == NULL) return NULL;
  if(list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List *list, void *data) {
  Node* nuevoNodo = createNode(data);
  if(list->head){
    list->head->prev = nuevoNodo;
    nuevoNodo->next = list->head;
  }
  list->head = nuevoNodo;
  Node* aux = list->head;
  while(aux->next != NULL){
    aux = aux->next;
  }
  list->tail = aux;
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  Node* nuevoNodo = createNode(data);
  if(list->current == NULL) pushFront(list, data);
  else{
    nuevoNodo->prev = list->current;
    nuevoNodo->next = list->current->next;
    if(list->current->next) list->current->next->prev = nuevoNodo;
    list->current->next = nuevoNodo;
    if(list->current == list->tail) list->tail = nuevoNodo;
  }
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) { 
  if(list->current == NULL)
    return NULL;
  void *data = list->current->data;
  if(list->current->prev)
    list->current->prev->next = list->current->next;
  if(list->current->next)
    list->current->next->prev = list->current->prev;
  if(list->current == list->head) {
    list->head = list->current->next;
    if(list->head)
      list->head->prev = NULL;
  }
  if(list->current == list->tail) {
    list->tail = list->current->prev;
    if(list->tail)
      list->tail->next = NULL;
  }
  free(list->current);
  list->current = NULL;
  return data;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}