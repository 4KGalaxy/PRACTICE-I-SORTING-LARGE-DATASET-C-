#include "QuickSort.hpp"
#include <utility>

using namespace std;

int particion(vector<string> &palabras, int low, int high)
{
    // Se usa el elemento de la mitad porque es una buena práctica para evitar el peor caso en listas ya ordenadas o casi ordenadas. Esto ayuda a mejorar el rendimiento promedio del algoritmo QuickSort.
    int medio = (low + high) / 2;
    swap(palabras[medio], palabras[high]);

    string pivot = palabras[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (palabras[j] <= pivot)
        {
            i++;
            swap(palabras[i], palabras[j]);
        }
    }

    swap(palabras[i + 1], palabras[high]);
    return i + 1;
}

void quickSortRecursivo(vector<string> &palabras, int low, int high)
{
    // Caso base: si low no es menor que high, el rango tiene 0 o 1 elementos,
    // ya está ordenado y no es necesario hacer nada más.
    // Si no, se ubica el pivote y se ordenan recursivamente los lados izquierdo y derecho.
    if (low < high)
    {
        int posPivote = particion(palabras, low, high);
        quickSortRecursivo(palabras, low, posPivote - 1);
        quickSortRecursivo(palabras, posPivote + 1, high);
    }
}

void quickSort(vector<string> &palabras)
{
    // Se debe de revisar el vector vacio porque si no, se puede caer en un error de segmentación al intentar acceder a elementos que no existen.
    if (palabras.empty())
    {
        return;
    }
    quickSortRecursivo(palabras, 0, palabras.size() - 1);
}
