# Esta es la gramática que se va a usar en el parser:
```
Sentencia ::= <DEFINICION>; | <APLICACION>; | <BUSQUEDA>;
DEFINICION ::= 'deff' <ID> '=' <EXPRESION> | 'defl' <ID> = <LISTA>
APLICACION ::= apply <EXPRESION1> <LISTA>
BUSQUEDA ::= search <PAR>
```
---
## Definición de las expresiones
```
EXPRESION ::= <FBASE> <EXPRESION> | <FBASE> | <FCREADA> <EXPRESION> | <FCREADA>
EXPRESION1 ::= <FBASE> | <FCREADA>
```
---
## Definición de un par de listas
```
<PAR> ::= <LISTA> <LISTA> ', ' <PAR> | <LISTA> <LISTA>
```
---
## Definición de una lista
```
LISTA ::= '['<ELEMENTOS>']'
ELEMENTOS ::= <ELEMENTO> <RESTOELEMENTOS> | ε
RESTOELEMENTOS ::= ', ' <ELEMENTO> <RESTOELEMENTOS> | ε
ELEMENTO ::= <DIGITOS>
DIGITOS ::= <DIGITO><DIGITOS> | <DIGITO>
DIGITO ::= 1 | 2| 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
```
---
## Definición de funciones
```
FBASE ::= '0i' | '0d' | 'Si' | 'Sd' | 'Di' | 'Dd'
FCREADA ::= Y aquí es donde no sé cómo se va a guardar todo
```