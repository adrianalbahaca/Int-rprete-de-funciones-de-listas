#include "string-auxiliar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

const String primitivas[] = {"0i", "0d", "Si", "Sd", "Di", "Dd"};
const int primitivas_tam = sizeof(primitivas) / sizeof(primitivas[0]);

const String comandos[] = {"deff", "defl", "apply", "search", "quit"};
const int comandos_tam = sizeof(comandos) / sizeof(comandos[0]);

/**
 * str_dup: String -> String
 * Asigna el espacio necesario para duplicar un string a otro.
 * Básicamente, hace lo mismo que strdup(), pero como no está en el estándar C99
 * aparentemente, me toca escribir la función
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