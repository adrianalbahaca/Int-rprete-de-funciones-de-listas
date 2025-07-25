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

    // Primero, se define los tipos de nodo raíz

    DEFF_FUNCION, // Definicion := 'deff' DEF '=' FUNCIONES | 'deff' DEF '=' REPETICION
    DEFL_LISTA, // 'defl' DEF '=' '[' ELEMENTOS ']'
    APPLY, // 'apply' FUNCION LISTA
    SEARCH, // 'search' '{' LISTAS '}'

    // Luego, se define los nodos hoja

    DEF, // String a asociar a una lista
    PRIMITIVA, // PRIMITIVA := '0i' | '0d' | 'Si' | 'Sd' | 'Di' | 'Dd'
    DIGITO, // Número entero

    // Tipos de Sentencia

    LISTAS,
    LISTA,
    ELEMENTOS,

    // Finalmente, símbolos

    COMA,
    PUNTO_COMA,
    LLAVE_APERTURA,
    LLAVE_CIERRE,
    CORCHETE_APERTURA,
    CORCHETE_CIERRE,

    // Por último, el comando de cierre
    
    QUIT

} TipoDeNodo;

/**
 * Luego, defino las funciones primitivas
 */
typedef enum {
    CERO_IZQ, 
    CERO_DER,
    SUC_IZQ,
    SUC_DER,
    DEL_IZQ,
    DEL_DER
} TipoPrimitiva;

/**
 * Se define la estructura de los nodos hoja
 */

typedef struct {
    String def;
} NodoDef;

typedef struct {
    int digito;
} NodoDigito;

typedef struct {
    TipoPrimitiva primitiva;
} NodoPrimitiva;

/**
 * Finalmente, una unión masiva donde se guarda cada tipo
 */
typedef union {

    // Nodos hoja

    NodoDef def;
    NodoDigito digito;
    NodoPrimitiva primitiva;


} DatosNodo;

/**
 * Esta es la definición del nodo general
 */
typedef struct _ASTNodo {
    TipoDeNodo tipo;
    DatosNodo datos; 
} ASTNodo;

typedef ASTNodo* ASTTree;

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens); // Sentencia ::= Definicion ';' | Aplicacion  ';' | Busqueda ';'

#endif /* __AST__ */