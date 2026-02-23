#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

#include "tas.h"

#define SIZE 9

void print_heap(int* heap)
{
    for (int i = 0; i < SIZE; i++) {
        printf("%i ", heap[i]);
    }
    printf("\n");
}

void swap(int* heap, int parent, int i)
{
    int tmp = heap[parent];
    heap[parent] = heap[i];
    heap[i] = tmp;
}

int find_parent(int i)
{   int parent;
    if (i % 2 != 0) {
        // i is odd, so the child is inserted on the left
        parent = (i - 1) / 2;
    } else {
        // i is even, so the child is inserted on the right
        parent = (i - 2) / 2;
    }
    return parent;
}

void pile_up(int* heap, int value)
{
    int parent;
    int i = 0;
    // to start, we insert the new value at the end of our array
    while (heap[i] != -1) {
        i++;
    };
    heap[i] = value;

    parent = find_parent(i);

    // now, we sort the tree
    while (heap[i] < heap[parent]) {
        swap(heap, parent, i);
        i = parent;
        // avoid reaching for the memory outside of our array
        if (i == 0) {
            break;
        }
        parent = find_parent(i);
    }
}

// unpack()
// {

// }

int main()
{
    int* heap = malloc(SIZE*sizeof(int));
    memset(heap, -1, SIZE*sizeof(int));

    //test values
    heap[0] = 38;
    heap[1] = 42;
    heap[2] = 40;
    heap[3] = 48;
    heap[4] = 49;
    heap[5] = 62;
    heap[6] = 55;
    heap[7] = 51;
    pile_up(heap, 39);

    // after inserting 39, we should have 38 39 40 42 49 62 55 51 48
    print_heap(heap);

    return 0;
}