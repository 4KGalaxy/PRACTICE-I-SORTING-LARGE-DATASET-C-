#include "QuickSort.hpp"
#include <utility>

using namespace std;

int particion(vector<string> &palabras, int low, int high)
{
    // uso del elemento de la mitad ya que es buena práctica para evitar el peor caso en listas ya ordenadas o casi ordenadas. Ayuda a mejorar el rendimiento promedio del algoritmo
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
    if (low < high)
    {
        int posPivote = particion(palabras, low, high);
        quickSortRecursivo(palabras, low, posPivote - 1);
        quickSortRecursivo(palabras, posPivote + 1, high);
    }
}

void quickSort(vector<string> &palabras)
{
    if (palabras.empty())
    {
        return;
    }
    quickSortRecursivo(palabras, 0, palabras.size() - 1);
}