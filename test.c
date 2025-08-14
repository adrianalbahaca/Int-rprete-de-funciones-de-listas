#include <stdio.h>
#include "lexer.h"
#include "estructuras/tokens.h"

const String token[] = {
  "TOKEN_DEFF", "TOKEN_DEFL", "TOKEN_APPLY", "TOKEN_SEARCH", "TOKEN_QUIT",
  "TOKEN_DEF", "TOKEN_PRIMITIVA", "TOKEN_DIGITO",
  "TOKEN_IGUAL", "TOKEN_COR_ABRE", "TOKEN_COR_CIERRA", "TOKEN_LLAVE_ABRE", "TOKEN_LLAVE_CIERRA",
  "TOKEN_COMA", "TOKEN_PUNTO_COMA", "TOKEN_ANG_ABRE", "TOKEN_ANG_CIERRA", "TOKEN_ERROR", "TOKEN_EOF"
};

int main(void) {
    String input = get_input("==> ");
    TokenList tokens = tokenize(input);
    for (TokenNodo* n = tokens->head; n != NULL; n = n->next) {
      printf("[%s %s]->", token[n->tipo], n->token);
    }
    puts("NULL");
    liberar_string(input);
    destruir_lista(tokens);
    return 0;
}
