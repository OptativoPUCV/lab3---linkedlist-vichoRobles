#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

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

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void * firstList(List * list) {
  if (!list->head) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if (!list->current || !(list->current->next)) return NULL;
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (!list->tail) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if (!list->current || !(list->current->prev)) return NULL;

  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *node = createNode(data);
  if (!list->head)
  {
    list->head = node;
    list->tail = node;
  }
  else
  {
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  } 
}

void pushBack(List * list, void * data) {
  Node *node = createNode(data);
  if (!list->tail)
  {
    list->head = node;
    list->tail = node;
  }
  else
  {
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
  }
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (!list->current) return;
  Node *node = createNode(data);
  node->next = list->current->next;
  node->prev = list->current;
  list->current->next = node;
  if (node->next) node->next->prev = node;
  else list->tail = node;
  
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
  if (!list->current) return NULL;
  void *data = list->current->data;
  if (list->current == list->head)
  {
    list->head = list->head->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
  }
  else
  {
    list->current->prev->next = list->current->next;
    if (list->current->next)
    {
      list->current->next->prev = list->current->prev;
    }
    else
    {
      list->tail = list->current->prev;
    }
  }
  free(list->current);
  list->current = NULL;
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}