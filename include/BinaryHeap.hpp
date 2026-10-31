#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <cstddef>
#include <string>
#include <vector>


// BinaryHeap: heap binario MAXIMO (el padre siempre es >= que sus hijos)
// implementado sobre un arreglo (std::vector<std::string>).
//
// Relacion entre posiciones (indices desde 0):
//padre(i)  = (i - 1) / 2
//hijoIzq(i) = 2*i + 1
//hijoDer(i) = 2*i + 2
//
// Truco para que HeapSort sea "in-place" (sin memoria extra):
//   el vector se divide en dos zonas
//        [ 0 ........ tamanio-1 ][ tamanio ........ fin ]
//        <---- zona del heap ---><---- zona ya ordenada --->
//   Cada vez que se extrae el maximo, este se manda al inicio de la zona
//   ordenada y la zona del heap se achica en 1. Al final todo el vector queda
//   ordenado de menor a mayor.

class BinaryHeap {
public:
    // Recibe el vector por movimiento (no se copian las palabras).
    explicit BinaryHeap(std::vector<std::string>&& datos);

    // Convierte el arreglo en un heap valido (algoritmo de Floyd): O(n).
    void construir();

    // Saca el maximo del heap y lo deja en la zona ordenada: O(log n).
    // Si el heap esta vacio no hace nada.
    void extraerMaximo();

    // Cantidad de elementos que siguen dentro de la zona del heap.
    std::size_t tamanio() const;
    bool vacio() const;

    // Entrega el vector (ya ordenado si se extrajo todo) y deja el heap vacio.
    std::vector<std::string> liberar();

private:
    std::vector<std::string> datos;  // arreglo que guarda el heap + zona ordenada
    std::size_t n;                   // tamanio actual de la zona del heap

    // "Hunde" el elemento en la posicion i hasta que cumpla la propiedad
    // del heap: O(log n).
    void hundir(std::size_t i);
};

#endif