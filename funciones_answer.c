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

/*void importarCredencialesAdmin (HashMap* mapaAdmin)
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
*/

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercados) {
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
        printf("INGRESE NOMBRE DEL PRODUCTO AGREGAR A LA CANASTA\n");
        scanf("%s",nomSupermercado);
        getchar();
    }while(strlen(nomSupermercado) > MAXLEN);


    if(searchMap(mapaSupermercados,nomSupermercado) == NULL) {
        printf("EL SUPERMERCADO A BUSCAR NO SE ENCUENTRA EN LA BASE DE DATOS\n");
        return;
    }
    
    pushBack(canasta,current);
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
    puts(barra4);
    printf("Nombre Producto: %s\nPrecio: %s\nCategoria: %s\n", productoAMostrar->nombre, productoAMostrar->precio, productoAMostrar->categoria);
    tipoSupermercado* supermercadoPtr = firstList(productoAMostrar->supermercados);
    printf("Supermercado 1: %s\n", supermercadoPtr->nombre);
    for (int i = 1; i < productoAMostrar->cantSupermercados; i++)
    {
        supermercadoPtr = nextList(productoAMostrar->supermercados);
        printf("Supermercado %d: %s\n", i + 1, supermercadoPtr->nombre);
    }
    puts(barra4);
}


void printAllP(HashMap* productos) {
    Pair* current = firstMap(productos);
    if(current == NULL) {
        printf("NO HAY PRODUCTOS EN LA BASE DE DATOS\n");
        return;
    }
    
    printf("\nLISTA DE PRODUCTOS A NIVEL NACIONAL:\n\n");
    
    int cont = 1;
     while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        printf("            PRODUCTO %d", cont);
        mostrarProducto(producto);
         //printf("%d. Nombre Producto: %s. Categoria: %s. Precio: %s\n",cont,producto->nombre,producto->categoria,producto->precio);
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
        }
        printf("RUT o contraseña incorrectos. Inténtelo nuevamente.\n");
      return 0;
    }
}

/* cuando estaba intentando utilizar esta funcion para validar las credenciales se me quedaba atrapada en un loop asi que hice todo en la misma funcion.
int successLogin(Pair* adminItem, char* rut, char* password) {
    if (adminItem == NULL || adminItem->value == NULL) {
        return 0;
    }

    tipoAdministrador* admin = (tipoAdministrador *) adminItem->value;
    if(strcmp(admin->rut,rut) != 0 || strcmp(admin->password,password) != 0)
        return 0;

    return 1;
}
*/

void busquedaProductosDirecta(HashMap* mapa)
{
    printf("BUSQUEDA DE PRODUCTOS POR NOMBRE\n");
    char nombreProductoBuscado[MAXLEN + 1];
    puts(barra2);
    printf("Ingrese el nombre del producto a buscar.\n");
    scanf("%s", nombreProductoBuscado);
    
    Pair* parBuscado = searchMap(mapa, nombreProductoBuscado);
    tipoProducto* productoBuscado = parBuscado->value;
    mostrarProducto(productoBuscado);
}

void busquedaPorPrecio(BTree* arbolP)
{
    printf("BUSQUEDA DE PRODUCTOS POR PRECIO\n");
    puts(barra2);
    
    int precio1 = 1, precio2 = 0;
    List* listaP = createList();
    
    while (precio1 > precio2)
    {
        printf("INGRESE EL RANGO DE PRECIOS.\n");
        scanf("%d %d", &precio1, &precio2);
    }


    if (listaP == NULL)
    {
        printf("Error.");
    }
    
   searchByRangeBTree(getRoot(arbolP), precio1, precio2, listaP);
    
    if (isListEmpty(listaP))
    {
        printf("TESTTTTTTKKKK NO SE HALLARON PRODUCTOS EN EL RANGO DE PRECIOS SELECCIONADO.");
        return;
    }

    tipoProducto* productoBuscado = firstList(listaP);
    
    int test = get_size(listaP);
    printf("%d", test);
    
    if (productoBuscado == NULL)
    {
        printf("NO SE HALLARON PRODUCTOS EN EL RANGO DE PRECIOS SELECCIONADO.");
        return;
    }
    
    mostrarProducto(productoBuscado);
    
    while (1)
    {
        productoBuscado = nextList(listaP);
        if (productoBuscado == NULL) return;
        mostrarProducto(productoBuscado);
    }
}

/*
void mostrarMenuAdmin()
{
    puts(barra3);
    printf("1. INGRESE 1 SI DESEA AGREGAR PRODUCTOS\n");
    printf("2. INGRESE 2 SI DESEA AGREGAR SUPERMERCADOS\n");
    printf("3. INGRESE 3 SI DESEA AGREGAR CATEGORIA\n");
    printf("4. INGRESE 4 SI DESEA QUITAR PRODUCTOS\n");
    printf("5. INGRESE 5 SI DESEA SALIR AL MENU PRINICIPAL\n");
    puts(barra3);
}

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias)
{
    mostrarMenuAdmin();
    int opcion;
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
        printf("OPCION 1 INGRESADA\n\n");
        //agregarProducto(mapaProductos, mapaCategorias, mapaSupermercados);
        break;
    case 2:
        printf("OPCION 2 INGRESADA\n\n");
        
        break;
    case 3:
        printf("OPCION 3 INGRESADA\n\n");
        
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

/*void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados) {
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

        // Verificar si el supermercado ya está asociado al producto
        Node* currentNode = nuevoProducto->supermercados->head;
        while (currentNode != NULL) {
            tipoSupermercado* existingSupermercado = (tipoSupermercado*)currentNode->data;
            if (strcmp(existingSupermercado->nombre, nombreSupermercado) == 0) {
                printf("El supermercado ya está asociado al producto.\n");
                break;
            }
            currentNode = currentNode->next;
        }

        // Si el supermercado no está asociado, agregarlo al producto y a la lista de productos del supermercado
        if (currentNode == NULL) {
            pushBack(supermercado->productos, nuevoProducto);
            pushBack(nuevoProducto->supermercados, supermercado);
        }
    }

    
 // Imprimir el producto agregado
    printf("Producto agregado exitosamente:\n");
    printf("Nombre: %s\n", nuevoProducto->nombre);
    printf("Precio: %s\n", nuevoProducto->precio);
    printf("Categoría: %s\n", nuevoProducto->categoria);
    printf("Cantidad de supermercados: %d\n", nuevoProducto->cantSupermercados);

    printf("Supermercados asociados:\n");
    Node* currentNode = nuevoProducto->supermercados->head;
    while (currentNode != NULL) {
        tipoSupermercado* supermercado = (tipoSupermercado*)currentNode->data;
        printf("- %s\n", supermercado->nombre);
        currentNode = currentNode->next;
    }
}
*/

void mostrarOpciones()
{
    puts(barra3);
    printf("1. INGRESE 1 SI DESEA ARMAR CANASTA CON PRODUCTOS A COMPRAR\n");
    printf("2. INGRESE 2 SI DESEA MOSTRAR TODOS LOS PRODUCTOS\n");
    printf("3. INGRESE 3 SI DESEA BUSCAR PRODUCTO POR NOMBRE\n");
    printf("4. INGRESE 4 SI DESEA MOSTRAR PRODUCTO POR PRECIO\n");
    printf("5. INGRESE 5 SI DESEA MOSTRAR PRODUCTO POR SUPERMERCADO\n");
    printf("6. INGRESE 6 SI DESEA MOSTRAR PRODUCTO POR CATEGORIA\n");
    printf("7. INGRESE 7 SI DESEA INICIAR SESION COMO ADMINISTRADOR\n");
    printf("8. INGRESE 0 SI DESEA SALIR\n");
    puts(barra3);
}

void mostrarMenu()
{
    HashMap* mapaProductos=createMap(MAPINITIALCAPAC);
    HashMap* mapaSupermercados=createMap(MAPINITIALCAPAC);
    HashMap* mapaCategorias=createMap(MAPINITIALCAPAC);
    BTree* arbolProductos = createBTree(1 + MAPINITIALCAPAC / 6); // Debe ser impar
    
    HashMap* mapaAdmin = createMap(MAPADMINITIALCAPAC);
    
    importarDatosCSV(mapaProductos, mapaSupermercados, mapaCategorias, arbolProductos);
    traverseBTree(getRoot(arbolProductos));
    //(importarCredencialesAdmin(mapaAdmin);
    
    List* canasta = createList();
    int opcion;
    do {
        puts(barra1);
        mostrarOpciones();
        puts(barra1);
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            printf("OPCION 1 INGRESADA\n\n");
            //armarCanasta(canasta,mapaProductos,mapaSupermercados);
            break;
        case 2:
            puts(barra2);
            printf("OPCION 2 INGRESADA\n\n");
            printAllP(mapaProductos);
            puts(barra2);
            break;
        case 3:
            puts(barra2);
            printf("OPCION 3 INGRESADA\n\n");
            busquedaProductosDirecta(mapaProductos);
            puts(barra2);
            break;
        case 4:
            puts(barra2);
            printf("OPCION 4 INGRESADA\n\n");
            busquedaPorPrecio(arbolProductos);
            puts(barra2);
            break;
        case 5:
            printf("OPCION 5 INGRESADA\n\n");
            break;
        case 6:
            printf("OPCION 6 INGRESADA\n\n");
            break;
        case 7:
            printf("OPCION 7 INGRESADA\n\n");
            //if(loginAdmin(mapaAdmin) != 0)
            //    menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
            break;
        default:       
            printf("CERRANDO EL PROGRAMA...\n");
        }
    } while (opcion != 0);
}
