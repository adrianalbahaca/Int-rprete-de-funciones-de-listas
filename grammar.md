# Esta es la gramática que se va a usar en el parser:
## Sentencia principal:
```
Sentencia := Definicion ';' | Aplicacion  ';' | Busqueda ';'
```
---
## Definicion de funciones:
```
Definicion := 'deff' DEF '=' FUNCIONES | 'deff' DEF '=' REPETICION
REPETICION := FUNCION '<' FUNCION '>' FUNCION
FUNCIONES := FUNCION FUNCIONES | FUNCION
```
---
## Definicion de listas:
```
Definicion := 'defl' DEF '=' '[' ELEMENTOS ']'
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

## Terminales
```
ELEMENTOS := DIGITOS ',' ELEMENTOS | DIGITOS | ε
FUNCION := DEF | PRIMITIVA
PRIMITIVA := '0i' | '0d' | 'Si' | 'Sd' | 'Di' | 'Dd'
```