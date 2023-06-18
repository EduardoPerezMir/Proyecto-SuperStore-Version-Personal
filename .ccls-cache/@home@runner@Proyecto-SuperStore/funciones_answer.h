#ifndef Funciones_answer_h
#define Funciones_answer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "hashmap.h"
#include "list.h"
#include "btree.h"
#include "list.h"
#include "hashmap.h"

#define MAXLEN 30
#define PRICELEN 9
#define MAPINITIALCAPAC 36
#define MAPADMINITIALCAPAC 4
#define barra1 "\n=================================================================\n"
#define barra2 "\n-----------------------------------------------------------------\n"
#define barra3 "\n*****************************************************************\n"
#define barra4 "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"

typedef struct{
    char nombre[MAXLEN + 1];
    char precio[PRICELEN + 1];
    int price;
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

typedef struct{
    char nombre[MAXLEN + 1];
    char supermercado[M]
}tipoCanasta;

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias, BTree* arbolProductos);

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercado);

void mostrarTodosProductos(HashMap* productos);

void printListS(List* Super); // Muestra lista de supermercados

void printAllP(HashMap* mapaProductos); // Mostrar todos los productos OPCION 2

void printListP(List* Super); // Mostrar toda la lista de productos (OPCION CANASTA)

int loginAdmin(HashMap* mapaAdministradores); // Iniciar sesion como administrador OPCION 7, Si se inicia sesion correctamente retorna distinto a 0

int successLogin(Pair* adminItem, char* rut, char* password);

void mostrarMenuAdmin();

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias);

void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados);

void agregarSupermercado (HashMap* mapaSupermercados);

void agregarCategoria (HashMap* mapaCategorias);

void busquedaProductosDirecta(HashMap* mapa);

void busquedaPorPrecio(BTree* arbolP);

tipoProducto* busquedaProductosAdyacentes(HashMap* mapa);

void mostrarProducto(tipoProducto* producto);

void subMenuCanasta();

void mostrarMenu();

void mostrarOpciones(); //

#endif /* Funciones_answer_h */