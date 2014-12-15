#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "test.h"

void sunburFreeNodeVal(void *ptr)
{
  free(ptr);
}

int main(void)
{
  sunburList *list = sunburListCreate();
  sunburFreeNodeValPtr = &sunburFreeNodeVal;
  list->free = sunburFreeNodeVal;
  struct kv {
    char *key;
    int val;
  };
  struct kv *i1;
  i1 = malloc(sizeof(i1));
  i1->key = "test1";
  i1->val = 100;
  struct kv *i2;
  i2 = malloc(sizeof(i2));
  i2->key = "test2";
  i2->val = 300;
  sunburListAddNode(list, i1, sunburListDirectionForward);
  sunburListAddNode(list, i2, sunburListDirectionForward);
  sunburListIter *iter = sunburListGetIterator(list, sunburListDirectionForward);
  sunburListNode *xnode;
  xnode = sunburListNextNode(iter);
  printf("%s -> %d\n", ((struct kv *)xnode->val)->key, ((struct kv *)xnode->val)->val);
  xnode = sunburListNextNode(iter);
  printf("%s -> %d\n", ((struct kv *)xnode->val)->key, ((struct kv *)xnode->val)->val);
  sunburListRealseIterator(iter);
  sunburListRelease(list);
}
