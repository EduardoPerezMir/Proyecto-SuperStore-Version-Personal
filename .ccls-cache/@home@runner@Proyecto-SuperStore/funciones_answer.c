#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "list.h"
#include "hashmap.h"
#include "funciones_answer.h"

#define MAXLEN 30
#define CODELEN 8

typedef struct{
    char nombre[MAXLEN + 1];
    char codigo[CODELEN];
    char precio[9];
    //char marca[MAXLEN];
    //int precio;
    char categoria[MAXLEN + 1];
    int cantSupermercados;
    List *supermercados;
}tipoProducto;

typedef struct{
    char nombre[MAXLEN + 1];
    List *productos;
}tipoCategoria;

typedef struct{
    char nombre[MAXLEN + 1];
    List *productos;
}tipoSupermercado;

typedef struct{
    char rut[MAXLEN + 1];
    char password[MAXLEN + 1];
}tipoAdministrador;

void mostrarOpciones()
{
    printf("*****************************************************************\n");
    printf("1. INGRESE 1 SI DESEA ARMAR CANASTA CON PRODUCTOS A COMPRAR\n");
    printf("2. INGRESE 2 SI DESEA MOSTRAR TODOS LOS PRODUCTOS\n");
    printf("3. INGRESE 3 SI DESEA BUSCAR PRODUCTO POR NOMBRE\n");
    printf("4. INGRESE 4 SI DESEA MOSTRAR PRODUCTO POR PRECIO\n");
    printf("5. INGRESE 5 SI DESEA MOSTRAR PRODUCTO POR SUPERMERCADO\n");
    printf("6. INGRESE 6 SI DESEA MOSTRAR PRODUCTO POR CATEGORIA\n");
    printf("7. INGRESE 7 SI DESEA INICIAR SESION COMO ADMINISTRADOR\n");
    printf("8. INGRESE 0 SI DESEA SALIR\n");
    printf("*****************************************************************\n\n");
    
}

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias) {
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
        strncpy(nuevoProducto->codigo, token, sizeof(nuevoProducto->codigo));
        
        token = strtok(NULL, ",");
        strncpy(nuevoProducto->nombre, token, sizeof(nuevoProducto->nombre));

        token = strtok(NULL, ",");
        strncpy(nuevoProducto->precio, token, sizeof(nuevoProducto->precio));
        
        token = strtok(NULL, ",");
        
        tipoCategoria* nuevaCategoria = (tipoCategoria*) malloc(sizeof(tipoCategoria));
        strncpy(nuevoProducto->categoria, token, sizeof(nuevoProducto->categoria));
        strncpy(nuevaCategoria->nombre, token, sizeof(nuevaCategoria->nombre));
        nuevaCategoria->productos = createList();
        
        pushBack(nuevaCategoria->productos, nuevoProducto);
        insertMap(mapaCategorias, nuevaCategoria->nombre,nuevaCategoria->nombre, nuevaCategoria);
        
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
            
 Pair* pair = searchMap(mapaSupermercados, nuevoSupermercado->nombre);
            if (pair == NULL) {
                insertMap(mapaSupermercados, nuevoSupermercado->nombre, nuevoSupermercado->nombre, nuevoSupermercado);
            } else {
                tipoSupermercado* supermercadoExistente = pair->value;
                pushBack(supermercadoExistente->productos, nuevoProducto);
            }
        }
        
        insertMap(mapaProductos, nuevoProducto->nombre,nuevoProducto->codigo, nuevoProducto);
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
     
      insertMap(mapaAdmin,nuevoAdmin->rut, nuevoAdmin->rut, nuevoAdmin);
   }
}

void mostrarMenu()
{
    HashMap* mapaProductos=createMap(5);
    HashMap* mapaSupermercados=createMap(5);
    HashMap* mapaCategorias=createMap(5);
    
    HashMap* mapaAdmin=createMap(5);
    
    importarDatosCSV(mapaProductos, mapaSupermercados, mapaCategorias);
    importarCredencialesAdmin(mapaAdmin);
  
    List* canasta = createList();
    int opcion;
    do {
        printf("\n");
        mostrarOpciones();
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            printf("OPCION 1 INGRESADA\n\n");
            armarCanasta(canasta,mapaProductos,mapaSupermercados);
            break;
        case 2:
            printf("OPCION 2 INGRESADA\n\n");
            printAllP(mapaProductos);
            break;
        case 3:
            printf("OPCION 3 INGRESADA\n\n");
            break;
        case 4:
            printf("OPCION 4 INGRESADA\n\n");
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
        case 0:
            printf("CERRANDO EL PROGRAMA...\n");
        }
    } while (opcion != 0);
}

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

void printAllP(HashMap* productos) {
    Pair* current = firstMap(productos);
    if(current == NULL) {
        printf("NO HAY PRODUCTOS EN LA BASE DE DATOS\n");
        return;
    }

    printf("LISTA DE PRODUCTOS A NIVEL NACIONAL:\n");
    
    int cont = 1;
     while(current != NULL) {
        tipoProducto* producto = (tipoProducto*) current->value;
        printf("%d. %s %s %s\n",cont,producto->nombre,producto->categoria,producto->precio);
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

void mostrarMenuAdmin()
{
    printf("***********************************************\n");
    printf("1. INGRESE 1 SI DESEA AGREGAR PRODUCTOS\n");
    printf("2. INGRESE 2 SI DESEA AGREGAR SUPERMERCADOS\n");
    printf("3. INGRESE 3 SI DESEA AGREGAR CATEGORIA\n");
    printf("4. INGRESE 4 SI DESEA QUITAR PRODUCTOS\n");
    printf("5. INGRESE 5 SI DESEA SALIR AL MENU PRINICIPAL\n");
    printf("***********************************************\n");
    
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

void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados) {
    char nombre[MAXLEN + 1];
    char codigo[CODELEN];
    char precio[9];
    char categoria[MAXLEN + 1];
    int cantSupermercados;

    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    getchar(); 

    printf("Ingrese el código del producto: ");
    scanf("%s", codigo);
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
    strncpy(nuevoProducto->codigo, codigo, sizeof(nuevoProducto->codigo));
    strncpy(nuevoProducto->precio, precio, sizeof(nuevoProducto->precio));
    strncpy(nuevoProducto->categoria, categoria, sizeof(nuevoProducto->categoria));
    nuevoProducto->cantSupermercados = cantSupermercados;
    nuevoProducto->supermercados = createList();

    // Insertar el nuevo producto en el mapa de productos
    insertMap(mapaProductos, nombre, codigo, nuevoProducto);

    // Verificar si la categoría existe en el mapa de categorías
    tipoCategoria* catExistente = (tipoCategoria*)searchMap(mapaCategorias, categoria);
    if (catExistente == NULL) {
        // La categoría no existe, se crea una nueva y se agrega al mapa de categorías
        tipoCategoria* nuevaCategoria = (tipoCategoria*)malloc(sizeof(tipoCategoria));
        strncpy(nuevaCategoria->nombre, categoria, sizeof(nuevaCategoria->nombre));
        nuevaCategoria->productos = createList();
        insertMap(mapaCategorias, categoria, categoria, nuevaCategoria);
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
            insertMap(mapaSupermercados, nombreSupermercado, nombreSupermercado, supermercado);
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
    printf("Código: %s\n", nuevoProducto->codigo);
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
