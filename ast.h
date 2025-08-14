#ifndef __AST__
#define __AST__
#include "tokenizer.h"

/**
 * Se define los tipos de nodos para el AST
 */

typedef enum {
    /* Estos son los tipos de nodo raíz */
    AST_DEFF, AST_DEFL, AST_APPLY, AST_SEARCH, AST_QUIT,

    /* Estos son tipos de nodo internos */
    AST_FUNCS, AST_FUNC, AST_REP, AST_LISTAS, AST_LISTA, AST_ELEMENTOS,

    /* Esto son tipos de nodos hoja */
    AST_DEF, AST_PRIMITIVA, AST_DIGITO, AST_ERROR
    
} TipoDeNodo;

/**
 * Se define la cant. de hijos posibles que puede tener cada nodo
 */
#define CANT_HIJOS 3

/**
 * Se define la estructura general de un nodo de un árbol. Tiene un máx. de
 * 3 hijos cada uno
 */
typedef struct _ASTNodo {
    TipoDeNodo tipo;
    String lexema;
    int num_hijos;
    struct _ASTNodo* hijos[];
} ASTNodo;

/**
 * También, por conveniencia, se define un nombre para el nodo raíz del AST
 */

typedef ASTNodo* ASTTree;

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenNodo* tokens); // Sentencia ::= Definicion ';' | Aplicacion  ';' | Busqueda ';'

#endif /* __AST__ */