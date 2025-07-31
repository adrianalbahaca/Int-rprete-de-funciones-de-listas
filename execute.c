#include "execute.h"
#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * TODO: Definir las funciones que sigan la instrucción del nodo raíz del arbol
 */

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
 * agregar_def: TablaDeFunciones String Definicion -> void
 * Guarda en la tabla hash la función definida. Busca manejar las colisiones
 */
void agregar_def(TablaDeFunciones tabla, String nombre, Definicion def) {

    int pos = hash(nombre) % CANT_FUNCIONES;
    if (tabla->funciones[pos] == NULL) {
        tabla->funciones[pos] = def;
        tabla->capacidad++;
        return tabla;
    }
    else {
        printf("ERROR: Esta función ya está definida\n");
        return;
    }

}

/**
 * inicializar_tabla_func: void -> TablaDeFunciones
 * Retorna una tabla de funciones vacía
 */
TablaDeFunciones inicializar_tabla_func() {

    TablaDeFunciones tabla = malloc(sizeof(TablaDeFunciones));
    for (int i = 0; i < CANT_FUNCIONES; i++) {
        tabla->funciones[i] = NULL;
    }
    tabla->capacidad = 0;
    return tabla;

}

/**
 * inicializar_tabla_listas(): void -> TablaDeListas
 * Retorna una tabla de listas vacía
 */
TablaDeListas inicializar_tabla_listas() {

    TablaL* tabla = malloc(sizeof(TablaL));
    for (int i = 0; i < CANT_LISTAS; i++) {
        tabla->listas[i] = NULL;
    }
    tabla->capacidad = 0;
    return tabla;

}

/**
 * tipo_funcion: ASTNodo* -> Funcion*
 * Toma un nodo de tipo FUNC y retorna una función de tipo DEF o PRIMITIVA
 */
Funcion* tipo_funcion(ASTNodo* f) {
    if (f->tipo == AST_PRIMITIVA) {

    }
    else {
        Funcion* retorno = malloc(sizeof(Funcion));
        retorno->tipo = FUNC_DEF;
        retorno->def = str_dup(f->lexema);
        retorno->next = NULL;
        return retorno;
    }
}

/**
 * agregar_funciones: ASTNodo* -> Funcion*
 * Va agregando cada función de forma recursiva. Si se llega a un punto nulo,
 * no se retorna nada
 */
Funcion* agregar_funciones(ASTNodo* funciones) {

    if (funciones == NULL) return NULL;

    else if (funciones->tipo == AST_FUNCS) {
        Funcion* funcion = agregar_funciones(funciones->hijos[0]);
        Funcion* funcion2 = agregar_funciones(funciones->hijos[1]);
        funcion->next = funcion2;
        return funcion;
    }
    else if(funciones->tipo == AST_FUNC) {
        Funcion* funcion = tipo_funcion(funciones->hijos[0]);
        return funcion;
    }

}

/**
 * crear_lista_de_funciones: void -> Definición
 * Crea un nodo de Definición de funciones vacíos 
 */
Definicion crear_lista_de_funciones(String nombre) {

    Definicion def = malloc(sizeof(Def));
    def->funciones = NULL;
    def->def = nombre;
    return def;

}
/**
 * comando: ASTNodo* TablaDeFunciones TablaDeListas -> void
 * Verifica qué instrucción tiene, ya sea 'deff', 'defl', 'apply' o 'search'
 * y aplica según sea el caso
 */
void comando(ASTNodo* sentencia, TablaDeFunciones TablaF, TablaDeListas TablaL) {

    String nombre = NULL;

    switch (sentencia->tipo) {

        case AST_DEFF:

            nombre = str_dup(sentencia->hijos[0]->lexema);
            Definicion funciones = crear_lista_de_funciones(nombre);
            funciones->funciones = agregar_funciones(sentencia->hijos[0]);
            agregar_def(TablaF, nombre, funciones);
            break;

        case AST_DEFL:

            nombre = str_dup(sentencia->hijos[0]->lexema);
            Lista elementos = crear_lista(sentencia->hijos[1]->lexema);
            agregar_lista(TablaL, nombre, elementos);
            break;

        case AST_APPLY:

            Definicion funcion = funcion_a_aplicar(sentencia->hijos[0]);
            Lista lista = lista_a_aplicar(sentencia->hijos[1]);
            aplicar_funcion(funcion, lista);
            break;

        case AST_SEARCH:
            /**
             * TODO: Definir un algoritmo que busca entre las funciones hechas y primitivas
             * para convertir una lista L1 en otra lista L2. Tomar en cuenta que puede que
             * no haya solución
             */
            break;

        case AST_QUIT:

            borrar_tabla_listas(TablaL);
            borrar_tabla_funciones(TablaF);
            break;
        
        default:
            break;
    }
    return;
}
/**
 * execute: ASTTree TablaDeFunciones TablaDeListas -> void
 * Ejecuta todas las instrucciones dentro del AST
 */
void execute(ASTTree tree, TablaDeFunciones TablaF, TablaDeListas TablaL) {

    /* Entramos en el árbol como un personaje de una película de terror entra
    en un bosque oscuro */

    comando(tree->hijos[0], TablaF, TablaL); // Este sería el hijo del nodo AST_SENTENCIA

    /* Después, se borra todo el árbol */
    liberar_arbol(tree);

    return;
}