#include "ast.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/**
 * TODO: Definir las funciones auxiliares, como una función que determine si hay
 * algún token específico en una posición específica
 */

/* ----- Funciones auxiliares ----- */

/**
 * lista_contiene_pos: TokenList, String, int -> bool
 * Determina si tiene un token específico en una posición específica, considerando
 * la primera posición como 0, como en los arreglos
 * 
 * Ej.1: lista_contiene_pos([Pepsi]->[CocaCola]->[Fanta], "CocaCola", 1) -> true
 * 
 * Ej.2: lista_contiene_pos([Pepsi]->[CocaCola]->[Fanta], "Fanta", 0) -> false
 */

bool lista_contiene_pos(TokenList lista, String token, int pos) {

    int i = 0;
    for(TokenNodo* n = lista->head; n != NULL; n = n->sig) {
        if (strcmp(n->token, token) && (i == pos)) {
            return true;
        }
        i++;
    }
    return false;

}

/**
 * destruir_lista: TokenList -> void
 * Destruye todos los elementos de una lista de tokens, y la estructura
 * que apunta a la cabeza y cola de la lista
 */
void destruir_lista(TokenList lista) {
    TokenNodo* n = lista->head;
    while (n != NULL) {
        TokenNodo* next = n->sig;
        free(n->token);
        free(n);
        n = next;
    }
    lista->head = lista->tail = NULL;
    free(lista);
    return;
}

/*----------------------------------------------------------------------------------*/
/* ----- Nodos hoja ----- */

/**
 * TODO: Definir nodos hojas
 */

/**
 * crear_nodo_func_primitiva: String -> ASTNodo*
 * Crea un nodo hoja del AST que contiene una función primitiva
 */
ASTNodo* crear_nodo_func_primitiva(String primitiva) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = PRIMITIVA;
    nodo->datos.Primitiva.primitiva = tipo_primitiva(primitiva);
    return nodo;
}

/**
 * crear_nodo_def: String -> ASTNodo*
 * Crea un nodo hoja del AST que contiene una definición como una cadena
 * de caractéres
 */
ASTNodo* crear_nodo_def(String def) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = DEF;
    strcpy(nodo->datos.Def.def, def);
    return nodo;
}

/**
 * crear_nodo_digito: int -> ASTNodo*
 * Crea un nodo hoja que contiene un dígito entero
 */
ASTNodo* crear_nodo_digito(int digito) {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = DIGITO;
    nodo->datos.Digito.digito = digito;
    return nodo;
}

/* --------------------------------------------------------------- */
/* ----- Nodos intermedios ----- */

/**
 * TODO: Definir nodos intermedios, chequeando que la escritura durante el proceso sea
 * la adecuada
 */

/*-----------------------------------------------------------------*/
/* ----- Nodos raíces ----- */

/**
 * TODO: Definir nodos raíces, con sus reglas
 */

/**
 * crear_nodo_raiz: TokenList -> ASTTree
 * 
 */
 ASTTree crear_nodo_raiz (TokenList tokens) {

    ASTTree arbol = NULL;

    // Primero, se verifica que el comando termine en un punto y coma

    if (strcmp(tokens->tail->token, ";")) {

        /**
         * Luego, verifico que la cabeza de la lista de tokens sea alguno de los comandos pedidos
         * ya sea 'deff', 'defl', 'apply', 'search' o 'quit', en la primera posición de la lista
         */

        if (lista_contiene_pos(tokens, "deff", 0)) {
            arbol = crear_nodo_deff(tokens);
        }

        else if (lista_contiene_pos(tokens, "defl", 0)) {
            arbol = crear_nodo_defl(tokens);
        }

        else if (lista_contiene_pos(tokens, "apply", 0)) {
            arbol = crear_nodo_apply(tokens);
        }

        else if (lista_contiene_pos(tokens, "search", 0)) {
            arbol = crear_nodo_search(tokens);
        }

        else if (lista_contiene_pos(tokens, "quit", 0)) {
            arbol = crear_nodo_quit();
        }

        /* Si no contiene ninguno de estos comandos, salta error */

        else {
            printf("ERROR: Comando no permitido. Verifique de nuevo");
        }

    } else {
        printf("ERROR: Todo comando termina con punto y coma");
    }

    return arbol;
 }

 /* ------------------------------------------------------------------ */

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y arma poco a poco el AST, revisando que la lista de tokens
 * sigue la gramática predeterminada
 */
ASTTree parse(TokenList lista) {
    ASTTree arbol = crear_nodo_raiz(lista);
    assert(arbol);
    destruir_lista(lista);
    return arbol;
}