#include "mostrarElementosSistema.h"

/* La opcion imprime la lista de supermercados, recorriendo la lista de inicio a fin*/
void printListS(List* Super) {
    // Se recorre con variable current y se inicializa con primer elemento de la lista
    tipoSupermercado* current = firstList(Super);
    int cont = 1;
    printf("┌──────────────────────────────────┐\n");
    while(current != NULL) {
        printf(" %d. %s\n",cont,current->nombre);
        cont++;
        // Avanza en la lista con funcion nextList
        current = nextList(Super);
    }
    printf("└──────────────────────────────────┘\n");
}

/* La opción imprime la lista de productos, recorriendo la lista de inicio a fin*/
void printListP(List* Super) {
    // Se recorre con variable current y se inicializa con primer elemento de la lista
    tipoProducto* current = firstList(Super);
    int cont = 1;
    while(current != NULL) {
        printf("%d. %s\n",cont,current->nombre);
        cont++;
        // Avanza en la lista con funcion nextList
        current = nextList(Super);
    }
}

/* La opcion muestra todos los elementos del mapa, recibe como segundo parametro un valor para personalizar la impresión dependiendo del tipo de mapa, cabe aclarar que al ser un mapa no ordenado no muestra en un cierto orden*/
void printMap(HashMap* mapa, int indicadorMSJ)
{
    Pair* current = firstMap(mapa);
    // Si no hay elementos en el mapa se finaliza la ejecución
    if(current == NULL) {
        printf("No hay elementos existentes.\n");
        return;
    }

    // Se muestra mensaje personalizado segun el tipo de mapa que indica el segundo parametro
    if (indicadorMSJ == 0)    printf("\nLista de productos existentes:\n");
    else if (indicadorMSJ == 1) printf("\nLista de supermercados existentes:\n");
    else printf("\nLista de categorías existentes:\n");
    
    printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    int cont = 0;
    char caracterAux = ' ';
    while (current != NULL || (current == NULL && cont % 3 != 0)) {
        if (current != NULL) 
        {
            char elemento[MAXLEN + 1];
            // Se copia el nombre del elemento en el mapa en una variable que es la que muestra el nombre del elemento
            strcpy(elemento, current->key);
            printf("|%-4i|%-31s| ", cont + 1, elemento);
            // Variable cont utilizada para calcular saltos de linea, %3 para mostrar 3 elementos por linea
            if ((cont + 1) % 3 == 0)    printf("\n");
            // Se avanza en el mapa con el current
            current = nextMap(mapa);
        }
        else 
        {
            // Para cuadricular el mensaje, linea especifica cuando se mostraron todos los elementos del mapa
            printf("|%-4c|%-31c| ", caracterAux, caracterAux);
            if ((cont + 1) % 3 == 0)    printf("\n");
        }
        cont++;
    }
    printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n");
}

/* La funcion muesta un producto en especifico*/
void mostrarProducto(tipoProducto* productoAMostrar)
{
    printf("┌──────────────────────────────────────────┐\n");
    printf("  Nombre Producto: %s\n", productoAMostrar->nombre);
    printf("  Precio: $%s\n", productoAMostrar->precio);
    printf("  Categoria: %s\n", productoAMostrar->categoria);

    // Variable utilizada para recorrer la lista de supermercados que tienen ese producto
    tipoSupermercado* supermercadoPtr = firstList(productoAMostrar->supermercados);
    printf("  Supermercado 1: %s\n", supermercadoPtr->nombre);
    // Se recorren los supemercados
    for (int i = 1; i < productoAMostrar->cantSupermercados; i++)
    {
        supermercadoPtr = nextList(productoAMostrar->supermercados);
        printf("  Supermercado %d: %s\n", i + 1, supermercadoPtr->nombre);
    }
    printf("└──────────────────────────────────────────┘\n");
}

/* Esta opcion muestra todos productos del mapa de productos*/
void mostrarOfertaNacional(HashMap* productos) {
    puts(MSJVISUALIZACIONOFERTA);

    // Variable current recorre todos los elementos y se inicializa con el primer elemento
    Pair* current = firstMap(productos);
    // Si no  hay productos en el mapa de productos se finaliza la ejecucion
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n\n");
    
    int cont = 1;
    // Se recorre el mapa de productos con la funcion nextMap y se va mostrando el producto llamando a la funcion mostrarProducto
     while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        printf("\n%24s %d\n","PRODUCTO",cont);
        mostrarProducto(producto);
        cont++;
        current = nextMap(productos);
     }
}