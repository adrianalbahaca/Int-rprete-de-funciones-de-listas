#include "parser.h"
#include "estructuras/tokens.h"
#include "estructuras/string-auxiliar.h"
#include "estructuras/ast.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Para ver cada token, se declara de forma global la lista de tokens a analizar
 */
static TokenNodo* siguiente;

/* ------ Funciones Auxiliares ------ */

/**
 * next: TokenNodo* -> void
 * Si se le pasa un nodo de la lista de tokens, lo asigna en la variable universal
 * Sino, se mueve al siguiente nodo
 */
void next(TokenNodo* lista) {
    if (lista == NULL) {
        siguiente = lista;
    }
    else {
        siguiente = siguiente->next;
    }
    return;
}

/**
 * match: TipoDeToken -> bool
 * Si el tipo de nodo coincide con el tipo de token, se mueve al siguiente y retorna true
 * Sino, no se hace nada y se retorna false
 */
bool match(TipoDeToken tipo) {
    if (siguiente->tipo == tipo) {
        next(NULL);
        return true;
    }
    else return false;
}

/* -------------------------------------------- */


