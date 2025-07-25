#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tokenizer.h"

/**
 * TODO: Definir las funciones auxiliares, como una función que borra todo el árbol
 * en caso de que algo salga mal
 */

/**
 * TODO: Definir nodos hojas
 */
ASTNodo* crear_nodo_func_primitiva(String primitiva) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = PRIMITIVA;
    nodo->datos.Primitiva.primitiva = tipo_primitiva(primitiva);
    return nodo;
}

ASTNodo* crear_nodo_def(String def) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = DEF;
    strcpy(nodo->datos.Def.def, def);
    return nodo;
}

ASTNodo* crear_nodo_digito(int digito) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = DIGITO;
    nodo->datos.Digito.digito = digito;
    return nodo;
}

/**
 * TODO: Definir nodos raíces, con sus reglas
 */

 ASTTree crear_nodo_raiz (TokenList tokens) {
    if (strcmp(tokens->tail->token, ";")) {
        if(strcmp(tokens->head->sig->sig->token, "=")) {
            if (strcmp(tokens->head->token, "deff")) {

            } else if (strcmp(tokens->head->token, "defl")) {

            } else if (strcmp(tokens->head->token, "apply")) {

            } else if (strcmp(tokens->head->token, "search")) {

            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    } else if (strcmp(tokens->head->token, "quit")) {
        
    }
 }

/**
 * TODO: Definir nodos intermedios, chequeando que la escritura durante el proceso sea
 * el adecuado
 */