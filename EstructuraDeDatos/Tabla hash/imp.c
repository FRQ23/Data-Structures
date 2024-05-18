//
// Created by Fernando Rosales on 5/8/24.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    char *name;
    char *lastName;
    short int year;
    int month;
    int day;
}Data;

typedef struct hashttable
{
    int size;
    Data **table;

}HashTable;


int hash_function(HashTable myHash, int *key)
{
    return *key % myHash.size;
}

int rehash_function(HashTable myHash, int index, int k)
{
    return (index + (k*k) % myHash.size;
}

void print_HashTable(HashTable myHash)
{
    int i;
    for(i = 0; i < myHash->size; i++)
    {
        data - myHash->table[i];
        if(data)
            printf
    }
}



void insert_data(HashTable *myHash, Data *data)
{
    int key;
    int i;
    i = 0;

    while(data->name[i]!-'\0')
    {
        key += data->name[i++];

    }

    printf("\n Key: %d\n", key);
    index = hash_function(*myHash, key);
    printf("\n Index: %d\n", index);

    int new_index;

    //revisar si hay colisision
    if(!myHash->table[index])
    {
        myHash->table[index] = data;
    }
    else
    {
        i =0;
        do {
            i++;
            new_index = rehash_function(*myHash, index, i);

        }while(!myHash->table[new_index] && i <4);
        if(!myHash->table[new_index])
        {

            myHash->table[new_index] = data;
        }
        else
        {
            printf("\n No se pudo insertar el dato\n");
        }


    }

}




int main(void){

    HashTable myHash;
    myHash.size = 11;

    myHash.table = (Data**) calloc(myHash.size, sizeof(Data*));

    Data *data;

    data = (data*) calloc(1, sizeof(Data));
    *data (Data) (.name "Christopher\0", .lastName "Morales\0", .year 2001, .month 4, .day 7);
    printf("\n %s % %d/%d/%d\n", data->name, data->lastName, data->year, data->month, data->day);
    insert_data(&myHash, data);




    printf("\n \n \n");




}