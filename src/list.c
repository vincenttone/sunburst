#include <stdlib.h>
#include <stdio.h>
#include "list.h"

sunburList *sunburListCreate(void)
{
  sunburList *list;
  list = malloc(sizeof(sunburList));
  if (list == NULL) 
    return NULL;
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
  list->free = NULL;
  list->dup = NULL;
  return list;
}

void sunburListRelease(sunburList *list)
{
  unsigned long len;
  sunburListNode *current, *next;

  current = list->head;
  len = list->len;
  if (current != NULL) {
    while (len--) {
      next = current->next;
      if (list->free) list->free(current->val);
      if (current != NULL) free(current);
      current = next;
    }
    free(list);
  }
}

sunburList *sunburListAddNode(sunburList *list, void *val, enum SunburListDirection direction)
{
  sunburListNode  *node;
  node = malloc(sizeof(sunburListNode));
  if (node == NULL)
    return NULL;
  node->val = val;
  if (list->len == 0) {
    list->head = node;
    list->tail = node;
    node->pre = NULL;
    node->next = NULL;
  } else {
    if (direction == sunburListDirectionBackward) {
      node->pre = NULL;
      node->next = list->head;
      list->head->pre = node;
      list->head = node;
    } else {
      node->pre = list->tail;
      node->next = NULL;
      list->tail->next = node;
      list->tail = node;
    }
  }
  list->len++;
  return list;
}

void sunburListDelNode(sunburList *list, sunburListNode *node)
{
  if (node->pre) {
    node->pre->next = node->next;
  } else {
    list->head = node->next;
  }
  if (node->next) {
    node->next->pre = node->pre;
  } else {
    list->tail = node->pre;
  }
  if (list->free) {
    list->free(node->val);
  }
  free(node);
}

sunburListIter *sunburListGetIterator(sunburList *list, enum SunburListDirection direction)
{
  sunburListIter *iterator;
  iterator = malloc(sizeof(sunburListIter));
  if (iterator == NULL) {
    return NULL;
  }
  iterator->direction = direction;
  if (direction == sunburListDirectionBackward) {
    iterator->next = list->tail;
  } else {
    iterator->next = list->head;
  }
  return iterator;
}

void sunburListRealseIterator(sunburListIter *iterator)
{
  free(iterator);
}

void sunburListRewind(sunburList *list, sunburListIter *iterator)
{
  if (iterator->direction == sunburListDirectionBackward) {
    iterator->next = list->tail;
  } else {
    iterator->next = list->head;
  }
}

sunburListNode *sunburListNextNode(sunburListIter *iterator)
{
  sunburListNode *current = iterator->next;
  if (current != NULL) {
    if (iterator->direction == sunburListDirectionBackward) {
      iterator->next = current->pre;
    } else {
      iterator->next = current->next;
    }
  }
  return current;
}
