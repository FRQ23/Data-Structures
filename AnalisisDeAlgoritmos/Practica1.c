//
// Created by Fertronic on 8/26/2024.
//

/*

 • Elabora los algoritmos que se piden a continuación y luego analiza su
complejidad.
    • Escribe una función que reciba como parámetro 2 arreglos, y que imprima
    sólo aquellos valores que se encuentren en ambos arreglos.
    • Escribe una función que reciba como parámetro 2 arreglos, y que imprima
    sólo aquellos elementos que están en el primer arreglo, pero que no están en
    el segundo arreglo.
    • Escribe una función que reciba como parámetro 2 arreglos, y que imprima
    todos los elementos que no estén en el primer arreglo.
*/

#include <stdio.h>
//#include <stdlib.h>

// Escribe una función que reciba como parámetro 2 arreglos, y que imprima
//    sólo aquellos valores que se encuentren en ambos arreglos.
void coinciden(int arreglo1[], int arreglo2[]){
    //Se hace un ciclo para "recorrer" el arreglo 1.
    for (int i = 0; i < 10; i++){
        //Se hace un ciclo para "recorrer" el arreglo 2.
        for (int j = 0; j < 10; j++){
            //Si el valor del arreglo 1 es igual al valor del arreglo 2, se imprime el valor
            if (arreglo1[i] == arreglo2[j]){
                printf("%d\n", arreglo1[i]);
            }
        }
    }
}

// Escribe una función que reciba como parámetro 2 arreglos, y que imprima
//    sólo aquellos elementos que están en el primer arreglo, pero que no están en
//    el segundo arreglo.
void coinciden2(int arreglo1[], int arreglo2[]){
    //Se hace un ciclo para "recorrer" el arreglo 1.
    for (int i = 0; i < 10; i++){
        //Se hace un ciclo para "recorrer" el arreglo 2.
        for (int j = 0; j < 10; j++){
            //Si el valor del arreglo 1 es igual al valor del arreglo 2, se imprime el valor
            if (arreglo1[i] == arreglo2[j]){
                break;
            }
            //Si el valor del arreglo 1 no es igual al valor del arreglo 2, se imprime el valor
            if (j == 9){
                printf("%d\n", arreglo1[i]);
            }
        }
    }
}

//Escribe una función que reciba como parámetro 2 arreglos, y que imprima
//    todos los elementos que no estén en el primer arreglo.

void coinciden3(int arreglo1[], int arreglo2[]){
    //Se hace un ciclo para "recorrer" el arreglo 2.
    for (int i = 0; i < 10; i++){
        //Se hace un ciclo para "recorrer" el arreglo 1.
        for (int j = 0; j < 10; j++){
            //Si el valor del arreglo 2 es igual al valor del arreglo 1, se imprime el valor
            if (arreglo2[i] == arreglo1[j]){
                break;
            }
            //Si el valor del arreglo 2 no es igual al valor del arreglo 1, se imprime el valor
            if (j == 9){
                printf("%d\n", arreglo2[i]);
            }
        }
    }
}

//Bloque main, se definen los arreglos y se piden los valores de estos
int main (){
    //definición de variables
    int arreglo1[10];
    int arreglo2[10];

    //Se piden los valores de los arreglos

    printf("Ingresa los valores del primer arreglo\n");
    for (int i = 0; i < 10; i++){
        scanf("%d \n", &arreglo1[i]);
    }

    printf("Ingresa los valores del segundo arreglo\n");
    for (int i = 0; i < 10; i++){
        scanf("%d \n", &arreglo2[i]);
    }

    //Se imprime el mensaje y se llama a la función coinciden dando como parametro los arreglos
    printf("Los valores que coinciden son (primer ejercicio):\n");
    coinciden(arreglo1, arreglo2);

    printf("Los valores que coinciden son (segundo ejercicio):\n");
    coinciden2(arreglo1, arreglo2);

    printf("Los valores que coinciden son (tercer ejercicio):\n");
    coinciden3(arreglo1, arreglo2);

}