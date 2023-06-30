#ifndef BTREE_H
#define BTREE_H

#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 3
#define MAX 7

typedef struct BTreeNode {
  int numKeys;                 // Número de claves almacenadas en el nodo
  int *keys;                   // Array de claves
  List **values;               // Array de listas de valores asociados a las claves
  struct BTreeNode **children; // Array de punteros a los nodos hijos
  int leaf;                    // Es hoja?
} BTreeNode;

typedef struct BTree {
  int order;              // Orden del árbol B
  struct BTreeNode *root; // Puntero al nodo raíz del árbol
} BTree;

BTree *createBTree(int order);

BTreeNode *newBTreeNode(BTree *tree, int leaf);

BTreeNode *searchBTree(BTreeNode *root, int value);

int insertBTree(BTree *tree, int key, void *value);

int splitChildBTree(BTree *tree, BTreeNode *x, int i);

int insertNonFullBTree(BTree *tree, BTreeNode *x, int key, void *value);

void searchByRangeBTree(BTreeNode *root, int key1, int key2, List *listaP);

BTreeNode *getRoot(BTree *tree);

int getNumChildren(BTreeNode* node);

void destroyBTreeNodes(BTreeNode *node);

void destroyBTree(BTree *BTree);

int isLeaf(BTreeNode *node);

#endif
