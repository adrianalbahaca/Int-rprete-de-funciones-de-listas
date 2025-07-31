#ifndef __EXECUTE__
#define __EXECUTE__
#include "ast.h"

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
    String def;
    struct _Funcion* next;
} Funcion;

typedef struct _Def {
    String def;
    Funcion* funciones;
} Comp;

typedef Comp* Composicion;

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

typedef struct {
    Composicion funcion;
} CasillaTablaFunciones;

typedef struct _TablaDeFunciones {
    CasillaTablaFunciones* funciones;
    int numElem;
    int capacidad;
} TablaF;

typedef TablaF* TablaDeFunciones;

typedef struct {
    Lista lista;
} CasillaTablaListas;

typedef struct _TablaDeListas {
    CasillaTablaListas *listas;
    int numElems;
    int capacidad;
} TablaL;

typedef TablaL* TablaDeListas;

/**
 * inicializar_tabla_func: void -> TablaDeFunciones
 * Retorna una tabla de funciones vacía
 */
TablaDeFunciones crear_tabla_funciones();

/**
 * inicializar_tabla_listas(): void -> TablaDeListas
 * Retorna una tabla de listas vacía
 */
TablaDeListas inicializar_tabla_listas();

/**
 * execute: ASTTree -> void
 * Ejecuta todas las instrucciones dentro del AST
 */
void execute(ASTTree tree, TablaDeFunciones TablaF);

#endif /* __EXECUTE__ */