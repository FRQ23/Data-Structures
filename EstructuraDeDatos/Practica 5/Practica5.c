//
// Created by que te importa metiche on 4/8/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
    int dato;
    struct nodo * izquierda;
    struct nodo * derecha;
}nodo;

nodo* agregar_nodo(nodo *raiz, int dato)
{
    if(raiz == NULL)
    {
        raiz = (nodo*)malloc(sizeof(nodo));
        raiz->dato = dato;
        raiz->izquierda = raiz->derecha = NULL;

    }
    else if(dato <= raiz->dato)
    {
        raiz->izquierda = agregar_nodo(raiz->izquierda, dato);
    }
    else if(dato > raiz->dato)
    {
        raiz->derecha = agregar_nodo(raiz->derecha, dato);
    }
    return raiz;
}

int sacar_nivel(nodo *raiz, int dato, int nivel)
{
    if(raiz == NULL)
    {
        return -1;
    }
    if(raiz->dato == dato)
    {
        return nivel;
    }
    int izquierda = sacar_nivel(raiz->izquierda, dato, nivel+1);
    if (izquierda != -1)
    {
        return izquierda;
    }
    return sacar_nivel(raiz->derecha, dato, nivel+1);
}

int cantidad_elementos(nodo *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    return 1 + cantidad_elementos(raiz->izquierda) + cantidad_elementos(raiz->derecha);
}

int sacar_profundidad(nodo *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    int profundidadIzquierda = sacar_profundidad(raiz->izquierda);
    int profundidadDerecha = sacar_profundidad(raiz->derecha);
    return(profundidadIzquierda > profundidadDerecha) ? profundidadIzquierda + 1 : profundidadDerecha + 1;
}

void print_arbol(nodo* raiz, int espacio)
{
    if(raiz == NULL)
    {
        return;
    }

    espacio += 10;

    print_arbol(raiz->derecha, espacio);

    printf("\n");
    for (int i = 10; i < espacio; i++)
    {
        printf(" ");
    }
    printf("%d\n", raiz->dato);

    print_arbol(raiz->izquierda, espacio);
}

int main(){

    nodo *raiz = NULL;
    int num;

    printf("Ingrese numeros enteros, n para terminar: ");
    while(1){
        char c;
        if(scanf("%d", &num) == 1){
            raiz = agregar_nodo(raiz, num);
        }else if(scanf("%c", &c) == 1 && c == 'n'){
            break;
        }

        raiz = agregar_nodo(raiz, num);
    }

    printf("Nivel: %d\n", sacar_nivel(raiz, 7, 1));
    printf("Cantidad de elementos: %d\n", cantidad_elementos(raiz));
    printf("Profundidad: %d\n", sacar_profundidad(raiz));

    print_arbol(raiz, 0);

    return 0;
}