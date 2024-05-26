cmake_minimum_required(VERSION 3.27)
project(siu C)

set(CMAKE_C_STANDARD 99)

add_executable(siu
        "EstructuraDeDatos/Practica 7/Practica7-1.c"
        "EstructuraDeDatos/Practica 7/Practica7-Stack.c"
        "EstructuraDeDatos/Practica 7/Practica7-Tree.c"
        "EstructuraDeDatos/Practica 6/libros.c"
        "EstructuraDeDatos/Practica 6/tree.h"
        "EstructuraDeDatos/Practica 6/main.c"
        "EstructuraDeDatos/Practica 6/stack.c"
        "EstructuraDeDatos/Practica 6/tree.c")
