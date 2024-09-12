//
// Created by Fernando Rosales on 9/12/24.
//

#include <stdio.h>

int main(void)
{
    int edad;
    char nombre [10];

    printf("Introduce tu edad: \n");
    scanf("%d", &edad);

    printf("Introduce tu nombre: \n");
    scanf("%s", nombre);

    printf("Hola %s tu edad es: %d", nombre, edad);

    return 0;
}