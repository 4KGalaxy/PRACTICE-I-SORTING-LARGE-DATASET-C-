#include "HeapSort.hpp"

#include <utility>  // std::move

#include "BinaryHeap.hpp"


// heapSort
// Fase 1: construir el heap maximo con todas las palabras        -> O(n)
// Fase 2: extraer el maximo n veces. Cada extraccion lo coloca al
//         final de la zona del heap, asi el vector se va llenando
//         de mayor a menor desde atras                           -> O(n log n)
// Resultado: el vector queda en orden ascendente (A -> Z).

void heapSort(std::vector<std::string>& palabras) {
    if (palabras.size() < 2) return;

    // El vector se MUEVE dentro del heap: no se copia ninguna palabra.
    BinaryHeap heap(std::move(palabras));

    heap.construir();

    while (!heap.vacio()) {
        heap.extraerMaximo();
    }

    // Se devuelve el vector (ya ordenado) a quien llamo la funcion.
    palabras = heap.liberar();
}