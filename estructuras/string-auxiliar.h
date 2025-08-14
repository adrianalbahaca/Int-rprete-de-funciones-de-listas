#ifndef __STRING_AUXILIAR__
#define __STRING_AUXILIAR__

/**
 * Por conveniencia, se declara char* como string
 */
typedef char* String;

/**
 * Se guarda en arreglos los comandos que permite este parser y las funciones
 * primitivas a usar, más sus tamaños respectivamente
 */

extern const String primitivas[];
extern const int primitivas_tam;
extern const String comandos[];
extern const int comandos_tam;

/**
 * str_dup: String -> String
 * Asigna el espacio necesario para duplicar un string a otro.
 * Básicamente, hace lo mismo que strdup(), pero como no está en el estándar C99
 * aparentemente, me toca escribir la función
 */
String str_dup(const String s);

/**
 * string_a_token: String -> String
 * Retorna cada token de la cadena, como los símbolos, identificadores, números, etc
 * Es como strtok, pero personalizado para lo que necesito
 */
String string_a_token (String cadena, String delimitador);

void liberar_string(String cadena);


#endif // __STRING_AUXILIAR__