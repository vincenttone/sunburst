#ifndef _V_BRTREE
#define _V_BRTREE 1

#include "shm.h"
#define V_MALLC v_shm_malloc;
#define V_FREE v_shm_free;

typedef enum {
  VT_RED = 1,
  VT_BLACK = 2,
} v_color_t;

typedef struct v_br_node {
  long key;
  v_color_t color;
  v_br_node *left, *right, *parent;
} v_br_node;

typedef struct v_br_tree {
  v_br_node *NIL;
  v_br_node *root;
} v_br_tree;

v_br_tree* init_tree(v_br_tree *tree);
void insert_node(v_br_tree *tree, long key);

#endif
