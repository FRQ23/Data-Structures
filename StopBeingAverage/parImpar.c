//
// Created by Fernando Rosales on 9/12/24.
//

/*
#include <stdio.h>

int main(void)
{

    int numero, resto;

    printf("Ingrese un numero: ");
    scanf("%d", &numero);

    resto = numero % 2;

    if(resto == 0)
    {
        printf("El numero %d es par.\n" ,numero);
    }else
    {
        printf("El numero %d es impar. \n",numero);
    }

    return 0;
}

*/


#include <stdio.h>


int es_par(int numero)
{
    int resto;

    resto = numero%2;


    if (resto == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main (void)
{
    int numero;

    int resultado;

    printf("Ingrese un numero: ");
    scanf("%d", &numero);

    resultado = es_par(numero);

    if (resultado == 1)
    {
        printf("Tu numero %d es par. \n", numero);
    }else
    {
        printf("Tu numero %d es impar. \n", numero);
    }


    return 0;
}
