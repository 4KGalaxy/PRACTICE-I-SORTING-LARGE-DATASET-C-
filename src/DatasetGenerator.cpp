#include "DatasetGenerator.hpp"
#include "Utils.hpp"
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

bool generarDataset(const string& rutaEntrada, const string& rutaSalida, size_t cantidad) {
    vector<string> palabras = leerPalabras(rutaEntrada);

    if (palabras.size() < cantidad) {
        return false;
    }

    random_device semilla;
    mt19937 generador(semilla());
    shuffle(palabras.begin(), palabras.end(), generador);

    palabras.resize(cantidad);

    return escribirPalabras(rutaSalida, palabras);
}