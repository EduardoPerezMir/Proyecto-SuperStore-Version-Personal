#include "opcionesAdmin.h"

int loginAdmin(HashMap * mapaAdmin) {
    printf("            INICIO DE SESIÓN.\n\n");
    while (1) {
        char rut[MAXLEN + 1];
        do {
            printf("INGRESE RUT PARA INICIAR.            (Ingrese 0 para salir)\n");
            scanf("%s", rut);
            while (getchar() != '\n');
            if (strcmp(rut, "0") == 0) return 0;
        } while (strlen(rut) > MAXLEN);
        
        char password[MAXLEN + 1];
        do {
            printf("INGRESE CONTRASEÑA PARA INICIAR SESIÓN.            (Ingrese 0 para salir)\n");
            scanf("%s", password);
            while (getchar() != '\n');
            if (strcmp(rut, "0") == 0) return 0;
        } while (strlen(password) > MAXLEN);
        
        Pair* adminItem = searchMap(mapaAdmin, rut);
        if (adminItem != NULL) {
            tipoAdministrador* admin = (tipoAdministrador*)adminItem->value;
            if (strcmp(admin->rut, rut) == 0 && strcmp(admin->password, password) == 0) 
            {
                printf("SE HA INICIADO SESIÓN EXITOSAMENTE\n");
                return 1;
            }
        }
        else
        {
            printf("RUT o contraseña incorrectos. Inténtelo nuevamente.\n");
        }
    }
}

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias)
{
    puts(MSJMENUADMINISTRADOR);
    mostrarMenuAdmin();
    int opcion;
    scanf("%d", &opcion);
    // Segun la opcion ingresadaos
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
        guardarDatosCSV2(mapaSupermercados, mapaCategorias);
        printf("GURDANDO CAMBIOS ...");
        return;
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
    while (getchar() != '\n');

    nombre[0] = toupper(nombre[0]);
    for (char i = 1; nombre[i] != '\0'; i++)
        nombre[i] = tolower(nombre[i]);
    
    if(searchMap(mapaProductos, nombre) != NULL){
    printf("El prodcuto ya existe en el mapa de productos.\n");
    mostrarMenuAdmin();
    }

    printf("Ingrese el precio del producto: ");
    scanf("%s", precio);
    while (getchar() != '\n');
    
    // Convertir el precio de cadena de caracteres a entero
    int price = atoi(precio);

    printf("Ingrese la categoría del producto: ");
    scanf("%s", categoria);
    while (getchar() != '\n');

    printf("Ingrese la cantidad de supermercados: ");
    scanf("%d", &cantSupermercados);
    while (getchar() != '\n');

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
        while (getchar() != '\n');
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
    char *nombreSupermercado = (char*) malloc(sizeof(MAXLEN + 1));
    printf("Ingrese el nombre del supermercado: ");
    scanf("%s", nombreSupermercado);
    while (getchar() != '\n');
    
    if (searchMap(mapaSupermercados, nombreSupermercado) != NULL) {
        printf("El supermercado ya existe en el mapa de supermercados.\n");
        return;
    }
    tipoSupermercado* supermercado = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
    strncpy(supermercado->nombre, nombreSupermercado, MAXLEN);
    supermercado->productos = createList();
    
    insertMap(mapaSupermercados, nombreSupermercado, supermercado);
    
    printf("Supermercado agregado exitosamente.\n");
    
    // Comprobación de que el supermercado se agregó al mapa
    Pair* test = searchMap(mapaSupermercados, nombreSupermercado);
    if (test != NULL) {
    printf("Supermercado encontrado en el mapa de supermercados: %s\n", test->key);
    } else {
    printf("No se encontró el supermercado en el mapa de supermercados.\n");
    }
}

void agregarCategoria(HashMap* mapaCategorias) {
    char *nombreCategoria = (char*) malloc(sizeof(MAXLEN + 1));
    printf("Ingrese el nombre de la categoría: ");
    scanf("%s", nombreCategoria);
    while (getchar() != '\n');
    
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
    while(currentList != NULL)//ciclo que recorre la lista recibida
    {
        if (strcmp(currentList->nombre, nomProducto) == 0)
        {
            popCurrent(productos);
            return;
        }
        currentList=nextList(productos);
    }
}

void quitarProductos(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados)
{
    printMap(mapaProductos, 0);
    char nomProducto[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto ha eliminar de la base de datos: ");
        while (getchar() != '\n');
        scanf("%[^\n]s",nomProducto);
        while (getchar() != '\n');
        printf("\n");
    }while(strlen(nomProducto) > MAXLEN);
    
    Pair* current = searchMap(mapaProductos, nomProducto);
    if (current == NULL)
    {
        printf("El producto %s no existe en la base de datos",nomProducto);
        menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
    }
    
    tipoProducto* producto = current->value;
    
    //eliminacion del producto de la lista de productos del mapa de supermercados
    tipoSupermercado* currentListSuper = firstList(producto->supermercados);
    while(currentListSuper != NULL)//ciclo para recorrer todos los supermercados de la lista del producto a eliminar
    {
        Pair* parSuper = searchMap(mapaSupermercados,currentListSuper->nombre);
        tipoSupermercado* elemenMapSuper = parSuper->value;

        //(eliminarProductoLista)ciclo para recorrer lista del mapa de supermercado para eliminar producto
        eliminarProductoLista(elemenMapSuper->productos, nomProducto);
        
        currentListSuper = nextList(producto->supermercados);
    }
    
    //eliminacion del producto en la lista del producto del mapa de categoria
    Pair* parCategoria = searchMap(mapaCategorias,producto->categoria);
    tipoCategoria* categoria = parCategoria->value;//categoria donde se encuentra el producto a eliminar
    
    tipoProducto* currentListP = firstList(categoria->productos);
    while(currentListP != NULL)//ciclo que recorre lista de productos del mapa categoria
    {
        if (strcmp(currentListP->nombre,nomProducto) == 0)
        {
            popCurrent(categoria->productos);
            break;
        }
        currentListP = nextList(categoria->productos);
    }
    
    eraseMap(mapaProductos, nomProducto);
    printf("El producto %s ha sido eliminado de la base de datos\n", nomProducto);
    menuAdmin(mapaProductos, mapaSupermercados, mapaCategorias);
}

void guardarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias) {
    FILE* archivo = fopen("Base de datos/db_productos.csv", "w");

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
//ARREGLAR
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
        }

        currentProducto = nextMap(mapaProductos);
    }

    fclose(archivo);

    printf("Datos guardados exitosamente en la base de dato.\n");
}

void guardarDatosCSV2 (HashMap* mapaSupermercados, HashMap* mapaCategorias){
    FILE *file_super = fopen("Base de datos/db_supermercados.csv", "w");
    FILE *file_categoria = fopen("Base de datos/db_categorias.csv", "w");
    if (file_super == NULL) {
        printf("No se pudo abrir el archivo para guardar los datos.\n");
        return;
    }
    
    fprintf(file_super, "Supermercados\n");
    
    Pair* currentSupermercado = firstMap(mapaSupermercados);
    tipoSupermercado* supermercadoAux = currentSupermercado->value;
    while(currentSupermercado != NULL) {
        if (supermercadoAux->nombre[0] != '\0') {
            printf("test: %s\n", supermercadoAux->nombre);
        fprintf(file_super, "%s\n", supermercadoAux->nombre);
        }
        currentSupermercado = nextMap(mapaSupermercados);
        supermercadoAux = currentSupermercado->value;
    }
    
    fclose(file_super);
//categoria
fprintf(file_categoria, "Categorias\n");
Pair* currentCategoria = firstMap(mapaCategorias);
    tipoSupermercado* categoriaAux = currentCategoria->value;
    while(currentCategoria != NULL) {
        if (categoriaAux->nombre[0] != '\0') {
            printf("test: %s\n", categoriaAux->nombre);
        fprintf(file_categoria, "%s\n", categoriaAux->nombre);
        }
        currentCategoria = nextMap(mapaCategorias);
        categoriaAux = currentCategoria->value;
    }
    
    fclose(file_categoria);

    
    printf("Datos de los supermercados guardados.\n");
}
