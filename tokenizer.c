#include "tokenizer.h"
#include "glist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

/**
 * Por convección y practicidad, se declara char* como string
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

typedef struct _TokenNodo *TokenNodo;

/**
 * Se declara la lista de tokens con una estructura que apunta al principio y fin de la
 * lista, por practicidad
 */

struct _TokenList {
  TokenNodo first;
  TokenNodo last;
};

typedef struct _TokenList *TokenList;

TokenList guardar_token(TokenList l, String token);

/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario. Luego, solicita una entrada al usuario
 */
String getInput(String message) {

  // Mostrar el mensaje al usuario

  printf("%s", message);

  // Inicialización de variables

  String buffer = NULL;         // Guardado temporal de la entrada del usuario
  size_t capacity = 0, size = 0;        // Capacidad del buffer y tamaño real
  int c;                        // Caracter leído

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
 * tokenize: string -> tokenList
 * Toma un string y tokeniza cada palabra en una lista simplemente enlazada de tokens
 */
TokenList tokenize(String tokens) {

  // Primero, si el string está vacío, no hacer nada

  if (tokens == NULL) {
    return NULL;
  }

  // Sino, se continua con el proceso

  /**
   * TODO: Comprimir funciones de la lista de tokens en funciones anónimas
   */

  TokenList list = malloc(sizeof(TokenList));
  list->first = list->last = NULL;

  // Primero, se escanea el primer token y se guarda en la lista

  String s = strtok(tokens, " ");

  while (s != NULL) {
    list = guardar_token(list, s);
    s = strtok(NULL, " ");
  }

  return list;
}

TokenList guardar_token(TokenList l, String token) {

  // Crear nodo

  TokenNodo nodo = malloc(sizeof(TokenNodo));
  strcpy(nodo->token, token);
  nodo->sig = NULL;

  if (l->first == l->last == NULL) { // Caso 1: Lista vacía
    l->first = l->last = nodo;
  }
  else { // Caso 2: Lista con elementos. Añadir al final
    l->last->sig = nodo;
    l->last = nodo;
  }

  return l;

}
