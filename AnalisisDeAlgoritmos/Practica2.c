//
// Created by Fernando Rosales on 2/4/25.
//

/*

    Fernando Rosales Quiñones 1299440

    Practica 2


*/


#include <stdio.h>
#include <stdbool.h>
//#include <conio.h>\


//Prototipos de funciones

void asignarBoletos(char cine[9][10], int precios[9], char fila, int asiento, int rows, int cols);
void cancelarVenta(char cine[9][10], char fila, int asiento);
void mostrarMapa(char cine[9][10], int rows, int cols);
void calcularMonto(char cine[9][10], const int precios[9]);
char validarInput();

valiod verga hijo de tu puta madre



void asignarBoletos(char cine[9][10], int precios[9], char fila, int asiento, int rows, int cols) {

    bool lugaresLibres = true;
    //Verificar si hay lugares libres
    // si es d si es disponible y si es x no lo esta

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cine[i][j] == 'd') {
                lugaresLibres = false;
                break;
            }
        }
    }

    if (lugaresLibres) {
        printf("No hay lugares disponibles\n");
        return;
    }

    printf("Seleccione el boletos que desea comprar\n");
    printf("Fila: \n");
    scanf("%c", &fila);
    printf("Asiento: \n1");
    scanf("%d", &asiento);


}


//cancelar venta es lo inverso a asignar boletos, se debe de liberar el asiento y la fila

void cancelarVenta(char cine[9][10], char fila, int asiento) {

    printf("Seleccione el boletos que desea cancelar\n");
    printf("Fila: ");
    scanf("%c", &fila);
    printf("Asiento: ");
    scanf("%d", &asiento);

    cine[fila - 'A'][asiento - 1] = 0;

    printf("Boleto cancelado\n");




}

void mostrarMapa(char cine[9][10], int rows, int cols)
{

    printf("Mapa de asientos\n");

    //imprimir la matriz cine

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", cine[i][j]);
        }
        printf("\n");
    }






}

void calcularMonto(char cine[9][10], const int precios[9]) {

    int total = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            if (cine[i][j] == 0) {
                total += precios[i];
            }
        }
    }

    printf("El monto total es: %d\n", total);



}

int validaDigitos()
{
    char tecla;
    int numero[2], i = 0, j=0, valor =0;
    int ENTER =

    while (tecla != ENTER)
    {
        tecla = getch();

        if(tecla >= '1' && tecla <= '9')
            if(i<2)
            {
                printf("%c", tecla);
                numero[i] = tecla - '0';
                i++;


            }

        if(i>0 && tecla == BACKSPACE)
        {
            printf("\b \b");
            numero[i-1] = 0;
            i--;
        }

    }

    for(j=0; j<i; j++)
    {
        valor = valor * 10 + numero[j];
    }
    return valor;
}




int main(void)
{
    int opcion = 0;

    //Definir matrix de asientos
    // d = disponible
    // x = ocupado

    char cine[9][10] = {
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'},
        {'d', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'}
    };

    int rows = 9;
    int cols = 10;

    int precios[9] = {1000, 750, 500, 300, 300, 300, 300, 300, 300};
    char fila;
    int asiento;

    do
    {
        printf("Menu cinee:\n");
        printf("1. Asignar boletos\n");
        printf("2. Cancelar venta\n");
        printf("3. Mostrar mapa\n");
        printf("4. Calcular monto\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
            case 1:
                asignarBoletos(cine, precios, fila, asiento, rows, cols);
                break;
            case 2:
                cancelarVenta(cine, fila, asiento);
                break;
            case 3:
                mostrarMapa(cine, rows, cols);
                break;
            case 4:
                calcularMonto(cine, precios);
                break;
            default:
                printf("Ponga un input valido porfavor\n");
                break;
        }
    } while (opcion != 5);


}

