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

    ASTTree arbol = NULL;

    if (strcmp(tokens->tail->token, ";")) {

        if (strcmp(tokens->head->token, "deff")) {

            arbol = crear_nodo_deff(tokens);

        } else if (strcmp(tokens->head->token, "defl")) {

            arbol = crear_nodo_defl(tokens);

        } else if (strcmp(tokens->head->token, "apply")) {

            arbol = crear_nodo_apply(tokens);

        } else if (strcmp(tokens->head->token, "search")) {

            arbol = crear_nodo_search(tokens);

        }

    } else if (strcmp(tokens->head->token, "quit")) {

        arbol = (ASTNodo*) malloc(sizeof(ASTNodo));
        arbol->tipo = QUIT;
        arbol->datos.Quit.quit = 0;
        
    }
    return arbol;
 }

/**
 * TODO: Definir nodos intermedios, chequeando que la escritura durante el proceso sea
 * el adecuado
 */

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y arma poco a poco el AST, revisando que la lista de tokens
 * sigue la gramática predeterminada
 */
ASTTree parse(TokenList lista) {
    ASTTree arbol = crear_nodo_raiz(lista);
    assert(arbol);
    borrar_lista(lista);
    return arbol;
}