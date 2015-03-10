#include <stdlib.h>
#include <stdio.h>
#include "brtree.h"

void print_key(v_br_node *node)
{
  printf("key: %ld\n", node->key);
}

int main()
{
  v_br_tree *tree = malloc(sizeof(v_br_tree));
  v_br_node *node;
  init_tree(tree, malloc, free);
  insert_node(tree, 10);
  insert_node(tree, 50);
  insert_node(tree, 40);
printf("max val is %ld\n", search_max(tree, tree->root)->key);
  insert_node(tree, 80);
  insert_node(tree, 100);
  printf("root val is %ld\n", tree->root->key);
  node = search_min(tree, tree->root);
  printf("min val is %ld\n", node->key);
  printf("max val is %ld\n", search_max(tree, tree->root)->key);
  inorder(tree, tree->root, print_key);
  free(tree);
}
