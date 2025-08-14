#include "ast.h"
#include "tokens.h"
#include "estructuras/string-auxiliar.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
 * A continuación, este es el código que viene con respecto al AST y la eliminación de
 * la lista doblemente enlazada de tokens
 */
static TokenNodo* siguiente;

/* -------------------------------------------- */

/**
 * crear_nodo: String TipoDeNodo -> ASTNodo*
 * Crea un nodo sin hijos con un cierto tipo y un lexema, si lo hubiera
 */
ASTNodo* crear_nodo(String lexema, TipoDeNodo tipo) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo != NULL);
    for (int i = 0; i < CANT_HIJOS; i++) {
        nodo->hijos[i] = NULL;
    }
    if (lexema != NULL) nodo->lexema = str_dup(lexema);
    else nodo->lexema = NULL;
    nodo->tipo = tipo;
    return nodo; 
}

/**
 * agregar_hijo: ASTNodo* ASTNodo* -> ASTNodo*
 * Recibe dos nodos y retorna un nodo donde el padre tenga al hijo
 */
ASTNodo* agregar_hijo(ASTNodo* padre, ASTNodo* hijo) {
    padre->hijos[padre->num_hijos] = hijo;
    padre->num_hijos++;
    return padre;
}

/**
 * destruir_arbol: ASTTree -> void
 * Destruye un árbol completo
 */
void destruir_arbol(ASTTree arbol) {
    if (arbol == NULL) return;

    for (int i = 0; i < arbol->num_hijos; i++) {
        destruir_arbol(arbol->hijos[i]);
    }
    if (arbol->lexema != NULL) free(arbol->lexema);
    free(arbol);
    return;
}

/**
 * match: TipoDeToken -> bool
 * Verifica que en la lista
 */
/* -------------------------------------------- */
ASTTree parse(TokenNodo* tokens) {
    
}