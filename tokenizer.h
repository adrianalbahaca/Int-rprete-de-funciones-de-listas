#ifndef __TOKENIZER__
#define __TOKENIZER__

/**
 * TODO: Diseñar los tipos de cada token. Son los siguientes:
 * 1. Nodos de la sentencia: Busqueda, Aplicacion y Definicion
 * 2. Nodos hoja (Terminales): DEF, DIGITO, PRIMITIVA
 * 3. Nodos intermedios (No terminales): FUNCION, FUNCIONES, LISTA, LISTAS, etc
 * 4. Símbolos: cosas como las comas, puntos y comas, corchetes angulados y llaves
 */

/**
 * Por convección, se declara char* como string
 */

typedef char *String;

/**
 * Se declara la lista de tokens como una lista simplemente enlazada que guarda
 * cadenas
 */

struct _TokenNodo {
  String token;
  struct _TokenNodo *sig;
};

typedef struct _TokenNodo TokenNodo;

/**
 * Se declara la lista de tokens con una estructura que apunta al principio y fin de la
 * lista, por practicidad al añadir tokens
 */

struct _TokenList {
  TokenNodo *head;
  TokenNodo *tail;
};

typedef struct _TokenList *TokenList;

/**
 * getInput: String -> String
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
String get_input(String mensaje);

/**
 * tokenize: String -> TokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
TokenList tokenize(String tokens);

#endif /* __TOKENIZER__ */