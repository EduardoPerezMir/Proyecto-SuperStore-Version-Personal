#include "importarBaseDeDatos.h"

// Importacion de base de datos

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias, BTree* arbolP) {
    FILE* file_productos = fopen("Base de datos/db_productos.csv", "r");
    FILE* file_super = fopen("Base de datos/db_supermercados.csv", "r");
    FILE* file_categorias = fopen("Base de datos/db_categorias.csv", "r");
    if (file_super == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char linea[1024];
    char* token = (char*) malloc(sizeof(MAXLEN + 1));
    fgets(linea, sizeof(linea), file_productos);
    
    while (fgets(linea, sizeof(linea), file_productos) != NULL) {   
        tipoProducto* nuevoProducto = (tipoProducto*) malloc(sizeof(tipoProducto));

        token = strtok(linea, ",");
        strncpy(nuevoProducto->nombre, token, sizeof(nuevoProducto->nombre));
        
        token = strtok(NULL, ",");
        strncpy(nuevoProducto->precio, token, sizeof(nuevoProducto->precio));
        
        nuevoProducto->price = atoi(nuevoProducto->precio);
        
        token = strtok(NULL, ",");

        strncpy(nuevoProducto->categoria, token, sizeof(nuevoProducto->categoria));
        Pair* parAux = searchMap(mapaCategorias, token);
        
        if (parAux == NULL)
        {
            tipoCategoria* nuevaCategoria = (tipoCategoria*) malloc(sizeof(tipoCategoria));
            strncpy(nuevaCategoria->nombre, token, sizeof(nuevaCategoria->nombre));
            nuevaCategoria->productos = createList();
            pushBack(nuevaCategoria->productos, nuevoProducto);
            insertMap(mapaCategorias, nuevaCategoria->nombre, nuevaCategoria);
        }
        else
        {
            tipoCategoria* categoriaExistente = parAux->value;
            pushBack(categoriaExistente->productos, nuevoProducto);
        }

        
        token = strtok(NULL, ",");
        nuevoProducto->cantSupermercados = atoi(token);
        
        nuevoProducto->supermercados = createList();
        
        Pair* parAux2 = (Pair*) malloc(sizeof(Pair)); 
        int cantSupermercados = nuevoProducto->cantSupermercados;
        for (unsigned short i = 0; i < cantSupermercados; i++) {
            if (i == cantSupermercados - 1)
            {
                token = strtok(NULL, ".");
            }
            else
            {
                token = strtok(NULL, ",");
            }
            parAux2 = searchMap(mapaSupermercados, token);
            if (parAux2 == NULL)
            {
                tipoSupermercado *nuevoSupermercado = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
                strncpy(nuevoSupermercado->nombre, token, sizeof(nuevoSupermercado->nombre));
                pushBack(nuevoProducto->supermercados, nuevoSupermercado);      
                nuevoSupermercado->productos = createList();
                pushBack(nuevoSupermercado->productos, nuevoProducto);
                insertMap(mapaSupermercados, nuevoSupermercado->nombre, nuevoSupermercado);
            }
            else
            {
                tipoSupermercado *supermercadoExistente = parAux2->value;
                pushBack(nuevoProducto->supermercados, supermercadoExistente);
                pushBack(supermercadoExistente->productos, nuevoProducto);
            }
        }
        
        tipoSupermercado *superAux = firstList(nuevoProducto->supermercados);
        for (int i = 1; i < nuevoProducto->cantSupermercados; i++)
        {
            superAux = nextList(nuevoProducto->supermercados);
        }
        insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto);
        insertBTree(arbolP, nuevoProducto->price, nuevoProducto);
    }
    
    fclose(file_productos);
    
    //supermercados
    fgets(linea, sizeof(linea), file_super);
    while (fgets(linea, sizeof(linea), file_super) != NULL) {
        token = strtok(linea, ".");
         
        if (searchMap(mapaSupermercados, token) == NULL)
        {
            tipoSupermercado* nuevoSupermercado2 = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
            strncpy(nuevoSupermercado2->nombre, token, sizeof(nuevoSupermercado2->nombre));
            nuevoSupermercado2->productos = createList();
            insertMap(mapaSupermercados, nuevoSupermercado2->nombre, nuevoSupermercado2);
        }
     }

    fclose(file_super);
    
    //categorias
    fgets(linea, sizeof(linea), file_categorias);
     while (fgets(linea, sizeof(linea), file_categorias) != NULL) {
        token = strtok(linea, ".");
        if (searchMap(mapaCategorias, token) == NULL)
        {
            tipoCategoria* nuevaCategoria2 = (tipoCategoria*) malloc(sizeof(tipoCategoria));
            strncpy(nuevaCategoria2->nombre, token, sizeof(nuevaCategoria2->nombre));
            nuevaCategoria2->productos = createList();
            insertMap(mapaCategorias, nuevaCategoria2->nombre, nuevaCategoria2);
        }
     }

    fclose(file_categorias);
}

void importarCredencialesAdmin(HashMap* mapaAdmin)
{
    FILE* file_admin = fopen("Base de datos/credenciales_admin.csv", "r");
    if (file_admin == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    char linea[1024];
    char* token;
    fgets(linea, sizeof(linea), file_admin);
    
    while (fgets(linea, sizeof(linea), file_admin) != NULL) {
     tipoAdministrador* nuevoAdmin = (tipoAdministrador*) malloc(sizeof(tipoAdministrador));
     
      token = strtok(linea, ",");
     strncpy(nuevoAdmin->rut, token, sizeof(nuevoAdmin->rut));
    
     token = strtok(NULL, ",");
     strncpy(nuevoAdmin->password, token, sizeof(nuevoAdmin->password));
     nuevoAdmin->password[strcspn(nuevoAdmin->password, "\n")] = '\0';
     
      insertMap(mapaAdmin,nuevoAdmin->rut, nuevoAdmin);
    }
    fclose(file_admin);
}
