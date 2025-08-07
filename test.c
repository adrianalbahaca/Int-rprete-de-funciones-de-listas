#include <stdio.h>
#include "tokenizer.h"
#include "ast.h"

int main(void) {
    TokenList input = tokenize("Inserte un comando ==>");
    for (TokenNodo* n = input->head; n != NULL; n = n->sig) {
        printf("[%s %s]->", n->token, n->tipo);
    }
    return 0;
}
