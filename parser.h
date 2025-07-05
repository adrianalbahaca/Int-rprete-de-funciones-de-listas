#ifndef __PARSER__
#define __PARSER__

/* 
    Nada más por conveniencia, represento char* como string, porque a la final
    eso es lo que es una cadena, un puntero al principio de un arreglo de caracteres
    terminado en '\0'
*/

typedef char *string;

/**
 * TODO: Cómo se representa el árbol de síntax abstracto?
 */

/**
 * Se representa TokenList con una lista de cadenas simplemente enlazada, usando punteros al principio
 * y final de la misma
 */

typedef struct _TokenNodo{
    string token;
    struct _TokenNodo *sig;
} TokenNodo;

typedef struct _TokenList {
    TokenNodo *start;
    TokenNodo *end;
} TokenList;

/**
 * getInput: string -> string
 * Solicita al usuario un comando, y lo guarda en un arreglo de caracteres (una cadena)
 */
string getInput(string message);

/**
 * tokenize: string -> TokenList
 * Recibe una cadena y tokeniza cada caracter, devolviendo una lista con los tokens
 */
TokenList tokenize(string tokens);

/**
 * parse: TokenList -> ??
 * TODO: Crear Árbol de Síntax Abstracto y hacer la función 'parse', que recibe la lista de tokens
 * y crea el árbol a partir de la gramática determinada
 */

/**
 * execute: ASA -> void
 * TODO: Crea una función que se encargue de ejecutar todo lo que el usuario haya pedido. Hay que
 * buscar una forma de guardar las funciones que crea el usuario, para después poder implementarlas
 */


#endif /* __PARSER__ */