# Research Paper
* Name: Najib Mosquera
* Semester: Fall 2025
* Topic: AVL Trees

## Introduction  
Efficient data retrieval forms the foundation of many computing systems, including databases, compilers, file structures, operating systems, and real time applications. Although binary search trees (BSTs) are widely used to support these operations, their performance depends on the tree remaining balanced. When keys are inserted in sorted or adversarial order, a traditional BST becomes skewed, causing search, insertion, and deletion operations to degrade from $O(\log n)$ to $O(n)$ time [2]. This degradation can significantly impact system performance, particularly in applications requiring reliable and predictable runtimes. AVL trees were introduced in 1962 as a solution to this problem by Georgy Adelson-Velsky and Evgenii Landis, making them the first self balancing search tree in the history of computer science [1]. They maintain strict height balance by tracking the height of each subtree and applying rotations whenever the structure becomes unbalanced. Because of this balancing strategy, AVL trees preserve logarithmic height regardless of insertion order and therefore deliver worst-case $O(\log n)$ performance for search, insertion, and deletion [2].

The significance of AVL trees extends beyond their historical impact. Their design ensures predictable runtime behavior, a property essential in systems where performance must remain consistent even as data grows. Classic algorithm literature, including Knuths The Art of Computer Programming and the CLRS textbook, highlights AVL trees as a foundational model of self balancing structures due to their strong theoretical guarantees [2][3]. This report provides a clear and academically grounded overview of AVL trees while maintaining accessibility for beginning C programmers. It explains the motivation behind self balancing trees, their historical origin, and their structural mechanics. It then examines theoretical properties of AVL trees, evaluates their empirical performance using an implementation written in C, explores real-world applications, and concludes with implementation insights and reflections on the development process.

## Analysis of Algorithm/Data Structure  

At a high level, an AVL tree is a binary search tree that enforces a balance condition on every node: the heights of the left and right subtrees may differ by at most one. For every insertion, the tree first performs the usual binary search tree insertion, then walks back up the recursion updating heights and checking the balance factor. If a node becomes unbalanced, one of the four rotation patterns (LL, RR, LR, RL) is applied to restore the AVL property without breaking the in-order (sorted) order of the keys.    
**AVL insertion (pseudocode)**    
```text
function avl_insert(node, key):
    if node is null:
        return new_node(key)

    if key < node.key:
        node.left  = avl_insert(node.left, key)
    else if key > node.key:
        node.right = avl_insert(node.right, key)
    else:
        return node      // ignore duplicate keys

    update_height(node)
    balance = height(node.left) - height(node.right)

    // Left Left
    if balance > 1 and key < node.left.key:
        return rotate_right(node)

    // Right Right
    if balance < -1 and key > node.right.key:
        return rotate_left(node)

    // Left Right
    if balance > 1 and key > node.left.key:
        node.left = rotate_left(node.left)
        return rotate_right(node)

    // Right Left
    if balance < -1 and key < node.right.key:
        node.right = rotate_right(node.right)
        return rotate_left(node)

    return node
```

AVL trees make sure that the left and right subtrees of every node are always balanced by requiring that the heights of the two trees differ by no more than one. The balance factor is the difference between these two numbers. It makes sure that the tree's overall height stays below O(log n). A recurrence relation that is comparable to the Fibonacci sequence demonstrates that AVL height grows logarithmically with the number of nodes [2]. This is the theoretical reason for this height limit. Because the height is always logarithmic, every action that goes from the root to the leaf, such searching, adding, or deleting, will also take logarithmic time.

The binary search tree property says that values less than the current node go left and values bigger than the current node go right. The number of comparisons is similar to the height of the tree, which is logarithmic. The insertion method starts with the same search process and then adds the key as a leaf. After insertion, the tree updates the height values as it goes back to the root. If any node gets out of balance during this process, the tree uses one of four rotation patterns to bring it back into equilibrium. Because each rotation takes the same amount of time, the entire insertion and deletion operations stay O(log n). AVL trees have a linear space complexity since each node contains a key, pointers to its two offspring, and an integer that tells how tall it is [2].

The in-order traversal order of the tree does not change during balancing operations, hence correctness is maintained. Even while rotations change the organization in a small area, they keep the nodes in the same sequence. Because of this, the binary search property stays the same, and the tree still keeps data in order even after multiple modifications [2].  

## Theoretical Analysis

### Runtime and Height

The height guarantee of AVL trees comes from the fact that they maintain a strict balance condition: for every node, the heights of the left and right subtrees may differ by at most one. As shown in the original paper by Adelson-Velsky and Landis [1] and later formalized in algorithmic texts such as CLRS [2] and Knuth [3], this invariant forces the tree to remain logarithmic in height.  
Let h be the height of an AVL tree, and let N(h) be the minimum number of nodes in any AVL tree of height h. Because a node of height $h$ must have children of heights h-1 and h-2 at minimum, the size satisfies the recurrence:
$$
N(h) = 1 + N(h-1) + N(h-2), 
\quad N(0) = 1,\; N(1) = 2.
$$
This recurrence mirrors the Fibonacci sequence, a fact highlighted in both CLRS [2] and Knuth’s Sorting and Searching volume [3]. From this, we obtain the lower bound:
$$
N(h) \ge c \cdot \varphi^h,
$$
where $\varphi \approx 1.618$ is the golden ratio and c is a positive constant. Solving for height $h$ in terms of the number of nodes $n$ gives:
$$
h \le \frac{\log n - \log c}{\log \varphi}
= O(\log n).
$$
Because search, insertion, and deletion all require following a path from the root to a leaf, their worst-case cost is proportional to the height of the tree. The balancing operations (rotations) require only constant time and occur at most once per level on the way back up from a recursive call, giving:

- Search: $O(\log n)$  
- Insert: $O(\log n)$  
- Delete: $O(\log n)$  
- Space: $\Theta(n)$  

These performance guarantees are the defining feature of AVL trees and are repeatedly emphasized in classic algorithm literature [2][3].

### Correctness (High-Level Argument)

Correctness follows from maintaining two invariants after every update:

1. **Binary Search Tree (BST) Invariant**  
   Keys in the left subtree are strictly less than the node’s key, and keys in the right subtree are strictly greater.  
   This invariant is preserved during insertion because the algorithm descends the tree using comparisons before creating a new leaf node.

2. **AVL Balance Invariant**  
   The height difference between the left and right subtrees of any node is at most one.  
   This is restored after insertion using the four standard rotations (LL, RR, LR, RL), as described originally by Adelson-Velsky and Landis [1].

Each rotation rearranges only a small, local portion of the tree. As formally proven in CLRS [2], rotations preserve in-order traversal, so the BST invariant remains valid. Rotations also correct height imbalances, re-establishing the AVL invariant.

By induction on the height of the tree—an argument presented in algorithm textbooks [2][3]—both invariants hold after every insertion. Therefore, an AVL tree maintains sorted order, balance, and worst-case logarithmic runtime for all operations.

## Empirical Analysis   

Theoretical behavior provides valuable insight into the asymptotic performance of AVL trees, but empirical analysis verifies whether the expected performance occurs in practice. To evaluate performance, a C implementation of an AVL tree was used to conduct experiments analyzing insertion time, rotation count, and final height for datasets of increasing size. The tests used both random key sequences and strictly increasing sequences, the latter representing a worst-case input for naive BSTs. Timing on Windows was performed using the QueryPerformanceCounter and QueryPerformanceFrequency APIs, which provide high-resolution microsecond timing. These functions are used inside the `test_empirical.c` helper to measure insertion performance. Which provides high resolution timing suitable for microsecond-level analysis.

The empirical results showed that insertion time grew proportionally to n log n, which is consistent with theoretical expectations. Sorted input triggered more rotations, because each new key arrived on the same side of the tree, but the AVL balancing mechanism compensated effectively. Even in this worst-case pattern, tree height remained logarithmic, demonstrating the effectiveness of balance enforcement. A summary of representative results is shown below [4]:

Table 1 summarizes the measured insertion time, height, and rotation counts for both random and sorted inputs, collected from [test empirical](test_empirical.c).

| n      | Input Type | Time (µs) | Height | Single Rotations | Double Rotations |
|--------|-----------:|----------:|-------:|-----------------:|-----------------:|
| 1,000  | Random     |     283   |    11  |              718 |              244 |
| 1,000  | Sorted     |     236   |     9  |              990 |                0 |
| 5,000  | Random     |   1,595   |    13  |            3,177 |            1,057 |
| 5,000  | Sorted     |   1,377   |    12  |            4,987 |                0 |
| 10,000 | Random     |   3,480   |    14  |            5,900 |            1,971 |
| 10,000 | Sorted     |   2,971   |    13  |            9,986 |                0 |
| 50,000 | Random     |  18,969   |    16  |           17,822 |            5,976 |
| 50,000 | Sorted     |  17,708   |    15  |           49,984 |                0 |


The height values observed in the experiments closely matched the theoretical height bound of approximately 1.44 log_2(n), confirming that AVL trees do not permit significant height growth [2]. These results show that AVL trees preserve efficient behavior even under inputs that would cause ordinary binary search trees to collapse into linear structures. The empirical findings therefore support the theoretical guarantees that make AVL trees suitable for performance critical applications.

These measurements are subject to typical microbenchmark limitations. The experiments were run on a single Windows machine, so absolute timing depends on hardware, compiler optimization, and system load. Each dataset size was measured once rather than averaged across many trials. Despite these limitations, the observed patterns match the theoretical expectations: height grows logarithmically, and sorted input requires more rotations but still maintains efficient $O(\log n)$ behavior.


## Application  

AVL trees are widely used in situations requiring predictable performance and rapid access to ordered data. They appear in in-memory database indexing structures, where logarithmic search time is essential to control query performance under large workloads. They are used in compilers and interpreters to store symbol tables efficiently during parsing and semantic analysis. Operating systems use balanced trees for memory region tracking, process scheduling, and virtual file system indexing. Networking software uses balanced search trees to manage routing tables and prefix matching, ensuring that lookup operations are fast and consistent. Discussions in classical algorithm literature, including Knuth’s analysis of balanced trees and Cormen et , highlight these practical scenarios where strict balancing ensures stable and scalable behavior [3][2].

Because AVL trees guarantee logarithmic performance in all cases, they are especially useful in systems that cannot tolerate worst-case degradation. Although red–black trees are more common in languages such as C++ and Java, AVL trees remain valuable in embedded systems and academic settings where tighter height bounds and worst-case guarantees are more important than average-case flexibility [5].


## Implementation

The AVL tree implemented for this project was written in the C programming language and compiled using GCC. All implementation files are stored in the / src directory, including the AVL header file, the source file containing insertion, rotation, search, and utility logic, a basic test driver, and an empirical testing program. No external libraries were required beyond the C standard library and the Windows windows.h header. Empirical timing uses the QueryPerformanceCounter and QueryPerformanceFrequency to collect microsecond resolution measurements in test_empirical.c. The structure of the rotation cases and the insertion procedure follows the standard AVL pseudocode from Cormen et al. [2] and GeeksforGeeks [5], but all code was written from scratch in C.

The core AVL node structure consists of an integer key, an integer height, and two child pointers, as shown below:

```c
typedef struct AvlNode {
    int key;
    int height;
    struct AvlNode *left;
    struct AvlNode *right;
} AvlNode;
```
Insertion was done over and over again. First, the method does a normal BST insertion. Then, it updates the height of the current node. After the height is adjusted, the function calculates the balance factor to see if the subtree is now unbalanced. If that is the case, the right rotation is done based on where the new key was added. The following is a critical part of the insertion algorithm:

```c
AvlNode *avl_insert(AvlNode *node, int key) {
    if (node == NULL)
        return new_node(key);

    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;

    update_height(node);

    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}
```
Developing this implementation as a beginner working in C introduced challenges related to pointer manipulation, memory allocation, recursive logic, and debugging segmentation faults. Tree rotations required especially careful handling of pointers and subtree relationships to avoid corrupting the structure. Memory management also required attention, as every node allocated with malloc must eventually be freed to avoid leaks. Through iterative testing, careful printing of tree structures, and incremental development, the implementation became stable and correct. This process highlighted the importance of writing modular code, verifying assumptions frequently, and testing edge cases when working with low-level languages like C.

## Results  

To verify the correctness of my implementation, I created a separate program [test_basic.c](test_basic.c) to test fundamental AVL operations such as insertion, search, traversal, height computation, and rotation counts. The output of this test is included in the repository as [basic output](basic_output.txt), which shows a sorted inorder traversal, successful and unsuccessful search operations, and the final tree height. This file serves as direct evidence that the AVL tree implementation behaves correctly under normal operations.

All empirical measurements were captured using the test_empirical.c program, which evaluates insertion performance for random and sorted datasets at multiple sizes. The raw output, including timing results, rotation counts, and final tree heights, is included in the repository as [empirical results](empirical_results.txt). This file provides the complete data used to construct the empirical observations discussed in this section and serves as verifiable evidence of the AVL tree’s performance in practice. Here you can find the [test_empirical.c](test_empirical.c) file.

## Summary  

The study and execution of AVL trees yielded significant insights into the correlation between theoretical algorithm design and practical performance. Their stringent balance rules make sure that the height is logarithmic and the runtime behavior is stable, as shown by real-world tests. Building the tree in C gave me a chance to work with pointers, memory management, recursion, and algorithmic thinking. The project also showed how important it is to write precise technical documents and follow the rules for academic citations. In general, this study helped me grasp basic data structures better and made me better at using and analyzing efficient algorithms in a systems programming setting.

## References  

[1] G. M. Adelson-Velsky and E. M. Landis. 1962. An algorithm for the organization of information. Soviet Mathematics Doklady, 3, 1259–1263.  
[2] T. H. Cormen, C. E. Leiserson, R. Rivest, and C. Stein. 2009. Introduction to Algorithms (3rd ed.). MIT Press.  
[3] D. E. Knuth. 1998. The Art of Computer Programming, Volume 3: Sorting and Searching. Addison-Wesley.  
[4] Wikipedia Contributors. 2024. AVL Tree. https://en.wikipedia.org/wiki/AVL_tree   
[5] GeeksforGeeks. AVL Tree – Introduction and Rotations. https://www.geeksforgeeks.org/avl-tree-set-1-insertion  