//
// Created by que te importa metiche on 2/29/2024.
//

#include "Pila.h"

int main(){

    Pila miPila = crearPila();

    push(&miPila, 10);

    printf("El valor del tope es: %d \n", miPila.tope);
    printf("El valor dentro del tope es: %d \n", miPila.lista[miPila.tope-1]);

    push(&miPila, 12);
    push(&miPila, 13);
    push(&miPila, 14);

    printf("El valor del tope es: %d \n", miPila.tope);
    printf("El valor dentro del tope es: %d\n", top(miPila));

    int valor = pop(&miPila);
    printf("Valor: %d \n" ,valor);
    printf("El valor del tope es: %d \n", miPila.tope);
    printf("El valor dentro del tope es: %d\n", top(miPila));

    pop(&miPila);
    pop(&miPila);
    pop(&miPila);
    pop(&miPila);

}