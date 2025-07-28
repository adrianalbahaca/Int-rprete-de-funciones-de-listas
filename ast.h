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

    LISTAS, // Listas ::= Lista COMA Lista PUNTO_COMA Listas | Lista COMA Lista
    LISTA, // Lista ::= DEF | COR_ABRE Elementos COR_CIERRA
    ELEMENTOS, // 
    REPETICION,
    FUNCS,

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

/**
 * Esta es la estructura para el nodo hoja de tipo DEF
 */
typedef struct {
    String def;
} NodoDef;

/**
 * Esta es la estructura para el nodo hoja de tipo DIGITO
 */
typedef struct {
    int digito;
} NodoDigito;

typedef struct {
    TipoPrimitiva primitiva;
} NodoPrimitiva;

typedef struct {
    int quit;
} NodoQuit;

/**
 * Se define los nodos raíces
 */
typedef struct {
    ASTNodo* def;
    ASTNodo* funcs;
} NodoDeff;

typedef struct {
    ASTNodo* function;
    ASTNodo* lista;
} NodoDefl;

typedef struct {
    ASTNodo* function;
    ASTNodo* list;
} NodoApply;

/**
 * Además, se define los nodos intermedios
 */

typedef struct {
    ASTNodo* funcion;
    ASTNodo* funciones;
} NodoFunciones;

/**
 * Finalmente, una unión masiva donde se guarda cada tipo
 */
typedef union {

    // Nodos hoja

    NodoDef Def;
    NodoDigito Digito;
    NodoPrimitiva Primitiva;

    // Nodos raíz
    NodoDeff Deff;
    NodoDefl Defl;
    NodoApply Apply;
    NodoSearch Search;

    // Nodos intermedios
    NodoFunciones Funciones;

    // Comando quit
    NodoQuit Quit;


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