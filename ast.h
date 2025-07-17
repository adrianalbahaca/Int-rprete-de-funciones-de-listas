#ifndef __AST__
#define __AST__
#include "tokenizer.h"

/**
 * Definición de comandos a hacer
 */
typedef enum {
    DEFF,
    DEFL,
    APPLY,
    SEARCH
} Sentencia;

/**
 * Definición de funciones primitivas
 */
typedef enum {
    ZERO_I,
    ZERO_D,
    SUC_I,
    SUC_D,
    DEL_I,
    DEL_D
} Primitivas;

// Se define las estructuras que estarán en cada nodo

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens);

#endif /* __AST__ */