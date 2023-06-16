#ifndef Funciones_answer_h
#define Funciones_answer_h

#include "hashmap.h"
#include "list.h"

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias);

void mostrarMenu();

void mostrarOpciones();

void mostrarMenuAdmin();

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias,HashMap* mapaAdmin);

void agregarProductos(HashMap* mapaProductos,HashMap* mapaSupermercados);

void agregarSupermercado(HashMap* mapaSupermercados);

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercado);

void mostrarTodosProductos(HashMap* productos);

void printListS(List* Super); // Muestra lista de supermercados

void printAllP(HashMap* mapaProductos); // Mostrar todos los productos OPCION 2

int loginAdmin(HashMap* mapaAdministradores); // Iniciar sesion como administrador OPCION 7, Si se inicia sesion correctamente retorna distinto a 0

int successLogin(Pair* adminItem, char* rut, char* password);

#endif /* Funciones_answer_h */