#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include "tokenizer.h"

// Se guarda de forma global la siguiente de tokens
static TokenNodo* siguiente;

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
 * Si se ingresa una lista simplemente enlazada de tokens, se guarda la siguiente. Sino, se mueve
 * al siguiente token de una lista ya guardada anteriormente
 */
void next(TokenNodo* tokens) {

    if (tokens != NULL) {
        siguiente = tokens;
    }
    else {
        siguiente = siguiente->sig;
    }
}

/**
 * match: TipoDeToken -> bool
 * Si el token buscado coincide con el primer token de siguiente, invoca a next. Sino, salta un error
 */
bool match(TipoDeToken tipo) {
    if (tipo == siguiente->tipo) {
        next(NULL);
        return true;
    }
    else return false;
}

/**
 * crear_nodo: TipoDeNodo String -> ASTNodo*
 * Crea un nodo con un tipo y, si se incluye, un lexema como string
 */
ASTNodo* crear_nodo(TipoDeNodo tipo, String lexema) {
    ASTNodo* nodo = (ASTNodo*) malloc(sizeof(ASTNodo));
    nodo->tipo = tipo;
    if (lexema != NULL) {
        nodo->lexema = str_dup(lexema);
    }
    else {
        nodo->lexema = NULL;
    }
    nodo->num_hijos = 0;
    for(int i = 0; i < CANT_HIJOS; i++) {
        nodo->hijos[i] = NULL;
    }
    return nodo;
}

/**
 * agregar_hijo: ASTNodo* ASTNodo* -> void
 * Le ingresa un nodo hijo a un nodo padre, y actualiza la cant. de hijos que tiene
 * el nodo padre
 */
void agregar_hijo(ASTNodo* padre, ASTNodo* hijo) {
    padre->hijos[padre->num_hijos++] = hijo;
    return;
}
/* ---------------------------------- */

/**
 * Search: void -> ASTNodo*
 * Va revisando la gramática de la regla siguiente:
 * => Search ::= "search" LLAVE_ABRE Listas LLAVE_CIERRA
 * Si la cumple, retorna un nodo de tipo SEARCH con la siguiente de pares de
 * listas a buscar respectivamente
 */
ASTNodo* Search() {

    match(TOKEN_SEARCH);
    ASTNodo* search = crear_nodo(AST_SEARCH, NULL);

    match(TOKEN_LLAVE_ABRE);

    ASTNodo* listas = Listas();
    agregar_hijo(search, listas);

    match(TOKEN_LLAVE_CIERRA);

    return search;
}

/**
 * Apply: void -> ASTNodo*
 * Va revisando la gramática de la regla siguiente:
 * => Apply ::= "apply" FUNC DEF | "apply" FUNC LISTA
 * Si la cumple, retorna un nodo del AST de tipo APPLY
 */
ASTNodo* Apply() {

    match(TOKEN_APPLY);
    ASTNodo* apply = crear_nodo(AST_APPLY, NULL);

    ASTNodo* func = Func();
    agregar_hijo(apply, func);

    ASTNodo* lista = Lista();
    agregar_hijo(apply, lista);
}

/**
 * Defl: void -> ASTNodo*
 * Va revisando la gramática de la siguiente regla:
 * => Defl ::= "defl" DEF IGUAL COR_ABRE Elementos COR_CIERRA
 * Si la cumple, devuelve un nodo de tipo DEFL con los elementos de la siguiente
 */
ASTNodo* Defl() {
    match(TOKEN_DEFL);
    ASTNodo* defl = crear_nodo(AST_DEFL, NULL);

    ASTNodo* def = crear_nodo(AST_DEF, siguiente->token);
    match(TOKEN_DEF);
    agregar_hijo(defl, def);

    match(TOKEN_IGUAL);
    match(TOKEN_COR_ABRE);

    ASTNodo* elementos = Elementos();

    match(TOKEN_COR_CIERRA);

    agregar_hijo(defl, elementos);

    return defl;
}

/**
 * Deff: void -> ASTNodo*
 * Va chequeando la gramática de la siguiente regla
 * => Deff ::= "deff" DEF IGUAL Funcs | "deff" DEF IGUAL Rep
 * => Rep ::= Funcs "<" Funcs ">" Funcs
 * Si sigue la gramática, retorna el nodo del AST del tipo DEFF
 */
ASTNodo* Deff() {
    
    // Se empieza con el nodo DEFF
    match(TOKEN_DEFF);
    ASTNodo* deff = crear_nodo(AST_DEFF, NULL);

    // Luego, sigue un nodo DEF
    ASTNodo* def = crear_nodo(AST_DEF, siguiente->token);
    match(TOKEN_DEF);
    agregar_hijo(deff, def);

    match(TOKEN_IGUAL);

    // Luego, tengo que ir guardando la siguiente de funciones
    ASTNodo* funcs = Funcs();

    if (siguiente->tipo == TOKEN_ANG_ABRE) {
        match(TOKEN_ANG_ABRE);

        ASTNodo* funcs2 = Funcs();
        
        match(TOKEN_ANG_CIERRA);

        ASTNodo* funcs3 = Funcs();

        ASTNodo* repeticion = crear_nodo(AST_REP, NULL);
        agregar_hijo(repeticion, funcs);
        agregar_hijo(repeticion, funcs2);
        agregar_hijo(repeticion, funcs3);
        agregar_hijo(deff, repeticion);
    }
    else {
        agregar_hijo(deff, funcs);
    }

    return deff;
}

/**
 * parse: TokenList -> ASTTree
 * Toma una siguiente de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens) {

    /* Primero, voy a inicializar la siguiente en la función next */
    next(tokens->head);
    
    ASTTree tree = NULL;

    /*
        Luego, se inicia el parser
        => Sentencia ::= Deff PUNTO_COMA | Defl PUNTO_COMA | Apply PUNTO_COMA | Search PUNTO_COMA
    */
    switch (siguiente->tipo) {
        case TOKEN_DEFF:
            ASTNodo* hijo = Deff();
            if(hijo == NULL) return NULL;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;
        case TOKEN_DEFL:
            ASTNodo* hijo = Defl();
            if(hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;
        case TOKEN_APPLY:
            ASTNodo* hijo = Apply();
            if (hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;
        case TOKEN_SEARCH:
            ASTNodo* hijo = Search();
            if (hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;
        default:
            break;
    }

    // Si todo sale bien, borrar la siguiente de tokens y siguiente
    siguiente = NULL;
    destruir_lista(tokens);

    return tree;
}