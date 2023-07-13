#include "busquedas.h"

/*La función busquedaProductosDirecta consiste en una busqueda por clave el nombre del producto en el mapa de productos. 
Si no hay coincidencias, se muestra un mensaje que lo indique.*/
void busquedaProductosDirecta(HashMap* mapa) {
    printMap(mapa, 0);    // Muestra todos los productos disponibles.
    puts(MSJBUSQUEDA1); //Mensaje de búsqueda de productos por nombre.
    
    char nombreProductoBuscado[MAXLEN + 1]; //Variable que almacenará la cadena ingresada por el usuario para este caso.
    printf("Ingrese el nombre del producto a buscar: ");
    scanf("%30[^\n]s", nombreProductoBuscado); //Se pide al usuario ingresar el nombre exacto del producto (incluyendo la mayúscula inicial).
    while (getchar() != '\n'); // Limpiar el buffer del teclado.
    
    nombreProductoBuscado[0] = toupper(nombreProductoBuscado[0]);     // Para evitar case sensitive.
    for (char i = 1; nombreProductoBuscado[i] != '\0'; i++)           // Para evitar case sensitive.
        nombreProductoBuscado[i] = tolower(nombreProductoBuscado[i]); // Para evitar case sensitive.
    
    Pair* parBuscado = searchMap(mapa, nombreProductoBuscado); //Se busca en el mapa de productos con clave el nombre del producto.
    
    if (parBuscado == NULL)
    {
        puts(MSJBUSQUEDASC); // Mensaje para indicar que no hay coincidencias de búsqueda.
        return;              // En este caso, se termina el algoritmo.
    }
    else
    {
        tipoProducto* productoBuscado = parBuscado->value; //Se crea una variable auxiliar tipoProducto 
                                                           //para almacenar la data del producto buscado por su nombre.
        List* listaAux = createList();
        pushBack(listaAux, productoBuscado);
        mostrarProductos(listaAux); //Se muestra el producto.
        destroyList(listaAux); // Se libera memoria.
    }
}


/*La función busquedaPorPrecio consiste en una búsqueda por rango de precios en el árbol B. El usuario establece un rango y el algoritmo se encarga de llamar a las funciones correspondientes para realizar la búsqueda y mostrar todas las coincidencias que correspondan.*/
void busquedaPorPrecio(BPlusTree* arbolProductos)
{
    puts(MSJBUSQUEDA2); // Mensaje de búsqueda de productos por precio.
    int precio1 = 1, precio2 = 0; // Valores iniciales para que funcione el ciclo while. de la línea 43.
    List* listaProductos = createList(); // Se crea una lista de productos.
    
    if (listaProductos == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
        printf("Error.");
    
    while (precio1 > precio2 || precio1 <= 0 || precio2 <= 0) // Se pide al usuario ingresar dos precios hasta que el precio 1 sea menor que el precio 2 y ambos precios sean mayores que cero.
    {
        printf("Ingrese el precio menor: "); 
        scanf("%d", &precio1); // El precio 1 es el precio menor.
        printf("Ingrese el precio mayor: ");
        scanf("%d", &precio2);  // El precio 2 es el precio mayor.
    }
    
    searchRangeBPlusTree(arbolProductos, precio1, precio2, listaProductos);
    // Se busca por rango de precios en el arbol B y se agregan todos los productos en ese rango a la lista de productos 'listaP'.
    
    if (isListEmpty(listaProductos)) // Si la lista está vacía es porque no hay productos en ese rango de precios.
    {
        puts(MSJBUSQUEDASC); // Mensaje para indicar que no hay coincidencias de búsqueda.
        return;              // En este caso, se termina el algoritmo.
    }
    
    printf("            PRODUCTOS ENTRE $%d y $%d PESOS: \n", precio1, precio2);
    
    tipoProducto* productoBuscado = firstList(listaProductos); //Se accede al primer elemento de la lista de productos hallados en el rango.

    if (productoBuscado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
    {
        printf("ERROR DE MEMORIA.");
        return; // Se termina el algoritmo.
    }
    
    List* listaAux = createList();
    pushBack(listaAux, productoBuscado);
    // Se muestra la información del primer producto dentro del rango.
    int cont = 2;
    while (1)
    {
        productoBuscado = nextList(listaProductos); // Se accede al siguiente elemento de la lista.
        if (productoBuscado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
        pushBack(listaAux, productoBuscado);
        if (cont % 3 == 0) // Cada 3 productos se llama a la función mostrarProductos (para que muestre cada 3 productos uno al lado del otro).
        {
            mostrarProductos(listaAux);
            cleanList(listaAux);
        }
        cont++;// Se van mostrando todos los elementos de la lista.
    }
    if ((cont - 1) % 3 != 0) // Si el resto es distinto de cero, quedaron 1 o 2 productos por mostrar.
    {
        mostrarProductos(listaAux);
    }
    destroyList(listaAux); // Se libera memoria.
}

/* La función busquedaProductosAdyacentes se encarga de realizar una búsqueda de productos en listas adyacentes (en el mapa de 
supermercados y en el mapa de categorías). Esto lo logra con funciones propias de la TDA hashmap y list. Además, antes de realizar la búsqueda se hace una conversión a mayúsculas y minúsculas según corresponda para evitar case sensitive.*/
void busquedaProductosAdyacentes(HashMap* mapa, int indicador)
{
    // Si el indicador es 1, se estaría accediendo al mapa de supemercados.
    // Si el indicador es 2 (distinto de 1), se estaría accediendo al mapa de categorías.
    if (indicador == 1)
    {
        printMap(mapa, 1);
        puts(MSJBUSQUEDA3);  // Mensaje de búsqueda de productos por supermercado.
        printf(MSJBUSQUEDA31); // Mensaje de búsqueda de productos por supermercado.
    }
    else
    {
        printMap(mapa, 2);
        puts(MSJBUSQUEDA4);  // Mensaje de búsqueda de productos por categoría.
        printf(MSJBUSQUEDA41); // Mensaje de búsqueda de productos por categoría.
    }
    
    char nombreElementoBuscado[MAXLEN + 1]; // Cadena para almacenar el nombre del elemento a buscar.
    
    //printf("\n");
    scanf("%30[^\n]s", nombreElementoBuscado);
    while (getchar() != '\n'); // Limpiar el buffer del teclado.
    
    nombreElementoBuscado[0] = toupper(nombreElementoBuscado[0]);        // Para evitar case sensitive.
    for (char i = 1; nombreElementoBuscado[i] != '\0'; i++)              // Para evitar case sensitive.
    {
        nombreElementoBuscado[i] = tolower(nombreElementoBuscado[i]);    // Para evitar case sensitive.
        if (indicador == 1 && isspace(nombreElementoBuscado[i - 1]))     // Condición puesta para el caso especial del supermercado "Santa Isabel", que contiene una mayuscula la primera letra después del espacio "Santa **I**sabel".
            nombreElementoBuscado[i] = toupper(nombreElementoBuscado[i]);// Para evitar case sensitive. 
    }
    
    Pair* parBuscado = searchMap(mapa, nombreElementoBuscado); // Variable tipo Pair para almacenar el par encontrado.

    if (parBuscado == NULL)
    {
        puts(MSJBUSQUEDASC); // Mensaje para indicar que no hay coincidencias de búsqueda. 
        return;              // En este caso, se termina el algoritmo.
    }
    else
    {
        if (indicador == 1) // Si el indicador es 1 se crea una variable tipoSupermercado para almacenar el supermercado encontrado.
        {
            tipoSupermercado* supermercadoEncontrado = parBuscado->value; // Se le asigna el valor del par encontrado a 
                                                                          // la variable tipoSupermercado.
            if (isListEmpty(supermercadoEncontrado->productos))
            {
                puts(MSJBUSQUEDASCP1); 
                return;
            }
            tipoProducto* productoAsociado = firstList(supermercadoEncontrado->productos); // Se accede al primer elemento de la lista.

            if (productoAsociado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
            {
                printf("ERROR DE MEMORIA.");
                return; // Se termina el algoritmo.
            }
            List* listaProductos = createList();
            pushBack(listaProductos, productoAsociado);    // Se muestra el producto.
            int cont = 2;
            while (1)
            {
                productoAsociado = nextList(supermercadoEncontrado->productos); // Se accede al siguiente elemento de la lista.
                if (productoAsociado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
                pushBack(listaProductos, productoAsociado); // Se van mostrando todos los elementos de la lista.
                if (cont % 3 == 0)
                {
                    mostrarProductos(listaProductos);
                    cleanList(listaProductos);
                }
                cont++;// Se van mostrando todos los elementos de la lista.
            }
            if ((cont - 1) % 3 != 0)
            {
                mostrarProductos(listaProductos);
            }
            destroyList(listaProductos); // Se libera memoria.
        }
        else
        {
            tipoCategoria* categoriaEncontrada = parBuscado->value;
            if (isListEmpty(categoriaEncontrada->productos))
            {
                puts(MSJBUSQUEDASCP2); 
                return;
            }
            //int cantProductoAsociados = get_size_list(categoriaEncontrada->productos);
            tipoProducto* productoAsociado = firstList(categoriaEncontrada->productos);
            if (productoAsociado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
            {
                printf("ERROR DE MEMORIA.");
                return; // Se termina el algoritmo.
            }
            
            List* listaAsociada = createList();
            pushBack(listaAsociada, productoAsociado);
            int cont2 = 2;

            while (1)
            {
                productoAsociado = nextList(categoriaEncontrada->productos); // Se accede al siguiente elemento de la lista.
                if (productoAsociado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
                pushBack(listaAsociada, productoAsociado); // Se van mostrando todos los elementos de la lista.
                if (cont2 % 3 == 0) // Cada 3 productos se llama a la función mostrarProductos (para que muestre cada 3 productos uno al lado del otro).
                {
                    mostrarProductos(listaAsociada);
                    cleanList(listaAsociada);
                }
                cont2++;// Se van mostrando todos los elementos de la lista.
            }
            if ((cont2 - 1) % 3 != 0) // Si el resto es distinto de cero, quedaron 1 o 2 productos por mostrar.
            {
                mostrarProductos(listaAsociada);
            }
            destroyList(listaAsociada); // Se libera memoria.
        }
    }
}



void busquedaProductosPorNombreParcial(HashMap *mapa, trieTree* trie)
{
    printMap(mapa, 0);    // Muestra todos los productos disponibles.
    puts(MSJBUSQUEDA5); //Mensaje de búsqueda de productos por nombre.

    List* listaProductos = createList();
    char nombreProductoBuscado[MAXLEN + 1]; //Variable que almacenará la cadena ingresada por el usuario para este caso.
    printf("Ingrese el nombre o nombre parcial del producto a buscar: ");
    scanf("%30[^\n]s", nombreProductoBuscado); //Se pide al usuario ingresar el nombre exacto del producto (incluyendo la mayúscula inicial).
    while (getchar() != '\n'); // Limpiar el buffer del teclado.
    
    trieNode* rootTrie = getRootTrie(trie);
    searchWordsStartingWith(rootTrie, nombreProductoBuscado, listaProductos);
    
    if (isListEmpty(listaProductos))
    {
        puts(MSJBUSQUEDASC); // Mensaje para indicar que no hay coincidencias de búsqueda.
        return;              // En este caso, se termina el algoritmo.
    }
    
    printf("            PRODUCTOS ENCONTRADOS: \n");
    
    tipoProducto* productoBuscado = firstList(listaProductos); 

    if (productoBuscado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
    {
        printf("ERROR DE MEMORIA.");
        return; // Se termina el algoritmo.
    }
    
    List* listaAux = createList();
    pushBack(listaAux, productoBuscado);
    // Se muestra la información del primer producto dentro del rango.
    int cont = 2;
    while (1)
    {
        productoBuscado = nextList(listaProductos); // Se accede al siguiente elemento de la lista.
        if (productoBuscado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
        pushBack(listaAux, productoBuscado);
        if (cont % 3 == 0) // Cada 3 productos se llama a la función mostrarProductos (para que muestre cada 3 productos uno al lado del otro).
        {
            mostrarProductos(listaAux);
            cleanList(listaAux);
        }
        cont++;// Se van mostrando todos los elementos de la lista.
    }
    if ((cont - 1) % 3 != 0) // Si el resto es distinto de cero, quedaron 1 o 2 productos por mostrar.
    {
        mostrarProductos(listaAux);
    }
    destroyList(listaAux); // Se libera memoria.
    
}