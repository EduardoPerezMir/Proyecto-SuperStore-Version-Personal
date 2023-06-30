#include "busquedas.h"

// Mostrar producto por nombre

/*La función busquedaProductosDirecta consiste en una busqueda por el nombre del producto en el mapa de productos.*/
void busquedaProductosDirecta(HashMap* mapa) {
    printMap(mapa, 0);    // Muestra todos los productos disponibles.
    puts(MSJBUSQUEDA1); //Mensaje de búsqueda de productos por nombre.
    
    char nombreProductoBuscado[MAXLEN + 1]; //Variable que almacenará la cadena ingresada por el usuario para este caso.
    printf("INGRESE EL NOMBRE DEL PRODUCTO A BUSCAR: ");
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
        tipoProducto* productoBuscado = parBuscado->value; //Se crea una variable auxiliar tipoProducto para almacenar la data del producto buscado por su nombre.
        List* listaAux = createList();
        pushBack(listaAux, productoBuscado);
        mostrarProducto(listaAux); //Se muestra el producto.
    }
}


// Mostrar por precio Opcion 4

void busquedaPorPrecio(BTree* arbolProductos)
{
    puts(MSJBUSQUEDA2); // Mensaje de búsqueda de productos por precio.
    int precio1 = 1, precio2 = 0; // Valores iniciales para que funcione el ciclo while. de la línea 43.
    List* listaProductos = createList(); // Se crea una lista de productos.
    
    if (listaProductos == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
        printf("Error.");
    
    while (precio1 > precio2 || precio1 <= 0 || precio2 <= 0) // Se pide al usuario ingresar dos precios hasta que el precio 1 sea menor que el precio 2 y ambos precios sean mayores que cero.
    {
        printf("INGRESE EL PRECIO MENOR.\n"); 
        scanf("%d", &precio1); // El precio 1 es el precio menor.
        printf("INGRESE EL PRECIO MAYOR.\n");
        scanf("%d", &precio2);  // El precio 2 es el precio mayor.
    }
    printf("            PRODUCTOS ENTRE $%d y $%d PESOS: \n", precio1, precio2);
    searchByRangeBTree(getRoot(arbolProductos), precio1, precio2, listaProductos); 
    // Se busca por rango de precios en el arbol B y se agregan todos los productos en ese rango a la lista de productos 'listaP'.
    
    if (isListEmpty(listaProductos)) // Si la lista está vacía es porque no hay productos en ese rango de precios.
    {
        puts(MSJBUSQUEDASC); // Mensaje para indicar que no hay coincidencias de búsqueda.
        return;              // En este caso, se termina el algoritmo.
    }
    
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
        if (cont % 3 == 0)
        {
            mostrarProducto(listaAux);
            cleanList(listaAux);
        }
        cont++;// Se van mostrando todos los elementos de la lista.
    }
    if ((cont - 1) % 3 != 0)
    {
        mostrarProducto(listaAux);
        cleanList(listaAux);
    }
}

// Busqueda de Productos en Listas Adyacentes (en el mapa de supermercados y en el mapa de categorías):

void busquedaProductosAdyacentes(HashMap* mapa, int indicador)
{
    // Si el indicador es 1, se estaría accediendo al mapa de supemercados.
    // Si el indicador es 2 (distinto de 1), se estaría accediendo al mapa de categorías.
    if (indicador == 1)
    {
        printMap(mapa, 1);
        puts(MSJBUSQUEDA3);  // Mensaje de búsqueda de productos por supermercado.
        puts(MSJBUSQUEDA31); // Mensaje de búsqueda de productos por supermercado.
    }
    else
    {
        printMap(mapa, 2);
        puts(MSJBUSQUEDA4);  // Mensaje de búsqueda de productos por categoría.
        puts(MSJBUSQUEDA41); // Mensaje de búsqueda de productos por categoría.
    }
    
    char nombreElementoBuscado[MAXLEN + 1]; // Cadena para almacenar el nombre del elemento a buscar.
    
    printf("\n");
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
            tipoSupermercado* supermercadoEncontrado = parBuscado->value; // Se le asigna el valor del par encontrado a la variable tipoSupermercado.
            tipoProducto* productoAsociado = firstList(supermercadoEncontrado->productos); // Se accede al primer elemento de la lista.
            if (productoAsociado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
            {
                printf("ERROR DE MEMORIA.");
                return; // Se termina el algoritmo.
            }
            mostrarProducto(productoAsociado);    // Se muestra el producto.

            while (1)
            {
                productoAsociado = nextList(supermercadoEncontrado->productos); // Se accede al siguiente elemento de la lista.
                if (productoAsociado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
                mostrarProducto(productoAsociado); // Se van mostrando todos los elementos de la lista.
            }
        }
        else
        {
            tipoCategoria* categoriaEncontrada = parBuscado->value;
            //int cantProductoAsociados = get_size_list(categoriaEncontrada->productos);
            tipoProducto* productoAsociado = firstList(categoriaEncontrada->productos);
            mostrarProducto(productoAsociado);
            if (productoAsociado == NULL) //Esta condición fue puesta por seguridad en fugas de memoria.
            {
                printf("ERROR DE MEMORIA.");
                return; // Se termina el algoritmo.
            }

            while (1)
            {
                productoAsociado = nextList(categoriaEncontrada->productos); // Se accede al siguiente elemento de la lista.
                if (productoAsociado == NULL) break;         // Una vez que el producto buscado es NULL, se termina el ciclo.
                mostrarProducto(productoAsociado); // Se van mostrando todos los elementos de la lista.
            }
        }
    }
}