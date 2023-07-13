#include "trie.h"

trieTree* createTrieTree() {
    trieTree* trie = (trieTree*)malloc(sizeof(trieTree));
    trie->root = createTrieNode();  // asumiendo que tienes una función que crea un nuevo TrieNode
    trie->total = 0;
    return trie;
}

trieNode *createTrieNode() {
    trieNode *node = (trieNode *)malloc(sizeof(trieNode));
    if (node == NULL)
        return NULL;

    node->isEndOfWord = 0;
    node->data = NULL;
    node->parent = NULL;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

int getTrieIndex(char ch) {
    ch = tolower(ch);  // Convertir a minúsculas
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a';
    } else if (isspace(ch)) {
        return 26;  // Índice 26 para el espacio
    } else {
        // Carácter no válido
        return -1;  // O cualquier otro valor que indique un carácter inválido
    }
}

void insert(trieNode *root, char str[], void *data, trieTree *trie) {
    if (root == NULL || data == NULL || trie == NULL)
        return;
    int a;
    
    int level, index;
    for (level = 0; level < strlen(str) - 1; level++) {
        index = getTrieIndex(str[level]);
        if (!root->children[index]) {
            trieNode *newNode = createTrieNode();
            newNode->parent = root;
            root->children[index] = newNode;
        } else if (level == strlen(str) - 2 && root->children[index]->isEndOfWord) {
            // La palabra ya existe en el Trie, no hacer nada
            return;
        }
        root = root->children[index];
    }

    if (!root->isEndOfWord) {
        root->isEndOfWord = 1;
        root->data = data;
        trie->total++;
    }
}

void addSearchResult(void *dataStructure,List *data) {
    // Lógica para agregar el resultado a tu estructura de datos
    // Aquí debes implementar la lógica específica de tu estructura de datos
    // para agregar el resultado (data) a la misma
}

void searchWordsStartingWith(trieNode *node, char prefix[MAXLEN], void *dataStructure) {
    if (node == NULL) {
        return;
    }

    if (node->isEndOfWord) {
        addSearchResult(dataStructure, node->data);
    }

    int prefixLength = strlen(prefix);
    if (prefixLength == 0) {
        // El prefijo está vacío, busca todas las palabras
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != NULL) {
                searchWordsStartingWith(node->children[i], prefix, dataStructure);
            }
        }
    } else {
        int index = getTrieIndex(prefix[0]);
        if (index == -1 || node->children[index] == NULL) {
            return;
        }
        searchWordsStartingWith(node->children[index], prefix + 1, dataStructure);
    }
}

trieNode* getRootTrie(trieTree* trie)
{
    return trie->root;
}