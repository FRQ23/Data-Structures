//
// Created by Fertronic on 2/29/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_LIMITE 0
#define VERDADERO 1

typedef struct libro
{
    char *nombre;
    char *genero;
    int release_date;
}Libro;

typedef struct elemento
{
    Libro *eLibro;
    struct elemento *sig;
}Elemento;

typedef struct pila
{
    Elemento *cima;
    int longitud;
    int num_elementos;
}Pila;

typedef struct arreglo_pilas
{
    Pila *libros;
    int num_pilas;
} Arreglo_pilas;

///---------------------
//IMPLEMENTAR
Pila* inicializar_caja(void);
void inicializar_pila(Pila *pLibro,int longitud);
void imprimir_pila(Pila *pLibro);
int esta_llena(Pila pLibro);
int esta_vacia(Pila pLibro);
void push(Pila *pLibro,Libro *nuevo);
Libro* pop(Pila *pLibro);
void vaciar_pila(Pila *pLibro);
void apilar_genero(Arreglo_pilas *pila_libros,Libro *eLibro);
void apilar_fecha(Arreglo_pilas *pila_libros,Libro *eLibro, int yearSeleccionado);
///---------------------

int main(void)
{
    int i;
    int option;
    int corre_programa=VERDADERO;
    int yearSeleccionado;
    Pila *caja;
    caja= inicializar_caja();

    Arreglo_pilas pila_libros[2];
    for(i=0;i<2;i++)
    {
        pila_libros[i].libros= malloc(sizeof(Pila));
        pila_libros[i].num_pilas=0;
        inicializar_pila(pila_libros[i].libros,SIN_LIMITE);
    }

    while(corre_programa)
    {
        system("cls"); //WINDOWS
        printf("\n\r [1] MOSTRAR CONTENIDO DE LA CAJA");
        printf("\n\r [2] APILAR POR GENERO");
        printf("\n\r [3] APILAR POR FECHA");
        printf("\n\r [4] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                //MOSTRAR CONTENIDO DE LA CAJA
                imprimir_pila(caja);
                break;
            case 2:
                //REGRESAR LIBROS A LA CAJA
                //SACAR Y APILAR POR GENERO
                while(!esta_vacia(*caja))
                {
                    apilar_genero(&pila_libros[0],pop(caja));
                }
                break;
            case 3:

                printf("Ingrese el año para apilar los libros: ");
                scanf("%d", &yearSeleccionado);

                // Llamada a la función apilar_fecha con el año seleccionado.
                while (!esta_vacia(*caja)) {
                    apilar_fecha(&pila_libros[1], pop(caja), yearSeleccionado);
                }
                break;
            case 4:
                corre_programa=0;
                break;
            default:
                break;
        }
        printf("\n\n\r");
        system("pause"); //WINDOWS
    }
    printf("\n\n\r");
    return 0;
}


Pila* inicializar_caja(void)
{
    char i;
    Pila *caja;
    Libro libros[44] =  {
            {"Cell","Horror",2006},
            {"The Street Lawyer","Thriller",1998},
            {"Nineteen Minutes","Thriller",2007},
            {"Harry Potter y la piedra filosofal","Fantasy",1997},
            {"Armageddon","Post-apocalyptic fiction",2003},
            {"The Jester","Historical fiction",2003},
            {"Harry Potter y el prisionero de Azkaban","Fantasy",1999},
            {"Star Wars: Episode I The Phantom Menace","Science fiction",1999},
            {"Dreamcatcher","Fantasy",2001},
            {"Rainbow Six","Thriller",1998},
            {"Hannibal","Horror",1999},
            {"Twelve Sharp","Crime",2006},
            {"The Bear and the Dragon","Thriller",2000},
            {"The Testament","Adventure Story",1999},
            {"Red Rabbit","Historical fiction",2002},
            {"Anansi Boys","Fantasy",2005},
            {"Airframe","Thriller",1997},
            {"Harry Potter y la camara secreta","Fantasy",1998},
            {"The King of Torts","Thriller",2003},
            {"The Da Vinci Code","Mystery",2003},
            {"Harry Potter y la Orden del Fenix","Fantasy",2003},
            {"Mary, Mary","Crime",2005},
            {"The Summons","Thriller",2002},
            {"Bag of Bones","Horror",1998},
            {"The 5th Horseman","Thriller",2006},
            {"Step on a Crack","Thriller",2007},
            {"Winter's Heart","Fantasy",2000},
            {"Plum Island","Fiction",1997},
            {"Eleven on Top","Crime",2005},
            {"Harry Potter y el misterio del principe","Fantasy",2005},
            {"The Closers","Crime",2005},
            {"Glorious Appearing","Post-apocalyptic fiction",2004},
            {"Prey ","Science fiction",2002},
            {"The Last Juror","Thriller",2004},
            {"'S' Is for Silence","Mystery",2005},
            {"4th of July","Mystery",2005},
            {"Harry Potter y las reliquias de la Muerte","Fantasy",2007},
            {"The Shelters of Stone","Historical fiction",2002},
            {"Harry Potter y el caliz de fuego","Fantasy",2000},
            {"The Dark Tower VII: The Dark Tower","Fantasy",2004},
            {"Book of the Dead ","Crime",2007},
            {"The Dark Tower VI: Song of Susannah","Fantasy",2004},
            {"Cold Mountain","Historical novel",1997},
            {"A Feast for Crows","Fantasy",2005},
    };


    caja = malloc(sizeof(Pila));
    inicializar_pila(caja,44);
    for(i=0;i<44;i++)
    {
        push(caja,&libros[i]);
    }
    return caja;
}

void inicializar_pila(Pila *pLibro,int longitud)
{
    pLibro->cima=NULL;
    pLibro->longitud=longitud;
    pLibro->num_elementos=0;
}

void push(Pila *pLibro, Libro *nuevo)
{
    if (!esta_llena(*pLibro))
    {
        Elemento *nuevo_elemento = malloc(sizeof(Elemento));
        nuevo_elemento->eLibro = nuevo;
        nuevo_elemento->sig = pLibro->cima;
        pLibro->cima = nuevo_elemento;
        pLibro->num_elementos++;
    }
    else
    {
        printf("La pila está llena\n");
    }
}


Libro* pop(Pila *pLibro)
{
    if (!esta_vacia(*pLibro)){
        Elemento *temp = pLibro->cima;
        Libro *libro_pop = temp->eLibro;
        pLibro->cima = temp->sig;
        free(temp);
        pLibro->num_elementos--;
        return libro_pop;
    } else {
        printf("La pila está vacía\n");
        return NULL;
    }
}



void imprimir_pila(Pila *pLibro) {
    Pila auxiliar;
    inicializar_pila(&auxiliar, pLibro->longitud);

    while (!esta_vacia(*pLibro)) {
        Libro *libro_temporal = pop(pLibro);
        push(&auxiliar, libro_temporal);
        printf("Nombre: %s, Género: %s, Año: %d\n", libro_temporal->nombre, libro_temporal->genero, libro_temporal->release_date);
    }

    while (!esta_vacia(auxiliar)) {
        push(pLibro, pop(&auxiliar));
    }

    vaciar_pila(&auxiliar);
}



int esta_llena(Pila pLibro)
{
    return pLibro.num_elementos == pLibro.longitud;
}


int esta_vacia(Pila pLibro)
{

    return pLibro.num_elementos == 0;
}

void vaciar_pila(Pila *pLibro)
{
    while(!esta_vacia(*pLibro)){
        pop(pLibro);
    }
}


void apilar_genero(Arreglo_pilas *pila_libros,Libro *eLibro)
{
    char *genero = eLibro->genero;

    for (int i = 0; i < pila_libros->num_pilas; i++){
        if(strcmp(genero, pila_libros->libros[i].cima->eLibro->genero) == 0){
            push(pila_libros->libros + i, eLibro);
            return;
        }
    }

    if(pila_libros->num_pilas < 2){
        pila_libros->libros[pila_libros->num_pilas].cima = NULL;
        pila_libros->libros[pila_libros->num_pilas].longitud = SIN_LIMITE;
        pila_libros->libros[pila_libros->num_pilas].num_elementos = 0;

        push(pila_libros->libros + pila_libros->num_pilas, eLibro);

        pila_libros->num_pilas++;
    }
}

void apilar_fecha(Arreglo_pilas *pila_libros,Libro *eLibro, int yearSeleccionado)
{
    int fecha = eLibro->release_date;

    for (int i = 0; i < pila_libros->num_pilas; i++) {
        if (fecha == yearSeleccionado) {

            push(pila_libros->libros + i, eLibro);
            return;
        }
    }
    for (int i = 0; i < pila_libros->num_pilas; i++) {

        if (fecha == yearSeleccionado) {

            push(pila_libros->libros + i, eLibro);
            return;
        }
    }
}