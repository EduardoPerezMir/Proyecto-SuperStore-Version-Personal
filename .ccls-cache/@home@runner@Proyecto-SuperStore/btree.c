#include "btree.h"

BTree* createBTree(int order) {
    BTree* tree = (BTree*)calloc(1, sizeof(BTree));
    tree->order = order;
    return tree;
}

BTreeNode* newBTreeNode(BTree* tree, int leaf) {
    int order = tree->order;
    BTreeNode* newNode = (BTreeNode*)calloc(1, sizeof(BTreeNode));
    
    if(newNode == NULL) {
        return NULL;
    }
    
    newNode->keys = (int*)calloc(order - 1, sizeof(int));
    newNode->values = (List**)calloc(order - 1, sizeof(List*));
    if (newNode->keys == NULL || newNode->values == NULL) {
        free(newNode->keys);
        free(newNode->values);
        free(newNode);
        return NULL;
    }

    for (int i = 0; i < order - 1; i++) {
        newNode->values[i] = createList();
        if (newNode->values[i] == NULL) {
            free(newNode->keys);
            free(newNode->values);
            free(newNode);
            return NULL;
        }
    }

    if (leaf == 0) {
        newNode->children = (BTreeNode**)calloc(order, sizeof(BTreeNode*));
        if (newNode->children == NULL) {
            free(newNode->values);
            free(newNode->keys);
            free(newNode);
            return NULL;
        }
    }

    newNode->leaf = leaf;
    return newNode;
}

void freeBTreeNode(BTreeNode* node) {
    if (node == NULL) {
        return;
    }
    
    if (node->leaf == 0) {
        int i;
        for (i = 0; i <= node->numKeys; i++) {
            freeBTreeNode(node->children[i]);
        }
        free(node->children);
    }

    free(node->keys);
    free(node->values);
    free(node);
}

void freeBTree(BTree* tree) {
    freeBTreeNode(tree->root);
    free(tree);
}

int splitChildBTree(BTree* tree, BTreeNode* x, int i) {
    int order = tree->order;
    BTreeNode* y = x->children[i];
    BTreeNode* z = newBTreeNode(tree, y->leaf);
    if (z == NULL) return -1;

    x->children[i + 1] = z;
    z->numKeys = (order - 1) / 2;

    for (int j = 0; j < z->numKeys; j++) {
        z->keys[j] = y->keys[j + y->numKeys/2 + 1];
        z->values[j] = y->values[j + y->numKeys/2 + 1];
    }

    if (!y->leaf) {
        for (int j = 0; j <= z->numKeys; j++) {
            z->children[j] = y->children[j + y->numKeys/2 + 1];
        }
    }

    y->numKeys = y->numKeys/2;

    for (int j = x->numKeys; j > i; j--) {
        x->children[j + 1] = x->children[j];
        x->keys[j] = x->keys[j - 1];
        x->values[j] = x->values[j - 1];
    }

    x->children[i + 1] = z;
    x->keys[i] = y->keys[y->numKeys];
    x->values[i] = y->values[y->numKeys];
    x->numKeys++;

    return 0;
}

int insertNonFullBTree(BTree* tree, BTreeNode* x, int key, void* value) {
    int i = x->numKeys - 1;

    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        
        i++;  // Increment i to ensure it's not negative
        
        // If the key already exists, append the value to the list
        if (i < x->numKeys && key == x->keys[i]) {
            pushBack(x->values[i], value);
        } else {
            // Insert key and value into the correct position
            for (int j = x->numKeys; j > i; j--) {
                x->keys[j] = x->keys[j - 1];
                x->values[j] = x->values[j - 1];
            }
            x->keys[i] = key;
            x->values[i] = createList();
            if (x->values[i] == NULL) {
                return -1;  // Failed to allocate memory
            }
            pushBack(x->values[i], value);
            x->numKeys++;
        }
    } else {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }

        i++;

        if (x->children[i]->numKeys == ( tree->order - 1)) {
            if (splitChildBTree(tree, x, i) < 0) {
                return -1;
            }

            if (key > x->keys[i]) {
                i++;
            }
        }

        if (insertNonFullBTree(tree, x->children[i], key, value) < 0) {
            return -1;
        }
    }

    return 0;
}

int insertBTree(BTree* tree, int key, void* value) {
    BTreeNode* root = tree->root;

    if (root == NULL) {
        root = newBTreeNode(tree, 1);
        if (root == NULL) {
            return -1;  // Failed to allocate memory
        }
        root->keys[0] = key;
        root->values[0] = createList();
        if (root->values[0] == NULL) {
            return -1;  // Failed to allocate memory
        }
        pushBack(root->values[0], value);
        root->numKeys = 1;
        tree->root = root;
    } else {
        if (root->numKeys == (2 * tree->order) - 1) {
            BTreeNode* s = newBTreeNode(tree, 0);
            if (s == NULL) {
                return -1;  // Failed to allocate memory
            }
            tree->root = s;
            s->children[0] = root;
            splitChildBTree(tree, s, 0);
            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            if (insertNonFullBTree(tree, s->children[i], key, value) < 0) {
                return -1;  // Insertion failed
            }
        } else {
            if (insertNonFullBTree(tree, root, key, value) < 0) {
                return -1;  // Insertion failed
            }
        }
    }
    return 0;  // Success
}

void searchByRangeBTree(BTreeNode* node, int key1, int key2, List* listaP) {
    if (node == NULL) {
        return;
    }

    int i = 0;

    // Busca la primera clave mayor o igual a key1.
    while (i < node->numKeys && node->keys[i] < key1) {
        i++;
    }

    // Mientras la clave es menor o igual a key2, agrega los valores a listaP y avanza.
    while (i < node->numKeys && node->keys[i] <= key2) {
        pushBack(listaP, firstList(node->values[i]));
        for (unsigned short cont = 1; cont < get_size_list(node->values[i]); cont++) {
            pushBack(listaP, nextList(node->values[i]));
        }
        i++;
    }

    // Si el nodo es una hoja, ya hemos terminado.
    if (node->leaf) {
        return;
    }

    // Si el nodo no es una hoja, busca en sus hijos que podrían contener valores entre key1 y key2.
    for (int j = 0; j < i; j++) {
        if ((j == 0 || node->children[j]->keys[node->children[j]->numKeys-1] >= key1) && node->children[j]->keys[0] <= key2) {
            searchByRangeBTree(node->children[j], key1, key2, listaP);
        }
    }

    // Si la última clave que revisamos fue <= key2 y el siguiente hijo podría contener valores entre key1 y key2, busca en ese hijo también.
    if (i < node->numKeys && node->children[i]->keys[node->children[i]->numKeys-1] >= key1) {
        searchByRangeBTree(node->children[i], key1, key2, listaP);
    }
}

BTreeNode* getRoot(BTree *tree)
{
    return tree->root;
}

void traverseBTree(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->numKeys; i++) {
            // Imprimir clave actual y su valor
            printf("%d. Precio: %d\n", i + 1,root->keys[i]);
        }

        // Recorrer recursivamente los hijos
        if (root->leaf == 0) {
            for (i = 0; i <= root->numKeys; i++) {
                traverseBTree(root->children[i]);
            }
        }
    }
}


BTreeNode* searchBTree(BTreeNode* root, int key) {
    if (root == NULL)    return NULL;

    int i = 0;
    while (i < root->numKeys && key > root->keys[i])    i++;

    if (i < root->numKeys && key == root->keys[i])    return root;

    if (root->leaf == 1)    return NULL;

    return searchBTree(root->children[i], key);
}