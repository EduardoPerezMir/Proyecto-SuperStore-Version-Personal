#include "funciones_answer.h"

// Importacion de base de datos

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
    printf("║ 1. INGRESE 1 SI DESEA VER TODOS PRODUCTOS DE LA CANASTA     ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR PRODUCTOS A LA CANASTA        ║\n");
    printf("║                                                             ║\n");
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

tipoCanasta* searchListCanasta(List* canasta,char* key)
{
    for (tipoCanasta* current=firstList(canasta);current!=NULL;current=nextList(canasta))
    {
        if (strcmp(key,current->nombre)==0)
        {
            return current;
        }
    }
    return NULL;
}

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercados)
{
    
    subMenuCanasta();
    int opcion;
    do {
        printf("Opción: ");
        scanf("%i",&opcion);
    }while(opcion!=1 && opcion!=2);
    printf("\n");

    if (opcion == 1) 
    {
        if (isListEmpty(canasta))
            printf("No existen productos en la canasta\n");
        else printListPC(canasta);
    } 
    else
    {

        printMapP(mapaProductos);
        char nomProducto[MAXLEN + 1];
        do{
            printf("Ingrese el nombre del producto agregar a la canasta: ");
            scanf("%s",nomProducto);
            getchar();
            printf("\n");
        }while(strlen(nomProducto) > MAXLEN);
    
        Pair* current;
        if( (current = searchMap(mapaProductos,nomProducto)) == NULL) {
            printf("El producto a buscar no se encuentra en la base de datos\n");
            return;
        }
        printf("Lista de supermercados que contienen el producto: %s\n",nomProducto);
        printListS(((tipoProducto *)current->value)->supermercados);
        
        char nomSupermercado[MAXLEN + 1];
        do{
            printf("Ingrese el nombre del supermercado que posee el producto agregar a la canasta: ");
            scanf("%s",nomSupermercado);
            getchar();
            printf("\n");
        }while(strlen(nomSupermercado) > MAXLEN);
    
        if(searchMap(mapaSupermercados,nomSupermercado) == NULL) {
            printf("El supermercado a buscar no se encuentra en la base de datos\n");
            return;
        }
        size_t cantidad=0;
        tipoCanasta* productoBuscado=searchListCanasta(canasta,nomProducto);
        
        if (productoBuscado==NULL)
        {
            printf("Ingrese la cantidad de %s que desea agregar a la canasta :",nomProducto);
            do{
                scanf("%zd",&cantidad);
            }while(cantidad<=0);
    
            tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
            strcpy(elemCanasta->nombre,nomProducto);
            strcpy(elemCanasta->supermercado,nomSupermercado);
            strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
            elemCanasta->cantidad=cantidad;
            
            pushBack(canasta,elemCanasta);
            printf("El producto %s del supermercado %s ha sido agregado a la canasta.\n\n",nomProducto,nomSupermercado);
            
        }
        else
        {
            if (strcmp(productoBuscado->supermercado,nomSupermercado)==0)
            {
                printf("El producto %s se encuentra en la canasta con una cantidad de %zd\n",nomProducto,productoBuscado->cantidad);
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
                printf("La cantidad actual de %s en la canasta es %zd\n",nomProducto,productoBuscado->cantidad);
            }
            else
            {
                printf("Ingrese la cantidad de %s que desea agregar a la canasta :",nomProducto);
                do{
                    scanf("%zd",&cantidad);
                }while(cantidad<=0);
        
                tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
                strcpy(elemCanasta->nombre,nomProducto);
                strcpy(elemCanasta->supermercado,nomSupermercado);
                strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
                elemCanasta->cantidad=cantidad;
                
                pushBack(canasta,elemCanasta);
                printf("El producto %s del supermercado %s ha sido agregado a la canasta.\n\n",nomProducto,nomSupermercado);
            }
        }
        

        /*
        if (productoBuscado != NULL)
        {
            if (strcmp(productoBuscado->supermercado,nomSupermercado)==0)
            {
                printf("El producto %s se encuentra en la canasta con una cantidad de %zd\n",nomProducto,productoBuscado->cantidad);
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
                printf("La cantidad actual de %s en la canasta es %zd\n",nomProducto,productoBuscado->cantidad);
            }
            
        }
        if (cantidad==0)//si es 0 quiere decir que no esta repetida
        {
            printf("Ingrese la cantidad de %s que desea agregar a la canasta :",nomProducto);
            do{
                scanf("%zd",&cantidad);
            }while(cantidad<=0);
    
            tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
            strcpy(elemCanasta->nombre,nomProducto);
            strcpy(elemCanasta->supermercado,nomSupermercado);
            strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
            elemCanasta->cantidad=cantidad;
            
            pushBack(canasta,elemCanasta);
            printf("El producto %s del supermercado %s ha sido agregado a la canasta.\n\n",nomProducto,nomSupermercado);
        }  */  
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
        cont++;
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
    Pair* current = firstMap(productos);
    if(current == NULL) {
        printf("No hay productos existentes\n");
        return;
    }
    
    printf("\nLista de productos existentes:\n\n");
    //char cadena[20];
    
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

void busquedaPorPrecio(BTree* arbolP)
{
    int precio1 = 1, precio2 = 0;
    List* listaP = createList();
    
    puts(MSJBUSQUEDA2);
    
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
        puts(MSJBUSQUEDASC);
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
    mostrarMenuAdmin();
    int opcion;
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
        printf("\nOpción 1 ingresada\n");
        agregarProducto(mapaProductos, mapaCategorias, mapaSupermercados);
        break;
    case 2:
        printf("\nOpción 2 ingresada\n");
        agregarSupermercado(mapaSupermercados);
        break;
    case 3:
        printf("\nOpción 3 ingresada\n");
        agregarCategoria(mapaCategorias);
        break;
    case 4:
        printf("\nOpción 4 ingresada\n");
        break;
    case 5:
        printf("\nOpción 5 ingresada\n");
        
        printf("GURDANDO CAMBIOS ...");
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

    //SI EL PRODUCTO NO EXISTE BREAK; TODO.
  
    tipoProducto* nuevoProducto = (tipoProducto*)malloc(sizeof(tipoProducto));
    strncpy(nuevoProducto->nombre, nombre, sizeof(nuevoProducto->nombre));
    strncpy(nuevoProducto->precio, precio, sizeof(nuevoProducto->precio));
    nuevoProducto->price = price;
    strncpy(nuevoProducto->categoria, categoria, sizeof(nuevoProducto->categoria));
    
    /*
    strcpy(nuevoProducto->nombre, nombre);
    strcpy(nuevoProducto->precio, precio);
    nuevoProducto->price = price;
    strcpy(nuevoProducto->categoria, categoria);
  */
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
    
        //strncpy(nuevaCategoria->nombre, categoria, sizeof(nuevaCategoria->nombre));
         strcpy(nuevaCategoria->nombre, categoria);
        nuevaCategoria->productos = createList();
      
        insertMap(mapaCategorias, categoria, nuevaCategoria);
         // Actualizar la referencia a la nueva categoría
        categoriaProducto = malloc(sizeof(Pair));
        categoriaProducto->value = nuevaCategoria;
        //pushBack(nuevaCategoria->productos, nuevoProducto);
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
            //auxSupermercado->value = supermercado; // Actualizar la referencia a la nueva categoría
    
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
  
  if (searchMap(mapaSupermercados,nombreSupermercado) != NULL) {
    printf("El supermercado ya existe en el mapa de supermercados.\n");
    return;
  }

 tipoSupermercado* supermercado = (tipoSupermercado*)malloc(sizeof(tipoSupermercado));
  strncpy(supermercado->nombre, nombreSupermercado, MAXLEN);
  supermercado->nombre[MAXLEN] = '\0';
  supermercado->productos = createList();

    insertMap(mapaSupermercados, nombreSupermercado, supermercado);
  //insertMap(mapaSupermercados, supermercado->nombre, supermercado);
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
    mostrarTodo(mapaSupermercados);
    List* canasta = createList();
    int opcion;
    do {
        mostrarOpciones();
        printf("Opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');
        switch (opcion) {
        case 1:
            printf("\nOpción 1 ingresada\n");
            armarCanasta(canasta,mapaProductos,mapaSupermercados);
            break;
        case 2:
            printf("\nOpción 2 ingresada\n");
            printAllP(mapaProductos);
            break;
        case 3:
            printf("\nOpción 3 ingresada\n");
            busquedaProductosDirecta(mapaProductos);
            break;
        case 4:
            printf("\nOpción 4 ingresada\n");
            busquedaPorPrecio(arbolProductos);
            break;
        case 5:
            printf("\nOpción 5 ingresada\n");
            busquedaProductosAdyacentes(mapaSupermercados, 1);
            break;
        case 6:
            printf("\nOpción 6 ingresada\n");
            busquedaProductosAdyacentes(mapaCategorias, 2);
            break;
        case 7:
            printf("\nOpción 7 ingresada\n");
            if(loginAdmin(mapaAdmin) != 0)
               menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
            break;
        default:       
            printf("CERRANDO EL PROGRAMA...\n");
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