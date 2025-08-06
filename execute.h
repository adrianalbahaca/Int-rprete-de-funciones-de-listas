#ifndef __EXECUTE__
#define __EXECUTE__

typedef char* String;

/**
 * Se declara los tipos de funciones posibles, desde las funciones primitivas hasta
 * la función definida antes
 */
typedef enum {
    PRIM_0I,
    PRIM_0D,
    PRIM_SI,
    PRIM_SD,
    PRIM_DI,
    PRIM_DD,
    DEF,
} TipoFuncion;

/**
 * las funciones hechas por el usuario se guardan en una lista simplemente enlazada, donde
 * cada nodo es una función o primitiva o definida antes
 */

typedef struct _SFNodo {
    TipoFuncion tipo;
    String def; // Esto es opcional y sólo se usa si la función es una definida antes
    struct _SFNodo* next;
} Funcion;

typedef struct _SLNodo {
    int valor;
    struct _SLNodo* next;
} SLNodo;

typedef struct _Lista {
    SLNodo* head;
    SLNodo* tail;
} Lista;

/**
 * Para guardar los datos durante el curso del programa, se usan dos tablas hash, cuyas
 * casillas sean listas simplemente enlazadas de ya sea alguno de los dos tipos:
 * Uno es para guardar funciones y otro para guardar listas
 */

typedef struct _CasillaHash {
    String def;
    union {
        Funcion* funcion;
        Lista* lista;
    } elemento;
} CasillaHash;

typedef struct _TablaHash {
    CasillaHash* elementos;
    int capacidad;
    int numElem;
};

typedef struct _TablaHash* TablaHash;

#endif // __EXECUTE__