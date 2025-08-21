#include "parser.h"
#include "estructuras/ast.h"
#include "estructuras/string-auxiliar.h"
#include "estructuras/tokens.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Para ver cada token, se declara de forma global la lista de tokens a analizar
 */
static TokenNodo *siguiente;

/* ------ Funciones Auxiliares ------ */

/**
 * next: TokenNodo* -> void
 * Si se le pasa un nodo de la lista de tokens, lo asigna en la variable
 * universal Sino, se mueve al siguiente nodo
 */
void next(TokenNodo *lista) {
  if (lista != NULL) {
    siguiente = lista;
  } else {
    siguiente = siguiente->next;
  }
  return;
}

/**
 * match: TipoDeToken -> bool
 * Si el tipo de nodo coincide con el tipo de token, se mueve al siguiente y
 * retorna true Sino, no se hace nada y se retorna false
 */
bool match(TipoDeToken tipo) {
  if (siguiente->tipo == tipo) {
    next(NULL);
    return true;
  } else
    return false;
}

/**
 * error: String ASTTree -> void
 * Si ocurre algo, recibe el árbol y borra todo el árbol, si se estaba formando.
 * De lo contrario, no añade nada
 */
void error(String mensaje, ASTTree arbol) {
  printf((String)mensaje);
  if (arbol != NULL)
    destruir_arbol(arbol);
  return;
}

/* -------------------------------------------- */

/**
 * deff: void -> ASTTree
 * Arma poco a poco el AST que representa el comando 'deff'
 * Se representa con la siguiente gramática
 * Deff ::= 'deff' DEF '=' Funcs | 'deff' DEF '=' Repeticion
 */

ASTTree deff() {
  // Se chequea por el tipo de token deff por si las moscas
  if (!match(TOKEN_DEFF))
    return NULL;
  ASTTree arbol = crear_arbol();
  arbol = crear_nodo_arbol(NULL, AST_DEFF);

  // Luego, se chequea por una definicion apropiada
  if (!match(TOKEN_DEF)) {
    error("Definición no válida", arbol);
    return NULL;
  }

  ASTNodo *definicion = def(siguiente->prev->token);
  anadir_hijo(arbol, definicion);

  // Sigue el chequeo del igual
  if (!match(TOKEN_IGUAL)) {
    error("Falta el símbolo '='", arbol);
    return NULL;
  }

  // Finalmente, se chequea si sigue una definicion de funciones adecuada
  ASTTree funciones = funcs();

  if (match(TOKEN_ANG_ABRE)) {
    ASTTree repeticion = crear_arbol();
    anadir_hijo(repeticion, funciones);

    ASTTree funciones2 = funcs();

    if (!match(TOKEN_ANG_CIERRA)) {
      printf("Falta cerrar con '>'. Intente de nuevo");
      destruir_arbol(funciones);
      destruir_arbol(arbol);
      return NULL;
    }

    anadir_hijo(repeticion, funciones2);
    ASTTree funciones3 = funcs();

    anadir_hijo(repeticion, funciones3);
    anadir_hijo(arbol, repeticion);
  } else {
    anadir_hijo(arbol, funciones);
  }

  return arbol;
}

/**
 * parse: TokenList -> ASTTree
 * Toma una lista de tokens y la convierte en un árbol de sintáxis abstracto
 * para poder procesarlo Sentencia ::= Definicion ';' | Aplicacion  ';' |
 * Busqueda ';'
 */
ASTTree parse(TokenList tokens) {

  // Asignar lista de tokens a procesar y a inicializar el arbol
  next(tokens->head);
  ASTTree ast = crear_arbol();

  // Luego, empezamos a determinar el caso que tenemos
  switch (siguiente->tipo) {
  case TOKEN_DEFF:
    ast = deff();
    if (!match(TOKEN_PUNTO_COMA))
      destruir_arbol(ast);
    break;

  case TOKEN_DEFL:
    ast = defl();
    if (!match(TOKEN_PUNTO_COMA))
      destruir_arbol(ast);
    break;

  case TOKEN_APPLY:
    ast = apply();
    if (!match(TOKEN_PUNTO_COMA))
      destruir_arbol(ast);
    break;

  case TOKEN_SEARCH:
    ast = search();
    if (!match(TOKEN_PUNTO_COMA))
      destruir_arbol(ast);
    break;

  case TOKEN_QUIT:
    ast = quit();
    if (!match(TOKEN_PUNTO_COMA))
      destruir_arbol(ast);
    break;
  default:
    error("ERROR: Comando no válido. Intente de nuevo", ast);
    return NULL;
    break;
  }

  if (ast == NULL) {
    printf("Parece que hubo un error con el parsing. Intente de nuevo");
  } else {
    siguiente = NULL;
    destruir_lista(tokens);
  }
  return ast;
}
