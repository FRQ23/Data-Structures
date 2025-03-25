#include <stdio.h>
#include <stdlib.h>


// Definicion de la estrucutra
typedef struct Node{
    int data;
    struct Node* next;
}Node;


// prototipos de funciones

void insertAtBeginning(Node** head, int valor);
void insertAtEnd(Node** head, int valor);
int deleteNode(Node** head, int valor);
int search(Node* head, int valor);
void display(Node* head);
void freeList(Node** head);

// funcion extra para mostrar y modificar la lista

void displayAndModify(Node** head, void (*modifyFunc)(Node**, int), int valor);


 /*
*  Crear un nuevo nodo con malloc.
*  Asignar el valor recibido al nuevo nodo.
*  Hacer que el nuevo nodo apunte al head actual.
*  Actualizar head para que apunte al nuevo nodo.
*
 */

void insertAtBeginning(Node** head, int valor)
{
    Node* nuevoNodo = (Node*)malloc(sizeof(Node));
    nuevoNodo->data = valor;
    nuevoNodo->next = *head;
    *head = nuevoNodo;
}


/*
* Crear un nuevo nodo con malloc.
* Si la lista está vacía, actualizar head con el nuevo nodo.
* Si la lista no está vacía, recorrer la lista hasta el último nodo y hacer que su next apunte al
* nuevo nodo.
*/

void insertAtEnd(Node** head, int valor)
{
    Node* nuevoNodo = (Node*)malloc(sizeof(Node));
    nuevoNodo->data = valor;
    nuevoNodo->next = NULL;
    if(*head == NULL){
        *head = nuevoNodo;
    }
    else
    {
        Node* temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}


/*
* Buscar el nodo que contenga el valor especificado.
* Si el nodo está en el head, actualizar head y liberar memoria.
* Si el nodo está en otra posición, hacer que el nodo anterior apunte al siguiente del nodo
* eliminado.
* Liberar memoria del nodo eliminado.
* Retornar 1 si se eliminó correctamente, 0 si no se encontró el valor.
*/

int deleteNode(Node** head, int valor)
{
    Node* temp = *head;
    Node* prev = NULL;

    if(temp != NULL && temp->data == valor)
    {
        *head = temp->next;
        free(temp);
        return 1;
    }
    while(temp != NULL && temp->data != valor)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL)
    {
        return 0;
    }

    prev->next = temp->next;
    free(temp);
    return 1;

}


/*
* Recorrer la lista para verificar si el valor está presente.
* Retornar 1 si el valor se encuentra, 0 si no.
 */


int search(Node* head, int valor)
{
    Node *temp = head;
    while(temp != NULL)
    {
        if(temp->data == valor)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/*
* Recorrer la lista e imprimir los valores de cada nodo, mostrando -> entre ellos y finalizando
* con NULL.
 */

void display(Node* head)
{
    Node* temp = head;
    while(temp != NULL)
    {
        printf("%d ---> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/*
* Implementar una función void freeList(Node** head) que libere todos los nodos de la lista
* para evitar fugas de memoria.
 */

void freeList(Node** head)
{
    Node *temp;
    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Funcion extra para mostrar y modificar la lista

void displayAndModify(Node** head, void (*modifyFunc)(Node**, int), int valor) {
    printf("Antes de modificar: ");
    display(*head);
    modifyFunc(head, valor);
    printf("Despues de modificar: ");
    display(*head);
}

int main(void) {
    Node* head = NULL;

    displayAndModify(&head, insertAtBeginning, 10);
    displayAndModify(&head, insertAtBeginning, 5);
    displayAndModify(&head, insertAtEnd, 20);
    displayAndModify(&head, insertAtEnd, 30);
    display(head); // Output: 5 ---> 10 ---> 20 ---> 30 ---> NULL

    printf("Buscar 20: %s\n", search(head, 20) ? "Encontrado" : "No encontrado");
    displayAndModify(&head, (void (*)(Node **, int)) deleteNode, 10);
    display(head); // Output: 5 ---> 20 ---> 30 ---> NULL
    freeList(&head);

    return 0;
}