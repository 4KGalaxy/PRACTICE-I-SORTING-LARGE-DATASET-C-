#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

// leerPalabras: Esta función lee palabras desde un archivo y las almacena en un vector de strings. Retorna el vector con las palabras leídas.
// convierte todo a minúscula
// leerPalabras retorna un vector vacio cuando no se puede abrir el archivo, o cuando el archivo está vacío.

std::vector<std::string> leerPalabras(const std::string& ruta);

// escribirPalabras: Esta función escribe palabras en un archivo. Retorna true si la operación es exitosa, false en caso contrario.
bool escribirPalabras(const std::string& ruta, const std::vector<std::string>& palabras);

// estaOrdenado: Esta función verifica si un vector de strings está ordenado alfabéticamente. Retorna true si está ordenado, false en caso contrario.
bool estaOrdenado(const std::vector<std::string>& palabras);

#endif