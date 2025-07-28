#ifndef __TOKENIZER__
#define __TOKENIZER__

/**
 * TODO: Diseñar los tipos de cada token. Son los siguientes:
 * 1. Nodos de la sentencia: Busqueda, Aplicacion y Definicion
 * 2. Nodos hoja (Terminales): DEF, DIGITO, PRIMITIVA
 * 3. Nodos intermedios (No terminales): FUNCION, FUNCIONES, LISTA, LISTAS, etc
 * 4. Símbolos: cosas como las comas, puntos y comas, corchetes angulados y llaves
 */

const String primitivas[] = {"0i", "0d", "Si", "Sd", "Di", "Dd"};

/**
 * Se declara la lista de tipos de tokens que puede tener cada token
 */
typedef enum {
  TOKEN_DEFF, TOKEN_DEFL, TOKEN_APPLY, TOKEN_SEARCH,
  TOKEN_DEF, TOKEN_PRIMITIVA, TOKEN_DIGITO, TOKEN_COR_ABRE,
  TOKEN_COR_CIERRA, TOKEN_LLAVE_ABRE, TOKEN_LLAVE_CIERRA, TOKEN_COMA,
  TOKEN_PUNTO_COMA, TOKEN_ERROR, TOKEN_EOF
} TipoDeToken;

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
  TipoDeToken tipo;
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