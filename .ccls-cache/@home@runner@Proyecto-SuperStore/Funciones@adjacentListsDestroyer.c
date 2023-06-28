#include "adjacentListsDestroyer.h"

void destroyAllAdjacentListsProductos(HashMap* mapaProductos)
{
    Pair* parAux = firstMap(mapaProductos);
    tipoProducto* productoCurrent = parAux->value;
    if (productoCurrent == NULL)
        return;
    while (parAux != NULL)
    {
        productoCurrent = parAux->value;
        if (productoCurrent->supermercados != NULL)
            destroyList(productoCurrent->supermercados);
        parAux = nextMap(mapaProductos);
    }
}


void destroyAllAdjacentListsSupermercados(HashMap* mapaSupermercados)
{
    Pair* parAux = firstMap(mapaSupermercados);
    tipoSupermercado* supermercadoCurrent = parAux->value;
    if (supermercadoCurrent == NULL)
        return;
    while (parAux != NULL)
    {
        supermercadoCurrent = parAux->value;
        if (supermercadoCurrent->productos != NULL)
            destroyList(supermercadoCurrent->productos);
        parAux = nextMap(mapaSupermercados);
    }
}

void destroyAllAdjacentListsCategorias(HashMap* mapaCategorias)
{
    Pair* parAux = firstMap(mapaCategorias);
    tipoSupermercado* categoriaCurrent = parAux->value;
    if (categoriaCurrent == NULL)
        return;
    while (parAux != NULL)
    {
        categoriaCurrent = parAux->value;
        if (categoriaCurrent->productos != NULL)
            destroyList(categoriaCurrent->productos);
        parAux = nextMap(mapaCategorias);
    }
}


void destroyAllAdjacentListsBTree(BTreeNode *node)
{
    if (node == NULL)
        return;

    // Si el nodo no es una hoja, llamar a BTreeDestroy en cada hijo
    if (!isLeaf(node)) {
        for (int i = 0; node->children[i] != NULL; i++) {
            if (node->children[i] != NULL)
                destroyAllAdjacentListsBTree(node->children[i]);
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

