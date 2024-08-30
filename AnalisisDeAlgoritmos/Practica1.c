#include <stdio.h>

// Función que imprime los valores que se encuentran en ambos arreglos
void coinciden(int arreglo1[], int tam1, int arreglo2[], int tam2){
    for (int i = 0; i < tam1; i++){
        for (int j = 0; j < tam2; j++){
            if (arreglo1[i] == arreglo2[j]){
                printf("%d\n", arreglo1[i]);
                break;  // Para evitar imprimir valores duplicados
            }
        }
    }
}

// Función que imprime los valores que están en el primer arreglo, pero no en el segundo
void coinciden2(int arreglo1[], int tam1, int arreglo2[], int tam2){
    for (int i = 0; i < tam1; i++){
        int encontrado = 0;
        for (int j = 0; j < tam2; j++){
            if (arreglo1[i] == arreglo2[j]){
                encontrado = 1;
                break;
            }
        }
        if (!encontrado){
            printf("%d\n", arreglo1[i]);
        }
    }
}

// Función que imprime los valores que están en el segundo arreglo pero no en el primero
void coinciden3(int arreglo1[], int tam1, int arreglo2[], int tam2){
    for (int i = 0; i < tam2; i++){
        int encontrado = 0;
        for (int j = 0; j < tam1; j++){
            if (arreglo2[i] == arreglo1[j]){
                encontrado = 1;
                break;
            }
        }
        if (!encontrado){
            printf("%d\n", arreglo2[i]);
        }
    }
}

// Función principal
int main (){
    int tam1 = 6;  // Tamaño del primer arreglo
    int tam2 = 5;  // Tamaño del segundo arreglo
    int arreglo1[tam1];
    int arreglo2[tam2];

    // Leer los valores del primer arreglo
    printf("Ingresa los valores del primer arreglo\n");
    for (int i = 0; i < tam1; i++){
        scanf("%d", &arreglo1[i]);
    }

    // Leer los valores del segundo arreglo
    printf("Ingresa los valores del segundo arreglo\n");
    for (int i = 0; i < tam2; i++){
        scanf("%d", &arreglo2[i]);
    }

    // Llamadas a las funciones
    printf("Los valores que coinciden son (primer ejercicio):\n");
    coinciden(arreglo1, tam1, arreglo2, tam2);

    printf("Los valores que están en el primer arreglo pero no en el segundo son (segundo ejercicio):\n");
    coinciden2(arreglo1, tam1, arreglo2, tam2);

    printf("Los valores que están en el segundo arreglo pero no en el primero son (tercer ejercicio):\n");
    coinciden3(arreglo1, tam1, arreglo2, tam2);

    return 0;
}
