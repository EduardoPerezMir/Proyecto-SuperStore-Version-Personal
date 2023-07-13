#include "opcionesCanasta.h"

/*Se busca en la lista de la canasta.*/
tipoCanasta* searchListCanasta(List* canasta, char* producto, char* supermercado)
{
    // Con variable tipo current recorremos la lista de elementos de la canasta.
    for (tipoCanasta* current = firstList(canasta);current!=NULL;current=nextList(canasta))
    {
        // Con función strcmp comparamos si el producto a buscar de la canasta coincide con el current, es decir se comparan los nombres de ambos.
        if (strcmp(producto,current->nombre)==0)
            // Si coinciden los nombres del producto, se busca que coincida el supermercado ingresado, si es asi retorna el elemento de la lista encontrado.
            if (strcmp(current->supermercado,supermercado)==0)
                return current;
    }
    return NULL;
}

/*La función armarCanasta se encarga de mostrar y dar a elegir la opción del menú de armado de canasta.*/
void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercados)
{
    int opcion;
    puts(MSJARMADOCANASTA);
    while (1)
    {
        subMenuCanasta();
        printf("Opción: ");
        scanf("%i",&opcion);
        getchar();
        printf("\n");
        // Opciones dependiendo de lo ingresado.
        switch(opcion)
        {
            case 1:
                // Si esta vacia.
                if (isListEmpty(canasta))
                    printf("No existen productos en la canasta\n");
                else printListPC(canasta);
                break;
            case 2:
                agregarProduCanasta(mapaProductos,mapaSupermercados,canasta);
                break;
            case 3:
                eliminarProduCanasta(canasta);
                break; 
            case 0:
                printf("Has salido al menú principal.");
                return;
            default:
            
                printf("Opción no válida.");
                break;
        }
    }
}

/*La función eliminarProduCanasta se encarga de eliminar un producto de la lista de productos de la canasta.*/
void eliminarProduCanasta(List* canasta)
{
    // Si la lista esta vacia finaliza la ejecucion.
    if (isListEmpty(canasta))
    {
        printf("No existen productos en la canasta\n");
        return;
    }
    
    printf("Lista de productos en la canasta\n");
    // Se muestran todos los elementos de la lista.
    printListS(canasta);
    char nomProductoE[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto a eliminar de la canasta: ");
        scanf("%[^\n]s",nomProductoE);
        getchar();
        printf("\n");
    }while(strlen(nomProductoE) > MAXLEN);

    // Se transforma la cadena ingresada a la primera letra mayuscula y demas minusculas para ser buscado luego.
    nomProductoE[0] = toupper(nomProductoE[0]);
    for (char i = 1; nomProductoE[i] != '\0'; i++)
        nomProductoE[i] = tolower(nomProductoE[i]);
    // Variable entro se utiliza para saber si el producto se encuentra o no en la canasta.
    int entro = 0;
    tipoCanasta* currentCanasta = firstList(canasta);
    while (currentCanasta != NULL)//ciclo que recorre canasta
    {
        if (strcmp(currentCanasta->nombre, nomProductoE) == 0)
        {
            printf("El producto %s se ha eliminado de la canasta\n", nomProductoE);
            popCurrent(canasta);
            entro = 1;//quiere decir que el producto ingresado se encuentra
        }
        currentCanasta = nextList(canasta);    
    }
    if (entro == 0)
    {
        printf("El producto %s no se encuentra en la canasta\n",nomProductoE);
        return;
    }
}

/*La función agregarProduCanasta se encarga de agregar un producto a la lista de productos de la canasta.*/
void agregarProduCanasta(HashMap* mapaProductos, HashMap* mapaSupermercados, List* canasta)
{
    printMap(mapaProductos, 0);
    char nomProducto[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto agregar a la canasta: ");
        scanf("%[^\n]s", nomProducto);
        getchar();
        printf("\n");
    }while(strlen(nomProducto) > MAXLEN);
    // Se transforma la cadena ingresada a la primera letra mayuscula y demas minusculas para ser buscado luego
    nomProducto[0] = toupper(nomProducto[0]);
    for (char i = 1; nomProducto[i] != '\0'; i++)
        nomProducto[i] = tolower(nomProducto[i]);
    //se verifica si el producto existe ,si existe se muestran los supermercados
    Pair* current;
    if( (current = searchMap(mapaProductos, nomProducto)) == NULL) {
        printf("El producto a buscar no se encuentra en la base de datos\n");
        return;
    }
    printf("Lista de supermercados que contienen el producto: %s\n", nomProducto);
    printListS(((tipoProducto*) current->value)->supermercados);
        
    char nomSupermercado[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del supermercado que posee el producto agregar a la canasta: ");
        scanf("%[^\n]s",nomSupermercado);
        getchar();
        printf("\n");
    }while(strlen(nomSupermercado) > MAXLEN);
    
    // Se transforma la cadena ingresada a la primera letra mayuscula y demas minusculas para ser buscado luego
    nomSupermercado[0] = toupper(nomSupermercado[0]);
    for (char i = 1; nomSupermercado[i] != '\0'; i++)
    {
        nomSupermercado[i] = tolower(nomSupermercado[i]);
        if (isspace(nomSupermercado[i - 1]))
            nomSupermercado[i] = toupper(nomSupermercado[i]);
    }
    // Si el supermercado no se encuentra en el mapa de supermercados.
    if(searchMap(mapaSupermercados, nomSupermercado) == NULL) {
        printf("El supermercado a buscar no se encuentra en la base de datos\n");
        return;
    }
        
    size_t cantidad=0;
    // Se busca el producto junto al supermercado en la canasta.
    tipoCanasta* productoBuscado = searchListCanasta(canasta, nomProducto, nomSupermercado);
        
    if (productoBuscado == NULL) // Si es null quiere decir que no está.
    {
        printf("Ingrese la cantidad de %s que desea agregar a la canasta: ", nomProducto);
        do {
            scanf("%zd", &cantidad);
        } while(cantidad <= 0);

        // Se crea el tipoCanasta para ser ingresado a la canasta.
        tipoCanasta* elemCanasta = (tipoCanasta *) malloc(sizeof(tipoCanasta));
        strcpy(elemCanasta->nombre,nomProducto);
        strcpy(elemCanasta->supermercado,nomSupermercado);
        strcpy(elemCanasta->precio,((tipoProducto *)current->value)->precio);
        elemCanasta->cantidad=cantidad;
            
        pushBack(canasta,elemCanasta);
        printf("\nEl producto %s del supermercado %s ha sido agregado a la canasta.\n\n", nomProducto, nomSupermercado);
            
    }
    else
    {
        printf("El producto %s se encuentra en la canasta con una cantidad de %zd\n", nomProducto, productoBuscado->cantidad);
        // Si el producto se encuentra en la canasta se despliega un submenu para confirma la accion del usuario.
        subMenuCanastaCantidad();
        unsigned short opcion = 0;
        do{
            scanf("%hu",&opcion);
        }while(opcion!=1 && opcion!=2);
        
        if (opcion == 2) return;
        
        printf("Ingrese la cantidad ha agregar: ");
        do{
            scanf("%zd",&cantidad);
        }while(cantidad<=0);
        productoBuscado->cantidad+=cantidad;
        printf("La cantidad actual de %s en la canasta es %zd\n", nomProducto, productoBuscado->cantidad);
    }  
}

/* La función printListPC se encarga de realizar una impresion de la canasta con informacion de productos y total a pagar.*/
void printListPC(List* Super) {
    tipoCanasta* current = firstList(Super);
    int cont = 1;
    size_t pagar = 0;
    size_t precioTotalProduc;

    printf("┌────────────────────────────────────────────────┐\n");
    while(current != NULL) {
        precioTotalProduc = atol(current->precio)*current->cantidad;
        printf(" %d. Producto: %s\n Supermercado: %s\n Cantidad: %zd\n Precio unitario: $%s Precio total: $%zd\n\n",cont,current->nombre,current->supermercado,current->cantidad,current->precio,precioTotalProduc);
        cont++;
        pagar = pagar + precioTotalProduc;
        current = nextList(Super);
    }
    printf(" Total a pagar: $%zd\n",pagar);
    printf("└────────────────────────────────────────────────┘\n\n");
}
