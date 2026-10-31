#include "Utils.hpp"
#include <fstream>
#include <cctype>

using namespace std;

vector<string> leerPalabras(const string& ruta) {
    vector<string> palabras;
    ifstream archivo(ruta);

    // Si la función retorna un vector vacío, indica que no se pudo realizar la operación de lectura. 
    if (!archivo.is_open()) {
        return palabras;
    }

    string palabra;
    while (archivo >> palabra) {
        // cada letra se convierte a minuscula para que la comparación sea consistente
        for (char& c : palabra) {
            c = tolower((unsigned char)c);
        }
        palabras.push_back(palabra);
    }

    return palabras;
}

bool escribirPalabras(const string& ruta, const vector<string>& palabras) {
    ofstream archivo(ruta);

    if (!archivo.is_open()) {
        return false;
    }

    for (const string& palabra : palabras) {
        archivo << palabra << '\n';
    }

    return true;
}

bool estaOrdenado(const vector<string>& palabras) {
    // veriificacion del orden comparando cada palabra con la anterior.Si aparece alguna palabra que sea menor que la anterior, retorna false 
    for (size_t i = 1; i < palabras.size(); i++) {
        if (palabras[i] < palabras[i - 1]) {
            return false;
        }
    }
    return true;
}