// Creado por: Fernando Rosales Quiñones 1299440

#include <stdio.h>



// Función para verificar si una posición en el matriz es segura para el caballo
// Verifica si el caballo está dentro de los límites del matriz pos_y si la casilla no ha sido visitada previamente
int es_seguro(int pos_x, int pos_y, int F, int matriz[F][F]) {
    return (pos_x >= 0 && pos_x < F && pos_y >= 0 && pos_y < F && matriz[pos_x][pos_y] == -1);
}

// Función para imprimir la solución del recorrido del caballo
// Se imprime el matriz con los colores blanco pos_y amarillo de manera alternada para facilitar la visualización
void imprimir_solucion(int F, int matriz[F][F]) {
    int fila_actual, columna_actual;
    for (fila_actual = 0; fila_actual < F; fila_actual++) {
        for (columna_actual = 0; columna_actual < F; columna_actual++) {
            if ((fila_actual + columna_actual) % 2 == 0)
                printf("%s%2d ", "\x1b[30;47m", matriz[fila_actual][columna_actual]);
            else
                printf("%s%2d ", "\x1b[30;43m", matriz[fila_actual][columna_actual]);
        }
        printf("%s\n", "\x1b[0m"); // Restablecer el color al final de la línea
    }
}

// Función recursiva para realizar el recorrido del caballo mediante backtracking
int recorrido_caballo(int pos_x, int pos_y, int num_movimiento, int F, int matriz[F][F], int dx[], int dy[]) {
    int k, proximo_x, proximo_y;
    if (num_movimiento == F * F) // Condición de parada: si se han realizado todos los movimientos
        return 1;

    // Intentar los 8 movimientos posibles del caballo
    for (k = 0; k < 8; k++) {
        proximo_x = pos_x + dx[k];
        proximo_y = pos_y + dy[k];
        if (es_seguro(proximo_x, proximo_y, F, matriz)) {
            matriz[proximo_x][proximo_y] = num_movimiento; // Marcar la casilla con el número de num_movimiento
            if (recorrido_caballo(proximo_x, proximo_y, num_movimiento + 1, F, matriz, dx, dy))
                return 1; // Si se encuentra solución, retornar
            else
                matriz[proximo_x][proximo_y] = -1; // Backtracking: desmarcar la casilla
        }
    }
    return 0; // No se encontró solución desde esta posición
}

int main() {
    int F = 8; // Tamaño del matriz
    int matriz[F][F];
    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2}; // Posibles movimientos en la dirección pos_x
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1}; // Posibles movimientos en la dirección pos_y

    // Inicialización del matriz con -1 para indicar que las casillas no han sido visitadas
    for (int i = 0; i < F; i++)
        for (int j = 0; j < F; j++)
            matriz[i][j] = -1;

    // Posición inicial del caballo (0,0)
    int pos_x = 0;
    int pos_y = 0;
    matriz[pos_x][pos_y] = 0; // Primer num_movimiento marcado como 0

    // Llamada a la función para iniciar el recorrido del caballo
    if (recorrido_caballo(pos_x, pos_y, 1, F, matriz, dx, dy) == 0) { // Comienza con 1 ya que 0 es el inicio
        printf("No existe solución\n");
    } else {
        imprimir_solucion(F, matriz);
    }

    return 0;
}
