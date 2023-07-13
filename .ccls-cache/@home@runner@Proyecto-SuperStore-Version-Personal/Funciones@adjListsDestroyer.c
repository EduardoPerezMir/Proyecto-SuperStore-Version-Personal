#include "adjListsDestroyer.h"

/* La función "destroyAdjListsProductos" libera memoria de las listas de supermercados adyacentes al mapa de producto. Esto, lo logra recorriendo el mapa y llamando a la función destroyList, de la TDA lista. */
void destroyAdjListsProductos(HashMap *mapaProductos) {
  Pair *parAux = firstMap(mapaProductos);
  tipoProducto *productoCurrent = parAux->value;
  if (productoCurrent == NULL)
    return;
  while (parAux != NULL) {
    productoCurrent = parAux->value;
    if (productoCurrent->supermercados != NULL) {
      destroyList(productoCurrent->supermercados);
      productoCurrent->supermercados = NULL;
    }
    parAux = nextMap(mapaProductos); // Recorre el mapa de productos y libera la  memoria de toda lista adyacente a los elementos del mapa.
  }
}

/* La función destroyAdjListsSupermercados libera memoria de las listas de productos adyacentes al mapa de supermercados. Esto, lo logra recorriendo el mapa y llamando a la función destroyList, de la TDA lista. */
void destroyAdjListsSupermercados(HashMap *mapaSupermercados) {
  Pair *parAux = firstMap(mapaSupermercados);
  tipoSupermercado *supermercadoCurrent = parAux->value;
  if (supermercadoCurrent == NULL)
    return;
  while (parAux != NULL) {
    supermercadoCurrent = parAux->value;
    if (supermercadoCurrent->productos != NULL) {
      destroyList(supermercadoCurrent->productos);
      supermercadoCurrent->productos = NULL;
    }

    parAux = nextMap(mapaSupermercados); // Recorre el mapa de supermercados y libera la  memoria de toda lista adyacente a los elementos del mapa.
  }
}

/* La función "destroyAdjListsCategorías" libera memoria de las listas de productos adyacentes al mapa de categorías. Esto, lo logra recorriendo el mapa y llamando a la función destroyList, de la TDA lista. */
void destroyAdjListsCategorias(HashMap *mapaCategorias) {
  Pair *parAux = firstMap(mapaCategorias);
  tipoSupermercado *categoriaCurrent = parAux->value;
  if (categoriaCurrent == NULL)
    return;
  while (parAux != NULL) {
    categoriaCurrent = parAux->value;
    if (categoriaCurrent->productos != NULL) {
      destroyList(categoriaCurrent->productos);
      categoriaCurrent->productos = NULL;
    }
    parAux = nextMap(mapaCategorias); // Recorre el mapa de categorías y libera la  memoria de toda lista adyacente a los elementos del mapa.
  }
}

// La función destroyAdjListsBTree libera memoria de las listas de supermercados adyacentes al mapa ordenado (árbol B) de productos. Esto, lo logra recorriendo el árbol B y llamando a la función destroyList, de la TDA lista. */
