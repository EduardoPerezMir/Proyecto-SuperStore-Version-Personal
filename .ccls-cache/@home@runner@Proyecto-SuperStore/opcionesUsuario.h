#ifndef opciones_Usuario_h
#define opciones_Usuario_h

#include "registros.h"

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercado);

void eliminarProduCanasta(List* canasta);

void agregarProduCanasta(HashMap* mapaProductos,HashMap* mapaSupermercados,List* canasta);

void printListPC(List* Super); // Muestra los productos de la canasta

void subMenuCanastaCantidad();

tipoCanasta* searchListCanasta(List* canasta,char* producto,char* supermercado);

// Mostrar toda la oferta de productos OPCION 2

void mostrarTodosProductos(HashMap* productos); // Opcion 2 "Mostrar todos los productos"

void mostrarProducto(tipoProducto* producto);

void printAllP(HashMap* mapaProductos); // Mostrar todos los productos 

//Mostrar por nombre OPCION 3

void busquedaProductosDirecta(HashMap* mapa);

// Mostrar por precio OPCION 4

void busquedaPorPrecio(BTree* arbolP);

// Mostrar por supermercado OPCION 5




//Mostrar por categoria OPCION 6 

void busquedaProductosAdyacentes(HashMap* mapa, int indicador);


// Iniciar sesion como administrador OPCION 7
int loginAdmin(HashMap* mapaAdministradores); // Iniciar sesion como administrador, si se inicia sesion correctamente retorna distinto a 0


#endif
