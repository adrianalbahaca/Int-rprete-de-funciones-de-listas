# Esta es la gramática que se va a usar en el parser:
## Sentencia principal:
```
Sentencia := Definicion ';' | Aplicacion  ';' | Busqueda ';'
```
---
## Definicion de funciones:
```
Definicion := 'deff' DEF '=' FUNCIONES | 'deff' DEF '=' REPETICION
FUNCIONES := FUNCION FUNCIONES | FUNCION
FUNCION := DEF | PRIMITIVA
PRIMITIVA := '0i' | '0d' | 'Si' | 'Sd' | 'Di' | 'Dd'
```
---
## Definicion de listas:
```
Definicion := 'defl' DEF '=' '[' ELEMENTOS ']'
ELEMENTOS := ELEMENTO | ε
ELEMENTO := DIGITOS ',' ELEMENTO | DIGITOS
```
---
## Definición de aplicación de funciones:
```
Aplicacion := 'apply' FUNCION LISTA
LISTA := DEF | '[' ELEMENTOS ']'
```
---
## Definicion de búsqueda
```
Busqueda := 'search' '{' LISTAS '}'
LISTAS := LISTA ',' LISTA ';' LISTAS | LISTA ',' LISTA
```
---
## Definición de reconocimiento de números naturales y letras
```
DEF := LETRA | LETRA DEF
LETRA := LETRA_MAYUSCULA | LETRA_MINUSCULA | DIGITO
LETRA_MAYUSCULA := 'A' | 'B' | ... | 'Z' | [otras letras Unicode mayúsculas]
LETRA_MINUSCULA := 'a' | 'b' | ... | 'z' | [otras letras Unicode minúsculas]
DIGITOS ::= DIGITO DIGITOS | DIGITO
DIGITO ::= 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
```