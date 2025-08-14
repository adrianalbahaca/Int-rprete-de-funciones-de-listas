# Proyecto final de EDyA1: Parser de funciones de lista (EN PAUSA HASTA TERMINAR MESA DE EXÁMENES)
Este proyecto trabaja con funciones de lista, analizando el input de un usuario, siguiendo una gramática que se asegure de que cumpla con la gramática dada en la práctica

## Funciones base:
 - `0i`: Añade un cero al extremo izquierdo de una lista
 - `0d`: Añade un cero al extremo derecho de una lista
 - `Si`: Le suma 1 al valor del extremo izquierdo de una lista (Lista no vacía)
 - `Sd`: Le suma 1 al valor del extremo derecho de una lista (Lista no vacía)
 - `Di`: Elimina el valor del extremo izquierdo de una lista (Lista no vacía)
 - `Dd`: Elimina el valor del extremo derecho de una lista (Lista no vacía)

## Composición:
Se construye funciones de listas, a partir de funciones de lista, con el comando deff  
Ej: `deff f = 0d 0i Sd Sd Si 0d Sd; -> [2, 1, 1]`

## Repetición:
Usando una función de listas, se puede definir una función repetición, notada como:  
`<f> [x, X, y] = {[x, X, y] si x == y, <f>(f[x, X, y]) si x != y}` (x, y son elementos y X es una lista, posiblemente vacía)  
Ej: `deff Mi = 0i <Si> Dd;`

## Definición de listas:
Se pueden definir listas de forma directa usando el comando `defl`   
Ej: `defl L1 = [0, 2, 4 ,8];`

## Búsqueda:
El comando search genera una función de listas que convierte a la lista L1 en la lista L2  
Ej: `L1 = [0, 1, 2]; L2 = [1, 2, 3]; => search { L1, L2 }; -> Si Md Si Md Si Md;`
(Notar que pueden haber pares de listas que no tengan solución)

 # Al pendiente por separación de archivos
 - lexer.h: Tokeniza el input del usuario y lo guarda en una lista doblemente enlazada
    - dlist.h: Funciones que manejan una lista doblemente enlazada
 - parser.h: Procesa los tokens y arma el ast apropiado
    - gtree.h: Funciones que manejan un árbol general
 - execute.h: Procesa el AST y ejecuta los comandos
    - tablashash.h: Funciones que procesan una tabla hash
    - slist.h: Funciones que procesan una lista simplemente enlazada

# Cosas por hacer
 - [ ] Terminar los archivos `tokens.h` y `tokens.c`, que lidia con una lista doblemente enlazada de tokens
 - [ ] Terminar los archivos `lexer.c` y `lexer.h`, que tokeniza la entrada del usuario
 - [ ] Terminar los archivos `ast.c` y `ast.h` que guarda la estructura del AST, con sus funciones para manejarlo, añadirle hijos y eliminarlo
 - [ ] Terminar los archivos `parser.c` y `parser.h`, el parser recursivo descendente, que arma poco a poco el AST acorde a la gramática libre de contexto, y verifica si hay errores. La forma de lidiar con errores es borrando todo el AST y pidiendo el comando de nuevo
 - [ ] Terminar los archivos `tablas.c` y `tablas.h`, que guarda las estructuras de las tablas hash para guardar las funciones y las listas
 - [ ] Terminar los archivos `execute.h` y `execute.c` que implementa los comandos usando los parámetros, de acuerdo al AST dado
 - [ ] Crear una función `main.c` donde se ejecuta todo este parser, y formatear todo de acuerdo a lo pedido