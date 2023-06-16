#ifndef Funciones_answer_h
#define Funciones_answer_h

#include "hashmap.h"
#include "list.h"

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias);

void mostrarMenu();

void mostrarOpciones();

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercado);

void mostrarTodosProductos(HashMap* productos);

void printListS(List* Super); // Muestra lista de supermercados

#endif /* Funciones_answer_h */