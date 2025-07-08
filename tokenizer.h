#ifndef __TOKENIZER__
#define __TOKENIZER__

typedef char* string;

/**
 * Se declara la lista de tokens como una lista simplemente enlazada,
 * y una estructura que apunta al principio y final
 */

typedef struct _tokenNodo {
    string token;
    struct _tokenNodo *sig;
} tokenNodo;

typedef struct _tokenList {
    tokenNodo *first;
    tokenNodo *last;
} tokenList;

/**
 * getInput: string -> string
 * Recibe un string que se mostrará al usuario, y luego solicita una entrada al usuario
 */
string getInput(string mensaje);

/**
 * tokenize: string -> tokenList
 * Tokeniza cada parte del string en una lista de tokens, para después ser procesado
 */
tokenList tokenize(string input);

#endif /* __TOKENIZER__ */