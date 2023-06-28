#ifndef OPCIONES_ADMIN_H
#define OPCIONES_ADMIN_H

#include "constantesYRegistros.h"
#include "mostrarMenus.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "mostrarElementosSistema.h"

int loginAdmin(HashMap* mapaAdministradores); // Iniciar sesion como administrador, si se inicia sesion correctamente retorna distinto a 0

void menuAdmin(HashMap* mapaProductos,HashMap* mapaSupermercados,HashMap* mapaCategorias);

void agregarProducto(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados);

void agregarSupermercado (HashMap* mapaSupermercados);

void agregarCategoria (HashMap* mapaCategorias);

void quitarProductos(HashMap* mapaProductos, HashMap* mapaCategorias, HashMap* mapaSupermercados);

void eliminarProductoLista(List* productos,char* nomProducto);

void guardarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias);

void guardarDatosCSV2 (HashMap* mapaSupermercados, HashMap* mapaCategoria);

#endif
