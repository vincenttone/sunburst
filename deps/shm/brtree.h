#ifndef _V_BRTREE
#define _V_BRTREE 1

typedef enum {
  VT_RED = 1,
  VT_BLACK = 2,
} v_color_t;

typedef struct v_br_node {
  long key;
  v_color_t color;
  struct v_br_node *left, *right, *parent;
} v_br_node;

typedef struct v_br_tree {
  v_br_node *NIL;
  v_br_node *root;
  void* (*malloc_node)(size_t size);
  void (*free_node)(void* node);
} v_br_tree;

void init_tree(                                   \
               v_br_tree *tree,                   \
               void* (*malloc_node)(size_t size), \
               void (*free_node)(void* node));
void insert_node(v_br_tree *tree, long key);
void delete_node(v_br_tree *tree, long key);
v_br_node* search_node(v_br_tree *tree, long key);
v_br_node* search_min(v_br_tree *tree, v_br_node *node);
v_br_node* search_max(v_br_tree *tree, v_br_node *node);
void inorder(v_br_tree *tree, v_br_node *node, void (*action_func)(v_br_node *));

#define search_min_by_key(tree, key) \
  search_min(tree, search_node(tree, key));
#define search_max_by_key(tree, key) \
  search_max(tree, search_node(tree, key));

#endif
