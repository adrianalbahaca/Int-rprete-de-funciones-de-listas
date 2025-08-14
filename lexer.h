#ifndef __LEXER__
#define __LEXER__
#include "estructuras/string-auxiliar.h"
#include "estructuras/tokens.h"

/**
 * getInput: String -> String
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
String get_input(String mensaje);

/**
 * tokenize: String -> TokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
TokenNodo* tokenize(String tokens);

#endif /* __TOKENIZER__ */