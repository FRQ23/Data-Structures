//
// Created by Fernando Rosales on 3/28/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERDADERO 1
#define FALSO 0

typedef struct perro
{
    char nombre[50];
    int edad;
    float altura;
    char genero[20];
    char raza[50];
    char origen_raza[50];
    char tamano[20]; // "chica", "mediana", "grande"
} Perro;

typedef struct nodo
{
    Perro *data;
    struct nodo *siguiente;
} Nodo;

// Función de comparación para la edad en orden ascendente
int compararEdadAsc(Perro *a, Perro *b)
{
    return a->edad - b->edad;
}

// Función de comparación para la edad en orden descendente
int compararEdadDesc(Perro *a, Perro *b)
{
    return b->edad - a->edad;
}

// Función de comparación para la altura en orden ascendente
int compararAlturaAsc(Perro *a, Perro *b)
{
    if (a->altura < b->altura) return -1;
    if (a->altura > b->altura) return 1;
    return 0;
}

// Función de comparación para la altura en orden descendente
int compararAlturaDesc(Perro *a, Perro *b)
{
    if (a->altura < b->altura) return 1;
    if (a->altura > b->altura) return -1;
    return 0;
}

void insertarOrdenado(Nodo **lista, Perro *perro, int (*comparar)(Perro *, Perro *));
void imprimirLista(Nodo *lista);
void liberarLista(Nodo *lista);

int main(void)
{
    char option;
    int corre_programa = VERDADERO;

    Nodo *lista_edad_asc = NULL;
    Nodo *lista_edad_des = NULL;
    Nodo *lista_altura_asc = NULL;
    Nodo *lista_altura_des = NULL;

    // Crear un arreglo de datos (15 perros)
    Perro perros[15] = {
            {"Max", 3, 35.5, "Macho", "Labrador Retriever", "Inglaterra", "grande"},
            {"Luna", 2, 25.0, "Hembra", "Poodle", "Alemania", "mediana"},
            {"Rocky", 4, 40.2, "Macho", "Bulldog Francés", "Francia", "mediana"},
            {"Bella", 1, 20.5, "Hembra", "Chihuahua", "México", "chica"},
            {"Charlie", 5, 30.8, "Macho", "Golden Retriever", "Escocia", "grande"},
            {"Daisy", 2, 22.3, "Hembra", "Beagle", "Inglaterra", "mediana"},
            {"Buddy", 3, 18.7, "Macho", "Shih Tzu", "Tíbet", "chica"},
            {"Molly", 2, 21.1, "Hembra", "Dachshund", "Alemania", "chica"},
            {"Cooper", 4, 32.6, "Macho", "Siberian Husky", "Rusia", "grande"},
            {"Lucy", 1, 15.9, "Hembra", "Yorkshire Terrier", "Inglaterra", "chica"},
            {"Maximus", 6, 37.4, "Macho", "Rottweiler", "Alemania", "grande"},
            {"Lola", 3, 28.0, "Hembra", "Boxer", "Alemania", "mediana"},
            {"Leo", 2, 23.8, "Macho", "Shiba Inu", "Japón", "mediana"},
            {"Sophie", 1, 19.5, "Hembra", "Cavalier King Charles", "Inglaterra", "chica"},
            {"Zeus", 5, 42.1, "Macho", "Great Dane", "Alemania", "grande"}
    };

    while (corre_programa)
    {
        printf("\n\r [1] Lista ordenada por edad ascendente");
        printf("\n\r [2] Lista ordenada por edad descendente");
        printf("\n\r [3] Lista ordenada por altura ascendente");
        printf("\n\r [4] Lista ordenada por altura descendente");
        printf("\n\r [5] Terminar programa");
        printf("\n\n\r Escoge opcion: ");
        scanf(" %c", &option);

        switch (option)
        {
            case '1':
                printf("\n\r Lista ordenada por edad ascendente: ");
                for (int i = 0; i < 15; i++)
                {
                    insertarOrdenado(&lista_edad_asc, &perros[i], compararEdadAsc);
                }
                imprimirLista(lista_edad_asc);
                break;

            case '2':
                printf("\n\r Lista ordenada por edad descendente: ");
                for (int i = 0; i < 15; i++)
                {
                    insertarOrdenado(&lista_edad_des, &perros[i], compararEdadDesc);
                }
                imprimirLista(lista_edad_des);
                break;

            case '3':
                printf("\n\r Lista ordenada por altura ascendente: ");
                for (int i = 0; i < 15; i++)
                {
                    insertarOrdenado(&lista_altura_asc, &perros[i], compararAlturaAsc);
                }
                imprimirLista(lista_altura_asc);
                break;

            case '4':
                printf("\n\r Lista ordenada por altura descendente: ");
                for (int i = 0; i < 15; i++)
                {
                    insertarOrdenado(&lista_altura_des, &perros[i], compararAlturaDesc);
                }
                imprimirLista(lista_altura_des);
                break;

            case '5':
                corre_programa = FALSO;
                printf("\n\r CERRANDO PROGRAMA\n\r");
                break;

            default:
                break;
        }

        printf("Presiona Enter para continuar...");
        while (getchar() != '\n');  // Consumir todos los caracteres hasta el Enter
        system("clear");  // Limpiar la pantalla en sistemas basados en Unix
    }

    // Liberar la memoria de las listas
    liberarLista(lista_edad_asc);
    liberarLista(lista_edad_des);
    liberarLista(lista_altura_asc);
    liberarLista(lista_altura_des);

    return 0;
}

void insertarOrdenado(Nodo **lista, Perro *perro, int (*comparar)(Perro *, Perro *))
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->data = perro;
    nuevoNodo->siguiente = NULL;

    Nodo *actual = *lista;
    Nodo *anterior = NULL;

    while (actual != NULL && comparar(perro, actual->data) > 0)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL)
    {
        nuevoNodo->siguiente = *lista;
        *lista = nuevoNodo;
    }
    else
    {
        anterior->siguiente = nuevoNodo;
        nuevoNodo->siguiente = actual;
    }
}

void imprimirLista(Nodo *lista)
{
    Nodo *actual = lista;
    while (actual != NULL)
    {
        printf("%s (Edad: %d, Altura: %.2f, Raza: %s, Origen: %s, Tamaño: %s)\n",
               actual->data->nombre, actual->data->edad, actual->data->altura,
               actual->data->raza, actual->data->origen_raza, actual->data->tamano);
        actual = actual->siguiente;
    }
    printf("\n\r");
}

void liberarLista(Nodo *lista)
{
    Nodo *actual = lista;
    while (actual != NULL)
    {
        Nodo *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}