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
 * Primero, determino los tipos de nodos que pueden haber
 */
typedef enum {

    // Primero, se define los tipos de nodo raíz

    DEFF_FUNCION, // Definicion := 'deff' DEF '=' FUNCIONES | 'deff' DEF '=' REPETICION
    DEFL_LISTA, // 'defl' DEF '=' '[' ELEMENTOS ']'
    APPLY, // 'apply' FUNCION LISTA
    SEARCH, // 'search' '{' LISTAS '}'

    // Luego, se define los nodos hoja

    DEF, // String a asociar a una lista
    PRIMITIVA, // PRIMITIVA := '0i' | '0d' | 'Si' | 'Sd' | 'Di' | 'Dd'
    DIGITO, // Número entero

    // Tipos de Sentencia

    LISTAS,
    LISTA,
    ELEMENTOS,

    // Finalmente, símbolos
    COMA,
    PUNTO_COMA,
    LLAVE_APERTURA,
    LLAVE_CIERRE,
    CORCHETE_APERTURA,
    CORCHETE_CIERRE

} TipoDeNodo;

/**
 * Se declara la lista de tokens como una lista simplemente enlazada que guarda
 * cadenas
 */

struct _TokenNodo {
  TipoDeNodo tipo;
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