#include "mostrarMenus.h"

// Muestra Menu principal
void mostrarOpciones()
{
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA ARMAR CANASTA CON PRODUCTOS A COMPRAR ║\n");
    printf("║ 2. INGRESE 2 SI DESEA MOSTRAR TODOS LOS PRODUCTOS           ║\n");
    printf("║ 3. INGRESE 3 SI DESEA BUSCAR PRODUCTO POR NOMBRE            ║\n");
    printf("║ 4. INGRESE 4 SI DESEA MOSTRAR PRODUCTO POR PRECIO           ║\n");
    printf("║ 5. INGRESE 5 SI DESEA MOSTRAR PRODUCTO POR SUPERMERCADO     ║\n");
    printf("║ 6. INGRESE 6 SI DESEA MOSTRAR PRODUCTO POR CATEGORIA        ║\n");
    printf("║ 7. INGRESE 7 SI DESEA INICIAR SESION COMO ADMINISTRADOR     ║\n");
    printf("║ 8. INGRESE 0 SI DESEA SALIR                                 ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
}

// Muestra menu administrador
void mostrarMenuAdmin()
{
   printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA AGREGAR PRODUCTOS                     ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR SUPERMERCADOS                 ║\n");
    printf("║ 3. INGRESE 3 SI DESEA AGREGAR CATEGORIA                     ║\n");
    printf("║ 4. INGRESE 4 SI DESEA QUITAR PRODUCTOS                      ║\n");
    printf("║ 5. INGRESE 5 SI DESEA SALIR AL MENU PRINICIPAL              ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
    printf("Opción: ");
}


// Muestra submenu armar canasta al ingresar opción "1"
void subMenuCanasta() {
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA VER TODOS PRODUCTOS DE LA CANASTA.    ║\n");
    printf("║ 2. INGRESE 2 SI DESEA AGREGAR PRODUCTOS A LA CANASTA.       ║\n");
    printf("║ 3. INGRESE 3 SI DESEA ELIMINAR PRODUCTOS DE LA CANASTA.     ║\n");
    printf("║ 4. INGRESE 0 SI DESEA SALIR AL MENÚ PRINCIPAL.              ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
}

// Muestra submenu en el submenu de armar canasta al momento de ingresar un producto este ya se encuentra
void subMenuCanastaCantidad()
{
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                                                             ║\n");
    printf("║ 1. INGRESE 1 SI DESEA AUMENTAR LA CANTIDAD EN LA CANASTA    ║\n");
    printf("║ 2. INGRESE 2 SI DESEA SALIR                                 ║\n");
    printf("║                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n\n");
    printf("Opción: ");
}


// El logo de SuperStore (se imprime por pantalla al comenzar la ejecución de la aplicación).
void printLogo(){
    FILE *fptr = fopen("Base de datos/image.txt","r");
    char read_string[MAXLEN];
     
    while(fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s",read_string);
            
    fclose(fptr);
}