#ifndef METRICS_HPP
#define METRICS_HPP

#include <chrono>
#include <string>
#include <vector>

class Cronometro {
public:
    void iniciar();
    double detener();
private:
    std::chrono::steady_clock::time_point inicio;
};

// OJO, es una aproximacion prque no se puede medir el tamaño exacto de un vector de strings en bytes
std::size_t memoriaPalabras(const std::vector<std::string>& palabras);

void imprimirMetricas(const std::string& algoritmo, double milisegundos, std::size_t bytes);

#endif

// mmm revisar metrics cpp....