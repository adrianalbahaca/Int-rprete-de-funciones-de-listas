#ifndef __EXECUTE__
#define __EXECUTE__

/**
 * Para guardar los datos durante el curso del programa, se usan dos tablas hash, cuyas
 * casillas sean listas simplemente enlazadas:
 * una es para guardar funciones y otra para guardar listas
 */

typedef struct _CasillaHash {
    union {

    }
} CasillaHash;

typedef struct _TablaHash {
    CasillaHash elementos[];
    int capacidad;
    int numElem;
};

typedef struct _TablaHash* TablaHash;

#endif // __EXECUTE__