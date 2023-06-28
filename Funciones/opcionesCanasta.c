#include "opcionesCanasta.h"


tipoCanasta* searchListCanasta(List* canasta,char* producto,char* supermercado)
{
    for (tipoCanasta* current=firstList(canasta);current!=NULL;current=nextList(canasta))
    {
        if (strcmp(producto,current->nombre)==0)
            if (strcmp(current->supermercado,supermercado)==0)
                return current;
    }
    return NULL;
}

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
        switch(opcion)
        {
            case 1:
            {
                if (isListEmpty(canasta))
                    printf("No existen productos en la canasta\n");
                else printListPC(canasta);
                break;
            }
            case 2:
            {
                agregarProduCanasta(mapaProductos,mapaSupermercados,canasta);
                break;
            }
            case 3:
            {
                eliminarProduCanasta(canasta);
                break; 
            }
            case 0:
            {
                printf("Has salido al menú principal.");
                return;
            }
            default:
            {
                printf("Opción no válida.");
                break;
            }
        }
    }
}

void eliminarProduCanasta(List* canasta)
{
    if (isListEmpty(canasta))
    {
        printf("No existen productos en la canasta\n");
        return;
    }
    printf("Lista de productos en la canasta\n");
    printListS(canasta);
    char nomProductoE[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto a eliminar de la canasta: ");
        scanf("%[^\n]s",nomProductoE);
        getchar();
        printf("\n");
    }while(strlen(nomProductoE) > MAXLEN);

    nomProductoE[0] = toupper(nomProductoE[0]);
    for (char i = 1; nomProductoE[i] != '\0'; i++)
        nomProductoE[i] = tolower(nomProductoE[i]);
    
    int entro  = 0;
    tipoCanasta* currentCanasta = firstList(canasta);
    while (currentCanasta != NULL)
    {
        if (strcmp(currentCanasta->nombre, nomProductoE) == 0)
        {
            printf("El producto %s se ha eliminado de la canasta\n", nomProductoE);
            popCurrent(canasta);
            entro = 1;
        }
        currentCanasta = nextList(canasta);    
    }
    if (entro == 0)
    {
        printf("El producto %s no se encuentra en la canasta\n",nomProductoE);
        return;
    }
}

void agregarProduCanasta(HashMap* mapaProductos,HashMap* mapaSupermercados,List* canasta)
{
    printMap(mapaProductos);
    char nomProducto[MAXLEN + 1];
    do{
        printf("Ingrese el nombre del producto agregar a la canasta: ");
        scanf("%[^\n]s", nomProducto);
        getchar();
        printf("\n");
    }while(strlen(nomProducto) > MAXLEN);

    nomProducto[0] = toupper(nomProducto[0]);
    for (char i = 1; nomProducto[i] != '\0'; i++)
        nomProducto[i] = tolower(nomProducto[i]);
    
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

    nomSupermercado[0] = toupper(nomSupermercado[0]);
    for (char i = 1; nomSupermercado[i] != '\0'; i++)
    {
        nomSupermercado[i] = tolower(nomSupermercado[i]);
        if (isspace(nomSupermercado[i - 1]))
            nomSupermercado[i] = toupper(nomSupermercado[i]);
    }
    
    if(searchMap(mapaSupermercados, nomSupermercado) == NULL) {
        printf("El supermercado a buscar no se encuentra en la base de datos\n");
        return;
    }
        
    size_t cantidad=0;
    tipoCanasta* productoBuscado = searchListCanasta(canasta, nomProducto, nomSupermercado);
        
    if (productoBuscado == NULL) //Si es null quiere decir que no está.
    {
        printf("Ingrese la cantidad de %s que desea agregar a la canasta: ", nomProducto);
        do {
            scanf("%zd", &cantidad);
        } while(cantidad <= 0);
    
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
        subMenuCanastaCantidad();
        unsigned short opcion=0;
        do{
            scanf("%hu",&opcion);
        }while(opcion!=1 && opcion!=2);
        if (opcion == 2)return;
        printf("Ingrese la cantidad ha agregar: ");
        do{
            scanf("%zd",&cantidad);
        }while(cantidad<=0);
        productoBuscado->cantidad+=cantidad;
        printf("La cantidad actual de %s en la canasta es %zd\n", nomProducto, productoBuscado->cantidad);
    }  
}

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
