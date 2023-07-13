#ifndef TRIE_H
#define TRIE_H

#include "list.h"
#include "../Funciones/constantesYRegistros.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 27

#define MAX_RESULTS 240

typedef struct trieTree trieTree;

typedef struct trieNode {
    int isEndOfWord;
    void *data;
    struct trieNode *parent;
    struct trieNode *children[ALPHABET_SIZE];
} trieNode;


struct trieTree {
    trieNode *root;
    int total;
};

trieTree* createTrieTree();

trieNode *createTrieNode();

int getTrieIndex(char ch);

void insert(trieNode *root, char str[], void* data, trieTree* trie);

void searchWordsStartingWith(trieNode *node, char prefix[MAXLEN], void *dataStructure);

trieNode* getRootTrie(trieTree* trie);

#endif