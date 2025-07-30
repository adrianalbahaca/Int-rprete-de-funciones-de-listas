#ifndef __EXECUTE__
#define __EXECUTE__

/**
 * Para las tablas hash, se define un tamaño predeterminado para empezar
 */
#define CANT_FUNCIONES 10
#define CANT_LISTAS 10

typedef char* String;

/**
 * Se define los tipos de funciones, ya sea primitiva o una definición
 */
typedef enum {
    PRIMITIVA_0I, PRIMITIVA_0D, PRIMITIVA_SI, PRIMITIVA_SD,
    PRIMITIVA_DI, PRIMITIVA_DD, FUNC_DEF, 
} TipoDeFuncion;

/**
 * Las funciones se definen como listas simplemente enlazadas, con una estructura que
 * apunta a su principio exclusivamente
 */
typedef struct _Funcion {
    TipoDeFuncion tipo;
    char* def;
    struct _Funcion* next;
} Funcion;

typedef struct _Def {
    Funcion* funciones;
    char* def;
} Def;

typedef struct Def* Definicion;

/**
 * Las listas se definen como una lista simplemente enlazada con una estructura
 * que apunta a su principio y a su final
 */
typedef struct _Elemento {
    int dato;
    struct _Elemento* next;
} Elemento;

typedef struct {
    Elemento *head;
    Elemento *tail;
} _Lista;

typedef struct _Lista* Lista;

/**
 * TODO: Definir cómo guardar las funciones y listas hechas por el usuario
 * (Tablas hash de qué tipo?. Cómo lidio con las colisiones?)
 */

/** 
 * Se define el sitio donde se va a guardar cada funcion y lista como unas tablas
 * hash que apuntan a sus respectivos elementos
 */

typedef struct _TablaDeFunciones {
    Definicion funciones[CANT_FUNCIONES];
    int capacidad;
} TablaF;

typedef struct TablaF* TablaDeFunciones;

typedef struct _TablaDeListas {
    Lista listas[CANT_LISTAS];
    int capacidad;
} TablaL;

typedef struct TablaL* TablaDeListas;

/**
 * TODO: Definir una lista de funciones primitivas ya conocidas, de donde se arman otras funciones
 */

/**
 * execute: ASTTree -> void
 * Ejecuta todas las instrucciones dentro del AST
 */
void execute(ASTTree tree, TablaDeFunciones TablaF, TablaDeListas TablaL);

#endif /* __EXECUTE__ */