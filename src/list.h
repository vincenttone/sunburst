#ifndef SUNBUR_LIST_H
#define SUNBUR_LIST_H 1

enum SunburListDirection {
  sunburListDirectionForward = 1,
  sunburListDirectionBackward = 2,
};

typedef struct sunburListNode {
  void *val;
  struct sunburListNode *pre;
  struct sunburListNode *next;
} sunburListNode;

typedef struct {
  sunburListNode *head;
  sunburListNode *tail;
  unsigned long len;
  void *(*dup)(void *ptr);
  void (*free)(void *ptr);
  int (*match)(void *ptr);
  void *(*matchAndUpdate)(void *ptr);
} sunburList;

typedef struct {
  struct sunburListNode *next;
  enum SunburListDirection direction;
} sunburListIter;

sunburList *sunburListCreate(void);
void sunburListRelease(sunburList *list);
sunburList *sunburListAddNode(sunburList *list, void *val, enum SunburListDirection direction);
void sunburListDelNode(sunburList *list, sunburListNode *node);

sunburListIter *sunburListGetIterator(sunburList *list, enum SunburListDirection direction);
void sunburListRealseIterator(sunburListIter *iterator);
void sunburListRewind(sunburList *list, sunburListIter *iterator);
sunburListNode *sunburListNextNode(sunburListIter *iterator);

#endif
