#ifndef MOSTRAR_ELEMENTOS_SISTEMA_H
#define MOSTRAR_ELEMENTOS_SISTEMA_H

#include "constantesYRegistros.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"

void printListS(List* Super); // Muestra lista de supermercados

void printListP(List* Super); // Mostrar lista de productos 

void printMap(HashMap* mapaProducto, int indicadorMSJ); // Mostrar todos los productos para que el usuario sepa qué producto agregar a la canasta

void mostrarProductos(List* lista); // Esta función recibe una lista de hasta 3 productos, y muestra su información asociada
                                    // de forma secuencial en la pantalla (un producto al lado del otro).

void mostrarOfertaNacional(HashMap* mapaProductos); // Mostrar todos los productos almacenados en el sistema. 

#endif