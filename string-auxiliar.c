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