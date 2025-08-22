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

/* Reglas gramaticales */

/**
 * Deff ::= 'deff' DEF '=' Funcs | 'deff' DEF '=' Repeticion
 */
ASTTree deff();

/**
 * Rep ::= Funcs "<" Funcs ">" Funcs
 */
ASTTree rep();

/**
 * Funcs ::= DEF Funcs | PRIMITIVA Funcs | DEF | PRIMITIVA
 */
ASTTree funcs();

/**
 * Defl ::= "defl" DEF IGUAL COR_ABRE Elementos COR_CIERRA
 */
ASTTree defl();

/**
 * Elementos ::= DIGITO COMA Elementos | DIGITO | e
 */
ASTTree elementos();

/**
 * Apply ::= "apply" DEF DEF | "apply" PRIMITIVA DEF | "apply" DEF LISTA | "apply" PRIMITIVA LISTA
 */
ASTTree apply();

/**
 * Search ::= "search" LLAVE_ABRE Listas LLAVE_CIERRA 
 */
ASTTree search();

/**
 * Listas ::= Lista COMA Lista PUNTO_COMA Listas | Lista COMA Lista
 */
ASTTree listas();

/**
 * Lista ::= DEF | COR_ABRE Elementos COR_CIERRA
 */
ASTTree lista();

/*---------------------------------------------------------------*/

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
  }

  destruir_lista(tokens);
  return ast;
}

/**
 * deff: void -> ASTTree
 * Arma poco a poco el AST que representa el comando 'deff'
 * Se representa con la siguiente gramática:
 * Deff ::= 'deff' DEF '=' Funcs | 'deff' DEF '=' Repeticion
 */
ASTTree deff() {
  // Se chequea por el tipo de token deff por si las moscas
  if (!match(TOKEN_DEFF))
    return NULL;
  ASTTree arbol_deff = crear_arbol();
  arbol_deff = crear_nodo_arbol(NULL, AST_DEFF);

  // Luego, se chequea por una definicion apropiada
  if (!match(TOKEN_DEF)) {
    error("Definición no válida\n", arbol_deff);
    return NULL;
  }

  ASTNodo *definicion = def(siguiente->prev->token);
  anadir_hijo(arbol_deff, definicion);

  // Sigue el chequeo del igual
  if (!match(TOKEN_IGUAL)) {
    error("Falta el símbolo '='\n", arbol_deff);
    return NULL;
  }

  // Finalmente, se chequea si sigue una definicion de funciones adecuada
  ASTTree arbol_funciones = funcs();

  // En caso de detectar un '<', empezar a considerar una función repetición
  if (match(TOKEN_ANG_ABRE)) {
    ASTTree arbol_repeticion = crear_arbol();
    anadir_hijo(arbol_repeticion, arbol_funciones);

    ASTTree arbol_funciones2 = funcs();

    if (!match(TOKEN_ANG_CIERRA)) {
      printf("Falta cerrar con '>'. Intente de nuevo\n");
      destruir_arbol(arbol_funciones);
      destruir_arbol(arbol_deff);
      return NULL;
    }

    anadir_hijo(arbol_repeticion, arbol_funciones2);

    ASTTree arbol_funciones3 = funcs();
    anadir_hijo(arbol_repeticion, arbol_funciones3);
    anadir_hijo(arbol_deff, arbol_repeticion);

  } else {
    anadir_hijo(arbol_deff, arbol_funciones);
  }

  return arbol_deff;
}

/**
 * defl: void -> ASTTree
 * Arma un AST que representa el comando 'defl'
 * Se representa con la siguiente gramática:
 * Defl ::= "defl" DEF IGUAL COR_ABRE Elementos COR_CIERRA
 */
ASTTree defl() {
  // Se chequea que el tipo sea el adecuado
  if (!match(TOKEN_DEFL))
    return NULL;
  ASTTree arbol_defl = crear_arbol();
  arbol_defl = crear_nodo_arbol(NULL, AST_DEFL);

  // Luego se revisa si se tiene una definición correcta
  ASTNodo *nodo_def = def();
  if (nodo_def == NULL) {
    error("Definición incorrecta\n", arbol_defl);
    return NULL;
  }
  anadir_hijo(arbol_defl, nodo_def);

  // Luego, se verifica que haya un símbolo '='
  if (!match(TOKEN_IGUAL)) {
    error("Falta el símbolo '='\n", arbol_defl);
    return NULL;
  }

  // Se verifica que se abra con un '['
  if (!match(TOKEN_COR_ABRE)) {
    error("No se abre la lista con '['\n", arbol_defl);
    return NULL;
  }

  ASTNodo* arbol_elementos = elementos();
  anadir_hijo(arbol_defl, arbol_defl);

  if(!match(TOKEN_COR_CIERRA)) {
    error("No se ha cerrado con ']'\n", arbol_defl);
    return NULL;
  }

  return arbol_defl;
}

/**
 * apply: void -> ASTTree
 * Arma un AST que representa el comando 'apply'
 * Se representa con la siguiente gramática:
 * Apply ::= "apply" DEF DEF | "apply" PRIMITIVA DEF | "apply" DEF LISTA | "apply" PRIMITIVA LISTA
 */
ASTTree apply() {
  if(!match(TOKEN_APPLY)) 
    return NULL;
  ASTTree arbol_apply = crear_arbol();
  arbol_apply = crear_nodo_arbol(NULL, AST_APPLY);
  
  // Primero, verifica que use una Definición o una Primitiva
  if(match(TOKEN_DEF)) {
    ASTNodo* nodo_def = crear_nodo_arbol(siguiente->prev->token, AST_DEF);
    anadir_hijo(arbol_apply, nodo_def);
  }
  else if(match(TOKEN_PRIMITIVA)) {
    ASTNodo* nodo_prim = crear_nodo_arbol(siguiente->prev->token, AST_PRIMITIVA);
    anadir_hijo(arbol_apply, nodo_prim);
  }
  else {
    error("Definición de función no válida\n", arbol_apply);
    return NULL;
  }

  // Luego, verifica si es un tipo de lista válida
  if(match(TOKEN_DEF)) {
    ASTNodo* nodo_def = crear_nodo_arbol(siguiente->prev->token, AST_DEF);
    anadir_hijo(arbol_apply, nodo_def);
  }
  else if(match(TOKEN_COR_ABRE)) {
    ASTTree arbol_elementos = elementos();
    anadir_hijo(arbol_apply, arbol_elementos);
    if (!match(TOKEN_COR_CIERRA)) {
      error("No se ha cerrado con ']'", arbol_apply);
      return NULL;
    }
  }
  else {
    error("No se definió de forma adecuada una lista a aplicar la función", arbol_apply);
    return NULL;
  }
}

/**
 * search: void -> ASTTree
 * Crea un arbol AST que representa el comando 'search'
 * La gramática que sigue es la siguiente:
 * Search ::= "search" LLAVE_ABRE Listas LLAVE_CIERRA 
 */
ASTTree search() {
  if(!match(TOKEN_SEARCH))
    return NULL;
  ASTTree arbol_search = crear_arbol();
  arbol_search = crear_nodo_arbol(NULL, AST_SEARCH);

  if(!match(TOKEN_LLAVE_ABRE)) {
    error("No se colocó las funciones en '{}'\n", arbol_search);
    return NULL;
  }

  ASTTree arbol_listas = listas();
  anadir_hijo(arbol_search, arbol_listas);
  
  if(!match(TOKEN_LLAVE_CIERRA)) {
    error("No se cerró con '}'\n", arbol_search);
    return NULL;
  }

  return arbol_search;
}