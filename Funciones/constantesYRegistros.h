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
#define MAPINITIALCAPAC 41
#define MAPADMINITIALCAPAC 4
#define MSJARMADOCANASTA "            ARMADO DE CANASTA"
#define MSJVISUALIZACIONOFERTA "            OFERTA NACIONAL DE PRODUCTOS"
#define MSJMENUADMINISTRADOR "            MENÚ DEL ADMINISTRADOR"
#define MSJBUSQUEDA1 "            BUSQUEDA DE PRODUCTOS POR NOMBRE"
#define MSJBUSQUEDA2 "            BUSQUEDA DE PRODUCTOS POR RANGO DE PRECIOS"
#define MSJBUSQUEDA3 "            BUSQUEDA DE PRODUCTOS POR SUPERMERCADO"
#define MSJBUSQUEDA31 "            INGRESE EL NOMBRE DEL SUPERMERCADO A BUSCAR"
#define MSJBUSQUEDA4 "            BUSQUEDA DE PRODUCTOS POR CATEGORÍA"
#define MSJBUSQUEDA41 "            INGRESE EL NOMBRE DE LA CATEGORÍA A BUSCAR"
#define MSJBUSQUEDASC "            NO HAY COINCIDENCIAS EN LA BÚSQUEDA"
// MSJBUSQUEDASC: Mensaje de busqueda para los casos en que no haya coincidencias.

typedef struct{
    char nombre[MAXLEN + 1];
    char precio[PRICELEN + 1];
    int price;
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