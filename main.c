#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "ast.h"
#include "execute.h"

int main(void) {
    // Título
    printf("Trabajo final: Parser de funciones de listas. Adrian Albahaca | A-4708/2");

    // Se usa un booleano para indicar cuándo se sale del shell
    bool quit = true;
    
    while(quit) {
        
        String command = getInput("==> ");
        assert(command != NULL);

        TokenList tokens = tokenize(command);

        ASTTree ast = parse(tokens);

        /**
         * TODO: Crear una función que recibe el AAS y ejecuta cada instrucción de cada nodo
         */
        execute(ast);
    }
    return 0;
}
