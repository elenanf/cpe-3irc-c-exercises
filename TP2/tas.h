#ifndef __TAS_H__
#define __TAS_H__

void print_heap(int* heap);
void swap(int* heap, int a, int b);
void pile_up(int* heap, int value);
int find_parent(int i);
int find_left_child(int i);
int find_right_child(int i);

#endif