#ifndef CONSTANTES_Y_REGISTROS_H
#define CONSTANTES_Y_REGISTROS_H

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "../TDAs/list.h"

#define MAXLEN 30
#define PRICELEN 9
#define MAXLINE 1024
#define MAPINITIALCAPAC 41
#define MAPADMINITIALCAPAC 4
#define MSJARMADOCANASTA "            ARMADO DE CANASTA"
#define MSJVISUALIZACIONOFERTA "            OFERTA NACIONAL DE PRODUCTOS"
#define MSJMENUADMINISTRADOR "            MENÚ DEL ADMINISTRADOR"
#define MSJBUSQUEDA1 "            BUSQUEDA DE PRODUCTOS POR NOMBRE"
#define MSJBUSQUEDA2 "            BUSQUEDA DE PRODUCTOS POR RANGO DE PRECIOS"
#define MSJBUSQUEDA3 "            BUSQUEDA DE PRODUCTOS POR SUPERMERCADO"
#define MSJBUSQUEDA31 "Ingrese el nombre del supermercado a buscar: "
#define MSJBUSQUEDA4 "            BUSQUEDA DE PRODUCTOS POR CATEGORÍA"
#define MSJBUSQUEDA41 "Ingrese el nombre de la categoría a buscar: "
#define MSJBUSQUEDASC "            NO HAY COINCIDENCIAS EN LA BÚSQUEDA"
#define MSJBUSQUEDASCP1 "            NO HAY PRODUCTOS ASOCIADOS AL SUPERMERCADO INGRESADO"
#define MSJBUSQUEDASCP2 "            NO HAY PRODUCTOS ASOCIADOS A LA CATEGORÍA INGRESADA"
#define MSJBUSQUEDA5 "            BUSQUEDA DE PRODUCTOS POR NOMBRE PARCIAL"

// MSJBUSQUEDASC: Mensaje de busqueda para los casos en que no haya coincidencias en las búsquedas en mapas.
// MSJBUSQUEDASCP: Mensaje de búsqueda para los casos en que no haya productos en las listas adyacentes.

typedef struct{
    char nombre[MAXLEN + 1];
    char precio[PRICELEN + 1];
    int price;                // Este precio en tipo int fue exclusivamente implementado para la opción de búsqueda por rango de precios.
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
    char supermercado[MAXLEN + 1];
    char precio[PRICELEN + 1];
    size_t cantidad;
}tipoCanasta;

#endif