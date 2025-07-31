#include "execute.h"
#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * TODO: Definir las funciones que sigan la instrucción del nodo raíz del arbol
 */



/**
 * tipo_primitiva: String -> TipoDeFuncion
 * Determina qué tipo de primitiva es la cadena dada
 */
TipoDeFuncion tipo_funcion(String s) {
    if (strcmp(s, "0i")) {
        return PRIMITIVA_0I;
    }
    else if (strcmp(s, "0d")) {
        return PRIMITIVA_0D;
    }
    else if (strcmp(s, "Si")) {
        return PRIMITIVA_SI;
    }
    else if (strcmp(s, "Sd")) {
        return PRIMITIVA_SD;
    }
    else if (strcmp(s, "Di")) {
        return PRIMITIVA_DI;
    }
    else if(strcmp(s, "Dd")) {
        return PRIMITIVA_DD;
    }
    else {
        return FUNC_DEF;
    }
}

/**
 * hash: String -> int
 * Genera un número específico para la cadena dada
 */
int hash(String s) {

    int hash = 0;
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        hash = hash * 31 + s[i];
    }
    return hash;
}

/**
 * crear_tabla_funciones: void -> TablaDeFunciones
 * Crea una tabla de funciones vacía
 */
TablaDeFunciones crear_tabla_funciones() {
    TablaDeFunciones tabla = malloc(sizeof(TablaF));
    assert(tabla != NULL);
    tabla->funciones = malloc(sizeof(CasillaTablaFunciones) * CANT_FUNCIONES);
    assert(tabla->funciones != NULL);
    tabla->numElem = 0;
    tabla->capacidad = CANT_FUNCIONES;
    for (int i = 0; i < tabla->capacidad; i++) {
        tabla->funciones[i].funcion = NULL;
    }
    return tabla;
}

/**
 * crear_tabla_listas: void -> TablaDeListas
 * Crea una tabla de listas vacía
 */
TablaDeListas crear_tabla_listas() {
    TablaDeListas tabla = malloc(sizeof(TablaL));
    assert(tabla != NULL);
    tabla->listas = malloc(sizeof(Lista) * CANT_LISTAS);
    assert (tabla->listas != NULL);
    tabla->numElems = 0;
    tabla->capacidad = CANT_LISTAS;
    for (int i = 0; i < tabla->capacidad; i++) {
        tabla->listas[i].lista = NULL;
    }
    return tabla;
}

/**
 * agregar_def: TablaDeFunciones String Composicion -> void
 * Agrega una composición de funciones a la tabla
 */
TablaDeFunciones agregar_def(TablaDeFunciones tabla, String nombre, Composicion comp) {
    int pos = hash(nombre) % tabla->capacidad;
    if (tabla->funciones[pos].funcion == NULL) {
        tabla->funciones[pos].funcion = comp;
        return tabla;
    }
    else {
        printf("Esta función ya está definida. No se va a guardar nada");
        return tabla;
    }
}

/* ---------------------------------------------------------- */

/**
 * crear_funcion: ASTNodo* -> Funcion*
 * Crea una función de tipo DEF o de tipo PRIMITIVA_...
 */
Funcion* crear_funcion(ASTNodo* tipo) {
    Funcion* f = malloc(sizeof(Funcion));
    f->tipo = tipo_funcion(tipo->hijos[0]->lexema);
    if (f->tipo == FUNC_DEF) {
        f->def = str_dup(tipo->hijos[0]->lexema);
    }
    f->next = NULL;
    return f;
}

/**
 * crear_composicion_funciones: String -> Composicion
 * Crea una composición de funciones vacía
 */
Composicion crear_composicion_funciones(String nombre) {
    Composicion funcion = malloc(sizeof(Comp));
    funcion->def = str_dup(nombre);
    funcion->funciones = NULL;
    return funcion;
}

/**
 * agregar_funciones: ASTNodo* -> Funcion*
 * crea la lista de funciones poco a poco, mientras va recorriendo el árbol
 */
Funcion* agregar_funciones(ASTNodo* func) {
    if (func == NULL) return NULL;
    else if (func->tipo == AST_FUNCS) {
        Funcion* funcion = crear_funcion(func->hijos[0]);
        funcion->next = agregar_funciones(func->hijos[1]);
        return funcion;
    }
    else if (func->tipo == AST_REP) {
        // Primero, creo las 3 partes de la función
        Funcion* funcionPrincipio = crear_funcion(func->hijos[0]);
        Funcion* funcionRep = crear_funcion(func->hijos[1]);
        Funcion* funcionFin = crear_funcion(func->hijos[2]);
    }
}

/**
 * comando: ASTNodo* TablaDeFunciones TablaDeListas -> void
 * Verifica qué instrucción tiene, ya sea 'deff', 'defl', 'apply' o 'search'
 * y aplica según sea el caso
 */
void sentencia(ASTNodo* sentencia, TablaDeFunciones TablaF) {

    String nombre = NULL;

    switch (sentencia->tipo) {

        case AST_DEFF:

            nombre = str_dup(sentencia->hijos[0]->lexema);
            Composicion comp = crear_composicion_funciones(nombre);
            comp->funciones = agregar_funciones(sentencia->hijos[1]);
            TablaF = agregar_def(TablaF, nombre, comp);
            break;

        /* case AST_DEFL:

            nombre = str_dup(sentencia->hijos[0]->lexema);
            Lista elementos = crear_lista(sentencia->hijos[1]->lexema);
            agregar_lista(TablaL, nombre, elementos);
            break;

        case AST_APPLY:

            Composicion funcion = funcion_a_aplicar(sentencia->hijos[0]);
            Lista lista = lista_a_aplicar(sentencia->hijos[1]);
            aplicar_funcion(funcion, lista);
            break;

        case AST_SEARCH:
            *
             * TODO: Definir un algoritmo que busca entre las funciones hechas y primitivas
             * para convertir una lista L1 en otra lista L2. Tomar en cuenta que puede que
             * no haya solución
             
            break;

        case AST_QUIT:

            borrar_tabla_listas(TablaL);
            borrar_tabla_funciones(TablaF);
            break;*/
        
        default:
            break;
    }
    return;
}
/**
 * execute: ASTTree TablaDeFunciones TablaDeListas -> void
 * Ejecuta todas las instrucciones dentro del AST
 */
void execute(ASTTree tree, TablaDeFunciones TablaF) {

    /* Entramos en el árbol como un personaje de una película de terror entra
    en un bosque oscuro */

    sentencia(tree->hijos[0], TablaF); // Este sería el hijo del nodo AST_SENTENCIA

    /* Después, se borra todo el árbol */
    liberar_arbol(tree);

    return;
}