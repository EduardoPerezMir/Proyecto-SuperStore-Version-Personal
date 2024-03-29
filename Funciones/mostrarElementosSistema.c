#include "mostrarElementosSistema.h"

/*La opcion imprime la lista de supermercados, recorriendo la lista de inicio a fin*/
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

/*La opción imprime la lista de productos, recorriendo la lista de inicio a fin*/
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
    int cont = 1;
    char caracterAux = ' ';
    while (current != NULL) {
        if (current != NULL) 
        {
            char elemento[MAXLEN + 1];
            // Se copia el nombre del elemento en el mapa en una variable que es la que muestra el nombre del elemento
            strcpy(elemento, current->key);
            printf("|%-4i|%-31s| ", cont, elemento);
            // Variable cont utilizada para calcular saltos de linea, %3 para mostrar 3 elementos por linea
            if (cont % 3 == 0)    printf("\n");
            // Se avanza en el mapa con el current
            current = nextMap(mapa);
        }
        cont++;
    }
    if (cont % 3 == 0)
    {
        printf("%-5c%-32c|\n",caracterAux, caracterAux);
    }
    else if (cont % 3 == 2)
    {
        printf("%-5c%-32c|",caracterAux, caracterAux);
        printf("%-5c%-33c|\n",caracterAux, caracterAux);        
    }
    
    printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n");
}

/*La funcion muesta una lista de HASTA 3 productos de forma secuencial por pantalla (un producto al lado del otro).*/
void mostrarProductos(List* lista)
{
    int size = get_size(lista);
    tipoProducto* productoAMostrar1 = firstList(lista);
    tipoProducto* productoAMostrar2 = (tipoProducto*) malloc(sizeof(tipoProducto));
    productoAMostrar2 = NULL;
    if (size > 1)    productoAMostrar2 = nextList(lista); // Si hay más de un producto se inicializa el producto 2.
    tipoProducto* productoAMostrar3 = (tipoProducto*) malloc(sizeof(tipoProducto));
    productoAMostrar3 = NULL;
    if (size > 2)    productoAMostrar3 = nextList(lista); // Si hay más de dos productos, se inicializa el producto 3.
    
    char caracterAux = ' ';
    
    for (int i = 0; i < size; i++)    printf("%-3c|--------------------------------------------|%-3c", caracterAux, caracterAux);
    printf("\n");
    // En las siguientes 12 lineas se muestra la información asociada a los productos: Su nombre, precio y categoría.
    if (productoAMostrar1 != NULL)    printf("%-5cNombre Producto: %-31s", caracterAux, productoAMostrar1->nombre);
    if (productoAMostrar2 != NULL)    printf("%-4cNombre Producto: %-31s", caracterAux, productoAMostrar2->nombre);
    if (productoAMostrar3 != NULL)    printf("%-4cNombre Producto: %-31s", caracterAux, productoAMostrar3->nombre);
    printf("\n");
    if (productoAMostrar1 != NULL)    printf("%-5cCategoria: %-31s", caracterAux, productoAMostrar1->categoria);
    if (productoAMostrar2 != NULL)    printf("%-4c      Categoria: %-31s", caracterAux, productoAMostrar2->categoria);
    if (productoAMostrar3 != NULL)    printf("%-4c      Categoria: %-31s", caracterAux, productoAMostrar3->categoria);
    printf("\n");
    // Variable utilizada para recorrer la lista de supermercados que tienen ese producto

    tipoProductoEspecifico* preciosYSupermecados1 = (tipoProductoEspecifico*) malloc(sizeof(tipoProductoEspecifico));
    tipoProductoEspecifico* preciosYSupermecados2 = (tipoProductoEspecifico*) malloc(sizeof(tipoProductoEspecifico));
    tipoProductoEspecifico* preciosYSupermecados3 = (tipoProductoEspecifico*) malloc(sizeof(tipoProductoEspecifico));


    // Importante inicializar en NULL.
    preciosYSupermecados1 = NULL;
    preciosYSupermecados2 = NULL;
    preciosYSupermecados3 = NULL;

    //Si un producto no es nulo, entonces tiene supermercados asociados.
    if (productoAMostrar1 != NULL)  preciosYSupermecados1 = firstList(productoAMostrar1->preciosPorSupermercado);
    if (productoAMostrar2 != NULL)  preciosYSupermecados2 = firstList(productoAMostrar2->preciosPorSupermercado);
    if (productoAMostrar3 != NULL)  preciosYSupermecados3 = firstList(productoAMostrar3->preciosPorSupermercado);

    //Si un supermercado no es nulo, entonces tiene un nombre.
    if (preciosYSupermecados1 != NULL)    printf("%-5cSupermercado 1: %-31s", caracterAux, preciosYSupermecados1->nombreSupermercado);
    if (preciosYSupermecados2 != NULL)    printf("%-4c Supermercado 1: %-31s", caracterAux, preciosYSupermecados2->nombreSupermercado);
    if (preciosYSupermecados3 != NULL)    printf("%-4c Supermercado 1: %-31s", caracterAux, preciosYSupermecados3->nombreSupermercado);
    printf("\n");
    
    if (preciosYSupermecados1 != NULL)    printf("%-5cPrecio 1: $%-31s", caracterAux, preciosYSupermecados1->precio);
    if (preciosYSupermecados2 != NULL)    printf("%-4c      Precio 1: $%-31s", caracterAux, preciosYSupermecados2->precio);
    if (preciosYSupermecados3 != NULL)    printf("%-4c      Precio 1: $%-31s", caracterAux, preciosYSupermecados3->precio);
    
    printf("\n");

    int cont = 1; // Este contador es para indicar que supermercado se mostrará respecto a la lista asociada a cada producto.
    while (1)
    {
        // Se recorre las listas de supermercados respectivamente.
        if (preciosYSupermecados1 != NULL)    preciosYSupermecados1 = nextList(productoAMostrar1->preciosPorSupermercado);
        if (preciosYSupermecados2 != NULL)    preciosYSupermecados2 = nextList(productoAMostrar2->preciosPorSupermercado);
        if (preciosYSupermecados3 != NULL)    preciosYSupermecados3 = nextList(productoAMostrar3->preciosPorSupermercado);

        // El bucle termina cuando ya no hay más supermercados en ninguna de las tres posibles listas.
        if (preciosYSupermecados1 == NULL && preciosYSupermecados2 == NULL && preciosYSupermecados3 == NULL)    break;
        
        if (preciosYSupermecados1 != NULL)  printf("%-5cSupermercado %d: %-31s", caracterAux, cont + 1, preciosYSupermecados1->nombreSupermercado);
        else     printf("%-5c                %-31c", caracterAux, caracterAux);
        if (preciosYSupermecados2 != NULL)  printf("%-4c Supermercado %d: %-31s", caracterAux, cont + 1, preciosYSupermecados2->nombreSupermercado);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);
        if (preciosYSupermecados3 != NULL)  printf("%-4c Supermercado %d: %-31s", caracterAux, cont + 1, preciosYSupermecados3->nombreSupermercado);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);

        printf("\n");

        if (preciosYSupermecados1 != NULL)  printf("%-5cPrecio %d: $%-31s", caracterAux, cont + 1,preciosYSupermecados1->precio);
        else     printf("%-5c           %-31c", caracterAux, caracterAux);
        if (preciosYSupermecados2 != NULL)  printf("%-4c      Precio %d: $%-31s", caracterAux, cont + 1,  preciosYSupermecados2->precio);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);
        if (preciosYSupermecados3 != NULL)  printf("%-4c      Precio %d: $%-31s", caracterAux, cont + 1, preciosYSupermecados3->precio);
        else     printf("%-4c                 %-31c", caracterAux, caracterAux);

        printf("\n");
        cont++;
    }
    
   // if (productoAMostrar1 != NULL)  preciosYSupermecados1 = firstList(productoAMostrar1->preciosPorSupermercado);
   // if (productoAMostrar2 != NULL)  preciosYSupermecados2 = firstList(productoAMostrar2->preciosPorSupermercado);
   // if (productoAMostrar3 != NULL)  preciosYSupermecados3 = firstList(productoAMostrar3->preciosPorSupermercado);
/*
    if (preciosYSupermecados1 != NULL)  printf("%13s","Precios:");
    else     printf("%-5c                %-31c", caracterAux, caracterAux);
    if (preciosYSupermecados2 != NULL)  printf("%55s","Precios:");
    else     printf("%-4c                 %-31c", caracterAux, caracterAux);
    if (preciosYSupermecados3 != NULL)  printf("%55s","Precios:");
    else     printf("%-4c                 %-31c", caracterAux, caracterAux);*/
    
    for (int i = 0; i < size; i++)    printf("%-3c|--------------------------------------------|%-3c", caracterAux, caracterAux);
    printf("\n");
}




/*Esta opcion muestra todos productos del mapa de productos*/
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
        if (cont % 3 == 0) // Se usa esta condición para mostrar productos de 3 en 3.
        {
            printf("%26s %-4d","PRODUCTO", cont - 2);
            printf("%46s %-4d","PRODUCTO", cont - 1);
            printf("%46s %-4d","PRODUCTO", cont);
            printf("\n");
            mostrarProductos(productosAMostrar);
            cleanList(productosAMostrar);
        }
        cont++;
    }
    // La siguientes dos condiciones son para los casos en que quede 1 o 2 productos por mostrar.
    if ((cont  - 1) % 3 != 0)
    {
        if ((cont - 1) % 3 == 1) // Si el resto es 1, entonces hay 1 producto que queda por mostrar.
        {
            printf("%26s %-4d","PRODUCTO", cont);
        }    
        else // Si el resto es 2, entonces hay 2 productos que quedan por mostrar.
        {
            printf("%26s %-4d","PRODUCTO", cont - 1);
            printf("%46s %-4d","PRODUCTO", cont);
        }
        printf("\n");
        mostrarProductos(productosAMostrar); // Se llama a la función productosAMostrar (está generalizada para 1, 2 o 3 productos).
    }
}
