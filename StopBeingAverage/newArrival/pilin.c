//
// Created by Fernando Rosales on 3/28/25.
//


#include <stdlib.h>
#include <stdio.h>
#define VERDADERO 1
#define FALSO 0

typedef struct data
{
    int dato;
    char dato_2[48];
    int dato_3;
}Data;

typedef struct nodo
{
    Data *data;
    struct nodo *siguiente;
}Nodo;


// Protitipos de funciones

int ordenarFechaAscendente(Data *a, Data *b);
int ordenarFechaDescendente(Data *a, Data *b);
int ordenarNombreAscendente(Data *a, Data *b);
int ordenarNombreDescendente(Data *a, Data *b);
int ordenarCilindrosAscendente(Data *a, Data *b);
int ordenarCilindrosDescendente(Data *a, Data *b);



int main(void)
{
    char option;
    int num_articulo;
    int corre_programa=VERDADERO;
    //DECLARACION
    Nodo *lista_m1_asc;
    Nodo *lista_m1_des;
    Nodo *lista_m2_asc;
    Nodo *lista_m2_des;

    //CREAR UN ARREGLO DE DATOS, Y ALMACENAR DATOS DE ENTRADA
    Data datos[15] = {
            {1970, "Porsche 917k", 8},
            {1971, "Ferrari 312B", 6},
            {1972, "Lotus 72D", 5},
            {1973, "Lotus 72E", 7},
            {1974, "McLaren M23", 6},
            {1975, "Ferrari 312T", 6},
            {1976, "Ferrari 312T2", 6},
            {1977, "Ferrari 312T2", 6},
            {1978, "Lotus 79", 8},
            {1979, "Ferrari 312T4", 6},
            {1980, "Williams FW07", 6},
            {1981, "Williams FW07", 6},
            {1982, "Ferrari 126C2", 6},
            {1983, "Brabham BT52", 6},
            {1984, "McLaren MP4/2", 6}
    };

    while(corre_programa)
    {
        printf("\n\r [1] Lista ordenada por '_' ascendente");
        printf("\n\r [2] Lista ordenada por '_' descendente");
        printf("\n\r [3] Lista ordenada por '_' ascendente");
        printf("\n\r [4] Lista ordenada por '_' descendente");
        printf("\n\r [5] Terminar programa");
        printf("\n\n\r Escoge opcion: ");
        scanf("%c",&option);
        switch(option)
        {
            case '1':
                printf("\n\r Lista ordenada por '_' ascendente: ");
                //RECORRRER EL ARREGLO DE DATOS Y CREAR UNA LISTA ORDENADA
                printf("\n\r");
                system("pause");
                break;
            case '2':
                printf("\n\r Lista ordenada por '_' descendente: ");
                //RECORRRER EL ARREGLO DE DATOS Y CREAR UNA LISTA ORDENADA
                printf("\n\r");
                system("pause");
                break;
            case '3':
                printf("\n\r Lista ordenada por '_' ascendente: ");
                //RECORRRER EL ARREGLO DE DATOS Y CREAR UNA LISTA ORDENADA
                printf("\n\r");
                system("pause");
                break;
            case '4':
                printf("\n\r Lista ordenada por '_' descendente: ");
                //RECORRRER EL ARREGLO DE DATOS Y CREAR UNA LISTA ORDENADA
                printf("\n\r");
                system("pause");
                break;
            case '5':
                corre_programa=FALSO;
                printf("\n\r CERRANDO PROGRAMA");

                printf("\n\r");
                system("pause");
                break;
            default:
                break;

        }
        system("cls");
    }


    printf("\n\n\n\n\n\r");
    return 0;
}