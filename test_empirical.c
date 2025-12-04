#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "avl_tree.h"

// High resolution timer using Windows QueryPerformanceCounter
static long long get_microseconds(void) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);

    return (counter.QuadPart * 1000000LL) / frequency.QuadPart;
}

static void fill_random(int *arr, int n, int max_value) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_value;
    }
}

static void fill_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

static long measure_insertion(int *data, int n) {
    long long start_us = get_microseconds();

    AvlNode *root = NULL;

    avl_single_rotations = 0;
    avl_double_rotations = 0;

    for (int i = 0; i < n; i++) {
        root = avl_insert(root, data[i]);
    }

    long long end_us = get_microseconds();

    long microseconds = (long)(end_us - start_us);

    int height = avl_tree_height(root);

    printf("n=%d, time_us=%ld, height=%d, single_rot=%ld, double_rot=%ld\n",
           n, microseconds, height, avl_single_rotations, avl_double_rotations);

    avl_free(root);

    return microseconds;
}

int main(void) {
    srand((unsigned int)time(NULL));

    int sizes[] = {1000, 5000, 10000, 50000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("=== Random insertion experiment ===\n");
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *data = malloc(sizeof(int) * n);
        if (!data) return 1;

        fill_random(data, n, 1000000);
        measure_insertion(data, n);

        free(data);
    }

    printf("\n=== Sorted insertion experiment ===\n");
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *data = malloc(sizeof(int) * n);
        if (!data) return 1;

        fill_sorted(data, n);
        measure_insertion(data, n);

        free(data);
    }

    return 0;
}