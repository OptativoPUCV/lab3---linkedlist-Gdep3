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
  if (list->head == NULL) {
    list->current = NULL;
  } else {
    list->current = list->head;
  }
  return list->current;
}

void *nextList(List *list) {
  list->current = list->current->next;
  return list->current;
}

void *lastList(List *list) {
  while (list->current != NULL) {
    list->current->prev = list->current;
    list->current = list->current->next;
  }
  list->current = list->current->prev;
  return list->current;
}

void *prevList(List *list) {
  list->current = list->current->prev;
  return list->current;
}

void pushFront(List *list, void *data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = list->head;
  list->head = newNode;
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) { return NULL; }

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}