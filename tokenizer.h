#ifndef __TOKENIZER__
#define __TOKENIZER__

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
  TokenNodo *first;
  TokenNodo *last;
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