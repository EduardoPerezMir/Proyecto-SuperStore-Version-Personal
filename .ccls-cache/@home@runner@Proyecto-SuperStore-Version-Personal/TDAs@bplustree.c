#include "bplustree.h"

BPlusTree* createBPlusTree() {
    BPlusTree* tree = malloc(sizeof(BPlusTree));
    tree->root = NULL;
    return tree;
}

BPlusNode* createBPlusTreeNode() {
    BPlusNode* node = malloc(sizeof(BPlusNode));
    for (int i = 0; i < M; i++) {
        node->ptr[i] = (PtrElement*) malloc(sizeof(PtrElement));
        node->ptr[i]->node = NULL;
        node->ptr[i]->list = createList();
    }
    node->next = NULL;
    node->is_leaf = 0;
    node->num_keys = 0;
    return node;
}

void insertBPlusTree(BPlusTree* tree, int key, void* value) {
    BPlusNode* root = tree->root;
    BPlusNode* node;
    
    int i, j;
    int num;
    // Si el árbol está vacío, inicializamos el nodo raíz
    
    if (root == NULL) {
        root = createBPlusTreeNode();
        root->is_leaf = 1;
        root->keys[0] = key;
        pushBack(root->ptr[0]->list, value);
        root->num_keys++;
        tree->root = root;
        return;
    }

    // Encontramos el nodo hoja correcto donde debemos insertar la clave
    node = root;
    while (node->is_leaf == 0) {
        for (i = 0; i < node->num_keys; i++) {
            if (key <= node->keys[i]) {
                break;
            }
        }
        node = (BPlusNode*) node->ptr[i]->node;
    }

    // Insertamos la clave en la hoja encontrada
    for (i = 0; i < node->num_keys; i++) {
        if (key <= node->keys[i]) {
            break;
        }
    }
    if (key == node->keys[i])
    {
        pushBack(node->ptr[i]->list, value);
        return;
    }
    
    for (j = node->num_keys; j > i; j--) {
        node->keys[j] = node->keys[j - 1];
        node->ptr[j] = node->ptr[j - 1];
    }
    node->keys[i] = key;
    pushBack(node->ptr[i]->list, value);
    node->num_keys++;

    // Si el nodo está lleno, debemos dividirlo
    if (node->num_keys == M) {
        splitNode(tree, node);
    }
}

void splitNode(BPlusTree* tree, BPlusNode* node) {
    int i, mid;
    BPlusNode *newNode, *parent;

    // Creamos el nuevo nodo
    newNode = createBPlusTreeNode();
    newNode->is_leaf = node->is_leaf;
    newNode->next = node->next;
    node->next = newNode;

    // Encontramos la clave del medio
    mid = node->keys[M / 2];

    // Si el nodo no es una hoja, movemos la mitad de las claves y punteros al nuevo nodo
    if (!node->is_leaf) {
        for (i = M / 2; i < M; i++) {
            newNode->keys[i - M / 2] = node->keys[i];
            newNode->ptr[i - M / 2] = node->ptr[i];
            newNode->num_keys++;
            node->num_keys--;
        }
        node->ptr[i - M / 2] = node->ptr[i];
    }
    // Si el nodo es una hoja, movemos la mitad de las claves y punteros al nuevo nodo
    else {
        for (i = M / 2; i < M; i++) {
            newNode->keys[i - M / 2] = node->keys[i];
            newNode->ptr[i - M / 2] = node->ptr[i];
            newNode->num_keys++;
            node->num_keys--;
        }
        node->next = newNode;  // Asegura que los nodos hoja estén correctamente enlazados
    }

    // Si el nodo es la raíz, creamos una nueva raíz y actualizamos los punteros
    if (node == tree->root) {
        parent = createBPlusTreeNode();
        parent->keys[0] = mid;
        parent->ptr[0]->node = node;
        parent->ptr[1]->node = newNode;
        parent->num_keys++;
        tree->root = parent;
    }
    // Si el nodo no es la raíz, insertamos la clave del medio en el padre
    else {
        insertIntoParent(tree, node, mid, newNode);
    }
}

void insertIntoParent(BPlusTree* tree, BPlusNode* node, int key, BPlusNode* newNode) {
    int i, j;
    BPlusNode *parent = findParent(tree->root, node, key);

    // Encontramos la posición correcta para insertar la nueva clave
    for (i = 0; i < parent->num_keys; i++) {
        if (key < parent->keys[i]) {
            break;
        }
    }

    // Desplazamos las claves y punteros a la derecha para hacer espacio para la nueva clave
    for (j = parent->num_keys; j > i; j--) {
        parent->keys[j] = parent->keys[j - 1];
        parent->ptr[j + 1] = parent->ptr[j];
    }
    parent->keys[i] = key;
    parent->ptr[i + 1]->node = newNode;
    parent->num_keys++;

    // Si el nodo padre está lleno, lo dividimos
    if (parent->num_keys == M) {
        splitNode(tree, parent);
    }
}

BPlusNode* findParent(BPlusNode* root, BPlusNode* child, int key) {
    if (root == NULL || root->is_leaf) {
        return NULL;
    }

    BPlusNode* parent = NULL;
    for (int i = 0; i <= root->num_keys; i++) {
        if (root->ptr[i]->node == child) {
            return root;
        }
        if (root->ptr[i] && root->ptr[i]->node && key < root->ptr[i]->node->keys[0]) {
            parent = findParent(root->ptr[i]->node, child, key);
            if (parent) {
                return parent;
            }
        }
    }

    return NULL;
}


void searchRangeBPlusTree(BPlusTree* tree, int key1, int key2, List* lista) {
    BPlusNode* node;
    int i;

    // Si el árbol está vacío, simplemente regresamos
    if (tree->root == NULL) {
        return;
    }

    // Encontramos el nodo hoja que contiene la clave más pequeña
    node = tree->root;
    while (node->is_leaf == 0) {
        for (i = 0; i < node->num_keys; i++) {
            if (key1 <= node->keys[i]) {
                break;
            }
        }
        node = (BPlusNode*) node->ptr[i]->node;
    }
    
    for (i = 0; i < node->num_keys; i++) {
        if (node->keys[i] >= key1) {
            break;
        }
    }
    
    // Iteramos a través de los nodos hoja y las claves dentro del rango
    while (node != NULL) {
        while (i < node->num_keys && node->keys[i] <= key2) {
            int tamanioLista = get_size(node->ptr[i]->list);
            void* elemento;
            pushBack(lista, firstList(node->ptr[i]->list));
            for (int j = 1; j < tamanioLista; j++){
                pushBack(lista, nextList(node->ptr[i]->list));
            }
            i++;
        }
        node = node->next;
        i = 0;
    }
}
