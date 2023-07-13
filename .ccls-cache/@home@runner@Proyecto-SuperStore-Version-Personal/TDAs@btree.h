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

BTree *createBTree(int order); // Crea un árbol B

BTreeNode *newBTreeNode(BTree *tree, int leaf); // Crea un nodo de árbol B

BTreeNode *searchBTree(BTreeNode *root, int value); //Busca por clave en el árbol B

int insertBTree(BTree *tree, int key, void *value); // Inserta un nuevo elemento en el árbol B

int splitChildBTree(BTree *tree, BTreeNode *x, int i); // Divide a un nodo en dos: un padre y un hijo, para efectos de funcionamiento de la TDA

int insertNonFullBTree(BTree *tree, BTreeNode *x, int key, void *value); //Inserta un elemento en un nodo no lleno

void searchByRangeBTree(BTreeNode *root, int key1, int key2, List *listaP); // Busca por rango en el árbol B

BTreeNode *getRoot(BTree *tree); // Consigue la raíz del árbol B

int getNumChildren(BTreeNode* node); // Consigue el número de hijos del árbol B

void destroyBTreeNodes(BTreeNode *node); // Libera memoria de los nodos del árbol B y establece los nodos como valores nulos

void destroyBTree(BTree *BTree); // Libera la memoria del árbol B y establece al árbol B como valor nulo

int isLeaf(BTreeNode *node); // Función corta que indica si un nodo es hoja, gracias al componente leaf de la struct BTreeNode

#endif
