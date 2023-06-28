#include "mostrarElementosSistema.h"

void printListS(List* Super) {
    tipoSupermercado* current = firstList(Super);
    int cont = 1;
    printf("┌──────────────────────────────────┐\n");
    while(current != NULL) {
        printf(" %d. %s\n",cont,current->nombre);
        cont++;
        current = nextList(Super);
    }
    printf("└──────────────────────────────────┘\n");
}

void printListP(List* Super) {
    tipoProducto* current = firstList(Super);
    int cont = 1;
    while(current != NULL) {
        printf("%d. %s\n",cont,current->nombre);
        cont++;
        current = nextList(Super);
    }
}

void printMap(HashMap* mapa)
{
    Pair* current = firstMap(mapa);
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n");
    printf("┌──────────────────────────────────┐\n");
    int cont = 1;
    while(current != NULL) {
        char elemento[MAXLEN + 1];
        strcpy(elemento, current->key);
        printf(" %i. %s\n", cont, elemento);
        cont++;
        current = nextMap(mapa);
     }
    printf("└──────────────────────────────────┘\n\n");
}

void mostrarProducto(tipoProducto* productoAMostrar)
{
    printf("┌──────────────────────────────────────────┐\n");
    printf("  Nombre Producto: %s\n", productoAMostrar->nombre);
    printf("  Precio: $%s\n", productoAMostrar->precio);
    printf("  Categoria: %s\n", productoAMostrar->categoria);
    
    tipoSupermercado* supermercadoPtr = firstList(productoAMostrar->supermercados);
    printf("  Supermercado 1: %s\n", supermercadoPtr->nombre);
    for (int i = 1; i < productoAMostrar->cantSupermercados; i++)
    {
        supermercadoPtr = nextList(productoAMostrar->supermercados);
        printf("  Supermercado %d: %s\n", i + 1, supermercadoPtr->nombre);
    }
    printf("└──────────────────────────────────────────┘\n");
}

void mostrarOfertaNacional(HashMap* productos) {
    puts(MSJVISUALIZACIONOFERTA);
    
    Pair* current = firstMap(productos);
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n\n");
    
    int cont = 1;
     while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        printf("\n%24s %d\n","PRODUCTO",cont);
        mostrarProducto(producto);
        cont++;
        current = nextMap(productos);
     }
}