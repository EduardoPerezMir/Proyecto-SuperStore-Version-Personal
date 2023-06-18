#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>


typedef struct NodeVector {
    int key;
    void* value;
} NodeVector;

typedef struct Vector {
    NodeVector* nodes;
    int size;
    int capac;
} Vector;

NodeVector* newNodeVector(int key, void* value);
Vector* createVector(int capac);
void SortedInsertionVector(Vector* vector, NodeVector* node);
NodeVector* BinarySearchVector(Vector* vector, int key);

#endif
