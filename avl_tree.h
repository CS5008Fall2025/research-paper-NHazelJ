#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct AvlNode {
    int key;
    int height;
    struct AvlNode *left;
    struct AvlNode *right;
} AvlNode;

AvlNode *avl_insert(AvlNode *root, int key);
AvlNode *avl_search(AvlNode *root, int key);
void avl_inorder_print(AvlNode *root);
void avl_free(AvlNode *root);
int avl_tree_height(AvlNode *root);

extern long avl_single_rotations;
extern long avl_double_rotations;

#endif