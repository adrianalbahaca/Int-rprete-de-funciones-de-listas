#include "tokenizer.h"
#include "string-auxiliar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * Se declara la lista de tokens en este archivo con una estructura que apunta al principio y fin de la
 * lista, por practicidad al añadir tokens. Esta estructura es temporal para el proceso de
 * tokenización
 */

typedef struct __TokenList {
  TokenNodo *head;
  TokenNodo *tail;
} _TokenList;

typedef _TokenList *TokenList;

/* ------ Funciones Auxiliares ------ */

/**
 * es_simbolo: String -> bool
 * Retorna true si es un símbolo, y false si no lo es
 */
bool es_simbolo(String token) {
  return (strlen(token) == 1 && ispunct(token[0]));
}

/**
 * tipo_simbolo: String -> TipoDeToken
 * Retorna el tipo de token acorde al tipo de símbolo que es. Si no es ningún símbolo válido
 * retorna el TOKEN_ERROR
 */
TipoDeToken tipo_simbolo(String token) {
   switch(token[0]) {
      case '{':
        return TOKEN_LLAVE_ABRE;

      case '}':
        return TOKEN_LLAVE_CIERRA;

      case '[':
        return TOKEN_COR_ABRE;

      case ']':
        return TOKEN_COR_CIERRA;

      case ';':
        return TOKEN_PUNTO_COMA;

      case ',':
        return TOKEN_COMA;

      case '=':
        return TOKEN_IGUAL;

      case '<':
        return TOKEN_ANG_ABRE;

      case '>':
        return TOKEN_ANG_CIERRA;

      default:
        return TOKEN_ERROR;
    }
}

/**
 * es_comando_válido: String -> bool
 * Retorna true si el token dado es válido como comando, y false sino
 */
bool es_comando_valido(String token) {
  for (int i = 0; i < comandos_tam; i++) {
    if (!strcmp(token, comandos[i])) return true;
  }
  return false;
}

/**
 * tipo_comando: String -> TipoDeToken
 * Retorna el tipo de token acorde al tipo de comando dado. Si no es ningún comando válido
 * retorna el TOKEN_ERROR
 */
/**
 * TODO: Ver cómo corregir esta función para que no importe dónde esté los tokens en el enum
 */
TipoDeToken tipo_comando(String token) {
  for (int i = 0; i < comandos_tam; i++) {
    if(!strcmp(token, comandos[i])) return (TipoDeToken)(TOKEN_DEFF + i);
  }
  return TOKEN_ERROR;
}

/**
 * es_primitiva: String -> bool
 * Retorna true si el string dado es un tipo de función primitiva, y false si no lo es
 */
bool es_primitiva(String token) {
  for (int i = 0; i < primitivas_tam; i++) {
    if (!strcmp(token, primitivas[i])) return true;
  }
  return false;
}

/**
 * es_digito: String -> bool
 * Retorna true si un string solo tiene numeros. Sino, retorna false
 */
bool es_digito(String numero) {
  for (int i = 0; i < (int)strlen(numero); i++) {
    if(!isdigit(numero[i])) {
      return false;
    }
  }
  return true;
}

/**
 * es_def_valido: String -> bool
 * Retorna true si la definicion es válida. Sino, es false
 */
bool es_def_valida(String def) {

  // Si empieza con un número o un caracter no permitido, no es def válida
  if(!(isalpha(def[0]) || (def[0] == '_'))) return false;

  // Si dentro del string hay elementos no válidos, no es def válida
  for (int i = 1; i < (int)strlen(def); i++) {
    if(!(isalnum(def[i]) || def[i] == '_')) return false;
  }

  return true;
}

/**
 * tipo_token: String -> TipoDeToken
 * Detecta si un string dado es un token válido a usar, y retorna el tipo de
 * token acorde. Si no lo es, retorna el tipo TOKEN_ERROR
 */
TipoDeToken tipo_token(String token) {

  TipoDeToken tipo;

  if (token == NULL) return TOKEN_EOF;

  if (es_simbolo(token)) {
   tipo = tipo_simbolo(token);
  }
  else {
    if(es_comando_valido(token)) {
      tipo = tipo_comando(token);
    }
    else if (es_primitiva(token)) {
      tipo = TOKEN_PRIMITIVA;
    }
    else if (es_digito(token)) {
      tipo = TOKEN_DIGITO;
    }
    else if(es_def_valida(token)) {
      tipo = TOKEN_DEF;
    }
    else {
      tipo = TOKEN_ERROR;
    }
  }

  return tipo;
}

/**
 * crear_lista: void -> TokenList
 * Crea una lista simplemente enlazada de tokens vacía
 */
TokenList crear_lista() {

  TokenList list = malloc(sizeof(_TokenList));
  assert(list);
  list->head = list->tail = NULL;
  
  return list;
}

/**
 * anadir_token: TokenList String -> TokenList
 * Añade el token dado al final de la lista de tokens
 */
TokenList anadir_token(TokenList l, String token, TipoDeToken tipo) {

  // Crear nodo y copiar el token allí
  TokenNodo *nodo = malloc(sizeof(TokenNodo));
  assert(nodo);
  nodo->token = str_dup(token);
  nodo->tipo = tipo;
  nodo->sig = NULL;

  // Caso 1: Lista vacía
  if (l->head == NULL && l->tail == NULL) {
    nodo->ant = NULL;
    l->head = l->tail = nodo;
  }
  else { // Caso 2: Lista con elementos
    l->tail->sig = nodo;
    nodo->ant = l->tail;
    l->tail = nodo;
  }

  return l;

}

/**
 * string_a_token: String -> String
 * Retorna cada token de la cadena, como los símbolos, identificadores, números, etc
 * Es como strtok, pero personalizado para lo que necesito
 */
String string_a_token (String cadena, String delimitador) {

  static String retorno;
  static int pos;

  // Si la cadena dada no es NULL, asignar retorno a cadena
  if (cadena) {
    retorno = cadena;
    pos = 0;
  }

  // Si ya no queda más elementos por tokenizar, retornar NULL
  if (retorno == NULL) return NULL;

  // Saltar delimitadores
  while (retorno[pos] && strchr(delimitador, retorno[pos])) pos++;

  // Si llego al final del string, retornar NULL
  if (retorno[pos] == '\0') return NULL;

  int start = pos;

  // Si se llega a un símbolo, guardarlo y retornarlo
  if (ispunct(retorno[pos])) {
    String simbolo = malloc(sizeof(char) * 2);
    assert(simbolo);
    simbolo[0] = retorno[pos];
    simbolo[1] = '\0';
    pos++;
    return simbolo;
  }

  // Sino, recorrer la palabra y guardarla en un string nuevo
  while ((retorno[pos] && isalnum(retorno[pos])) || retorno[pos] == '_') pos++;

  int largo = pos - start;

  String token = malloc((largo + 1));
  assert(token);
  strncpy(token, retorno + start, largo);
  token[largo] = '\0';

  return token;

}

/* ---------------------------------- */

/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario. Luego, solicita una entrada al usuario
 */
String get_input(String message) {

  // Mostrar el mensaje al usuario
  printf("%s", message);

  // Inicialización de variables
  String buffer = NULL; // Guardado temporal de la entrada del usuario
  size_t capacidad = 0, tam = 0;  // Capacidad del buffer y tamaño real
  int c;  // Caracter leído

  while ((c = fgetc(stdin)) != '\n' && c != EOF) {

    // Hacer crecer el buffer si es necesario
    if ((tam + 1) > capacidad) {

      // Si la capacidad no sobrepasa el tamaño máximo que permite la computadora, aumentarlo
      if (capacidad < SIZE_MAX) capacidad++;

      // Sino, liberar buffer y retornar NULL para indicar un error
      else {
        free(buffer);
        return NULL;
      }

      // Extender el buffer
      String temp = realloc(buffer, capacidad * (sizeof(char)));
      assert(temp != NULL);
      buffer = temp;
    }
    // Meter el caracter en el buffer

    buffer[tam++] = c;
  }

  // Si el usuario no dió ninguna entrada, abortar y retornar NULL

  if (tam == 0 && c == EOF) {
    free(buffer);
    return NULL;
  }

  // Minimizar el buffer

  String s = malloc((tam + 1) * (sizeof(char)));
  if (s == NULL) {
    free(buffer);
    return NULL;
  }

  // Copiar lo que contiene el buffer en s con el tamaño real del string

  strncpy(s, buffer, tam);

  // Terminar string
  s[tam] = '\0';

  // Liberar el buffer y retornar
  free(buffer);
  return s;
}

/**
 * tokenize: String -> tokenList
 * Toma un string y tokeniza cada palabra en una lista simplemente enlazada de tokens
 */
TokenNodo* tokenize(String tokens) {

  // Primero, si el string está vacío, no hacer nada
  if (tokens == NULL) return NULL;

  // Sino, se crea la lista
  TokenList list = crear_lista();

  // Se busca el primer token
  String token = string_a_token(tokens, " ");
  TipoDeToken tipo = tipo_token(token);

  // Luego, se va añadiendo y buscando cada token para guardarlo
  while (token) {
    list = anadir_token(list, token, tipo);
    free(token);
    token = string_a_token(NULL, " ");
    tipo = tipo_token(token);
  }

  // Si todo sale bien, se retorna la lista sin la estructura y se libera la estructura
  TokenNodo* retorno = list->head;
  list->head = list->tail = NULL;
  free(list);

  return retorno;
}
