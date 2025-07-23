#include <stdlib.h>
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