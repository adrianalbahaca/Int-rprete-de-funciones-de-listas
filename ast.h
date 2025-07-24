#ifndef __AST__
#define __AST__
#include "tokenizer.h"

/**
 * TODO: Diseñar los nodos del AST. Son los siguientes:
 * 1. Nodos de la sentencia: Busqueda, Aplicacion y Definicion
 * 2. Nodos hoja (Terminales): DEF, DIGITO, PRIMITIVA
 * 3. Nodos intermedios (No terminales): FUNCION, FUNCIONES, LISTA, LISTAS, etc
 */

/**
 * Primero, determino los tipos de nodos que pueden haber
 */
typedef enum {
    AST_DEFINICION_DEFF,
    AST_DEFINICION_DEFF_REP,
    AST_DEFINICION_DEFL,
    AST_BUSQUEDA,
    AST_APLICACION,
    ID,
    PRIMITIVA,
    FUNCIONES,
    FUNCION,
    REPETICION,
    ELEMENTOS,
    ELEMENTO,
    LISTAS,
    LISTA,
    DIGITOS,
    DIGITO
} TipoDeNodo;

/**
 * Luego, se define cada estructura que representa cada nodo
 * Empiezo con los nodos hoja
 */
typedef struct {
    int digito;
} NodoDigito;

typedef struct {
    char* def;
} NodoDef;

typedef struct {
    char* primitiva;
} NodoPrimitiva;

/**
 * Luego, los nodos raíz posibles
 */
typedef struct {
    ASTNodo* funcion;
    ASTNodo* funciones;
} NodoDeffFunctions;

typedef struct {
    ASTNodo* def;
    ASTNodo* funcion1;
    ASTNodo* funcion2;
    ASTNodo* funcion3;
} NodoDeffRepetition;

typedef struct {
    ASTNodo* def;
    ASTNodo* elementos;
} NodoDefl;

typedef struct {
    ASTNodo* funcion;
    ASTNodo* lista;
} NodoApply;

typedef struct {
    ASTNodo* listas;
} NodoSearch;

/**
 * Vemos ahora los nodos intermedios
 */

typedef struct {
    ASTNodo* digito;
    ASTNodo* elementos;
} NodoElementos;

typedef struct {
    char* def;
} NodoLista;

typedef struct {
    ASTNodo* lista1;
    ASTNodo* lista2;
    ASTNodo* listas;
} NodoListas;

/**
 * Finalmente, se guarda todo en una union por practicidad
 */
typedef union {

    // Nodos hoja

    NodoDigito Digito;
    NodoDef Definicion;
    NodoPrimitiva Primitiva;

    // Nodos raíz

    NodoDeffFunctions DeffFunc;
    NodoDeffRepetition DeffRep;
    NodoApply Apply;
    NodoSearch Search;

    // Nodos intermedios

    NodoElementos Elementos;
    NodoListas Listas;
    NodoLista Lista;

} NodoDatos;

/**
 * Ahora, la estructura general del nodo
 */
typedef struct _ASTNodo {
    TipoDeNodo tipo;
    NodoDatos datos;
} ASTNodo;

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTNodo* parse(TokenList tokens);

#endif /* __AST__ */