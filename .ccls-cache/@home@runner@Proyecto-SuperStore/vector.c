#include "vector.h"

NodeVector* newNodeVector(int key, void* value) {
    NodeVector* node = malloc(sizeof(NodeVector));
    if (node == NULL) {
        return NULL;
    }

    node->key = key;
    node->value = value;
    return node;
}

// Crea un vector vacío.
Vector* createVector(int capac) {
    Vector* vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        return NULL;
    }
    vector->size = 0;
    vector->capac = capac;
    vector->nodes = calloc(vector->capac, sizeof(NodeVector));
    return vector;
}

// Inserta un nodo en un vector, manteniendo el vector ordenado por clave.
void SortedInsertionVector(Vector* vector, NodeVector* node) {
    if (vector->size + 1 == vector->capac)
    {
        (vector->capac) *= 2;
        vector->nodes = calloc(vector->capac, sizeof(NodeVector));
    }
    if (vector->nodes == NULL) {
        return;
    }

    int i = vector->size - 1;
    while (i >= 0 && vector->nodes[i].key > node->key) {
        vector->nodes[i+1] = vector->nodes[i];
        i--;
    }

    vector->nodes[i+1] = *node;
    vector->size++;
}

// Busca una clave en un vector utilizando la búsqueda binaria.
NodeVector* BinarySearchVector(Vector* vector, int key) {
    int left = 0;
    int right = vector->size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (vector->nodes[mid].key == key) {
            return &vector->nodes[mid];
        } else if (vector->nodes[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return NULL;  // Clave no encontrada
}