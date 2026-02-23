#ifndef __TAS_H__
#define __TAS_H__

void print_heap(int* heap);
void swap(int* heap, int parent, int i);
int find_parent(int i);
void pile_up(int* heap, int value);

#endif