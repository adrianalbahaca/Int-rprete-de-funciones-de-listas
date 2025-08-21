#ifndef __PARSER__
#define __PARSER__
#include "estructuras/ast.h"
#include "estructuras/tokens.h"

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto para poder procesarlo
 */
ASTTree parse(TokenList tokens); // Sentencia ::= Definicion ';' | Aplicacion  ';' | Busqueda ';'

#endif /* __PARSER__ */