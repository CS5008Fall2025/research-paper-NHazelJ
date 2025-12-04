#include <stdio.h>
#include "avl_tree.h"

/* Basic correctness test for the AVL tree. This test:
 - Inserts a set of known keys.
 - Prints the inorder traversal (should be sorted).
 - Searches for several keys (some present, some missing).
 - Prints the height of the final tree.
 - Prints rotation counts used during balancing.
*/

int main(void) {
    AvlNode *root = NULL;

    int keys[] = {30, 20, 40, 10, 25, 35, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("=== BASIC AVL TREE TEST ===\n");
    printf("Inserting keys: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
        root = avl_insert(root, keys[i]);
    }
    printf("\n");

    printf("Inorder traversal (should be sorted): ");
    avl_inorder_print(root);
    printf("\n");

    /* Test searching */
    int search_keys[] = {25, 15, 50, 100};
    int m = sizeof(search_keys) / sizeof(search_keys[0]);

    printf("\n=== SEARCH TESTS ===\n");
    for (int i = 0; i < m; i++) {
        int k = search_keys[i];
        AvlNode *found = avl_search(root, k);

        if (found != NULL) {
            printf("Key %d FOUND in tree.\n", k);
        } else {
            printf("Key %d NOT found in tree.\n", k);
        }
    }

    // Height and rotation stats
    printf("\n=== TREE STATISTICS ===\n");
    int h = avl_tree_height(root);
    printf("Final tree height: %d\n", h);
    printf("Single rotations performed: %ld\n", avl_single_rotations);
    printf("Double rotations performed: %ld\n", avl_double_rotations);

    // Free memory
    avl_free(root);

    return 0;
}