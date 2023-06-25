#include "funciones_answer.h"

// Importacion de base de datos

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias, BTree* arbolP) {
    FILE* file = fopen("db_productos.csv", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char linea[1024];
    char* token;
    fgets(linea, sizeof(linea), file);
    
    while (fgets(linea, sizeof(linea), file) != NULL) {   
        tipoProducto* nuevoProducto = (tipoProducto*) malloc(sizeof(tipoProducto));

        token = strtok(linea, ",");
        strncpy(nuevoProducto->nombre, token, sizeof(nuevoProducto->nombre));
        
        token = strtok(NULL, ",");
        strncpy(nuevoProducto->precio, token, sizeof(nuevoProducto->precio));
        
        nuevoProducto->price = atoi(nuevoProducto->precio);
        
        token = strtok(NULL, ",");

        strncpy(nuevoProducto->categoria, token, sizeof(nuevoProducto->categoria));
        Pair* parAux = searchMap(mapaCategorias, token);
        
        if (parAux == NULL)
        {
            tipoCategoria* nuevaCategoria = (tipoCategoria*) malloc(sizeof(tipoCategoria));
            strncpy(nuevaCategoria->nombre, token, sizeof(nuevaCategoria->nombre));
            nuevaCategoria->productos = createList();
            pushBack(nuevaCategoria->productos, nuevoProducto);
            insertMap(mapaCategorias, nuevaCategoria->nombre, nuevaCategoria);
        }
        else
        {
            tipoCategoria* categoriaExistente = parAux->value;
            pushBack(categoriaExistente->productos, nuevoProducto);
        }

        
        token = strtok(NULL, ",");
        nuevoProducto->cantSupermercados = atoi(token);
        
        nuevoProducto->supermercados = createList();
        
        Pair* parAux2 = (Pair*) malloc(sizeof(Pair)); 
        
        for (unsigned short i = 0; i < nuevoProducto->cantSupermercados; i++) {
            if (i == nuevoProducto->cantSupermercados - 1)
            {
                token = strtok(NULL, ".");
            }
            else
            {
                token = strtok(NULL, ",");
            }
            parAux2 = searchMap(mapaSupermercados, token);
            if (parAux2 == NULL)
            {
                tipoSupermercado *nuevoSupermercado = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
                strncpy(nuevoSupermercado->nombre, token, sizeof(nuevoSupermercado->nombre));
                pushBack(nuevoProducto->supermercados, nuevoSupermercado);      
                nuevoSupermercado->productos = createList();
                pushBack(nuevoSupermercado->productos, nuevoProducto);
                insertMap(mapaSupermercados, nuevoSupermercado->nombre, nuevoSupermercado);
            }
            else
            {
                tipoSupermercado *supermercadoExistente = parAux2->value;
                pushBack(nuevoProducto->supermercados, supermercadoExistente);
                pushBack(supermercadoExistente->productos, nuevoProducto);
            }
        }
        
        tipoSupermercado *superAux = firstList(nuevoProducto->supermercados);
        for (int i = 1; i < nuevoProducto->cantSupermercados; i++)
        {
            superAux = nextList(nuevoProducto->supermercados);
        }
        insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto);
        insertBTree(arbolP, nuevoProducto->price, nuevoProducto);
    }
    
    fclose(file);
}

void importarCredencialesAdmin (HashMap* mapaAdmin)
{
    FILE* file = fopen("credenciales_admin.csv", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
  char linea[1024];
  char* token;
  fgets(linea, sizeof(linea), file);

   while (fgets(linea, sizeof(linea), file) != NULL) {
     tipoAdministrador* nuevoAdmin = (tipoAdministrador*) malloc(sizeof(tipoAdministrador));
     
      token = strtok(linea, ",");
     strncpy(nuevoAdmin->rut, token, sizeof(nuevoAdmin->rut));

     token = strtok(NULL, ",");
     strncpy(nuevoAdmin->password, token, sizeof(nuevoAdmin->password));
     nuevoAdmin->password[strcspn(nuevoAdmin->password, "\n")] = '\0';
     
      insertMap(mapaAdmin,nuevoAdmin->rut, nuevoAdmin);
   }
}

// Funciones generales

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

// Armar canasta Opcion 1

void subMenuCanasta() {
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA VER TODOS PRODUCTOS DE LA CANASTA.    ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR PRODUCTOS A LA CANASTA.       ║\n");
    printf("║ 3. INGRESE 3 SI DESEA ELIMINAR PRODUCTOS DE LA CANASTA.     ║\n");
    printf("║ 4. INGRESE 0 SI DESEA SALIR AL MENÚ PRINCIPAL.              ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
}

void subMenuCanastaCantidad()
{
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA AUMENTAR LA CANTIDAD EN LA CANASTA    ║\n");
    printf("║ 2. INGRESE 2 SI DESEA SALIR                                 ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
    printf("Opción: ");
}

tipoCanasta* searchListCanasta(List* canasta,char* producto,char* supermercado)
{
    for (tipoCanasta* current=firstList(canasta);current!=NULL;current=nextList(canasta))
    {
        if (strcmp(producto,current->nombre)==0)
            if (strcmp(current->supermercado,supermercado)==0)
                return current;
    }
    return NULL;
}

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercados)
{
    int opcion;
    puts(MSJARMADOCANASTA);
    while (1)
    {
        subMenuCanasta();
        printf("Opción: ");
        scanf("%i",&opcion);
        getchar();
        printf("\n");
        switch(opcion)
        {
            case 1:
            {
                if (isListEmpty(canasta))
                    printf("No existen productos en la canasta\n");
                else printListPC(canasta);
                break;
            }
            case 2:
            {
                agregarProduCanasta(mapaProductos,mapaSupermercados,canasta);
                break;
            }
            case 3:
            {
                eliminarProduCanasta(canasta);
                break; 
            }
            case 0:
            {
                printf("Has salido al menú principal.");
                return;
            }
            default:
            {
                printf("Opción no válida.");
                break;
            }
        }
    }
}

void eliminarProduCanasta(List* canasta)
{
    if (isListEmpty(canasta))
    {
        printf("No existen productos en la canasta\n");
        return;
    }
    printf("Lista de productos en la canasta\n");
    printListS(canasta);
    char nomProductoE[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto a eliminar de la canasta: ");
        scanf("%[^\n]s",nomProductoE);
        getchar();
        printf("\n");
    }while(strlen(nomProductoE) > MAXLEN);
        
    int entro  = 0;
    tipoCanasta* currentCanasta = firstList(canasta);
    while (currentCanasta != NULL)
    {
        if (strcmp(currentCanasta->nombre, nomProductoE) == 0)
        {
            printf("El producto %s se ha eliminado de la canasta\n", nomProductoE);
            popCurrent(canasta);
            entro = 1;
        }
        currentCanasta = nextList(canasta);    
    }
    if (entro == 0)
    {
        printf("El producto %s no se encuentra en la canasta\n",nomProductoE);
        return;
    }
}

void agregarProduCanasta(HashMap* mapaProductos,HashMap* mapaSupermercados,List* canasta)
{
    printMapP(mapaProductos);
    char nomProducto[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto agregar a la canasta: ");
        scanf("%[^\n]s", nomProducto);
        getchar();
        printf("\n");
    }while(strlen(nomProducto) > MAXLEN);
    
    Pair* current;
    if( (current = searchMap(mapaProductos, nomProducto)) == NULL) {
        printf("El producto a buscar no se encuentra en la base de datos\n");
        return;
    }
    printf("Lista de supermercados que contienen el producto: %s\n", nomProducto);
    printListS(((tipoProducto*) current->value)->supermercados);
        
    char nomSupermercado[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del supermercado que posee el producto agregar a la canasta: ");
        scanf("%[^\n]s",nomSupermercado);
        getchar();
        printf("\n");
    }while(strlen(nomSupermercado) > MAXLEN);
    
    if(searchMap(mapaSupermercados, nomSupermercado) == NULL) {
        printf("El supermercado a buscar no se encuentra en la base de datos\n");
        return;
    }
        
    size_t cantidad=0;
    tipoCanasta* productoBuscado = searchListCanasta(canasta, nomProducto, nomSupermercado);
        
    if (productoBuscado == NULL) //Si es null quiere decir que no está.
    {
        printf("Ingrese la cantidad de %s que desea agregar a la canasta: ", nomProducto);
        do {
            scanf("%zd", &cantidad);
        } while(cantidad <= 0);
    
        tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
        strcpy(elemCanasta->nombre,nomProducto);
        strcpy(elemCanasta->supermercado,nomSupermercado);
        strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
        elemCanasta->cantidad=cantidad;
            
        pushBack(canasta,elemCanasta);
        printf("\nEl producto %s del supermercado %s ha sido agregado a la canasta.\n\n", nomProducto, nomSupermercado);
            
    }
    else
    {
        printf("El producto %s se encuentra en la canasta con una cantidad de %zd\n", nomProducto, productoBuscado->cantidad);
        subMenuCanastaCantidad();
        unsigned short opcion=0;
        do{
            scanf("%hu",&opcion);
        }while(opcion!=1 && opcion!=2);
        if (opcion == 2)return;
        printf("Ingrese la cantidad ha agregar: ");
        do{
            scanf("%zd",&cantidad);
        }while(cantidad<=0);
        productoBuscado->cantidad+=cantidad;
        printf("La cantidad actual de %s en la canasta es %zd\n", nomProducto, productoBuscado->cantidad);
    }  
}

void printMapP(HashMap* mapaProductos)
{
    Pair* current = firstMap(mapaProductos);
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n");
    printf("┌──────────────────────────────────┐\n");
    int cont = 1;
    while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        printf(" %i. %s\n", cont, producto->nombre);
        current = nextMap(mapaProductos);
     }
    printf("└──────────────────────────────────┘\n\n");
    
}

void printListPC(List* Super) {
    tipoCanasta* current = firstList(Super);
    int cont = 1;
    size_t pagar = 0;
    size_t precioTotalProduc;

    printf("┌────────────────────────────────────────────────┐\n");
    while(current != NULL) {
        precioTotalProduc = atol(current->precio)*current->cantidad;
        printf(" %d. Producto: %s\n Supermercado: %s\n Cantidad: %zd\n Precio unitario: $%s Precio total: $%zd\n\n",cont,current->nombre,current->supermercado,current->cantidad,current->precio,precioTotalProduc);
        cont++;
        pagar = pagar + precioTotalProduc;
        current = nextList(Super);
    }
    printf(" Total a pagar: $%zd\n",pagar);
    printf("└────────────────────────────────────────────────┘\n\n");
}

// Mostrar toda la oferta de productos Opcion 2

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

void printAllP(HashMap* productos) {
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

// Mostrar producto por nombre Opcion 3

/*La función busquedaProductosDirecta consiste en una busqueda por el nombre del producto en el mapa de productos.*/
void busquedaProductosDirecta(HashMap* mapa) {
    printMapP(mapa);
    puts(MSJBUSQUEDA1);
    
    char nombreProductoBuscado[MAXLEN + 1]; //Variable que almacenará la cadena ingresada por el usuario para este caso.
    printf("Ingrese el nombre del producto a buscar: ");
    scanf("%30[^\n]s", nombreProductoBuscado); //Se pide al usuario ingresar el nombre exacto del producto (incluyendo la mayúscula inicial).
    while (getchar() != '\n');
    Pair* parBuscado = searchMap(mapa, nombreProductoBuscado); //Se busca en el mapa de productos con clave el nombre del producto.
    if (parBuscado != NULL)
    {
            tipoProducto* productoBuscado = parBuscado->value; //Se crea una variable auxiliar tipoProducto para almacenar la data del producto buscado por su nombre.
    mostrarProducto(productoBuscado); //Se muestra el producto.
    }
    else
    {
        puts(MSJBUSQUEDASC);
    }
}


// Mostrar por precio Opcion 4

void busquedaPorPrecio(BTree* arbolProductos)
{
    puts(MSJBUSQUEDA2);
    int precio1 = 1, precio2 = 0;
    List* listaProductos = createList();
    
    if (listaProductos == NULL) //Esta línea fue escrita por seguridad en fugas de memoria.
    {
        printf("Error.");
    }
    
    while (precio1 > precio2 || precio1 <= 0 || precio2 <= 0) // Se pide al usuario ingresar dos precios hasta que el precio 1 sea menor que el precio 2 y el precio 2 sea mayor que cero.
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
        puts(MSJBUSQUEDASC);
        return;
    }
    
    tipoProducto* productoBuscado = firstList(listaProductos); //Se accede al primer elemento de la lista de productos hallados en el rango.

    if (productoBuscado == NULL)
    {
        printf("ERROR DE MEMORIA."); //Esta línea fue escrita por seguridad en fugas de memoria.
        return;
    }
    
    mostrarProducto(productoBuscado); // Se muestra la información del primer producto dentro del rango.
    
    while (1)
    {
        productoBuscado = nextList(listaProductos); // Se accede al siguiente elemento de la lista hasta que no hayan más.
        if (productoBuscado == NULL) break;
        mostrarProducto(productoBuscado); // Se van mostrando todos los elementos de la lista.
    }
}

// Busqueda Productos en Listas Adyacentes:

void busquedaProductosAdyacentes(HashMap* mapa, int indicador)
{
    if (indicador == 1)
    {
        puts(MSJBUSQUEDA3);
        puts(MSJBUSQUEDA31);
    }
    else
    {
        puts(MSJBUSQUEDA4);
        puts(MSJBUSQUEDA41);
    }
    
    char nombreElementoBuscado[MAXLEN + 1];
    
    printf("\n");
    scanf("%30[^\n]s", nombreElementoBuscado);
    while (getchar() != '\n');
    
    Pair* parBuscado = searchMap(mapa, nombreElementoBuscado);

    if (parBuscado == NULL)
    {
        puts(MSJBUSQUEDASC);
        return;
    }
    else
    {
        if (indicador == 1)
        {
            tipoSupermercado* supermercadoEncontrado = parBuscado->value;
            int cantProductoAsociados = get_size_list(supermercadoEncontrado->productos);
            tipoProducto* productoAsociado = firstList(supermercadoEncontrado->productos);
            mostrarProducto(productoAsociado);
            for (int i = 1; i < cantProductoAsociados; i++)
            {
                productoAsociado = nextList(supermercadoEncontrado->productos);
                mostrarProducto(productoAsociado);
            }
        }
        else
        {
            tipoCategoria* categoriaEncontrada = parBuscado->value;
            int cantProductoAsociados = get_size_list(categoriaEncontrada->productos);
            tipoProducto* productoAsociado = firstList(categoriaEncontrada->productos);
            mostrarProducto(productoAsociado);
            for (int i = 1; i < cantProductoAsociados; i++)
            {
                productoAsociado = nextList(categoriaEncontrada->productos);
                mostrarProducto(productoAsociado);
            }
        }
    }
}

// Iniciar sesion sesion como administrador Opcion 7

int loginAdmin(HashMap * mapaAdmin) {
  while (1) {
    char rut[MAXLEN + 1];
    do {
      printf("INGRESE RUT PARA INICIAR SESIÓN\n");
      scanf("%s", rut);
      getchar();
    } while (strlen(rut) > MAXLEN);

    char password[MAXLEN + 1];
    do {
      printf("INGRESE CONTRASEÑA PARA INICIAR SESIÓN\n");
      scanf("%s", password);
      getchar();
    } while (strlen(password) > MAXLEN);

    Pair* adminItem = searchMap(mapaAdmin, rut);
    if (adminItem != NULL) {
        tipoAdministrador* admin = (tipoAdministrador*)adminItem->value;
        if (strcmp(admin->rut, rut) == 0 && strcmp(admin->password, password) == 0) {
            printf("SE HA INICIADO SESIÓN EXITOSAMENTE\n");
            return 1;
        }
    
        printf("RUT o contraseña incorrectos. Inténtelo nuevamente.\n");
        return 0;
        }
    }
}

void mostrarMenuAdmin()
{
   printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA AGREGAR PRODUCTOS                     ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR SUPERMERCADOS                 ║\n");
    printf("║ 3. INGRESE 3 SI DESEA AGREGAR CATEGORIA                     ║\n");
    printf("║ 4. INGRESE 4 SI DESEA QUITAR PRODUCTOS                      ║\n");
    printf("║ 5. INGRESE 5 SI DESEA SALIR AL MENU PRINICIPAL              ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
}

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias)
{
    puts(MSJMENUADMINISTRADOR);
    mostrarMenuAdmin();
    int opcion;
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
        printf("\nOpción 1 ingresada\n");
        agregarProducto(mapaProductos, mapaCategorias, mapaSupermercados);
        menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
        break;
    case 2:
        printf("\nOpción 2 ingresada\n");
        agregarSupermercado(mapaSupermercados);
        menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
        break;
    case 3:
        printf("\nOpción 3 ingresada\n");
        agregarCategoria(mapaCategorias);
        menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
        break;
    case 4:
        printf("\nOpción 4 ingresada\n");
        quitarProductos(mapaProductos, mapaCategorias, mapaSupermercados);
        break;
    case 5:
        printf("\nOpción 5 ingresada\n");
        guardarDatosCSV(mapaProductos, mapaSupermercados,  mapaCategorias);
        printf("GURDANDO CAMBIOS ...");
        mostrarMenu();
        break;
    }
}

//Opciones administrador

void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados) {
    char nombre[MAXLEN + 1];
    char precio[PRICELEN + 1];
    char categoria[MAXLEN + 1];
    int cantSupermercados;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    getchar(); 

  if(searchMap(mapaProductos, nombre) != NULL){
    printf("El prodcuto ya existe en el mapa de productos.\n");
    mostrarMenuAdmin();
  }

    printf("Ingrese el precio del producto: ");
    scanf("%s", precio);
    getchar();
    
    // Convertir el precio de cadena de caracteres a entero
    int price = atoi(precio);

    printf("Ingrese la categoría del producto: ");
    scanf("%s", categoria);
    getchar();

    printf("Ingrese la cantidad de supermercados: ");
    scanf("%d", &cantSupermercados);
    getchar();

    // Crear una estructura para el nuevo producto
    tipoProducto* nuevoProducto = (tipoProducto*)malloc(sizeof(tipoProducto));
    strncpy(nuevoProducto->nombre, nombre, sizeof(nuevoProducto->nombre));
    strncpy(nuevoProducto->precio, precio, sizeof(nuevoProducto->precio));
    nuevoProducto->price = price;
    strncpy(nuevoProducto->categoria, categoria, sizeof(nuevoProducto->categoria));
    printf("\n%s %s %s\n",nuevoProducto->nombre,nuevoProducto->precio,nuevoProducto->categoria);
    
    nuevoProducto->cantSupermercados = cantSupermercados;
    nuevoProducto->supermercados = createList();

    // Insertar el nuevo producto en el mapa de productos
    insertMap(mapaProductos, nombre, nuevoProducto);
  
   /// Verificar si la categoría existe en el mapa de categorías
    Pair* categoriaProducto = searchMap(mapaCategorias, categoria);
  
    if (categoriaProducto == NULL) {
        // La categoría no existe, se crea una nueva y se agrega al mapa de categorías
        tipoCategoria* nuevaCategoria = (tipoCategoria*) malloc(sizeof(tipoCategoria));
  
         strcpy(nuevaCategoria->nombre, categoria);
        nuevaCategoria->productos = createList();
      
        insertMap(mapaCategorias, categoria, nuevaCategoria);
         // Actualizar la referencia a la nueva categoría
        categoriaProducto = malloc(sizeof(Pair));
        categoriaProducto->value = nuevaCategoria;
    }
    
    pushBack(((tipoCategoria *)categoriaProducto->value)->productos, nuevoProducto);
    // Agregar el producto a la lista de productos de la categoría
    for (int i = 0; i < cantSupermercados; i++) {
        char nombreSupermercado[MAXLEN + 1];
        printf("Ingrese el nombre del supermercado %d: ", i + 1);
        scanf("%s", nombreSupermercado);
        getchar();
        printf("\n");
        // Verificar si el supermercado existe en el mapa de supermercados
        Pair* auxSupermercado = searchMap(mapaSupermercados, nombreSupermercado);
        if (auxSupermercado == NULL) {
            // El supermercado no existe, se crea uno nuevo y se agrega al mapa de supermercados
            tipoSupermercado* supermercado = (tipoSupermercado*)malloc(sizeof(tipoSupermercado));
            strncpy(supermercado->nombre, nombreSupermercado, sizeof(supermercado->nombre));
            supermercado->productos = createList();
            insertMap(mapaSupermercados, nombreSupermercado, supermercado);
    
            // Agregar el producto a la lista de productos del supermercado
            auxSupermercado = malloc(sizeof(Pair));
            auxSupermercado->value = supermercado;
        }

        pushBack(((tipoSupermercado *)auxSupermercado->value)->productos, nuevoProducto);
        pushBack(nuevoProducto->supermercados, ((tipoSupermercado *)auxSupermercado->value)->nombre);
    }
    
    printf("Producto agregado exitosamente.\n");
}

void agregarSupermercado(HashMap* mapaSupermercados) {
  char nombreSupermercado[MAXLEN + 1];
  printf("Ingrese el nombre del supermercado: ");
  scanf("%s", nombreSupermercado);
  getchar();
  
  if (searchMap(mapaSupermercados, nombreSupermercado) != NULL) {
    printf("El supermercado ya existe en el mapa de supermercados.\n");
    return;
  }

 tipoSupermercado* supermercado = (tipoSupermercado*)malloc(sizeof(tipoSupermercado));
  strncpy(supermercado->nombre, nombreSupermercado, MAXLEN);
  supermercado->nombre[MAXLEN] = '\0';
  supermercado->productos = createList();

    insertMap(mapaSupermercados, nombreSupermercado, supermercado);
  
  printf("Supermercado agregado exitosamente.\n");

  // Comprobación de que el supermercado se agregó al mapa
  Pair* test = searchMap(mapaSupermercados, nombreSupermercado);
  if (test != NULL) {
    printf("Supermercado encontrado en el mapa de supermercados: %s\n", ((tipoSupermercado *)test->value)->nombre);
  } else {
    printf("No se encontró el supermercado en el mapa de supermercados.\n");
  }
}

void agregarCategoria(HashMap* mapaCategorias) {
  char nombreCategoria[MAXLEN + 1];
  printf("Ingrese el nombre de la categoría: ");
  scanf("%s", nombreCategoria);
  getchar();

  tipoCategoria* categoria = (tipoCategoria*)searchMap(mapaCategorias, nombreCategoria);
  if (categoria != NULL) {
    printf("La categoría ya existe en el mapa de categorías.\n");
    return;
  }

  categoria = (tipoCategoria*)malloc(sizeof(tipoCategoria));
  strncpy(categoria->nombre, nombreCategoria, MAXLEN);
  categoria->nombre[MAXLEN] = '\0'; 
  categoria->productos = createList();

  insertMap(mapaCategorias, nombreCategoria, categoria);
  printf("Categoría agregada exitosamente.\n");

  // Comprobación de que la categoría se agregó al mapa
   Pair* test = searchMap(mapaCategorias, nombreCategoria);
  if (test != NULL) {
    printf("Categoría encontrada en el mapa de categorías: %s\n", ((tipoCategoria *)test->value)->nombre);
  } else {
    printf("No se encontró la categoría en el mapa de categorías.\n");
  }
}

void eliminarProductoLista(List* productos,char* nomProducto)
{
    tipoProducto* currentList=firstList(productos);
    while(currentList != NULL)
    {
        if (strcmp(currentList->nombre,nomProducto)==0)
        {
            popCurrent(productos);
            return;
        }
        currentList=nextList(productos);
    }
}

void quitarProductos(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados)
{
    printMapP(mapaProductos);
    char nomProducto[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto ha eliminar de la base de datos: ");
        getchar();
        scanf("%[^\n]s",nomProducto);
        getchar();
        printf("\n");
    }while(strlen(nomProducto) > MAXLEN);
    
    Pair* current = searchMap(mapaProductos, nomProducto);
    if (current == NULL)
    {
        printf("El producto %s no existe en la base de datos",nomProducto);
        menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
    }

    tipoProducto* producto = current->value;

    //eliminacion del producto de la lista del mapa de supermercados
    tipoSupermercado* currentListSuper = firstList(producto->supermercados);
    while(currentListSuper != NULL)
    {
        Pair* parSuper = searchMap(mapaSupermercados,currentListSuper->nombre);
        tipoSupermercado* elemenMapSuper = parSuper->value;
        eliminarProductoLista(elemenMapSuper->productos, nomProducto);
        //se le manda la lista de cada elemento del mapa de supermercado ademas el nombre del producto a eliminar
        currentListSuper = nextList(producto->supermercados);
    }

    //eliminacion del producto en la lista del mapa de categoria
    Pair* parCategoria = searchMap(mapaCategorias,producto->categoria);
    tipoCategoria* categoria = parCategoria->value;
    
    tipoProducto* currentListP = firstList(categoria->productos);
    while(currentListP != NULL)
    {
        if (strcmp(currentListP->nombre,nomProducto) == 0)
        {
            popCurrent(categoria->productos);
            break;
        }
        currentListP = nextList(categoria->productos);
    }
    eraseMap(mapaProductos, nomProducto);
    printf("El producto %s ha sido eliminado de la base de datos", nomProducto);
    menuAdmin(mapaProductos, mapaSupermercados, mapaCategorias);
}

void guardarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias) {
    FILE* archivo = fopen("db_productos.csv", "w");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar los datos.\n");
        return;
    }

    fprintf(archivo, "Nombre,Precio,Categoría,Cantidad de Supermercados,Supermercados\n");

    // Recorrer los productos y escribirlos en el archivo
    Pair* currentProducto = firstMap(mapaProductos);

    while (currentProducto != NULL) {
        tipoProducto* producto = (tipoProducto*)currentProducto->value;

        // Verificar si el nombre del producto no es nulo
        if (producto->nombre[0] != '\0') {
            fprintf(archivo, "%s,%s,%s,", producto->nombre, producto->precio, producto->categoria);

            // Verificar si la lista de supermercados no es nula
            if (producto->supermercados != NULL) {
                int cantidadSupermercados = get_size_list(producto->supermercados);
                fprintf(archivo, "%d,", cantidadSupermercados);

                Node* nodoSupermercado = producto->supermercados->head;
                while (nodoSupermercado != NULL) {
                    char* supermercado = (char*)nodoSupermercado->data;
                    fprintf(archivo, "%s", supermercado);
                    
                    nodoSupermercado = nodoSupermercado->next;
                    
                    if (nodoSupermercado != NULL) {
                        fprintf(archivo, ",");
                    }
                }
            } else {
                fprintf(archivo, "0");
            }

            fprintf(archivo, ".\n"); // Agregar el punto al final de la línea
        }

        currentProducto = nextMap(mapaProductos);
    }

    fclose(archivo);

    printf("Datos guardados exitosamente en la base de dato.\n");
}

// Menu principal

void mostrarMenu()
{
    HashMap* mapaProductos = createMap(MAPINITIALCAPAC);
    HashMap* mapaSupermercados = createMap(MAPINITIALCAPAC);
    HashMap* mapaCategorias = createMap(MAPINITIALCAPAC);
    BTree* arbolProductos = createBTree(1 + MAPINITIALCAPAC / 6); // Debe ser impar
    
    HashMap* mapaAdmin = createMap(MAPADMINITIALCAPAC);
    
    importarDatosCSV(mapaProductos, mapaSupermercados, mapaCategorias, arbolProductos);
    importarCredencialesAdmin(mapaAdmin);
    List* canasta = createList();
    
    int opcion;
    do {
        mostrarOpciones();
        printf("Opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');
        switch (opcion) {
            case 1:
                armarCanasta(canasta,mapaProductos,mapaSupermercados);
                break;
            case 2:
                printAllP(mapaProductos);
                break;
            case 3:
                busquedaProductosDirecta(mapaProductos);
                break;
            case 4:
                busquedaPorPrecio(arbolProductos);
            case 5:
                busquedaProductosAdyacentes(mapaSupermercados, 1);
            case 6:
                busquedaProductosAdyacentes(mapaCategorias, 2);
            case 7:
                if(loginAdmin(mapaAdmin) != 0)
                   menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
            case 0:
            {
                printf("CERRANDO EL PROGRAMA...\n");
                return;
            }
            default:
            {
                printf("INGRESE UNA OPCIÓN VÁLIDA.");
            }    
        }
    } while (opcion != 0);
    
}

void mostrarOpciones()
{
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA ARMAR CANASTA CON PRODUCTOS A COMPRAR ║\n");
    printf("║ 2. INGRESE 2 SI DESEA MOSTRAR TODOS LOS PRODUCTOS           ║\n");
    printf("║ 3. INGRESE 3 SI DESEA BUSCAR PRODUCTO POR NOMBRE            ║\n");
    printf("║ 4. INGRESE 4 SI DESEA MOSTRAR PRODUCTO POR PRECIO           ║\n");
    printf("║ 5. INGRESE 5 SI DESEA MOSTRAR PRODUCTO POR SUPERMERCADO     ║\n");
    printf("║ 6. INGRESE 6 SI DESEA MOSTRAR PRODUCTO POR CATEGORIA        ║\n");
    printf("║ 7. INGRESE 7 SI DESEA INICIAR SESION COMO ADMINISTRADOR     ║\n");
    printf("║ 8. INGRESE 0 SI DESEA SALIR                                 ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
}