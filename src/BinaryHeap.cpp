#include "BinaryHeap.hpp"

#include <utility>  // std::move, std::swap

BinaryHeap::BinaryHeap(std::vector<std::string>&& datosEntrada)
    : datos(std::move(datosEntrada)), n(datos.size()) {}

std::size_t BinaryHeap::tamanio() const { return n; }

bool BinaryHeap::vacio() const { return n == 0; }


// hundir (sift-down)
// Compara el elemento i con sus dos hijos. Si algun hijo es mayor, intercambia
// con el MAYOR de los dos y sigue bajando. Se detiene cuando el elemento ya es
// mayor o igual que sus hijos, o cuando no tiene hijos.
// Es iterativo (sin recursion) para no gastar pila: O(log n).
void BinaryHeap::hundir(std::size_t i) {
    while (true) {
        std::size_t izq = 2 * i + 1;
        std::size_t der = 2 * i + 2;
        std::size_t mayor = i;

        // Solo se mira hasta n: lo que esta despues de n ya esta ordenado
        // y NO pertenece al heap.
        if (izq < n && datos[izq] > datos[mayor]) mayor = izq;
        if (der < n && datos[der] > datos[mayor]) mayor = der;

        if (mayor == i) break;  // propiedad del heap restablecida

        std::swap(datos[i], datos[mayor]);  // swap de strings: O(1), no copia letras
        i = mayor;
    }
}


// construir (heapify de Floyd)
// Las hojas ya son heaps validos de tamanio 1, asi que solo hace falta hundir
// los nodos internos, de abajo hacia arriba. El ultimo nodo interno es el
// padre del ultimo elemento: (n/2 - 1).
// Parece O(n log n) pero la suma real es O(n), porque la mayoria de nodos
// estan cerca de las hojas y bajan muy poco.

void BinaryHeap::construir() {
    n = datos.size();
    if (n < 2) return;

    // Se usa i+1 para evitar que el size_t sin signo se desborde al llegar a 0.
    for (std::size_t i = n / 2; i > 0; --i) {
        hundir(i - 1);
    }
}


// extraerMaximo
// 1. El maximo esta siempre en la raiz (posicion 0).
// 2. Se intercambia con el ultimo elemento del heap (posicion n-1): el maximo
//    queda en su lugar definitivo de la zona ordenada.
// 3. El heap se achica en 1 y el elemento que llego a la raiz se hunde.

void BinaryHeap::extraerMaximo() {
    if (n == 0) return;

    std::swap(datos[0], datos[n - 1]);
    --n;
    if (n > 1) hundir(0);
}

std::vector<std::string> BinaryHeap::liberar() {
    n = 0;
    return std::move(datos);
}