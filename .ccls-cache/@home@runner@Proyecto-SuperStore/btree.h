#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define MIN 3
#define MAX 7


typedef struct BTreeNode {
    int numKeys;            // Número de claves almacenadas en el nodo
    int *keys;            // Array de claves
    List **values;            // Array de valores asociados a las claves
    struct BTreeNode **children;            // Array de punteros a los subárboles hijos
    int leaf;            // Es hoja?
} BTreeNode;


typedef struct BTree {
    int order;             // Orden del árbol B
    struct BTreeNode *root;     // Puntero al nodo raíz del árbol
} BTree;

BTree* createBTree(int order);
BTreeNode* newBTreeNode(BTree* tree, int leaf);
void traverseBTree(BTreeNode *root);
BTreeNode* searchBTree(BTreeNode* root, int value);
int insertBTree(BTree *tree, int key, void* value);
int splitChildBTree(BTree* tree, BTreeNode *x, int i);
int insertNonFullBTree(BTree* tree, BTreeNode *x, int key, void* value);
void searchByRangeBTree(BTreeNode* root, int key1, int key2, List* listaP);
BTreeNode* getRoot(BTree *tree);
void freeBTreeNode(BTreeNode* node);

#endif