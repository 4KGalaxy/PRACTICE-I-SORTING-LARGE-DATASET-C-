#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Utils.hpp"
#include "DatasetGenerator.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "AVLTree.hpp"
#include "Metrics.hpp"

using namespace std;

const string RUTA_ORIGINAL = "data/words_alpha.txt";
const string RUTA_DATASET  = "data/dataset.txt";
const string RUTA_PROFE    = "data/dataset_profe.txt";
const size_t CANTIDAD_ELEMENTOS = 100000;

void probarQuickSort(const vector<string>& datasetBase, Cronometro& reloj) {
    cout << "\n--- Probando QuickSort ---\n";
    vector<string> datos = datasetBase;
    reloj.iniciar();
    quickSort(datos);
    double tiempo = reloj.detener();

    if (!estaOrdenado(datos)) {
        cerr << " -> [ERROR] QuickSort no ordenó el conjunto correctamente.\n";
    } else {
        size_t memoria = memoriaPalabras(datos);
        imprimirMetricas("QuickSort", tiempo, memoria);
    }
}

void probarHeapSort(const vector<string>& datasetBase, Cronometro& reloj) {
    cout << "\n--- Probando HeapSort ---\n";
    vector<string> datos = datasetBase;
    reloj.iniciar();
    heapSort(datos);
    double tiempo = reloj.detener();

    if (!estaOrdenado(datos)) {
        cerr << " -> [ERROR] HeapSort no ordenó el conjunto correctamente.\n";
    } else {
        size_t memoria = memoriaPalabras(datos);
        imprimirMetricas("HeapSort", tiempo, memoria);
    }
}

void probarAVL(const vector<string>& datasetBase, Cronometro& reloj) {
    cout << "\n--- Probando AVL Tree ---\n";
    size_t memoriaAVL = 0;
    reloj.iniciar();
    vector<string> datos = avlOrdenar(datasetBase, &memoriaAVL);
    double tiempo = reloj.detener();

    if (!estaOrdenado(datos)) {
        cerr << " -> [ERROR] AVL Tree no ordenó el conjunto correctamente.\n";
    } else {
        imprimirMetricas("AVL Tree", tiempo, memoriaAVL);
    }
}

bool cargarArchivoSeleccionado(const string& ruta, vector<string>& datasetBase) {
    datasetBase = leerPalabras(ruta);
    if (datasetBase.empty()) {
        cerr << "[ERROR] No se pudieron cargar palabras desde '" << ruta << "'.\n";
        return false;
    }
    cout << " -> Archivo '" << ruta << "' cargado exitosamente con " << datasetBase.size() << " palabras.\n";
    return true;
}

void regenerarDataset(vector<string>& datasetBase, string& rutaActual) {
    cout << "\n -> Generando nuevo 'dataset.txt' aleatorizado...\n";
    if (!generarDataset(RUTA_ORIGINAL, RUTA_DATASET, CANTIDAD_ELEMENTOS)) {
        cerr << "[ERROR] No se pudo generar el dataset.\n";
        return;
    }
    datasetBase = leerPalabras(RUTA_DATASET);
    rutaActual = RUTA_DATASET;
    cout << " -> Nuevo dataset de " << datasetBase.size() << " palabras listo en '" << RUTA_DATASET << "'.\n";
}

int main() {
    vector<string> datasetBase;
    string rutaActual = "";

    cout << "====================================================\n";
    cout << "  PRACTICA I - ORDENAMIENTO DE GRANDES VOLUMENES    \n";
    cout << "  Estructuras de Datos y Algoritmos - EAFIT         \n";
    cout << "====================================================\n";

    int opcionArchivo = 0;
    bool archivoCargado = false;

    do {
        cout << "\n----------------------------------------------------\n";
        cout << "         SELECCIONE EL ARCHIVO DE ENTRADA           \n";
        cout << "----------------------------------------------------\n";
        cout << " 1. Usar dataset.txt (data/dataset.txt)\n";
        cout << " 2. Usar dataset_profe.txt (data/dataset_profe.txt)\n";
        cout << " 3. Usar words_alpha.txt (data/words_alpha.txt)\n";
        cout << " 4. Generar nuevo dataset.txt aleatorizado (100,000 palabras)\n";
        cout << "----------------------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcionArchivo)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Opcion invalida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionArchivo) {
            case 1:
                rutaActual = RUTA_DATASET;
                archivoCargado = cargarArchivoSeleccionado(rutaActual, datasetBase);
                if (!archivoCargado) {
                    regenerarDataset(datasetBase, rutaActual);
                    archivoCargado = !datasetBase.empty();
                }
                break;
            case 2:
                rutaActual = RUTA_PROFE;
                archivoCargado = cargarArchivoSeleccionado(rutaActual, datasetBase);
                break;
            case 3:
                rutaActual = RUTA_ORIGINAL;
                archivoCargado = cargarArchivoSeleccionado(rutaActual, datasetBase);
                break;
            case 4:
                regenerarDataset(datasetBase, rutaActual);
                archivoCargado = !datasetBase.empty();
                break;
            default:
                cout << "\n[!] Opcion no valida. Elija un numero entre 1 y 4.\n";
                break;
        }
    } while (!archivoCargado);

    Cronometro reloj;
    int opcionMenu = 0;

    do {
        cout << "\n====================================================\n";
        cout << "                 MENU DE OPCIONES                   \n";
        cout << " Archivo activo: " << rutaActual << " (" << datasetBase.size() << " palabras)\n";
        cout << "====================================================\n";
        cout << " 1. Ejecutar QuickSort (std::vector)\n";
        cout << " 2. Ejecutar HeapSort (Binary Heap)\n";
        cout << " 3. Ejecutar AVL Tree (Insercion + Inorden)\n";
        cout << " 4. Ejecutar las 3 estrategias secuencialmente\n";
        cout << " 5. Cambiar archivo de entrada / Regenerar dataset\n";
        cout << " 0. Salir\n";
        cout << "----------------------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcionMenu)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Opcion invalida. Intente de nuevo.\n";
            continue;
        }

        switch (opcionMenu) {
            case 1:
                probarQuickSort(datasetBase, reloj);
                break;
            case 2:
                probarHeapSort(datasetBase, reloj);
                break;
            case 3:
                probarAVL(datasetBase, reloj);
                break;
            case 4:
                cout << "\n=== EJECUTANDO PRUEBA COMPLETA EN: " << rutaActual << " ===\n";
                probarQuickSort(datasetBase, reloj);
                probarHeapSort(datasetBase, reloj);
                probarAVL(datasetBase, reloj);
                break;
            case 5: {
                int subOpcion = 0;
                cout << "\n--- CAMBIAR ARCHIVO DE ENTRADA ---\n";
                cout << " 1. Usar dataset.txt\n";
                cout << " 2. Usar dataset_profe.txt\n";
                cout << " 3. Usar words_alpha.txt\n";
                cout << " 4. Regenerar dataset.txt (Nuevo orden aleatorio)\n";
                cout << "Seleccione: ";
                if (cin >> subOpcion) {
                    if (subOpcion == 1) {
                        rutaActual = RUTA_DATASET;
                        cargarArchivoSeleccionado(rutaActual, datasetBase);
                    } else if (subOpcion == 2) {
                        rutaActual = RUTA_PROFE;
                        cargarArchivoSeleccionado(rutaActual, datasetBase);
                    } else if (subOpcion == 3) {
                        rutaActual = RUTA_ORIGINAL;
                        cargarArchivoSeleccionado(rutaActual, datasetBase);
                    } else if (subOpcion == 4) {
                        regenerarDataset(datasetBase, rutaActual);
                    }
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 0:
                cout << "\nSaliendo del programa...\n";
                break;
            default:
                cout << "\n[!] Opcion no valida. Elija un numero entre 0 y 5.\n";
                break;
        }

    } while (opcionMenu != 0);

    return 0;
}