#ifndef __TOKENIZER__
#define __TOKENIZER__

/**
 * Por conveniencia, se declara char* como string
 */

typedef char* String;

/**
 * Se declara la lista de tipos de tokens que puede tener cada token
 */
typedef enum {

  /**
   * TODO: Necesito que los tokens de comandos estén de primero para que mi código funcione
   * Hay alguna manera más adecuada para evitar tener que hacer esto, y que no importe dónde los
   * coloque?
   */
  TOKEN_DEFF, TOKEN_DEFL, TOKEN_APPLY, TOKEN_SEARCH, TOKEN_QUIT,

  TOKEN_DEF, TOKEN_PRIMITIVA, TOKEN_DIGITO,
  TOKEN_IGUAL, TOKEN_COR_ABRE, TOKEN_COR_CIERRA, TOKEN_LLAVE_ABRE, TOKEN_LLAVE_CIERRA,
  TOKEN_COMA,TOKEN_PUNTO_COMA, TOKEN_ANG_ABRE, TOKEN_ANG_CIERRA, TOKEN_ERROR, TOKEN_EOF,
} TipoDeToken;

/**
 * Se declara la lista de tokens como una lista simplemente enlazada que guarda
 * el token como un String y el tipo de token
 */

typedef struct _TokenNodo {
  String token;
  TipoDeToken tipo;
  struct _TokenNodo *sig;
  struct _TokenNodo *ant;
} TokenNodo;

/**
 * str_dup: String -> String
 * Asigna el espacio necesario para duplicar un string a otro
 * (Como strdup no está en el estándar C99, me tocó escribir la función)
 */
String str_dup(const String s);

/**
 * getInput: String -> String
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
String get_input(String mensaje);

/**
 * tokenize: String -> TokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
TokenNodo* tokenize(String tokens);

#endif /* __TOKENIZER__ */