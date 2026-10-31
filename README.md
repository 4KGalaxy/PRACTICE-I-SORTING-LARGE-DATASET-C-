# Práctica I – Ordenamiento de un conjunto grande de palabras (C++)

**Estructuras de Datos y Algoritmos** · Universidad EAFIT · Profesor Carlos Alberto Alvarez H.

**Integrantes:** Sara Castaño Suárez · Simon Lopez Mesa · Antuan Alejandro Navarro Ortiz

---

## 1. Descripción

[REDACTAR: qué hace el programa en 2 o 3 líneas. Ordena 100.000 palabras con tres estrategias (QuickSort sobre vector, HeapSort con Binary Heap y árbol AVL con recorrido inorden) y compara tiempo, memoria y complejidad.]

---

## 2. Estructura del repositorio

```
├── README.md
├── .gitignore
├── data/
│   ├── words_alpha.txt        ← fuente original (~370.000 palabras, ordenadas)
│   ├── dataset_profe.txt      ← archivo entregado por el profesor (100.000 palabras)
│   └── dataset.txt            ← generado por DatasetGenerator (100.000 palabras aleatorias)
├── include/                   ← declaraciones (.hpp)
├── src/                       ← implementaciones (.cpp)
│   ├── main.cpp
│   ├── QuickSort.cpp
│   ├── BinaryHeap.cpp
│   ├── HeapSort.cpp
│   ├── AVLTree.cpp
│   ├── DatasetGenerator.cpp
│   ├── Metrics.cpp
│   └── Utils.cpp
└── output/                    ← listas ordenadas generadas por el programa
```

| Módulo | Responsable | Qué hace |
|---|---|---|
| QuickSort | Sara | Ordena un `vector<string>` con QuickSort |
| Utils | Sara | Lee y escribe archivos, convierte a minúscula y verifica el orden |
| Metrics | Sara | Mide el tiempo (`chrono`) y estima la memoria (`sizeof`) |
| DatasetGenerator | Sara | Genera `dataset.txt` a partir de `words_alpha.txt` |
| BinaryHeap / HeapSort | Simon | [COMPLETAR] |
| AVLTree | Simon | [COMPLETAR] |
| main (menú) | Antuan | [COMPLETAR] |

---

## 3. Compilación y ejecución

Desde la carpeta raíz del proyecto:

```
g++ -std=c++17 -O2 -Iinclude src/*.cpp -o sorting
```

Ejecutar en Windows con `.\sorting.exe` (en Linux/Mac: `./sorting`).

- El programa debe ejecutarse desde la carpeta raíz, porque usa rutas relativas como `data/dataset.txt`.
- Todas las mediciones se hicieron compilando con `-O2`.

[COMPLETAR – Antuan: cómo se usa el menú (opciones de archivo y de algoritmo).]

---

## 4. Datos

| Archivo | Contenido | Origen |
|---|---|---|
| `words_alpha.txt` | ~370.105 palabras en inglés, ordenadas alfabéticamente | Repositorio público [dwyl/english-words](https://github.com/dwyl/english-words) |
| `dataset_profe.txt` | 100.000 palabras desordenadas | Entregado por el profesor |
| `dataset.txt` | 100.000 palabras aleatorias | Generado por `DatasetGenerator` a partir de `words_alpha.txt` |

**Generación de `dataset.txt`:** [REDACTAR: se leen todas las palabras de `words_alpha.txt`, se barajan con `shuffle` (generador `mt19937` con semilla de `random_device`) y se conservan las primeras 100.000.]

- Cada ejecución del generador produce un dataset distinto. El `dataset.txt` del repositorio quedó fijo para que los tres algoritmos se midan con los mismos datos. **No se recomienda regenerar.**

**Minúsculas:** Todas las palabras se convierten a minúscula al leerlas (en `Utils`), para que los tres algoritmos ordenen igual sin importar mayúsculas.

---

## 5. Enfoque de implementación

### 5.1 QuickSort (Sara)

[REDACTAR con tus palabras. Puntos a cubrir:]

- Implementado desde cero sobre `std::vector<std::string>`, sin `std::sort`.
- Partición de Lomuto, basada en un ejemplo de [COMPLETAR: fuente/enlace del código de inspiración], adaptado de `int` a `string`.
- Pivote: el elemento central del rango, que se intercambia con el último antes de particionar. Evita el peor caso O(n²) con datos ya ordenados (como `words_alpha.txt`).
- Ordena *in place*: modifica el vector original.
- Estructura: `quickSort` (función pública) → `quickSortRecursivo` → `particion`.

### 5.2 HeapSort con Binary Heap (Simon)

[COMPLETAR – Simon]

### 5.3 Árbol AVL (Simon)

[COMPLETAR – Simon: inserción, rotaciones y recorrido inorden.]

---

## 6. Metodología de medición

**Tiempo:**
- Se usa `std::chrono::steady_clock` (clase `Cronometro`).
- El cronómetro mide **solo el ordenamiento**: la lectura del archivo y la conversión a minúscula quedan por fuera.
- [COMPLETAR: número de ejecuciones por algoritmo y si se reporta el promedio.]

**Memoria:**
- Estimación con `sizeof`: `n × sizeof(std::string)` + total de letras (función `memoriaPalabras`).
- Es una aproximación por encima: en g++, las palabras de 15 letras o menos guardan sus letras dentro del mismo `string` (32 bytes).
- Para el AVL se suma `n × sizeof(Nodo)`. [COMPLETAR – Simon]

---

## 7. Resultados

| Algoritmo | Archivo | Palabras | Tiempo (ms) | Memoria (MB) |
|---|---|---|---|---|
| QuickSort | `dataset.txt` | 100.000 | [COMPLETAR] | [COMPLETAR] |
| QuickSort | `dataset_profe.txt` | 100.000 | 25.51 | 3.95 |
| QuickSort | `words_alpha.txt` (ordenado) | 370.105 | 50.46 | 14.63 |
| HeapSort | `dataset.txt` | 100.000 | [COMPLETAR] | [COMPLETAR] |
| AVL | `dataset.txt` | 100.000 | [COMPLETAR] | [COMPLETAR] |

[COMPLETAR: los tiempos de QuickSort de esta tabla son de una sola ejecución; reemplazarlos por el promedio si se decide hacer varias.]

---

## 8. Análisis comparativo

### 8.1 Complejidad

| Algoritmo | Mejor caso | Promedio | Peor caso | Memoria adicional |
|---|---|---|---|---|
| QuickSort | O(n log n) | O(n log n) | O(n²) | O(log n) promedio (pila de recursión) |
| HeapSort | [COMPLETAR] | [COMPLETAR] | [COMPLETAR] | [COMPLETAR] |
| AVL | [COMPLETAR] | [COMPLETAR] | [COMPLETAR] | [COMPLETAR] |

### 8.2 ¿Qué algoritmo tuvo mejor rendimiento?

[COMPLETAR cuando estén los tres resultados.]

### 8.3 ¿Por qué la teoría difiere de la práctica?

[REDACTAR. Dato para usar:]
- `words_alpha.txt` tiene 3,7 veces más palabras que `dataset_profe.txt`. Según O(n log n) se esperaba ~4 veces más tiempo, pero QuickSort tardó solo ~2 veces más (50.46 ms vs 25.51 ms). Con datos ordenados, el pivote central parte cada rango justo a la mitad y el patrón de comparaciones es predecible para el procesador.

### 8.4 Ventajas y desventajas de cada estructura

- **QuickSort / vector:** [REDACTAR: rápido en la práctica y sin vector adicional; peor caso O(n²); no es estable; se degenera con muchos valores repetidos.]
- **HeapSort / Binary Heap:** [COMPLETAR – Simon]
- **AVL:** [COMPLETAR – Simon]

---

## 9. Problemas encontrados

### 9.1 Codificación UTF-16 de `dataset_profe.txt`

[REDACTAR. Puntos a cubrir:]
- Al leer el archivo, el programa contaba 199.999 palabras en vez de 100.000.
- El archivo venía en UTF-16; cada salto de línea dejaba un carácter nulo que se leía como una "palabra" extra, todas iguales.
- Esas ~100.000 palabras repetidas hacían que la partición de Lomuto se degenerara y el programa se cerraba por desbordamiento de la pila de recursión.
- Solución: convertir el archivo a UTF-8.
- Lección: QuickSort con Lomuto es vulnerable a datos con muchos valores repetidos.

[COMPLETAR: otros problemas que encuentren Simon y Antuan.]

---

## 10. Conclusiones

[COMPLETAR entre todos: qué enfoque es el más apropiado para este problema y por qué.]

---

## 11. Fuentes

- Lista de palabras: [dwyl/english-words](https://github.com/dwyl/english-words)
- Inspiración para la partición de QuickSort: [COMPLETAR: enlace]
- [COMPLETAR: fuentes usadas por Simon y Antuan]
