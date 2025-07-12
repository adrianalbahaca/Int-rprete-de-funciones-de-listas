#ifndef __TOKENIZER__
#define __TOKENIZER__

typedef char* String;

typedef struct _TokenNodo TokenNodo;

typedef struct _TokenList* TokenList;

/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
String getInput(String mensaje);

/**
 * tokenize: string -> tokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
TokenList tokenize(String tokens);

#endif /* __TOKENIZER__ */