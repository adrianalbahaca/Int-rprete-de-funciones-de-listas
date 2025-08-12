#include <stdio.h>
#include "tokenizer.h"
#include "ast.h"

const String token[] = {
  "TOKEN_DEFF", "TOKEN_DEFL", "TOKEN_APPLY", "TOKEN_SEARCH", "TOKEN_QUIT",
  "TOKEN_DEF", "TOKEN_PRIMITIVA", "TOKEN_DIGITO",
  "TOKEN_IGUAL", "TOKEN_COR_ABRE", "TOKEN_COR_CIERRA", "TOKEN_LLAVE_ABRE", "TOKEN_LLAVE_CIERRA",
  "TOKEN_COMA", "TOKEN_PUNTO_COMA", "TOKEN_ANG_ABRE", "TOKEN_ANG_CIERRA", "TOKEN_ERROR", "TOKEN_EOF"
};

int main(void) {
    String input = get_input("Inserte un comando ==> ");
    TokenNodo* tokens = tokenize(input);
    for (TokenNodo* n = tokens; n != NULL; n = n->sig) {
        printf("[%s %s]->", n->token, token[n->tipo]);
    }
    puts("NULL");
    return 0;
}
