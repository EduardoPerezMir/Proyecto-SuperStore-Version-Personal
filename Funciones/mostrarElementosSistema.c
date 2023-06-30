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
void mostrarProducto(List* lista)
{
    int size = get_size(lista);
    tipoProducto* productoAMostrar1 = firstList(lista);
    tipoProducto* productoAMostrar2 = (tipoProducto*) malloc(sizeof(tipoProducto));
    productoAMostrar2 = NULL;
    if (size > 1)    productoAMostrar2 = nextList(lista);
    tipoProducto* productoAMostrar3 = (tipoProducto*) malloc(sizeof(tipoProducto));
    productoAMostrar3 = NULL;
    if (size > 2)    productoAMostrar3 = nextList(lista);
    
    char caracterAux = ' ';
    
    for (int i = 0; i < size; i++)    printf("%-3c┌──────────────────────────────────────────┐%-3c", caracterAux, caracterAux);
    printf("\n");
    
    if (productoAMostrar1 != NULL)    printf("%-4cNombre Producto: %-31s", caracterAux, productoAMostrar1->nombre);
    if (productoAMostrar2 != NULL)    printf("%-4cNombre Producto: %-31s", caracterAux, productoAMostrar2->nombre);
    if (productoAMostrar3 != NULL)    printf("%-4cNombre Producto: %-31s", caracterAux, productoAMostrar3->nombre);
    printf("\n");
    if (productoAMostrar1 != NULL)    printf("%-4cPrecio: $%-31s", caracterAux, productoAMostrar1->precio);
    if (productoAMostrar2 != NULL)    printf("%-4c        Precio: $%-31s", caracterAux, productoAMostrar2->precio);
    if (productoAMostrar3 != NULL)    printf("%-4c        Precio: $%-31s", caracterAux, productoAMostrar3->precio);
    printf("\n");
    if (productoAMostrar1 != NULL)    printf("%-4cCategoria: %-31s", caracterAux, productoAMostrar1->categoria);
    if (productoAMostrar2 != NULL)    printf("%-4c      Categoria: %-31s", caracterAux, productoAMostrar2->categoria);
    if (productoAMostrar3 != NULL)    printf("%-4c      Categoria: %-31s", caracterAux, productoAMostrar3->categoria);
    printf("\n");
    // Variable utilizada para recorrer la lista de supermercados que tienen ese producto

    tipoSupermercado* supermercadoPtr1 = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
    tipoSupermercado* supermercadoPtr2 = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
    tipoSupermercado* supermercadoPtr3 = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));

    supermercadoPtr1 = NULL;
    supermercadoPtr2 = NULL;
    supermercadoPtr3 = NULL;
    
    if (productoAMostrar1 != NULL)    supermercadoPtr1 = firstList(productoAMostrar1->supermercados);
    if (productoAMostrar2 != NULL)    supermercadoPtr2 = firstList(productoAMostrar2->supermercados);
    if (productoAMostrar3 != NULL)    supermercadoPtr3 = firstList(productoAMostrar3->supermercados);
    
    if (supermercadoPtr1 != NULL)    printf("%-4cSupermercado 1: %-31s", caracterAux, supermercadoPtr1->nombre);
    if (supermercadoPtr2 != NULL)    printf("%-4c Supermercado 1: %-31s", caracterAux, supermercadoPtr2->nombre);
    if (supermercadoPtr3 != NULL)    printf("%-4c Supermercado 1: %-31s", caracterAux, supermercadoPtr3->nombre);
    
    printf("\n");
    
    int cont = 1; 
    while (1)
    {
        if (supermercadoPtr1 != NULL)    supermercadoPtr1 = nextList(productoAMostrar1->supermercados);
        if (supermercadoPtr2 != NULL)    supermercadoPtr2 = nextList(productoAMostrar2->supermercados);
        if (supermercadoPtr3 != NULL)    supermercadoPtr3 = nextList(productoAMostrar3->supermercados);

        if (supermercadoPtr1 == NULL && supermercadoPtr2 == NULL && supermercadoPtr3 == NULL)    break;
        
        if (supermercadoPtr1 != NULL)  printf("%-4cSupermercado %d: %-31s", caracterAux, cont + 1, supermercadoPtr1->nombre);
        else     printf("%-4c                %-31c", caracterAux, caracterAux);
        if (supermercadoPtr2 != NULL)    printf("%-4c Supermercado %d: %-31s", caracterAux, cont + 1, supermercadoPtr2->nombre);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);
        if (supermercadoPtr3 != NULL)    printf("%-4c Supermercado %d: %-31s", caracterAux, cont + 1, supermercadoPtr3->nombre);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);
        
        printf("\n");
        
        cont++;
    }
    
    for (int i = 0; i < size; i++)    printf("%-3c└──────────────────────────────────────────┘%-3c", caracterAux, caracterAux);
    printf("\n");
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
    List* productosAMostrar = createList();
    while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        pushBack(productosAMostrar, producto);
        current = nextMap(productos);
        if (cont % 3 == 0)
        {
            printf("%25s %-4d","PRODUCTO", cont - 2);
            printf("%45s %-4d","PRODUCTO", cont - 1);
            printf("%45s %-4d","PRODUCTO", cont);
            printf("\n");
            mostrarProducto(productosAMostrar);
            cleanList(productosAMostrar);
        }
        cont++;
    }
    if ((cont  - 1) % 3 != 0)
    {
        if ((cont - 1) % 3 == 1)
        {
            printf("%25s %-4d","PRODUCTO", cont);
        }    
        else
        {
            printf("%25s %-4d","PRODUCTO", cont - 1);
            printf("%45s %-4d","PRODUCTO", cont);
        }
        printf("\n");
        mostrarProducto(productosAMostrar);
    }
}
