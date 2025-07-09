#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

/**
 * Por convección y practicidad, se declara char* como string
 */

typedef char* string;

/**
 * Se declara la lista de tokens como una lista simplemente enlazada,
 * y una estructura que apunta al principio y final
 */
struct _tokenNodo {
    string token;
    struct _tokenNodo *sig;
};

typedef struct _tokenNodo tokenNodo;

struct _tokenList {
    tokenNodo *first;
    tokenNodo *last;
};

typedef struct _tokenList* tokenList;


/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario. Luego, solicita una entrada al usuario
 */
string getInput (string message) {
    
    printf("%s", message);

    // Inicialización de variables

    string buffer = NULL; // Guardado temporal de la entrada del usuario
    size_t capacity = 0, size = 0; // Capacidad del buffer y 
    int c; // Caracter leído

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {

        // Hacer crecer el buffer si es necesario
        if ((size + 1) > capacity) {

            /* Si la capacidad no sobrepasa el limite de tamaño, aumentarlo */

            if (capacity < SIZE_MAX)
                capacity++;
            else { // Sino, abortar y no retornar nada
                free(buffer);
                return NULL;
            }

            // Extender el buffer

            string temp = realloc(buffer, capacity * (sizeof(char)));
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

    string s = malloc((size + 1) * (sizeof(char)));
    if (s == NULL) {
        free(buffer);
        return NULL;
    }

    strncpy(s, buffer, size);

    // Terminar string
    s[size] = '\0';

    free(buffer);

    return s;

}

tokenList tokenize (string tokens) {
    return NULL;
}