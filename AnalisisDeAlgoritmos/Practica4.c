// Fernando Rosales Quiñones 1299440

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para los aspirantes
typedef struct {
    char nombre[100];
    char fechaNacimiento[11];
    char lugarNacimiento[100];
    char curp[19];
    int diaExamen;
} Aspirante;

// Función para asignar día de examen basado en la inicial del apellido
int asignarDiaExamen(char *nombreCompleto) {
    char apellido[50];
    sscanf(nombreCompleto, "%s", apellido);
    char inicial = apellido[0];

    if ((inicial >= 'A' && inicial <= 'F') || (inicial >= 'a' && inicial <= 'f'))
        return 1;
    if ((inicial >= 'G' && inicial <= 'L') || (inicial >= 'g' && inicial <= 'l'))
        return 2;
    if ((inicial >= 'M' && inicial <= 'Z') || (inicial >= 'm' && inicial <= 'z'))
        return 3;
    return 1; // Valor por defecto
}

// Función para Merge Sort
void merge(Aspirante arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Aspirante *L = (Aspirante *)malloc(n1 * sizeof(Aspirante));
    Aspirante *R = (Aspirante *)malloc(n2 * sizeof(Aspirante));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].curp, R[j].curp) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Merge Sort por CURP
void mergeSort(Aspirante arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Función Heapify para Min Heap
void heapify(Aspirante arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (arr[left].diaExamen < arr[smallest].diaExamen ||
                     (arr[left].diaExamen == arr[smallest].diaExamen &&
                      strcmp(arr[left].nombre, arr[smallest].nombre) < 0)))
        smallest = left;

    if (right < n && (arr[right].diaExamen < arr[smallest].diaExamen ||
                      (arr[right].diaExamen == arr[smallest].diaExamen &&
                       strcmp(arr[right].nombre, arr[smallest].nombre) < 0)))
        smallest = right;

    if (smallest != i) {
        Aspirante temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify(arr, n, smallest);
    }
}

// Heap Sort (Min Heap) por día de examen y nombre
void heapSort(Aspirante arr[], int n) {
    // Construir min heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos del heap uno por uno
    for (int i = 0; i < n; i++) {
        Aspirante temp = arr[0];
        arr[0] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
        heapify(arr, n - 1 - i, 0);
    }
}

// Función para capturar un nuevo aspirante
void capturarAspirante(Aspirante **aspirantes, int *total) {
    *aspirantes = (Aspirante *)realloc(*aspirantes, (*total + 1) * sizeof(Aspirante));

    if (*aspirantes == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    printf("Ingrese el nombre completo: ");
    scanf(" %[^\n]", (*aspirantes)[*total].nombre);
    printf("Ingrese la fecha de nacimiento (DD-MM-YYYY): ");
    scanf(" %[^\n]", (*aspirantes)[*total].fechaNacimiento);
    printf("Ingrese el lugar de nacimiento: ");
    scanf(" %[^\n]", (*aspirantes)[*total].lugarNacimiento);
    printf("Ingrese el CURP: ");
    scanf(" %[^\n]", (*aspirantes)[*total].curp);

    (*aspirantes)[*total].diaExamen = asignarDiaExamen((*aspirantes)[*total].nombre);

    (*total)++;
}

// Función para eliminar un aspirante
void eliminarAspirante(Aspirante *aspirantes, int *total) {
    int index;
    printf("Ingrese el índice del aspirante a eliminar (0 a %d): ", *total - 1);
    scanf("%d", &index);
    if (index >= 0 && index < *total) {
        for (int i = index; i < *total - 1; i++) {
            aspirantes[i] = aspirantes[i + 1];
        }
        (*total)--;
        aspirantes = (Aspirante *)realloc(aspirantes, (*total) * sizeof(Aspirante));
        printf("Aspirante eliminado.\n");
    } else {
        printf("Índice inválido.\n");
    }
}

// Función para mostrar aspirantes ordenados por CURP (usando Merge Sort)
void mostrarPorCURP(Aspirante *aspirantes, int total) {
    Aspirante *copia = (Aspirante *)malloc(total * sizeof(Aspirante));
    memcpy(copia, aspirantes, total * sizeof(Aspirante));

    mergeSort(copia, 0, total - 1);
    printf("\nAspirantes ordenados por CURP:\n");
    for (int i = 0; i < total; i++) {
        printf("%s - CURP: %s - Día de examen: %d\n", copia[i].nombre, copia[i].curp, copia[i].diaExamen);
    }
    free(copia);
}

// Función para mostrar aspirantes por día de examen y nombre en orden inverso (usando Heap Sort)
void mostrarPorDia(Aspirante *aspirantes, int total) {
    Aspirante *copia = (Aspirante *)malloc(total * sizeof(Aspirante));
    memcpy(copia, aspirantes, total * sizeof(Aspirante));

    heapSort(copia, total);

    printf("\nAspirantes ordenados por día de examen y nombre (en orden inverso):\n");
    int diaActual = 0;
    // Recorremos el arreglo en orden inverso
    for (int i = total - 1; i >= 0; i--) {
        if (copia[i].diaExamen != diaActual) {
            diaActual = copia[i].diaExamen;
            printf("\nDía de examen %d:\n", diaActual);
        }
        printf("%s\n", copia[i].nombre);
    }
    free(copia);
}


int main(void) {
    int total = 20;

    // Datos iniciales de aspirantes
    Aspirante datosIniciales[] = {
            {"Joaquín Cosío Osuna", "06-10-1962", "Tepic, Nayarit", "COSJ621006HNLSNS03", 0},
            {"Pedro Infante Cruz", "18-11-1917", "Mazatlán, Sinaloa", "INFP171118MNTZNS03", 0},
            {"Armando Manzanero Canché", "07-02-1935", "Mérida, Yucatán", "MANA350207YCNHDR09", 0},
            {"Jorge Damián Alcázar Castello", "08-01-1953", "Jiquilpan, Michoacán", "ALCJ530108HMICST08", 0},
            {"Adalberto Javier Ramones Martínez", "03-12-1961", "Monterrey, Nuevo León", "RAMJ611203HNLJRV03", 0},
            {"Mario Fortino Alfonso Moreno Reyes", "12-08-1911", "Ciudad de México", "MORM110812HDFRRN05", 0},
            {"Mauricio Feres Yazbek", "16-12-1926", "Tampico, Tamaulipas", "FERM261216HTMPRS03", 0},
            {"Vicente Fernández Gómez", "17-02-1940", "Guadalajara, Jalisco", "FERV400217HJCLSN01", 0},
            {"Alejandra Sánchez Barrero", "11-09-1971", "Ciudad de México", "SANB710911HDFLNR09", 0},
            {"Eugenio González Derbez", "02-09-1961", "Ciudad de México", "GONE610902HDFRNR03", 0},
            {"Adalberto Martínez Chávez", "25-01-1916", "Ciudad de México", "MARA160125HDFRTB08", 0},
            {"Gaspar Henaine Pérez", "06-01-1927", "Chignahuapan, Puebla", "HENG270106HPBLRL03", 0},
            {"Rodolfo Guzmán Huerta", "23-09-1917", "Tulancingo, Hidalgo", "GUHR171923HGTNNR05", 0},
            {"Alejandro Muñoz Moreno", "24-04-1922", "García, Nuevo León", "MUHA220424HNLGNR03", 0},
            {"Irma Consuelo Cielo Serrano Castro", "09-12-1933", "Comitán de Domínguez, Chiapas", "SERI331209HCHLNS03", 0},
            {"José Clemente Orozco Flores", "23-11-1883", "Ciudad de México", "OROJ831123HDFLRN03", 0},
            {"David Alfaro Siqueiros", "29-12-1896", "Santa Rosalía de Camargo, Chihuahua", "SIQA961229HCHLNS09", 0},
            {"José Victoriano Huerta Márquez", "23-12-1850", "Colotlán, Jalisco", "HUJV501223HJCLRJ01", 0},
            {"José María Pino Suárez", "08-09-1869", "Tenosique, Tabasco", "PINO690908HTBCRS01", 0},
            {"Arath de la Torre Balmaceda", "20-03-1975", "Ciudad de México", "DELA750320HDFRTR05", 0}
    };

    // Asignar días de examen a los aspirantes iniciales
    for (int i = 0; i < total; i++) {
        datosIniciales[i].diaExamen = asignarDiaExamen(datosIniciales[i].nombre);
    }

    // Crear arreglo dinámico y copiar los datos iniciales
    Aspirante *aspirantes = (Aspirante *)malloc(total * sizeof(Aspirante));
    if (aspirantes == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }
    memcpy(aspirantes, datosIniciales, total * sizeof(Aspirante));

    int opcion;
    do {
        printf("\nMenú:\n");
        printf("1. Capturar aspirante\n");
        printf("2. Eliminar aspirante\n");
        printf("3. Mostrar aspirantes ordenados por CURP\n");
        printf("4. Mostrar aspirantes ordenados por día de examen\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                capturarAspirante(&aspirantes, &total);
                break;
            case 2:
                eliminarAspirante(aspirantes, &total);
                break;
            case 3:
                mostrarPorCURP(aspirantes, total);
                break;
            case 4:
                mostrarPorDia(aspirantes, total);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 5);

    free(aspirantes); // Liberar la memoria antes de salir
    return 0;
}