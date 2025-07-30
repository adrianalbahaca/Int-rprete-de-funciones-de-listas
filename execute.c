#include "execute.h"
#include "ast.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * TODO: Definir las funciones que sigan la instrucción del nodo raíz del arbol
 */

/**
 * comando: ASTNodo* TablaDeFunciones TablaDeListas -> void
 * Verifica qué instrucción tiene, ya sea 'deff', 'defl', 'apply' o 'search'
 * y aplica según sea el caso
 */
void comando(ASTNodo* sentencia, TablaDeFunciones TablaF, TablaDeListas TablaL) {

    switch (sentencia->tipo) {

        case AST_DEFF:
            String nombre = str_dup(sentencia->hijos[0]->lexema);
            Definicion funciones = lista_de_funciones(sentencia->hijos[1]);
            agregar_def(TablaF, nombre, funciones);
            break;

        case AST_DEFL:
            String nombre = str_dup(sentencia->hijos[0]->lexema);
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