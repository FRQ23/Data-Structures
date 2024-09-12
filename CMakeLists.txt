cmake_minimum_required(VERSION 3.27)
project(siu C)

set(CMAKE_C_STANDARD 99)

add_executable(siu
        AnalisisDeAlgoritmos/Practica3/Practica3-1.c
        StopBeingAverage/hello_world.c
        StopBeingAverage/helloUser.c
        StopBeingAverage/parImpar.c
        StopBeingAverage/arraysStrings.c
        StopBeingAverage/calculator.c
        StopBeingAverage/pointers.c)
