#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "hashmap.h"

int enlarge_called=0; 

struct HashMap {
    Pair** buckets;
    long size; 
    long capacity;
    long current;
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

// Funcion hash para obtener el indice
long hash(char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;
    
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash % capacity;
}

void insertMap(HashMap * map, char * key, void * value) {
    if (map->size >= 0.70 * map->capacity)
        enlarge(map);
    
    long indice = hash(key,map->capacity);

    while (map->buckets[indice]!=NULL && map->buckets[indice]->key!=NULL)
    {
        if (strcmp(key,  map->buckets[indice]->key) == 0)    return;
        indice=(indice+1) % map->capacity;
    }

    map->buckets[indice] = createPair(key,value);
    map->current = indice;
    map->size++;
}

void enlarge(HashMap * map) {
    Pair** aux = map->buckets;
    long sizeAux = map->capacity;
    map->capacity *= 2;
    map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair *));
    
    if (map->buckets == NULL) return;
    map->size = 0;
    
    for (long k = 0 ; k < sizeAux ; k++)
    {
        if (aux[k] !=NULL && aux[k]->key != NULL) {
            long indice = hash(aux[k]->key, map->capacity);
            
            while (map->buckets[indice] != NULL && map->buckets[indice]->key != NULL) {
                indice = (indice + 1) % map->capacity;
            }
            
            map->buckets[indice] = createPair(aux[k]->key, aux[k]->value);
            map->size++;
        }
    }
    free(aux);
}



HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    if (map == NULL) return NULL;
    
    map->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
    
    if (map->buckets == NULL) return NULL;
    
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    if (searchMap(map,key) != NULL)
    {
        map->buckets[map->current]->key = NULL;
        map->size--;
        return;
    }
}

// Busca en el mapa segun la clave
Pair * searchMap(HashMap * map,  char * key) {  
    long indice = hash(key,map->capacity);
    while (map->buckets[indice] != NULL && map->buckets[indice]->key != NULL) // Mapea por la clave
    {
        if (strcmp(key, map->buckets[indice]->key) == 0 )
        {
            map->current=indice;
            return map->buckets[indice];
        }
        indice=(indice+1) % map->capacity;    
    }
    
    return NULL;
}

// Retorna el primer elemento del mapa
Pair * firstMap(HashMap * map) {
    for (size_t k = 0;k < map->capacity ; k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current = k;
            return map->buckets[k];
        }
    }
    return NULL;
    
}

Pair * nextMap(HashMap * map) {
    for (size_t k=map->current+1;k<map->capacity;k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
    }
    return NULL;

}

// Si hay productos en el mapa retorna true, sino false
bool areProductsPresents(HashMap * map)
{
    if(map->size == 0) return false;
    return true;
}

// Retorna el tamaño del mapa
long sizeMap(HashMap * map)
{
    return map->size;
}

/*La función destroyNode libera la memoria de un elemento Pair de la tabla hash.*/
void destroyNode(Pair* node) {
    if (node == NULL)
        return;
    
    free(node);
}

/*La función destroyHashMap libera memoria de la tabla hash junto a todos los punteros derivados.*/
void destroyHashMap(HashMap* map)
{
    if (map == NULL)
        return;

    if (map->buckets != NULL)
    {
        for (int i = 0; i < map->size; i++)
        {
            if (map->buckets[i] != NULL) {
                destroyNode(map->buckets[i]);
                map->buckets[i] = NULL;
            }
        }
        
        free(map->buckets);
        map->buckets = NULL;
    }
    
    free(map);
    map = NULL; // Todo después de liberarlo se deja en NULL para efectos del funcionamiento de los algoritmos del programa.
}