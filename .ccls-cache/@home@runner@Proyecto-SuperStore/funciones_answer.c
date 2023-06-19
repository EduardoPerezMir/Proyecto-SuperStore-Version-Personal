 #include "funciones_answer.h"


void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias, BTree* arbolP) {
    FILE* file = fopen("datos.csv", "r");
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

        tipoCategoria* nuevaCategoria = (tipoCategoria*) malloc(sizeof(tipoCategoria));
        strncpy(nuevoProducto->categoria, token, sizeof(nuevoProducto->categoria));
        strncpy(nuevaCategoria->nombre, token, sizeof(nuevaCategoria->nombre));
        nuevaCategoria->productos = createList();
        pushBack(nuevaCategoria->productos, nuevoProducto);
        insertMap(mapaCategorias, nuevaCategoria->nombre, nuevaCategoria);
        
        token = strtok(NULL, ",");
        nuevoProducto->cantSupermercados = atoi(token);
        
        nuevoProducto->supermercados = createList();
        
        for (unsigned short i = 0; i < nuevoProducto->cantSupermercados; i++) {
            token = strtok(NULL, ",");
            tipoSupermercado *nuevoSupermercado = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
            strncpy(nuevoSupermercado->nombre, token, sizeof(nuevoSupermercado->nombre));
            pushBack(nuevoProducto->supermercados, nuevoSupermercado);      
            nuevoSupermercado->productos = createList();
            pushBack(nuevoSupermercado->productos, nuevoProducto);
            insertMap(mapaSupermercados, nuevoSupermercado->nombre, nuevoSupermercado);
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

void subMenuCanasta() {
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA VER TODOS PRODUCTOS DE LA CANASTA     ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR PRODUCTOS A LA CANASTA        ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n");
}

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercados)
{
    
    subMenuCanasta();
    int opcion;
    do {
        scanf("%i",&opcion);
    }while(opcion!=1 && opcion!=2);


    if (opcion == 1) 
    {
        if (isListEmpty(canasta))
            printf("NO EXISTEN PRODUCTOS EN LA CANASTA\n");
        else printListPC(canasta);
    } 
    else
    {
        char nomProducto[MAXLEN + 1];
        do{
            printf("INGRESE NOMBRE DEL PRODUCTO AGREGAR A LA CANASTA\n");
            scanf("%s",nomProducto);
            getchar();
        }while(strlen(nomProducto) > MAXLEN);
    
        Pair* current;
        if( (current = searchMap(mapaProductos,nomProducto)) == NULL) {
            printf("EL PRODUCTO A BUSCAR NO SE ENCUENTRA EN LA BASE DE DATOS\n");
            return;
        }
        printf("Lista de supermercados que contienen el producto: %s\n",nomProducto);
        printListS(((tipoProducto *)current->value)->supermercados);
        
        char nomSupermercado[MAXLEN + 1];
        do{
            printf("INGRESE NOMBRE DEL SUPERMERCADO QUE POSEE EL PRODUCTO AGREGAR A LA CANASTA\n");
            scanf("%s",nomSupermercado);
            getchar();
        }while(strlen(nomSupermercado) > MAXLEN);
    
    
        if(searchMap(mapaSupermercados,nomSupermercado) == NULL) {
            printf("EL SUPERMERCADO A BUSCAR NO SE ENCUENTRA EN LA BASE DE DATOS\n");
            return;
        }

        tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
        strcpy(elemCanasta->nombre,nomProducto);
        strcpy(elemCanasta->supermercado,nomSupermercado);
        strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
        
        pushBack(canasta,elemCanasta);
        printf("EL PRODUCTO %s DEL SUPERMERCADO %s HA SIDO AGREGADO A LA CANASTA\n",nomProducto,nomSupermercado);
    }
}

void printListPC(List* Super) {
    tipoCanasta* current = firstList(Super);
    int cont = 1;
    size_t pagar = 0;
    while(current != NULL) {
        printf("%d.Producto: %s Supermercado: %s Precio: $%s\n",cont,current->nombre,current->supermercado,current->precio);
        cont++;
        pagar = pagar + atol(current->precio);
        current = nextList(Super);
    }
    printf("Total a pagar: $%zd\n",pagar);
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


void printListS(List* Super) {
    tipoSupermercado* current = firstList(Super);
    int cont = 1;
    while(current != NULL) {
        printf("%d. %s\n",cont,current->nombre);
        cont++;
        current = nextList(Super);
    }
}

void mostrarProducto(tipoProducto* productoAMostrar)
{
    //puts(barra4);
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
    //puts(barra4);
}


void printAllP(HashMap* productos) {
    Pair* current = firstMap(productos);
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n\n");
    char cadena[20];
    
    int cont = 1;
     while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        //printf(barra1);
        printf("\n%24s %d\n","PRODUCTO",cont);
        mostrarProducto(producto);
        //printf(barra1);
        cont++;
        current = nextMap(productos);
     }
}

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

/*La función busquedaProductosDirecta consiste en una busqueda por el nombre del producto en el mapa de productos.*/
void busquedaProductosDirecta(HashMap* mapa) {
    printf("BUSQUEDA DE PRODUCTOS POR NOMBRE\n");
    char nombreProductoBuscado[MAXLEN + 1]; //Variable que almacenará la cadena ingresada por el usuario para este caso.
    
    printf("Ingrese el nombre del producto a buscar.\n");
    scanf("%s", nombreProductoBuscado); //Se pide al usuario ingresar el nombre exacto del producto (incluyendo la mayúscula inicial).
    
    Pair* parBuscado = searchMap(mapa, nombreProductoBuscado); //Se busca en el mapa de productos con clave el nombre del producto.
    tipoProducto* productoBuscado = parBuscado->value; //Se crea una variable auxiliar tipoProducto para almacenar la data del producto buscado por su nombre.
    mostrarProducto(productoBuscado); //Se muestra el producto.
}

void busquedaPorPrecio(BTree* arbolP)
{
    int precio1 = 1, precio2 = 0;
    List* listaP = createList();
    
    printf("BUSQUEDA DE PRODUCTOS POR PRECIO\n");
    
    if (listaP == NULL) //Esta línea fue escrita por seguridad en fugas de memoria.
    {
        printf("Error.");
    }
    
    while (precio1 > precio2 || precio1 <= 0 || precio2 <= 0) // Se pide al usuario ingresar dos precios hasta que el precio 1 sea menor que el precio 2 y el precio 2 sea mayor que cero.
    {
        printf("RANGO DE PRECIOS.\n");
        printf("INGRESE EL PRECIO MENOR.\n");
        scanf("%d", &precio1); // El precio 1 es el precio menor.
        printf("INGRESE EL PRECIO MAYOR.\n");
        scanf("%d", &precio2);  // El precio 2 es el precio mayor.
    }
    
   searchByRangeBTree(getRoot(arbolP), precio1, precio2, listaP); 
    // Se busca por rango de precios en el arbol B y se agregan todos los productos en ese rango a la lista de productos 'listaP'.
    
    if (isListEmpty(listaP)) // Si la lista está vacía es porque no hay productos en ese rango de precios.
    {
        printf("NO SE HALLARON PRODUCTOS EN EL RANGO DE PRECIOS SELECCIONADO.");
        return;
    }
    
    tipoProducto* productoBuscado = firstList(listaP); //Se accede al primer elemento de la lista de productos hallados en el rango.

    if (productoBuscado == NULL)
    {
        printf("ERROR DE MEMORIA."); //Esta línea fue escrita por seguridad en fugas de memoria.
        return;
    }
    
    mostrarProducto(productoBuscado); // Se muestra la información del primer producto dentro del rango.
    
    while (1)
    {
        productoBuscado = nextList(listaP); // Se accede al siguiente elemento de la lista hasta que no hayan más.
        if (productoBuscado == NULL) break;
        mostrarProducto(productoBuscado); // Se van mostrando todos los elementos de la lista.
    }
}

void mostrarMenuAdmin()
{
    printf(barra3);
    printf("1. INGRESE 1 SI DESEA AGREGAR PRODUCTOS\n");
    printf("2. INGRESE 2 SI DESEA AGREGAR SUPERMERCADOS\n");
    printf("3. INGRESE 3 SI DESEA AGREGAR CATEGORIA\n");
    printf("4. INGRESE 4 SI DESEA QUITAR PRODUCTOS\n");
    printf("5. INGRESE 5 SI DESEA SALIR AL MENU PRINICIPAL\n");
    printf(barra3);
}

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias)
{
    mostrarMenuAdmin();
    int opcion;
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
        printf("OPCION 1 INGRESADA\n\n");
        agregarProducto(mapaProductos, mapaCategorias, mapaSupermercados);
        break;
    case 2:
        printf("OPCION 2 INGRESADA\n\n");
        agregarSupermercado(mapaSupermercados);
        break;
    case 3:
        printf("OPCION 3 INGRESADA\n\n");
        agregarCategoria(mapaCategorias);
        break;
    case 4:
        printf("OPCION 4 INGRESADA\n\n");
        break;
    case 5:
        printf("OPCION 5 INGRESADA\n\n");
        
        printf("GURDANDO CAMBIOS ...");
        break;
    }
}

void agregarSupermercado (HashMap* mapaSupermercados) {
  char nombreSupermercado [MAXLEN +1];
  printf("Ingrese el nombre del supermercado: ");
  scanf("%s", nombreSupermercado);
  getchar();

  tipoSupermercado* supermercado = (tipoSupermercado*) searchMap(mapaSupermercados, nombreSupermercado);
  if (supermercado != NULL) {
      printf("El supermercado ya existe en el mapa de supermercados.\n");
      return;
  }
    supermercado = (tipoSupermercado*)malloc(sizeof(tipoSupermercado));
    strncpy(supermercado->nombre, nombreSupermercado, sizeof(supermercado->nombre));
    supermercado->productos = createList();

  insertMap(mapaSupermercados, nombreSupermercado, supermercado);
  printf("Supermercado agregado exitosamente.\n");
}

void agregarCategoria (HashMap* mapaCategoria) {
  char nombreCategoria [MAXLEN +1];
  printf("Ingrese el nombre de la categoria: ");
  scanf("%s", nombreCategoria);
  getchar();

  tipoCategoria* categoria = (tipoCategoria*) searchMap(mapaCategoria, nombreCategoria); 
  if (categoria != NULL) {
      printf("La categoria ya existe en el mapa de categorias.\n");
      return;
  }
    categoria = (tipoCategoria*)malloc(sizeof(tipoCategoria));
    strncpy(categoria->nombre, nombreCategoria, sizeof(categoria->nombre));
    categoria->productos = createList();

  insertMap(mapaCategoria, nombreCategoria, categoria);
  printf("Categoria agregado exitosamente.\n");
}

void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados) {
    char nombre[MAXLEN + 1];
    char precio[PRICELEN + 1];
    char categoria[MAXLEN + 1];
    int cantSupermercados;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    getchar(); 

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
    nuevoProducto->cantSupermercados = cantSupermercados;
    nuevoProducto->supermercados = createList();

    // Insertar el nuevo producto en el mapa de productos
    insertMap(mapaProductos, nombre, nuevoProducto);

    // Verificar si la categoría existe en el mapa de categorías
    tipoCategoria* catExistente = (tipoCategoria*)searchMap(mapaCategorias, categoria);
    if (catExistente == NULL) {
        // La categoría no existe, se crea una nueva y se agrega al mapa de categorías
        tipoCategoria* nuevaCategoria = (tipoCategoria*)malloc(sizeof(tipoCategoria));
        strncpy(nuevaCategoria->nombre, categoria, sizeof(nuevaCategoria->nombre));
        nuevaCategoria->productos = createList();
        insertMap(mapaCategorias, categoria, nuevaCategoria);
    }

    // Agregar el producto a la lista de productos de la categoría
    tipoCategoria* categoriaProducto = (tipoCategoria*)searchMap(mapaCategorias, categoria);
    pushBack(categoriaProducto->productos, nuevoProducto);

    for (int i = 0; i < cantSupermercados; i++) {
        char nombreSupermercado[MAXLEN + 1];
        printf("Ingrese el nombre del supermercado %d: ", i + 1);
        scanf("%s", nombreSupermercado);
        getchar();

        // Verificar si el supermercado existe en el mapa de supermercados
        tipoSupermercado* supermercado = (tipoSupermercado*)searchMap(mapaSupermercados, nombreSupermercado);
        if (supermercado == NULL) {
            // El supermercado no existe, se crea uno nuevo y se agrega al mapa de supermercados
            supermercado = (tipoSupermercado*)malloc(sizeof(tipoSupermercado));
            strncpy(supermercado->nombre, nombreSupermercado, sizeof(supermercado->nombre));
            supermercado->productos = createList();
            insertMap(mapaSupermercados, nombreSupermercado, supermercado);
        }

        // Agregar el producto a la lista de productos del supermercado
        pushBack(supermercado->productos, nuevoProducto);
        pushBack(nuevoProducto->supermercados, supermercado);
    }

    printf("Producto agregado exitosamente.\n");
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
    printf("╚═════════════════════════════════════════════════════════════╝\n");



}

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
        ////puts(barra1);
        mostrarOpciones();
        ////puts(barra1);
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            printf("OPCION 1 INGRESADA\n\n");
            armarCanasta(canasta,mapaProductos,mapaSupermercados);
            break;
        case 2:
          //  puts(barra2);
            printf("OPCION 2 INGRESADA\n\n");
            printAllP(mapaProductos);
          //  puts(barra2);
            break;
        case 3:
          //  puts(barra2);
            printf("OPCION 3 INGRESADA\n\n");
            busquedaProductosDirecta(mapaProductos);
          //  puts(barra2);
            break;
        case 4:
            ////puts(barra1);
            printf("\nOPCION 4 INGRESADA\n\n");
            busquedaPorPrecio(arbolProductos);
            ////puts(barra1);
            break;
        case 5:
            printf("OPCION 5 INGRESADA\n\n");
            break;
        case 6:
            printf("OPCION 6 INGRESADA\n\n");
            break;
        case 7:
            printf("OPCION 7 INGRESADA\n\n");
            if(loginAdmin(mapaAdmin) != 0)
               menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
            break;
        default:       
            printf("CERRANDO EL PROGRAMA...\n");
        }
    } while (opcion != 0);
    
}
