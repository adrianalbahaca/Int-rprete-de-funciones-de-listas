#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int main(void) {
    string s = getInput("Ingresar dato: ");
    printf("%s", s);
    free(s);
    return 0;
}