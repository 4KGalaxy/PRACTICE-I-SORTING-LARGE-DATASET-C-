#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <string>
#include <vector>

// Ordena alfabeticamente (de menor a mayor) el vector que recibe, usando un
// heap binario propio (BinaryHeap).
//   Tiempo:  O(n log n) en el mejor, promedio y peor caso.
//   Memoria: O(1) adicional (el ordenamiento es in-place).
void heapSort(std::vector<std::string>& palabras);

#endif