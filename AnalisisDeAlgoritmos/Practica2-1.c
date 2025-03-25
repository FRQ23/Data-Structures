/*
 *  Alumno: Fernando Rosales Quiñones
 *  Matricula: 1299440
 */



#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Prototipos de funciones
void asignarBoletos(char cine[9][10], int precios[9], int rows, int cols);
void cancelarVenta(char cine[9][10]);
void mostrarMapa(char cine[9][10], int rows, int cols);
void calcularMonto(char cine[9][10], const int precios[9]);
char validarFila();
int validarAsiento();

char validarFila() {
    char tecla;
    while (1) {
        tecla = getchar();
        tecla = toupper(tecla);
        if (tecla >= 'A' && tecla <= 'I') {
            printf("%c", tecla);
            return tecla;
        } else if (tecla == '\n') {
            break;
        }
    }
    return 0;
}

int validarAsiento() {
    char tecla;
    int numero[2] = {0}, i = 0, j, valor = 0;

    while (1) {
        tecla = getchar();
        if (tecla == '\n' && i > 0) break;

        if (tecla >= '1' && tecla <= '9') {
            if (i < 2) {
                printf("%c", tecla);
                numero[i] = tecla - '0';
                i++;
            }
        } else if (i > 0 && tecla == 8) {  //retroceso
            printf("\b \b");
            i--;
            numero[i] = 0;
        }
    }

    for (j = 0; j < i; j++) {
        valor = valor * 10 + numero[j];
    }
    return valor;
}

void asignarBoletos(char cine[9][10], int precios[9], int rows, int cols) {
    bool disponible = false;
    for (int i = 0; i < rows && !disponible; i++) {
        for (int j = 0; j < cols; j++) {
            if (cine[i][j] == 'd') {
                disponible = true;
                break;
            }
        }
    }
    if (!disponible) {
        printf("No hay asientos disponibles \n");
        return;
    }

    char fila;
    int asiento;
    bool valido = false;

    while (!valido) {
        printf("\nFila (A-I): ");
        fila = validarFila();

        if (fila) {
            printf("\nAsiento (1-10): ");
            asiento = validarAsiento();
            printf("\n");

            if (asiento >= 1 && asiento <= 10) {
                int filaIdx = fila - 'A';
                int asientoIdx = asiento - 1;

                if (cine[filaIdx][asientoIdx] == 'd') {
                    cine[filaIdx][asientoIdx] = 'x';
                    printf("Asiento %c%d asignado \n", fila, asiento);
                    valido = true;
                } else {
                    printf("Asiento ocupado\n");
                }
            } else {
                printf("Asiento no valido\n");
            }
        }
    }
}

void cancelarVenta(char cine[9][10]) {
    char fila;
    int asiento;
    bool valido = false;

    while (!valido) {
        printf("\nFila (A-I): ");
        fila = validarFila();

        if (fila) {
            printf("\nAsiento (1 al 10): ");
            asiento = validarAsiento();
            printf("\n");

            if (asiento >= 1 && asiento <= 10) {
                int filaIdx = fila - 'A';
                int asientoIdx = asiento - 1;

                if (cine[filaIdx][asientoIdx] == 'x') {
                    cine[filaIdx][asientoIdx] = 'd';
                    printf("Venta cancelada en %c%d \n", fila, asiento);
                    valido = true;
                } else {
                    printf("Asiento %c%d no esta ocupado \n", fila, asiento);
                }
            } else {
                printf("Asiento no valido \n");
            }
        }
    }
}

void mostrarMapa(char cine[9][10], int rows, int cols) {
    printf("\n   ");
    for (int j = 0; j < cols; j++) printf("%2d ", j + 1);
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < cols; j++) {
            printf("%2c ", cine[i][j]);
        }
        printf("\n");
    }
}

void calcularMonto(char cine[9][10], const int precios[9]) {
    int total = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 10; j++) {
            if (cine[i][j] == 'x') total += precios[i];
        }
    }
    printf("\nMonto total vendido: $%d\n ", total);
}

int main() {
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
    int precios[9] = {1000, 750, 500, 300, 300, 300, 300, 300, 300};
    char opcion;
    bool continuar = true;

    while (continuar) {
        printf("\n1. Asignar boleto \n2. Cancelar venta \n3. Mostrar mapa \n4. Calcular monto\n5. Salir \nOpcion: ");
        opcion = getchar();
        getchar();

        switch (opcion) {
            case '1':
                asignarBoletos(cine, precios, 9, 10);
                break;
            case '2':
                cancelarVenta(cine);
                break;
            case '3':
                mostrarMapa(cine, 9, 10);
                break;
            case '4':
                calcularMonto(cine, precios);
                break;
            case '5':
                continuar = false;
                break;
            default:
                printf("Opcion invalida \n");
        }
    }

    return 0;
}
