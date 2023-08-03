#include "importarBaseDeDatos.h"

// Importación de base de datos
/* Esta función importa de los archivos "db_productos.csv", "db_supermercados.csv" y "db_categorias.csv" todos los datos para 
poder manipularlos en la aplicación. Esto, se logra a través de la creación de un token y la función strtok principalmente. 
Primero, se lee línea a línea el archivo de productos, siguiendo el formato del archivo: 
"Nombre,Precio,Categoría,Cantidad de Supermercados,Supermercados", y cada elemento se guarda en las structs respectivas para 
ir almacenandolas en los mapas respectivamente.*/
void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados,
                      HashMap* mapaCategorias, BPlusTree* arbolP,
                      trieTree* trieProductos)
{
    FILE* file_productos = fopen("Base de datos/db_productos2.csv", "r");
    FILE* file_super = fopen("Base de datos/db_supermercados.csv", "r");
    FILE* file_categorias = fopen("Base de datos/db_categorias.csv", "r");
    // Si no se puede abrir alguno de los archivos, el algoritmo termina.
    if (file_productos == NULL || file_super == NULL || file_productos == NULL) { 
        printf("No se pudo abrir los archivos.\n");
        return;
    }
    
    char linea[1024];
    char* token = (char*) malloc(sizeof(MAXLEN + 1)); // El token es una cadena para ir almacenando los elementos de cada línea de los archivos.
    // Archivo de productos
    fgets(linea, sizeof(linea), file_productos); // La primera línea de la base de datos indica el formato de la base de datos.
    
    while (fgets(linea, sizeof(linea), file_productos) != NULL) { // Se lee línea a línea el archivo de productos.
        tipoProducto* nuevoProducto = (tipoProducto*) malloc(sizeof(tipoProducto));
        
        token = strtok(linea, ",");
        strncpy(nuevoProducto->nombre, token, sizeof(nuevoProducto->nombre)); // El primer texto hasta antes de la primera coma de cada línea
                                                                              // es el nombre del producto, y así sucesivamente
        token = strtok(NULL, ",");
        
        strncpy(nuevoProducto->categoria, token, sizeof(nuevoProducto->categoria));
        Pair* parAux = searchMap(mapaCategorias, token);
        
        if (parAux == NULL) // Si la categoría no está en el mapa de categorías, se crea e inserta esa categoría,
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
            pushBack(categoriaExistente->productos, nuevoProducto); // Si la categoría ya estaba en el mapa de categorías, 
                                                                    // simplemente se agrega ese producto a la lista adyacente de esa categoría.
        }
        
        token = strtok(NULL, ",");
        nuevoProducto->cantSupermercados = atoi(token);
        
        nuevoProducto->supermercados = createList();
        nuevoProducto->preciosPorSupermercado = createList();
        
        Pair* parAux2 = (Pair*) malloc(sizeof(Pair)); 
        int cantSupermercados = nuevoProducto->cantSupermercados;
        
        for (unsigned short i = 0; i < cantSupermercados; i++) {
            token = strtok(NULL, ",");
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
                tipoProductoEspecifico* NuevoProductoEspecifico = (tipoProductoEspecifico*) malloc(sizeof(tipoProductoEspecifico));
                strncpy(NuevoProductoEspecifico->nombreProducto, nuevoProducto->nombre, sizeof(NuevoProductoEspecifico->nombreProducto));
                strncpy(NuevoProductoEspecifico->nombreSupermercado, token, sizeof(NuevoProductoEspecifico->nombreSupermercado));
                
                if (i == cantSupermercados - 1)
                    token = strtok(NULL, ".");
                else
                    token = strtok(NULL, ",");
                
                
                strncpy(NuevoProductoEspecifico->precio, token, sizeof(NuevoProductoEspecifico->precio));
                NuevoProductoEspecifico->price = atoi(NuevoProductoEspecifico->precio);
                pushBack(nuevoProducto->preciosPorSupermercado, NuevoProductoEspecifico);
                insertBPlusTree(arbolP, NuevoProductoEspecifico->price, nuevoProducto);
        }
        
        tipoSupermercado *superAux = firstList(nuevoProducto->supermercados);
        for (int i = 1; i < nuevoProducto->cantSupermercados; i++)
        {
            superAux = nextList(nuevoProducto->supermercados);
        }
        insertMap(mapaProductos, nuevoProducto->nombre, nuevoProducto);
        trieNode* rootProductos = getRootTrie(trieProductos);
        insert(rootProductos, nuevoProducto->nombre, nuevoProducto, trieProductos);
    }
    
    fclose(file_productos);
    
    // Archivo de supermercados
    fgets(linea, sizeof(linea), file_super);
    while (fgets(linea, sizeof(linea), file_super) != NULL) {
        // El archivo de supermercados está diseñado tal que en una línea va el nombre del supermercado seguido por un punto.
        token = strtok(linea, ".");
        if (searchMap(mapaSupermercados, token) == NULL) // Si el supermercado del archivo de supermercados no está en el mapa respectivo, se agrega
        {
            tipoSupermercado* nuevoSupermercado2 = (tipoSupermercado*) malloc(sizeof(tipoSupermercado));
            strncpy(nuevoSupermercado2->nombre, token, sizeof(nuevoSupermercado2->nombre));
            nuevoSupermercado2->productos = createList();
            insertMap(mapaSupermercados, nuevoSupermercado2->nombre, nuevoSupermercado2);
        }
    }
    
    fclose(file_super);
    
    // Archivo de categorías
    fgets(linea, sizeof(linea), file_categorias);
    while (fgets(linea, sizeof(linea), file_categorias) != NULL) { // Si la categoría del archivo de categorías no está en el mapa respectivo, se agrega
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


/*La función importarCredencialesAdmin tiene como finalidad importar los RUTs y contraseñas de los administradores de la aplicación.
Esta función se realizó a través del uso de tokens y la función strtok..*/
void importarCredencialesAdmin(HashMap* mapaAdmin)
{
    FILE* file_admin = fopen("Base de datos/credenciales_admin.csv", "r");
    if (file_admin == NULL) 
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char linea[1024];
    char* token;
    fgets(linea, sizeof(linea), file_admin);
    
    while (fgets(linea, sizeof(linea), file_admin) != NULL) 
    {
    tipoAdministrador* nuevoAdmin = (tipoAdministrador*) malloc(sizeof(tipoAdministrador));
     
    token = strtok(linea, ","); // Copia la cadena hasta antes de la coma.
    strncpy(nuevoAdmin->rut, token, sizeof(nuevoAdmin->rut));
    
    token = strtok(NULL, ",");
    strncpy(nuevoAdmin->password, token, sizeof(nuevoAdmin->password));
    nuevoAdmin->password[strcspn(nuevoAdmin->password, "\n")] = '\0';
        
    insertMap(mapaAdmin, nuevoAdmin->rut, nuevoAdmin); // Se inserta en el mapa de administradores el elemento tipoAdministrador con clave el RUT.
    }
    
    fclose(file_admin);
}
