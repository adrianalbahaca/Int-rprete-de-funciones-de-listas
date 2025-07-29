#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include "tokenizer.h"

// Se guarda de forma global la lista de tokens
static TokenNodo* lista;

/* ------ Funciones auxiliares ------ */

/**
 * error: void -> void
 * Si se invoca, avisa que hay un error sintáctico en lo escrito
 */
void error() {
    printf("Error de sintáxis. Prueba de nuevo\n");
    exit(1);
}

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

/**
 * match: TipoDeToken -> void
 * Si el token buscado coincide con el primer token de lista, invoca a next. Sino, salta un error
 */
void match(TipoDeToken tipo) {
    if (tipo == lista->tipo) next(NULL);
    else error();
}
/* ---------------------------------- */

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens) {

    /* Primero, voy a inicializar la lista en la función next */
    next(tokens->head);
    
    // Luego, se inicia el parser
    ASTTree tree = NULL;

    switch (lista->tipo) {
        case TOKEN_DEFF:
            tree = Deff();
            match(TOKEN_PUNTO_COMA);
            break;
        case TOKEN_DEFL:
            tree = Defl();
            match(TOKEN_PUNTO_COMA);
            break;
        case TOKEN_APPLY:
            tree = Apply();
            match(TOKEN_PUNTO_COMA);
            break;
        case TOKEN_SEARCH:
            tree = Search();
            match(TOKEN_PUNTO_COMA);
            break;
        default:
            error();
            break;
    }

    return tree;
}