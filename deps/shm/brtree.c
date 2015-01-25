#include "brtree.h"

v_br_tree* init_tree()
{
  v_br_tree *tree;
  tree = V_MALLC(sizeof(v_br_tree));
  v_br_node *nil_node = NULL;
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
 * left rorate brtree
 *
 *    x               y
 *   / \             / \
 *  a   y           x   c
 *      / \        / \
 *     b   c      a   b
 *
 * @params v_br_tree *tree
 * @params v_br_node *node
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
 * right rorate tree
 *
 *     x           y
 *    / \         / \
 *   y   c       a   x
 *  / \             / \
 * a   b           b   c
 *
 * @params v_br_tree *tree
 * @params v_br_node *node
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

/**
 * search the needle key node
 * @params v_br_tree *tree
 * @params long key
 * @return v_br_node || NIL
 *         success: v_br_node
 *         failed: NIL
 */
v_br_node* search_node(v_br_tree *tree, long key)
{
  v_br_node *current_node = tree->root;
  while (
         current_node != tree->NIL
         && key != current_node->key
         ) {
    current_node = key < current_node->key
      ? current_node->left
      : current_node->right;
  }
  return current_node;
}
/**
 * find min node in node's sub tree
 * @params tree
 * @params node
 * @return min node
 */
v_br_node* search_min(v_br_tree *tree, v_br_node *node)
{
  if (node == tree->NIL) {
    return tree->NIL;
  }
  while (node->left != tree->NIL) {
    node = node->left;
  }
  return node;
}
/**
 * find max node int node's sub tree
 */
v_br_node* search_max(v_br_tree *tree, v_br_node *node)
{
  if (node == tree->NIL) {
    return tree->NIL;
  }
  while (node->right != tree->NIL) {
    node = node->right;
  }
  return node;
}
/**
 * find in order successor of the node in tree
 * when find in order successor:
 * print out the left node, then the right node
 * just think of this, it should be easy
 */
v_br_node* search_successor(v_br_tree *tree, v_br_node *node)
{
  if (node == tree->NIL) {
    return tree->NIL;
  }
  // has right branch
  // find the min node in right branch
  if (x->right != tree->NIL) {
    return search_min(tree, x->right);
  }
  // right branch not exists
  // cond 1: node is left child, successor is parent;
  // cond 2: node is right child, find up when match cond 1.
  v_br_node *s_node = node->parent;
  while (s_node != tree->NIL && node == s_node->right) {
    node = s_node;
    s_node->node->parent;
  }
  return y;
}
/**
 * delete node match the key int tree
 */
void delete_node(v_br_tree *tree, long key)
{
  v_br_node *del_node = search_node(tree, key);
  if (del_node == tree->NIL) return;
  // find the real position to del
  // cond 1: only one child branch, del the node
  // cond 2: two child branch, find the successor
  v_br_node *rp_node = 
    (del_node->left == tree->NIL
     || del_node->right == tree->NIL)
    ? del_node
    : search_successor(tree, del_node);
  v_br_node *rp_child_node = 
    rp_node->left == tree->NIL
    ? rp_node->right
    : rp_node->left;
  // adjust relations
  if (rp_child_node != tree->NIL) {
    rp_child_node->parent = rp_node->parent;
  }
  if (rp_node->parent == tree->NIL) {
    // rp_node is root
    tree->root = rp_child_node;
  } else if (rp_node->parent->left == rp_node) {
    // rp_node is left child
    rp_node->parent->left = rp_child_node;
  } else {
    // rp_node is right child
    rp_node->parent->right = rp_child_node;
  }
  // fix the key
  if (del_node != rp_node) {
    del_node->key = rp_node->key;
  }
  // if deleted node is black, need to fixup
  if (rp_node->color == VT_BLACK) {
    delete_fixup(tree, del_node);
  }
  // delete the node
  DELETE(rp_node); // TODO
}

static void delete_fixup(v_br_tree *tree, v_br_node *node)
{
}
