#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include "tokenizer.h"
#include <stdio.h>

// Se guarda de forma global la siguiente de tokens
static TokenNodo* siguiente;

/* ------ Funciones auxiliares ------ */

/**
 * destruir_lista: TokenList -> void
 * Destruye una lista de tokens
 */
void destruir_lista(TokenList lista) {
    for(TokenNodo *n = lista->head, *next = lista->head->sig; n != NULL; n = next) {
        free(n->token);
        next = n->sig;
        free(n);
    }
    lista->head = lista->tail = NULL;
    free(lista);
}
/**
 * error: ASTTree -> bool
 * Verifica si en alguno de los nodos hay un nodo de tipo ERROR
 */
bool contiene_error(ASTTree tree) {
    if (tree == NULL) {
        return false;
    }
    else if (tree->tipo == AST_ERROR) {
        return true;
    }
    
    else {
        bool error = false;
        for(int i = 0; i < CANT_HIJOS; i++) {
            error = contiene_error(tree->hijos[i]);
        }

        return error;
    }
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
    else {
        return false;
    }
}

/**
 * back: void -> void;
 * Retrocede un nodo atrás de la lista
 */
void back() {
    siguiente = siguiente->ant;
    return;
}

void liberar_arbol(ASTNodo* arbol) {
    if (arbol == NULL) return;
    else {
        for(int i = 0; i < arbol->num_hijos; i++) {
            liberar_arbol(arbol->hijos[i]);
        }
        free(arbol->lexema);
        free(arbol);
        return;
    }
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

/* ------ Nodos hoja ------ */

/**
 * Def: String -> ASTNodo*
 * Crear un nodo hoja de tipo DEF
 */
ASTNodo* Def(String def) {
    ASTNodo* defi = crear_nodo(AST_DEF, def);
    return defi;
}

/**
 * Digito: String -> ASTNodo*
 * Crear un nodo hoja de tipo DIGITO
 */
ASTNodo* Digito(String digito) {
    ASTNodo* dig = crear_nodo(AST_DIGITO, digito);
    return dig;
}

/**
 * Primitiva: String -> ASTNodo*
 * Crear un nodo hoja de tipo PRIMITIVA
 */
ASTNodo* Primitiva(String primitiva) {
    ASTNodo* prim = crear_nodo(AST_PRIMITIVA, primitiva);
    return prim;
}
/* ------------------------ */

/* ------ Nodos intermedios ------ */

/**
 * Func: void -> ASTNodo*
 * Crea una función de tipo DEF o tipo PRIMITIVA. Si el token no es de esos tipos,
 * retorna NULL
 */
ASTNodo* Func() {
    ASTNodo* func = crear_nodo(AST_FUNC, NULL);
    if(match(TOKEN_DEF)) {
        ASTNodo* def = Def(siguiente->ant->token);
        agregar_hijo(func, def);
    }
    else if (match(TOKEN_PRIMITIVA)) {
        ASTNodo* prim = Primitiva(siguiente->ant->token);
        agregar_hijo(func, prim);
    }
    else {
        free(func);
        func = NULL;
    }

    return func;
}

/**
 * Funcs: void -> ASTNodo*
 * Sigue la regla de la gramática siguiente:
 * => Funcs ::= Func Funcs | Func
 */
ASTNodo* Funcs() {

    ASTNodo* func = Func();
    if(func == NULL) {
        return NULL;
    }
    
    ASTNodo* funcs = crear_nodo(AST_FUNCS, NULL);
    agregar_hijo(funcs, func);

    ASTNodo* sig = Funcs();
    agregar_hijo(funcs, sig);

    return funcs;

}

/**
 * Rep: void -> ASTNodo*
 * Crea un nodo de tipo REPETICION
 */
ASTNodo* Rep() {
    ASTNodo* rep = crear_nodo(AST_REP, NULL);
    return rep;
}

/**
 * Elementos: void -> ASTNodo*
 * Crea un nodo de tipo ELEMENTOS, que debe tener un nodo hijo DIGITO y,
 * opcionalmente, otro nodo hijo ELEMENTOS
 */
ASTNodo* Elementos() {
    ASTNodo* digito = NULL;
    if (match(TOKEN_DIGITO)) {
        digito = Digito(siguiente->ant->token);
    }
    else {
        return NULL;
    }

    ASTNodo* nextElem = Elementos();
    ASTNodo* elem = crear_nodo(AST_ELEMENTOS, NULL);

    agregar_hijo(elem, digito);
    agregar_hijo(elem, nextElem);

    return elem;
}

/**
 * Lista: void -> ASTNodo*
 * Crea un nodo de tipo LISTA
 */
ASTNodo* Lista() {
    if(!match(TOKEN_COR_ABRE)) {
        return NULL;
    }

    ASTNodo* elem = Elementos();
    if(elem == NULL && !match(TOKEN_COR_CIERRA)) {
        return NULL;
    }

    ASTNodo* lista = crear_nodo(AST_LISTA, NULL);
    agregar_hijo(lista, elem);

    return lista;
}

/**
 * Listas: void -> ASTNodo*
 * Crea un nodo de tipo LISTAS que contiene dos nodos de tipo LISTA y, opcionalmente
 * un nodo de tipo LISTAS
 */
ASTNodo* Listas() {
    ASTNodo* lista1 = Lista();
    if(lista1 == NULL) {
        return NULL;
    }

    ASTNodo* lista2 = Lista();
    if(lista2 == NULL) {
        return NULL;
    }

    ASTNodo* listas = Listas();
    
    ASTNodo* pares = crear_nodo(AST_LISTAS, NULL);
    agregar_hijo(pares, lista1);
    agregar_hijo(pares, lista2);
    agregar_hijo(pares, listas);

    return pares;
}
/* ------------------------------- */

/* ------ Nodos raíz ------ */

/**
 * Quit: void -> ASTNodo*
 * Crea un nodo de tipo QUIT, para indicar que se quiere borrar todo
 * del programa y terminarlo
 */
ASTNodo* Quit() {
    if(match(TOKEN_QUIT)) return NULL;
    ASTNodo* quit = crear_nodo(AST_QUIT, NULL);
    return quit;
}

/**
 * Search: void -> ASTNodo*
 * Va revisando la gramática de la regla siguiente:
 * => Search ::= "search" LLAVE_ABRE Listas LLAVE_CIERRA
 * Si la cumple, retorna un nodo de tipo SEARCH con la siguiente de pares de
 * listas a buscar respectivamente
 */
ASTNodo* Search() {

    if(match(TOKEN_SEARCH)) return NULL;
    ASTNodo* search = crear_nodo(AST_SEARCH, NULL);

    if(match(TOKEN_LLAVE_ABRE)) {
        liberar_arbol(search);
        return NULL;
    }

    ASTNodo* listas = Listas();
    if (listas == NULL) {
        liberar_arbol(search);
        return NULL;
    }
    agregar_hijo(search, listas);

    if(match(TOKEN_LLAVE_CIERRA)) {
        liberar_arbol(search);
        return NULL;
    }

    return search;
}

/**
 * Apply: void -> ASTNodo*
 * Va revisando la gramática de la regla siguiente:
 * => Apply ::= "apply" FUNC DEF | "apply" FUNC LISTA
 * Si la cumple, retorna un nodo del AST de tipo APPLY
 */
ASTNodo* Apply() {

    if(match(TOKEN_APPLY)) return NULL;
    ASTNodo* apply = crear_nodo(AST_APPLY, NULL);

    ASTNodo* func = Func();
    if(func == NULL) {
        liberar_arbol(apply);
        return NULL;
    }
    agregar_hijo(apply, func);

    ASTNodo* lista = Lista();
    if(lista == NULL) {
        liberar_arbol(apply);
        return NULL;
    }
    agregar_hijo(apply, lista);

    return apply;
}

/**
 * Defl: void -> ASTNodo*
 * Va revisando la gramática de la siguiente regla:
 * => Defl ::= "defl" DEF IGUAL COR_ABRE Elementos COR_CIERRA
 * Si la cumple, devuelve un nodo de tipo DEFL con los elementos de la siguiente
 */
ASTNodo* Defl() {
    if(match(TOKEN_DEFL)) return NULL;
    ASTNodo* defl = crear_nodo(AST_DEFL, NULL);

    if(match(TOKEN_DEF)) {
        liberar_arbol(defl);
        return NULL;
    }
    ASTNodo* def = Def(siguiente->ant->token);
    agregar_hijo(defl, def);

    if(match(TOKEN_IGUAL) && !match(TOKEN_COR_ABRE)) {
        liberar_arbol(defl);
        return NULL;
    }

    ASTNodo* elementos = Elementos();
    if (elementos == NULL || !match(TOKEN_COR_CIERRA)) {
        liberar_arbol(defl);
        return NULL;
    }

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
    if (!match(TOKEN_DEFF)) return NULL;
    ASTNodo* deff = crear_nodo(AST_DEFF, NULL);

    // Luego, sigue un nodo DEF
    if (!match(TOKEN_DEF)) {
        liberar_arbol(deff);
        return NULL;
    }

    ASTNodo* def = Def(siguiente->ant->token);
    agregar_hijo(deff, def);


    if (!match(TOKEN_IGUAL)) {
        liberar_arbol(deff);
        return NULL;
    }

    // Luego, tengo que ir guardando la siguiente de funciones
    ASTNodo* funcs = Funcs();
    if (funcs == NULL) {
        liberar_arbol(deff);
        return NULL;
    }
    
    // Si se detecta algún token de angulo, es una repetición

    if(match(TOKEN_ANG_ABRE)) {

        // Se busca la segunda lista de tokens
        ASTNodo* funcs2 = Funcs();

        /* Si no se cierra el ángulo o la segunda lista de funciones
        tiene algún problema, borrar todo y avisar error */
        if(!match(TOKEN_ANG_CIERRA) || funcs2 == NULL) {
            liberar_arbol(funcs);
            liberar_arbol(funcs2);
            liberar_arbol(def);
            return NULL;
        }

        // Buscar tercera lista de funciones
        ASTNodo* funcs3 = Funcs();

        // Si algo sale mal con la tercera lista, borrar todo
        if(funcs3 == NULL) {
            liberar_arbol(funcs);
            liberar_arbol(funcs2);
            liberar_arbol(def);
            return NULL;
        }

        // Si todo sale bien, crear un nodo de repetición
        ASTNodo* rep = Rep();
        agregar_hijo(rep, funcs);
        agregar_hijo(rep, funcs2);
        agregar_hijo(rep, funcs3);
        agregar_hijo(deff, rep);
    }
    else { // Si no es repetición, simplemente meter la lista de funciones y retornar
        agregar_hijo(deff, funcs);
    }

    return deff;
}

/* -------------------------------------------- */

/**
 * parse: TokenList -> ASTTree
 * Toma una siguiente de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens) {

    /* Primero, voy a inicializar la siguiente en la función next */
    next(tokens->head);
    
    ASTTree tree = NULL;

    ASTNodo* hijo = NULL;

    /*
        Luego, se inicia el parser
        => Sentencia ::= Deff PUNTO_COMA | Defl PUNTO_COMA | Apply PUNTO_COMA | Search PUNTO_COMA
    */
    switch (siguiente->tipo) {
        case TOKEN_DEFF:

            hijo = Deff();
            if(hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;

        case TOKEN_DEFL:

            hijo = Defl();
            if(hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;

        case TOKEN_APPLY:

            hijo = Apply();
            if (hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;

        case TOKEN_SEARCH:

            hijo = Search();
            if (hijo == NULL) break;
            if(!match(TOKEN_PUNTO_COMA)) break;
            tree = crear_nodo(AST_SENTENCIA, NULL);
            agregar_hijo(tree, hijo);
            break;

        case TOKEN_QUIT:

            tree = Quit();
            break;

        default:
            break;
    }

    // Si todo sale bien, borrar la lista de tokens
    siguiente = NULL;
    destruir_lista(tokens);

    if (tree == NULL) {
        printf("Hubo un error en el parsing. Intente de nuevo\n");
    }
    if (contiene_error(tree)) {
        printf("Se detectó en su comando. Intente de nuevo\n");
    }

    return tree;
}