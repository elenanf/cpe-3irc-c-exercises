#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

#include "tas.h"

#define SIZE 10 // 9 + 1

void print_heap(int* heap)
{
    int i = 0;
    int to_print = 1;
    int spaces = 2;
    while (heap[i] != -1) {

        int numbers_printed = 0;
        for (int j = 0; j < to_print; j++) {
            printf("%*c", SIZE*3/spaces, ' ');
            printf("%d", heap[i]);
            printf("%*c", SIZE*3/spaces, ' ');
            i++;
            if (heap[i] == -1) {
                break;
            }
            numbers_printed++;
        }
        printf("\n");
        spaces = spaces*2;
        to_print = numbers_printed*2;
    }
    printf("\n");
}

void swap(int* heap, int a, int b)
{
    int tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
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

int find_left_child(int i)
{
    return i * 2 + 1;
}

int find_right_child(int i)
{
    return i * 2 + 2;
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

int unpack(int* heap)
{
    // fetch the root
    int root = heap[0];

    if (root != -1) {
        int i = 0;
        while (heap[i] != -1) {
            i++;
        };
        heap[0] = heap[i - 1];
        heap[i - 1] = -1;


        i = 0; // my i is root
        while(heap[find_left_child(i)] != -1) {
                if (heap[find_right_child(i)] == -1 || heap[find_left_child(i)] < heap[find_right_child(i)]) {
                    if (heap[i] > heap[find_left_child(i)]) {
                        swap(heap, i, find_left_child(i));
                        i = find_left_child(i);
                    } else {
                        break;
                    }
                } else if (heap[find_right_child(i)] < heap[find_left_child(i)]) {
                    if (heap[i] > heap[find_right_child(i)]) {
                        swap(heap, i, find_right_child(i));
                        i = find_right_child(i);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
                
        }

    }

    return root;
}



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

    unpack(heap);
    // after inserting 39, we should have 39 42 40 48 49 62 55 51
    print_heap(heap);

    return 0;
}