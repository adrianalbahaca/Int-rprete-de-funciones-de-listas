#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * Se declara la lista de tokens con una estructura que apunta al principio y fin de la
 * lista, por practicidad al añadir tokens
 */

struct _TokenList {
  TokenNodo *head;
  TokenNodo *tail;
};

typedef struct _TokenList *TokenList;

/* ------ Funciones Auxiliares ------ */

/**
 * es_comando_válido: String -> bool
 * Retorna true si el token dado es válido como comando, y false sino
 */
bool es_comando_valido(String token) {
  int tam = sizeof(comandos) / sizeof(comandos[0]);
  for (int i = 0; i < tam; i++) {
    if (strcmp(token, comandos[i]) == 0) return true;
  }
  return false;
}

/**
 * es_primitiva: String -> bool
 * Retorna true si el string dado es un tipo de función primitiva, y false si no lo es
 */
bool es_primitiva(String token) {
  int cantPrimitivas = sizeof(primitivas) / sizeof(primitivas[0]);
  for (int i = 0; i < cantPrimitivas; i++) {
    if (strcmp(token, primitivas[i]) == 0) return true;
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

  // Primero, verifico si el token no es nulo

  if (token == NULL) {
    tipo = TOKEN_EOF;
    return tipo;
  }

  if (strlen(token) == 1 && ispunct(token[0])) {
    switch(token[0]) {
      case '{':
        tipo = TOKEN_LLAVE_ABRE;
        break;
      case '}':
        tipo = TOKEN_LLAVE_CIERRA;
        break;
      case '[':
        tipo = TOKEN_COR_ABRE;
        break;
      case ']':
        tipo = TOKEN_COR_CIERRA;
        break;
      case ';':
        tipo = TOKEN_PUNTO_COMA;
        break;
      case ',':
        tipo = TOKEN_COMA;
        break;
      case '=':
        tipo = TOKEN_IGUAL;
        break;
      case '<':
        tipo = TOKEN_ANG_ABRE;
        break;
      case '>':
        tipo = TOKEN_ANG_CIERRA;
        break;
      default:
        tipo = TOKEN_ERROR;
        break;
    }
  }

  // Sino, verifico si es un tipo de palabra válida
  
  else {
    if(es_comando_valido(token)) {
      tipo = comando(token);
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
 * str_dup: String -> String (Función auxiliar)
 * Asigna el espacio necesario para duplicar un string a otro
 */
String str_dup(const String s) {
    size_t size = strlen(s) + 1;
    String p = malloc(size);
    assert(p);
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}

/**
 * crear_lista: void -> TokenList (Función auxiliar)
 * Crea una lista simplemente enlazada de tokens vacía
 */
TokenList crear_lista() {

  TokenList list = malloc(sizeof(struct _TokenList));
  assert(list);
  list->head = list->tail = NULL;
  
  return list;
}

/**
 * anadir_token: TokenList String -> TokenList (Función auxiliar)
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
  else {
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
  size_t capacity = 0, size = 0;  // Capacidad del buffer y tamaño real
  int c;  // Caracter leído

  while ((c = fgetc(stdin)) != '\n' && c != EOF) {

    // Hacer crecer el buffer si es necesario
    if ((size + 1) > capacity) {

      /* Si la capacidad no sobrepasa el limite de tamaño, aumentarlo */

      if (capacity < SIZE_MAX)
        capacity++;
      else {                    // Sino, abortar y no retornar nada
        free(buffer);
        return NULL;
      }

      // Extender el buffer

      String temp = realloc(buffer, capacity * (sizeof(char)));
      if (temp == NULL) {
        free(buffer);
        return NULL;
      }
      buffer = temp;
    }
    // Meter el caracter en el buffer

    buffer[size++] = c;
  }

  // Si el usuario no dió ninguna entrada, abortar y retornar NULL

  if (size == 0 && c == EOF) {
    free(buffer);
    return NULL;
  }

  // Minimizar el buffer

  String s = malloc((size + 1) * (sizeof(char)));
  if (s == NULL) {
    free(buffer);
    return NULL;
  }

  // Copiar lo que contiene el buffer en s con el tamaño real del string

  strncpy(s, buffer, size);

  // Terminar string
  s[size] = '\0';

  free(buffer);

  return s;

}

/**
 * tokenize: String -> tokenList
 * Toma un string y tokeniza cada palabra en una lista simplemente enlazada de tokens
 */
TokenNodo* tokenize(String tokens) {

  // Primero, si el string está vacío, no hacer nada

  assert(tokens);

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
