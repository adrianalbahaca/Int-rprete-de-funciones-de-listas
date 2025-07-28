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

/**
 * str_dup: String -> String (Función auxiliar)
 * Asigna el espacio en necesario para duplicar un string a otro
 */

String str_dup(const String s) {
    size_t size = strlen(s) + 1;
    String p = malloc(size);
    assert(p);
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}

TipoPrimitiva tipo_primitiva (String func) {
    if (strcmp(func, "0i")) {
        return CERO_IZQ;
    }
    else if (strcmp(func, "0d")) {
        return CERO_DER;
    }
    else if (strcmp(func, "Si")) {
        return SUC_IZQ;
    }
    else if (strcmp(func, "Sd")) {
        return SUC_DER;
    }
    else if (strcmp(func, "Di")) {
        return DEL_IZQ;
    }
    else if (strcmp(func, "Dd")) {
        return DEL_DER;
    }
    else {
        return -1;
    }
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
    nodo->datos.Def.def = str_dup(def);
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

/**
 * crear_nodo_quit: void -> ASTNodo*
 * Crear un nodo de tipo QUIT
 */
ASTNodo* crear_nodo_quit() {
    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = QUIT;
    nodo->datos.Quit.quit = 1;
    return nodo;
}

/* --------------------------------------------------------------- */
/* ----- Nodos intermedios ----- */

/**
 * TODO: Definir nodos intermedios, chequeando que la escritura durante el proceso sea
 * la adecuada
 */

/**
 * crear_nodo_funcs: TokenNodo* -> ASTNodo*
 * Crea un nodo de tipo FUNCS, que tiene un nodo hijo de tipo DEF, y otro
 * nodo hijo de tipo FUNCS, que puede ser NULL
 * Sigue la regla gramatical siguiente:
 * Funcs ::= Func Funcs | Func
 * Func ::= DEF | PRIMITIVA
 */
ASTNodo* crear_nodo_funcs(TokenNodo* funciones) {

    // Si la lista de funciones ya se recorrió, retornar NULL

    if (funciones == NULL || strcmp(funciones->token, ";")) {
       return NULL; 
    }

    // De lo contrario, guardar cada función acorde

    else {

        ASTNodo* nodo = malloc(sizeof(ASTNodo));
        nodo->tipo = FUNCS;

        if (tipo_primitiva(funciones->token) >= 0) {
            nodo->datos.Funciones.funcion = crear_nodo_func_primitiva(funciones->token);
        }
        else {
            nodo->datos.Funciones.funcion = crear_nodo_def(funciones->token);
        }
        nodo->datos.Funciones.funciones = crear_nodo_funcs(funciones->sig);
    }
}

/**
 * crear_nodo_rep: TokenNodo* -> ASTNodo*
 * Crea un nodo de tipo REP con 3 hijos de tipo FUNCS
 * Sigue la regla gramatical siguiente:
 * Rep ::= Funcs "<" Funcs ">" Funcs
 */
ASTNodo* crear_nodo_rep(TokenNodo* funciones) {

}

/**
 * crear_nodo_elementos: TokenNodo* -> ASTNodo*
 * Crea un nodo de tipo ELEMENTOS, que contiene un nodo hijo de tipo DIGITO,
 * y otro de tipo ELEMENTOS, que puede ser NULL
 * Elementos ::= DIGITO COMA Elementos | DIGITO | e
 */
ASTNodo* crear_nodo_elementos(TokenNodo* lista) {

}

/**
 * crear_nodo_listas: TokenNodo* -> ASTNodo*
 * Crea un nodo de tipo PAR_LISTAS que guarda un par de nodos de tipo LISTA y otro de tipo
 * PAR_LISTAS, que puede ser NULL
 * Sigue la regla gramatical siguiente:
 * Listas ::= Lista COMA Lista PUNTO_COMA Listas | Lista COMA Lista
 */
ASTNodo* crear_nodo_listas(TokenNodo* listas) {

}

/**
 * crear_nodo_lista: TokenNodo* -> ASTNodo
 * Crea un nodo de tipo LISTA, que puede contener o un nodo de tipo DEF
 * o de tipo ELEMENTOS, siguiendo una lista a definir
 * Sigue la regla gramatical siguiente:
 * Lista ::= DEF | COR_ABRE Elementos COR_CIERRA
 */
ASTNodo* crear_nodo_lista(TokenNodo* lista) {

}

/*-----------------------------------------------------------------*/
/* ----- Nodos raíces ----- */

/**
 * TODO: Definir nodos raíces, con sus reglas
 */

/**
 * crear_nodo_deff: TokenList -> ASTNodo*
 * Crea un nodo de tipo DEFF_FUNCION, que tiene como nodos hijos un nodo DEF y
 * otro nodo que puede ser una lista de funciones (FUNCS), o con una función
 * repetición (REPETICION)
 * Sigue la regla siguiente de la gramática:
 * Deff ::= "deff" DEF IGUAL Funcs | "deff" DEF IGUAL Rep
 */
ASTNodo* crear_nodo_deff(TokenList tokens) {

    ASTNodo* nodo = NULL;

    if (lista_contiene_pos(tokens, "=", 2)) {
        
        nodo = malloc(sizeof(ASTNodo));
        assert(nodo);
        nodo->tipo = DEFF_FUNCION;

        TokenNodo* funciones = tokens->head->sig->sig->sig;

        /**
         * Si tiene los corchetes angulados, se define como una repetición
         */
        if (lista_cierre(tokens, "<>")) {
            nodo->datos.Deff.funcs = crear_nodo_repeticion(funciones);
        } 
        
        /**
         * Sino, sólo se define como una lista de funciones
         */
        else {
            nodo->datos.Deff.funcs = crear_nodo_funcs(funciones);
        }
    }
    
    else {
        return nodo;
    }
}

/**
 * crear_nodo_defl: TokenList -> ASTNodo*
 * Crea un nodo de tipo DEFL_LISTA, que tiene como nodos hoja un nodo DEF
 * y otro nodo de tipo LISTA
 * Sigue la regla siguiente de la gramática:
 * Defl ::= "defl" DEF IGUAL COR_ABRE Elementos COR_CIERRA
 */
ASTNodo* crear_nodo_defl(TokenList tokens) {
    
    ASTNodo* nodo = NULL;

    if (lista_contiene_pos(tokens, "=" , 2) && lista_cierre(tokens, "[]")) {

        String funcion = tokens->head->sig->token;
        TokenNodo* lista = tokens->head->sig->sig->sig;

        nodo = malloc(sizeof(ASTNodo));
        assert(nodo);
        nodo->tipo = DEFL_LISTA;

        if (tipo_primitiva(tokens->head->sig->token) >= 0) {
            nodo->datos.Defl.function = crear_nodo_func_primitiva(tokens->head->sig->token);
        }
        else {
            nodo->datos.Defl.function = crear_nodo_def(tokens->head->sig->token);
        }

        nodo->datos.Defl.lista = crear_nodo_lista(lista);
        if (nodo->datos.Defl.lista) {
            free(nodo);
            nodo = NULL;
        }
    }

    return nodo;
}

/**
 * crear_nodo_apply: TokenList -> ASTNodo*
 * Crea un nodo de tipo APPLY, con un nodo hijo DEF y otros nodos hijos FUNCS
 * Sigue la regla siguiente de la gramática:
 * Apply ::= "apply" DEF DEF | "apply DEF" COR_ABRE Elementos COR_CIERRA
 */
ASTNodo* crear_nodo_apply(TokenList tokens) {

    String funcion = tokens->head->sig->token;
    TokenNodo* lista = tokens->head->sig->sig;

    ASTNodo* nodo = malloc(sizeof(ASTNodo));
    assert(nodo);
    nodo->tipo = APPLY;
    
    if (tipo_primitiva(funcion) >= 0) {
        nodo->datos.Apply.function = crear_nodo_func_primitiva(funcion);
    }
    else {
        nodo->datos.Apply.function = crear_nodo_def(funcion);
    }

    nodo->datos.Apply.list = crear_nodo_lista(lista);
}

/**
 * crear_nodo_search: TokenList -> ASTNodo*
 * Crea un nodo de tipo SEARCH, que guarda los pares de listas a buscar,
 * ya sea una ya definida previamente (DEF), o una a definir (LISTA)
 * Sigue la regla siguiente de la gramática:
 * Search ::= "search" LLAVE_ABRE Listas LLAVE_CIERRA
 */
ASTNodo* crear_nodo_search(TokenList tokens) {

}

/**
 * crear_nodo_raiz: TokenList -> ASTTree
 * Elige qué tipo de nodo raíz retornar, ya sea DEFF_FUNCION, DEFL_LISTA,
 * APPLY o SEARCH
 * Sigue la regla de la gramática siguiente:
 * Sentencia ::= Deff PUNTO_COMA | Defl PUNTO_COMA | Apply PUNTO_COMA | Search PUNTO_COMA
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