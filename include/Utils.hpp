#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

std::vector<std::string> leerPalabras(const std::string& ruta);

bool escribirPalabras(const std::string& ruta, const std::vector<std::string>& palabras);

bool estaOrdenado(const std::vector<std::string>& palabras);

#endif