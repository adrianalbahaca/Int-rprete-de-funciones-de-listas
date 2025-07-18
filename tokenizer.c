#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

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
 * str_dup: String -> String (Función auxiliar)
 * Asigna el espacio en necesario para duplicar un string a otro
 */

String str_dup(const String s) {
    size_t size = strlen(s) + 1;
    String p = malloc(size);
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
  list->first = list->last = NULL;
  
  return list;
}

/**
 * anadir_token: TokenList String -> TokenList (Función auxiliar)
 * Añade el token dado al final de la lista de tokens
 */
TokenList anadir_token(TokenList l, String token) {

  // Crear nodo y copiar el token allí

  TokenNodo *nodo = malloc(sizeof(TokenNodo));
  assert(nodo);
  nodo->token = str_dup(token);
  nodo->sig = NULL;

  // Caso 1: Lista vacía
  if (l->first == NULL && l->last == NULL) {
    l->first = l->last = nodo;
  }
  else {
    l->last->sig = nodo;
    l->last = nodo;
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
    static char simbolo[2];
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

/**
 * tokenize: String -> tokenList
 * Toma un string y tokeniza cada palabra en una lista simplemente enlazada de tokens
 */
TokenList tokenize(String tokens) {

  // Primero, si el string está vacío, no hacer nada

  assert(tokens);

  // Sino, se crea la lista

  TokenList list = crear_lista();

  // Se busca el primer token
  String token = string_a_token(tokens, " ");

  while (token) {
    list = anadir_token(list, token);
    token = string_a_token(NULL, " ");
  }

  return list;
}
