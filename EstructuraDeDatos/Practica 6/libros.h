#ifndef __LIBROS_H__
#define __LIBROS_H__

#include <stddef.h>

typedef struct {
    char title[64];
    char genre[32];
    unsigned int year;
} Libro;

extern Libro LIBROS[];
extern size_t LONGITUD_LIBROS;

#endif // __LIBROS_H__
