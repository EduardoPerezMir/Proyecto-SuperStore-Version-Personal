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
    int test;
    
    
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
        insertMap(mapaCategorias, nuevaCategoria->nombre, NULL, nuevaCategoria);
        
        nuevoProducto->supermercados = createList();
        
        for (size_t i = 0; (token = strtok(NULL, ",")) != NULL; i++) {
            token = strtok(NULL, ",");
            tipoSupermercado *nuevoSupermercado = (tipoSupermercado*) malloc(sizeof(nuevoSupermercado));
            strncpy(nuevoSupermercado->nombre, token, sizeof(nuevoSupermercado->nombre));
            pushBack(nuevoProducto->supermercados, nuevoSupermercado);
            pushBack(nuevoSupermercado->productos, nuevoProducto);
            replace(nuevoProducto->supermercados, nuevoSupermercado);
            insertMap(mapaSupermercados, nuevoSupermercado->nombre, NULL, nuevoSupermercado);
        }
        insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto->codigo, nuevoProducto);
    }
    fclose(file);
}

void mostrarMenu()
{
    HashMap* mapaProductos=createMap(5);
    HashMap* mapaSupermercados=createMap(5);
    HashMap* mapaCategorias=createMap(5);
    
    HashMap* mapaAdmin=createMap(5);
    
    //importarDatosCSV(mapaProductos, mapaSupermercados, mapaCategorias);
    
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

int loginAdmin(HashMap* mapaAdmin) {

    while(1) {
        char rut[MAXLEN + 1];
        do{
            printf("INGRESE RUT PARA INICIAR SESIÓN\n");
            scanf("%s",rut);
            getchar();
        }while(strlen(rut) > MAXLEN);
    
        char password[MAXLEN + 1];
        do{
            printf("INGRESE CONTRASEÑA PARA INICIAR SESIÓN\n");
            scanf("%s",password);
            getchar();
        }while(strlen(password) > MAXLEN);

        if (successLogin(searchMap(mapaAdmin,rut)->value,rut,password)) {
            printf("SE HA INICIADO SESION EXITOSAMENTE\n");
            
            return 1;
        } 
    }
    
}

int successLogin(Pair* adminItem, char* rut, char* password) {
    if(adminItem == NULL)
        return 0;

    tipoAdministrador* admin = (tipoAdministrador *) adminItem->value;
    
    if(strcmp(admin->rut,rut) != 0 || strcmp(admin->password,password) != 0)
        return 0;

    return 1;
}




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
