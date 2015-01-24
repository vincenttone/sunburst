#include "brtree.h"

v_br_tree* init_tree()
{
  v_br_tree *tree;
  tree = V_MALLC(sizeof(v_br_tree));
  v_br_node *nil_node;
  nil_node = V_MALLC(sizeof(v_br_node));
  tree->root = nil_node;
  tree->NIL = nil_node;
  return tree;
}

void insert_node(v_br_tree *tree, long key)
{
  v_br_node *node;
  node = V_MALLC(sizeof(v_br_node));
  node->color = VT_RED;
  node->key = key;
  node->left = tree->NIL;
  node->right = tree->NIL;
  node->parent = tree->NIL;
  // find insert position
  v_br_node *current_node = tree->root
    pre_node = tree->NIL;
  while (current_node != tree->NIL) {
    pre_node = current_node;
    if (current_node->key == node->key) {
      // has this node
      return;
    } else if (current_node->key > node->key) {
      current_node->current_node->right;
    } else {
      current_node->current_node->left;
    }
  }
  node->parent = pre_node;
  if (pre_node == tree->NIL) {
    // empty tree
    tree->root = node;
  } else if (node->key < pre_node->key ) {
    // is left child
    pre_node->left = node;
  } else {
    // is right child
    pre_node->right = node;
  }
  insert_fixup(tree, node);
}

static void function insert_fixup(v_br_tree *tree, v_br_node *node)
{
  // only fixup when parent is red
  while (node->parent->color == VT_RED) {
    int is_left_branch = 0; // parent is left child 0, right child 1
    v_br_node *uncle;
    if (node->parent->parent->left == node->parent) {
      // parent is left child
      is_left_branch = 0;
      uncle = node->parent->parent->right;
    } else {
      is_left_branch = 1;
      uncle = node->parent->parent->left;
    }
    // cond 1: uncle is red
    if (uncle->color == VT_RED) {
      // change parent and uncle color to black
      node->parent->color = uncle->color = VT_BLACK;
      // change parent's parent color to red
      uncle->parent->color = VT_RED;
      // now insert node is parent's parent
      node = uncle->parent;
    } else {
      if (is_left_branch == 0) {
        // cond 2: left branch, right child
        if (node->parent->right == node) {
          node = node->parent;
          left_rorate(tree, node);
        }
        // cond3: left branch, left child
        node->parent->color = VT_BLACK;
        node->parent->parent->color = VT_RED;
        right_rorate(tree, node->parent->parent);
      } else {
        if (node->parent->left == node) {
          node = node->parent;
          right_rorate(tree, node);
        }
        node->parent->color = VT_BLACK;
        node->parent->parent->color = VT_RED;
        left_rorate(tree, node->parent->parent);
      }
    }
  }
  tree->root = VT_BLACK;
}
/**
 *    x               y
 *   / \             / \
 *  a   y           x   c
 *      / \        / \
 *     b   c      a   b
 **/
static int left_rorate(v_br_tree *tree, v_br_node *node)
{
  if (node->right == tree->NIL) {
    // without right child! can not rorate
    return 1;
  }
  // node which chanage to node position
  v_br_node *replace2_node = node->right;
  // change right child's left child to node's right child
  node->right = replace2_node->left;
  if (node->right != tree->NIL) {
    node->right->parent = node;
  }
  // change new node and it's parent relation
  replace2_node->parent = node->parent;
  if (node->parent == tree->NIL) {
    tree->root = replace2_node;
  } else if (node->parent->left = node) {
    node->parent->left = replace2_node;
  } else {
    node->parent->right = replace2_node;
  }
  // change node and new node relation
  replace2_node->left = node;
  node->parent = replace2_node;

  return 0;
}
/**
 *     x           y
 *    / \         / \
 *   y   c       a   x
 *  / \             / \
 * a   b           b   c
 **/
static int right_rorate(v_br_tree *tree, v_br_node *node)
{
  if (node->left == tree->NIL) {
    // without left child! can not rorate
    return 1;
  }
  // the node which chanage to current node position
  v_br_node *replace2_node = node->left;
  // change left child's right child to node's left child
  node->left = replace2_node->right;
  if (node->left != tree->NIL) {
    node->left->parent = node;
  }
  // change new node and it's parent relation
  replace2_node->parent = node->parent;
  if (node->parent == tree->NIL) {
    tree->root = replace2_node;
  } else if (node->parent->left = node) {
    node->parent->left = replace2_node;
  } else {
    node->parent->right = replace2_node;
  }
  // change node and new node relation
  replace2_node->right = node;
  node->parent = replace2_node;

  return 0;
}
