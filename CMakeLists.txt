cmake_minimum_required(VERSION 3.27)
project(siu C)

set(CMAKE_C_STANDARD 99)

add_executable(siu EstructuraDeDatos/Practica3.c
        EstructuraDeDatos/Practica4-2.c
        EstructuraDeDatos/Practica4.c
        "EstructuraDeDatos/Practica5.c"
        EstructuraDeDatos/Practica5-1.c)
