#include "btree.h"

BTree* createBTree(int order) {
    BTree* tree = (BTree*)calloc(1, sizeof(BTree));
    if(tree == NULL) {
        return NULL;
    }
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
            for(int j = 0; j < i; j++) {
                free(newNode->values[j]);
            }
            free(newNode->keys);
            free(newNode->values);
            free(newNode);
            return NULL;
        }
    }

    if (leaf == 0) {
        newNode->children = (BTreeNode**)calloc(order, sizeof(BTreeNode*));
        if (newNode->children == NULL) {
            for(int i = 0; i < order - 1; i++) {
                free(newNode->values[i]);
            }
            free(newNode->values);
            free(newNode->keys);
            free(newNode);
            return NULL;
        }
    }

    newNode->leaf = leaf;
    return newNode;
}

int isLeaf(BTreeNode* node)
{
    if (node->leaf)    return 1;
    else    return 0;
}

int splitChildBTree(BTree* tree, BTreeNode* x, int i) {
    int order = tree->order;
    BTreeNode* y = NULL;
    BTreeNode* z = NULL;

    if (x == NULL || x->children == NULL || x->children[i] == NULL) {
        return -1;
    }

    y = x->children[i];
    z = newBTreeNode(tree, y->leaf);
    
    if (z == NULL) return -1;

    z->numKeys = (order - 1) / 2;

    for (int j = 0; j < z->numKeys; j++) {
        if (j + order / 2 < y->numKeys) {
            z->keys[j] = y->keys[j + order / 2];
            z->values[j] = y->values[j + order / 2];
            y->values[j + order / 2] = NULL;
        }
    }
    
    if (!y->leaf) {
        for (int j = 0; j <= z->numKeys; j++) {
            if (j + order / 2 < y->numKeys + 1) {
                z->children[j] = y->children[j + order / 2];
                y->children[j + order / 2] = NULL;
            }
        }
    }
    
    y->numKeys = order / 2 - 1;

    for (int j = x->numKeys; j > i; j--) {
        if (j + 1 < order) {
            x->children[j + 1] = x->children[j];
            x->keys[j] = x->keys[j - 1];
            x->values[j] = x->values[j - 1];
        }
    }

    if (i + 1 < order) {
        x->children[i + 1] = z;
        x->keys[i] = y->keys[order / 2 - 1];
        x->values[i] = y->values[order / 2 - 1];
    }

    x->numKeys++;

    return 0;
}

int insertNonFullBTree(BTree* tree, BTreeNode* x, int key, void* value) {
    int i = x->numKeys - 1;

    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }

        i++;

        if (i < x->numKeys && key == x->keys[i]) {
            pushBack(x->values[i], value);
        } else {
            for (int j = x->numKeys; j > i; j--) {
                if (j < tree->order - 1) {
                    x->keys[j] = x->keys[j - 1];
                    x->values[j] = x->values[j - 1];
                }
            }
            x->keys[i] = key;
            x->values[i] = createList();
            if (x->values[i] == NULL) {
                return -1;
            }
            pushBack(x->values[i], value);
            x->numKeys++;
        }
    } else {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }

        i++;

        if (x->children[i]->numKeys == tree->order - 1) {
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
    BTreeNode* nodeForKey = searchBTree(getRoot(tree), key);

    if (nodeForKey != NULL) {
        for (int i = 0; i < nodeForKey->numKeys; i++) {
            if (nodeForKey->keys[i] == key) {
                pushBack(nodeForKey->values[i], value);
                return 0;
            }
        }
    }

    if (root == NULL) {
        root = newBTreeNode(tree, 1);
        if (root == NULL) {
            return -1;
        }
        root->keys[0] = key;
        root->values[0] = createList();
        if (root->values[0] == NULL) {
            free(root);
            return -1;
        }
        pushBack(root->values[0], value);
        root->numKeys = 1;
        tree->root = root;
    } else {
        if (root->numKeys == tree->order - 1) {
            BTreeNode* s = newBTreeNode(tree, 0);
            if(s == NULL) {
                return -1;
            }
            tree->root = s;
            s->children[0] = root;
            if(splitChildBTree(tree, s, 0) < 0) {
                return -1;
            }
            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            if (insertNonFullBTree(tree, s->children[i], key, value) < 0) {
                return -1;
            }
        } else {
            if (insertNonFullBTree(tree, root, key, value) < 0) {
                return -1;
            }
        }
    }
    return 0;
}

void searchByRangeBTree(BTreeNode* node, int key1, int key2, List* listaP) {
    if (node == NULL) {
        return;
    }

    int i = 0;
    
    while (i < node->numKeys && node->keys[i] < key1) {
        i++;
    }

    while (i < node->numKeys && node->keys[i] <= key2) {
        int cantidadAux = get_size_list(node->values[i]);
        pushBack(listaP, firstList(node->values[i]));
        for (int cont = 1; cont < cantidadAux; cont++) {
            pushBack(listaP, nextList(node->values[i]));
        }
        i++;
    }

    if (node->leaf) {
        return;
    }
    else{
        for (int j = 0; j <= node->numKeys; j++)
        {
            searchByRangeBTree(node->children[j], key1, key2, listaP);
        }
    }
}
BTreeNode* getRoot(BTree *tree)
{
    return tree->root;
}

BTreeNode* searchBTree(BTreeNode* root, int key) {
    if (root == NULL)    return NULL;

    int i = 0;
    while (i < root->numKeys && key > root->keys[i])    i++;

    if (i < root->numKeys && key == root->keys[i])    return root;

    if (root->leaf == 1)    return NULL;

    return searchBTree(root->children[i], key);
}


void destroyBTreeNodes(BTreeNode *node)
{
    if (node == NULL)
        return;

    // Si el nodo no es una hoja, llamar a BTreeDestroy en cada hijo
    if (!isLeaf(node)) {
        for (int i = 0; node->children[i] != NULL; i++) {
            if (node->children[i] != NULL)
                destroyBTreeNodes(node->children[i]);
        }
    }

    // Liberar los recursos para las claves y los hijos
    if (node->keys != NULL) {
        free(node->keys);
        node->keys = NULL;
    }
    if (node->children != NULL) {
        free(node->children);
        node->children = NULL;
    }

    // Finalmente, liberar el nodo mismo
    free(node);
}

void destroyBTree(BTree* BTree)
{
    free(BTree->root);
    free(BTree);
}

