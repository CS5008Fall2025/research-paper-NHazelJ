#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

// Global counters for empirical analysis
long avl_single_rotations = 0;
long avl_double_rotations = 0;

// Helper to get height of a node, NULL has height -1 by convention
static int node_height(AvlNode *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Return the greater of two integers.
static int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node with a given key.
static AvlNode *new_node(int key) {
    AvlNode *node = (AvlNode *)malloc(sizeof(AvlNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Update a node's height based on its children
static void update_height(AvlNode *node) {
    int left_h = node_height(node->left);
    int right_h = node_height(node->right);
    node->height = 1 + max_int(left_h, right_h);
}

// Get balance factor of a node
static int get_balance(AvlNode *node) {
    if (node == NULL) return 0;
    return node_height(node->left) - node_height(node->right);
}

/* Right rotation:
 *
 *      y                x
 *     / \              / \
 *    x   T3   ->      T1  y
 *   / \                  / \
 *  T1 T2                T2 T3
 */
static AvlNode *right_rotate(AvlNode *y) {
    AvlNode *x = y->left;
    AvlNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    avl_single_rotations++;
    return x;
}

/* Left rotation:
 *
 *   x                     y
 *  / \                   / \
 * T1  y      ->         x  T3
 *    / \               / \
 *   T2 T3             T1 T2
 */
static AvlNode *left_rotate(AvlNode *x) {
    AvlNode *y = x->right;
    AvlNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    avl_single_rotations++;
    return y;
}

// Double rotation: Left-Right
static AvlNode *left_right_rotate(AvlNode *node) {
    avl_double_rotations++;
    node->left = left_rotate(node->left);
    return right_rotate(node);
}

// Double rotation: Right-Left
static AvlNode *right_left_rotate(AvlNode *node) {
    avl_double_rotations++;
    node->right = right_rotate(node->right);
    return left_rotate(node);
}

// Insert a key into the AVL tree
AvlNode *avl_insert(AvlNode *node, int key) {
    /* 1. Standard BST insert */
    if (node == NULL)
        return new_node(key);

    if (key < node->key) {
        node->left = avl_insert(node->left, key);
    } else if (key > node->key) {
        node->right = avl_insert(node->right, key);
    } else {
        return node; /* duplicate keys ignored */
    }

    /* 2. Update height */
    update_height(node);

    /* 3. Check balance */
    int balance = get_balance(node);

    /* 4. Handle 4 rotation cases */

    /* Case 1: Left Left */
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    /* Case 2: Right Right */
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    /* Case 3: Left Right */
    if (balance > 1 && key > node->left->key)
        return left_right_rotate(node);

    /* Case 4: Right Left */
    if (balance < -1 && key < node->right->key)
        return right_left_rotate(node);

    return node;
}

// Search for a key in the AVL tree
AvlNode *avl_search(AvlNode *root, int key) {
    AvlNode *current = root;

    while (current != NULL) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current; /* found */
    }

    return NULL; /* not found */
}

// Print inorder traversal
void avl_inorder_print(AvlNode *root) {
    if (root == NULL) return;
    avl_inorder_print(root->left);
    printf("%d ", root->key);
    avl_inorder_print(root->right);
}

// Free entire tree
void avl_free(AvlNode *root) {
    if (root == NULL) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

// Return height of entire tree
int avl_tree_height(AvlNode *root) {
    return node_height(root);
}