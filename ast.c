#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include "tokenizer.h"

// Se guarda de forma global la lista de tokens
static TokenNodo* lista;

/* ------ Funciones auxiliares ------ */

/**
 * next: TokenNodo* -> void
 * Si se ingresa una lista simplemente enlazada de tokens, se guarda la lista. Sino, se mueve
 * al siguiente token de una lista ya guardada anteriormente
 */
void next(TokenNodo* tokens) {

    if (tokens != NULL) {
        lista = tokens;
    }
    else {
        lista = lista->sig;
    }
}
/* ---------------------------------- */

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens) {

    /* Primero, voy a inicializar la lista en la función next */
    next(tokens->head);
    
}