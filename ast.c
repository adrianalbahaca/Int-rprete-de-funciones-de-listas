#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tokenizer.h"

/**
 * TODO: Definir las funciones que procesan de forma recursiva cada token dado, asegurándose
 * de que todo esté escrito adecuadamente. Se debe crear una función que borre todo si algo
 * sale mal en cualquier parte del camino
 */

ASTNodo* crear_nodo_digitos(int num) {
    ASTNodo* nodo = (ASTNodo*) malloc(sizeof(ASTNodo));
    nodo->tipo = DIGITO;
    nodo->datos.Digito.digito = num;
    return nodo;
}

ASTNodo* crear_nodo_funcion(String def) {
    ASTNodo* nodo = (ASTNodo*) malloc(sizeof(ASTNodo));
    nodo->tipo = FUNCION;
    nodo->datos.Definicion.def = NULL;
    strcpy(nodo->datos.Definicion.def, def);
    return nodo;
}

ASTNodo* crear_nodo_primitiva(String primitiva) {
    ASTNodo* nodo = (ASTNodo*) malloc(sizeof(ASTNodo));
    nodo->tipo = PRIMITIVA;
    nodo->datos.Primitiva.primitiva = NULL;
    strcpy(nodo->datos.Primitiva.primitiva, primitiva);
    return nodo;
}