# Proyecto final de EDyA1: Parser de funciones de lista
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

# Cosas a hacer:
 - [x] Crear una función que reciba cada comando y lo guarde. Será un string que no se sabe cuál es su largo
 - [x] Crear una función que tokenize cada comando que escriba el usuario <!-- Funciones que no puede declarar el usuario -->
 - [ ] Diseñar la gramática que leerá el input del usuario y se corroborará que sea correcta <!-- Consultar con el profesor de LFyC -->
 - [ ] Definir y guardar funciones primitivas <!-- Enum? -->
 - [ ] Definir la función composición, que guarda funciones de listas, para después usarlas más adelante <!-- Requerirá algún tipo de recursión -->
 - [ ] Definir una definición de listas directa <!-- Simple -->
 - [ ] Definir la búsqueda entre pares de listas <!-- Esta parece la parte más compleja -->