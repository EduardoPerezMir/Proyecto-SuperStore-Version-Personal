#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "list.h"
#include "funciones_answer.h"

void mostrarOpciones()
{
    printf("*****************************************************************\n");
    printf("1. INGRESE 1 SI DESEA ARMAR CANASTA CON PRODUCTOS A COMPRAR\n");
    printf("2. INGRESE 2 SI DESEA \n");
    printf("3. INGRESE 3 SI DESEA \n");
    printf("4. INGRESE 4 SI DESEA \n");
    printf("5. INGRESE 5 SI DESEA \n");
    printf("6. INGRESE 6 SI DESEA \n");
    printf("7. INGRESE 0 SI DESEA SALIR\n");
    

    printf("*****************************************************************\n\n");
    
}

void mostrarMenu()
{
    int opcion;
    do {
        printf("\n");
        mostrarOpciones();
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
            break;
        case 6:
            printf("OPCION 6 INGRESADA\n\n");

            break;
        case 0:
            printf("CERRANDO EL PROGRAMA...\n");
        }
    } while (opcion != 0);
}