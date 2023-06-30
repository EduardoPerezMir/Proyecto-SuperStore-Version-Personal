#include <stdio.h>
#include "Funciones/constantesYRegistros.h"
#include "Funciones/importarBaseDeDatos.h"
#include "Funciones/mostrarElementosSistema.h"
#include "Funciones/mostrarMenus.h"
#include "Funciones/opcionesAdmin.h"
#include "Funciones/opcionesCanasta.h"
#include "Funciones/busquedas.h"
#include "Funciones/adjacentListsDestroyer.h"

int main(void) {
    HashMap* mapaProductos = createMap(MAPINITIALCAPAC);
    HashMap* mapaSupermercados = createMap(MAPINITIALCAPAC);
    HashMap* mapaCategorias = createMap(MAPINITIALCAPAC);
    BTree* arbolProductos = createBTree(1 + MAPINITIALCAPAC / 6); // Debe ser impar
    
    HashMap* mapaAdmin = createMap(MAPADMINITIALCAPAC);
    
    importarDatosCSV(mapaProductos, mapaSupermercados, mapaCategorias, arbolProductos);
    importarCredencialesAdmin(mapaAdmin);
    List* canasta = createList();
    int opcion;
    
    printLogo();
    do {
        mostrarOpciones();
        printf("Opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');
        switch (opcion) {
            case 1:
                armarCanasta(canasta,mapaProductos,mapaSupermercados);
                break;
            case 2:
                mostrarOfertaNacional(mapaProductos);
                break;
            case 3:
            {
                busquedaProductosDirecta(mapaProductos);
                break;
            }
            case 4:
            {
                busquedaPorPrecio(arbolProductos);
                break;
            }   
            case 5:
            {
                busquedaProductosAdyacentes(mapaSupermercados, 1);
                break;
            }       
            case 6:
            {
                busquedaProductosAdyacentes(mapaCategorias, 2);
                break;
            }
            case 7:
            {
                if(loginAdmin(mapaAdmin) != 0)
                   menuAdmin(mapaProductos,mapaSupermercados,mapaCategorias);
                break;
            }        
            case 0:
            {
                printf("CERRANDO EL PROGRAMA...\n");
                break;
            }
            default:
            {
                printf("INGRESE UNA OPCIÓN VÁLIDA.");
            }    
        }
    } while (opcion != 0);
    
    destroyAllAdjacentListsProductos(mapaProductos);
    destroyAllAdjacentListsSupermercados(mapaSupermercados);
    destroyAllAdjacentListsCategorias(mapaCategorias);
    destroyAllAdjacentListsBTree(getRoot(arbolProductos));
    
    destroyHashMap(mapaProductos);
    destroyHashMap(mapaSupermercados);
    destroyHashMap(mapaCategorias);
    destroyHashMap(mapaAdmin);

    destroyBTree(getRoot(arbolProductos));
    destroyBTree(arbolProductos);

    return 0;
}
