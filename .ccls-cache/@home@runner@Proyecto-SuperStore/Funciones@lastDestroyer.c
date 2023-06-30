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
        {
            destroyList(productoCurrent->supermercados);
            productoCurrent->supermercados = NULL;
        }
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
        {
            destroyList(supermercadoCurrent->productos);
            supermercadoCurrent->productos = NULL;
        }
            
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
        {
            destroyList(categoriaCurrent->productos);
            categoriaCurrent->productos = NULL;
        }
        parAux = nextMap(mapaCategorias);
    }
}


void destroyAllAdjacentListsBTree(BTreeNode *node)
{
    if (node == NULL)
        return;

    if (!isLeaf(node)) {
        for (int i = 0; node->children[i] != NULL; i++) {
                destroyAllAdjacentListsBTree(node->children[i]);
        }
    }
    
    for (int i = 0; node->values[i] != NULL; i++)
    {
        List* listaCurrent = node->values[i];
        
        tipoProducto* productoCurrent = firstList(listaCurrent);
        
        for (int j = 0; productoCurrent != NULL; j++)
        {
            if (productoCurrent->supermercados != NULL)
            {
                destroyList(productoCurrent->supermercados);
                productoCurrent->supermercados = NULL;
            }
            productoCurrent = nextList(listaCurrent);
        }
    }
}
