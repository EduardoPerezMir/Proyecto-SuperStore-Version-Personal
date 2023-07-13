#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 40

typedef struct BPlusNode BPlusNode;

typedef struct PtrElement {
    BPlusNode* node;
    List* list;
} PtrElement;

struct BPlusNode {
    int keys[M - 1];
    PtrElement* ptr[M];
    struct BPlusNode* parent;
    struct BPlusNode* next;
    int is_leaf;
    int num_keys;
};

typedef struct BPlusTree {
    BPlusNode *root;
} BPlusTree;

BPlusTree* createBPlusTree();
void removeBPlusTree(BPlusTree* tree);
void insertBPlusTree(BPlusTree* tree, int key, void* value);
void splitNode(BPlusTree* tree, BPlusNode* node);
void insertIntoParent(BPlusTree* tree, BPlusNode* node, int key, BPlusNode* newNode);
BPlusNode* findParent(BPlusNode* root, BPlusNode* node, int key);
BPlusNode* createBPlusTreeNode();
void searchRangeBPlusTree(BPlusTree* tree, int key1, int key2, List* lista);

#endif
