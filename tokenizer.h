#ifndef __TOKENIZER__
#define __TOKENIZER__

typedef char* string;

typedef struct _tokenNodo tokenNodo;

typedef struct _tokenList* tokenList;

/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
string getInput(string mensaje);

/**
 * tokenize: string -> tokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
tokenList tokenize(string tokens);

#endif /* __TOKENIZER__ */