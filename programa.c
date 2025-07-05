#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

int main(void) {
    // Título
    printf("Trabajo final: Parser de funciones de listas. Adrian Albahaca | A-4708/2");

    // Se usa un booleano para indicar cuándo se sale del shell
    bool quit = true;
    while(quit) {
        /**
         * TODO: Crear una función que reciba un string para mostrarlo en pantalla, y retorne
         * el string ingresado por el usuario, sin importar su largo
         */
        string command = getInput("==> ");

        if (/* Comando es quit */) {
            quit = false;
            break;
        }

        /**
         * TODO: Crear una función que recibe el input y tokeniza cada elemento, agarrando
         * cada error que se pueda formar, retornando una lista de tokens
         */
        TokenList *tokens = tokenizate(command);

        /**
         * TODO: Crear una función que recibe la lista de tokens y lo convierte en un
         * Árbol Abstracto de Sintaxis (AAS)
         */
        ASTNodo *ast = parse(tokens);

        /**
         * TODO: Crear una función que recibe el AAS y ejecuta cada instrucción de cada nodo
         */
        execute(ast);
    }
    return 0;
}