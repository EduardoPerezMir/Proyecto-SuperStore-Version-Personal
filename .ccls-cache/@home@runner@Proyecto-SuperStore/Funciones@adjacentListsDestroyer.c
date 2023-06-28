#include "adjacentListsDestroyer.h"

void destroyAllAdjacentListsProductos(HashMap* mapaProductos)
{
    Pair* parAux = firstMap(mapaProductos);
    tipoProducto* productoCurrent = parAux->value;
    if (productoCurrent == NULL)
        return;
    while (productoCurrent != NULL)
    {
        productoCurrent = parAux->value;
        if (productoCurrent->supermercados != NULL)
            destroyList(productoCurrent->supermercados);
        parAux = nextMap(mapaProductos);
    }
}

/*
void destroyAllAdjacentListsSupermercados(HashMap* mapaSupermercados)
{
    Pair* parAux = firstMap(mapaSupermercados);
    tipoSupermercado* supermercadoCurrent = parAux->value;
    if (supermercadoCurrent == NULL)
        return;
    while (supermercadoCurrent != NULL)
    {
        supermercadoCurrent = parAux->value;
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
    while (categoriaCurrent != NULL)
    {
        categoriaCurrent = parAux->value;
        destroyList(categoriaCurrent->productos);
        parAux = nextMap(mapaCategorias);
    }
}

*/
//void destroyAllAdjacentListsBTree(BTree* arbolB)
//{
    
//}


