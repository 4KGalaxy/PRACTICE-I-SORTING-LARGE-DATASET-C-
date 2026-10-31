#include "Metrics.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void Cronometro::iniciar() {
    inicio = chrono::steady_clock::now();
}

double Cronometro::detener() {
    auto fin = chrono::steady_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;
    return duracion.count();
}

size_t memoriaPalabras(const vector<string>& palabras) {
    size_t bytes = palabras.size() * sizeof(string);
    for (const string& palabra : palabras) {
        bytes += palabra.size();
    }
    return bytes;
}

void imprimirMetricas(const string& algoritmo, double milisegundos, size_t bytes) {
    double megabytes = bytes / (1024.0 * 1024.0);
//  1 MB = 1024 KB y 1 KB = 1024 bytes, entonces 1 MB = 1024 * 1024 bytes
    cout << fixed << setprecision(2);
    cout << "Algoritmo: " << algoritmo << endl;
    cout << "Tiempo:    " << milisegundos << " ms" << endl;
    cout << "Memoria:   " << megabytes << " MB (" << bytes << " bytes)" << endl;
}
