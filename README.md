# Práctica I – Ordenamiento de un conjunto grande de palabras (C++)

**Estructuras de Datos y Algoritmos** · Universidad EAFIT · Profesor Carlos Alberto Alvarez H.

**Integrantes:** Sara Castaño Suárez · Simon Lopez Mesa · Antuan Alejandro Navarro Ortiz

---

## 1. Descripción

Se desarrolla un programa en C++ capaz de ordenar un gran conjunto de datos de palabras (Una colección de 100 000 palabras en inglés) utilizando tres estrategias algorítmicas diferentes: QuickSort, HeapSort y AVLTree, cada una basada en estructuras de datos distintas.
El objetivo de esta práctica es analizar cómo se comportan los diferentes algoritmos y estructuras al trabajar con grandes volúmenes de datos.

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
| BinaryHeap / HeapSort | Simon | Heap binario máximo propio y HeapSort in-place sobre `vector<string>` |
| AVLTree | Simon | Árbol AVL propio con rotaciones; inserta las palabras y devuelve el recorrido inorden |
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

QuickSort se implementó desde cero sobre un `std::vector<std::string>`, sin usar
`std::sort` ni otras funciones de ordenamiento de la librería estándar. Las palabras
se comparan alfabéticamente con los operadores `<` y `<=`, que en C++ funcionan
directamente con `string`.

La partición está basada en el esquema de Lomuto, tomando como punto de partida el
ejemplo de GeeksforGeeks que ordenaba números enteros ([C++ Program for Quick Sort](https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/)) únicamente usado como 
inspiración después de investigar diferentes formas de implementación de QuickSort.

**Elección del pivote.** Antes de cada partición se toma el elemento del medio del
rango y se intercambia con el último. Esto evita el peor caso, O(n²), que ocurre
cuando los datos ya vienen ordenados y el pivote es siempre el mayor. Con este cambio,
el pivote parte el rango justo a la mitad.

**Ordenamiento in place.** La función recibe el vector por referencia y lo ordena
directamente, sin crear otro vector. La única memoria adicional es la de la pila de
llamadas recursivas.

**Estructura del código.** Se dividió en tres funciones:

- `quickSort(palabras)`: es la única función pública (declarada en `QuickSort.hpp`).
  Revisa que el vector no esté vacío y arranca la recursión con todo el rango.
- `quickSortRecursivo(palabras, low, high)`: ubica el pivote y se llama a sí misma
  sobre el lado izquierdo y el lado derecho. Su caso base es cuando el rango tiene
  0 o 1 elementos.
- `particion(palabras, low, high)`: elige el pivote central, deja las palabras menores
  o iguales a su izquierda y las mayores a su derecha, y retorna la posición final
  del pivote.

**Pruebas.**

[COMPLETAR cuando el main esté terminado]

### 5.2 HeapSort con Binary Heap (Simon)

**Archivos:** `include/BinaryHeap.hpp`, `src/BinaryHeap.cpp`, `include/HeapSort.hpp`, `src/HeapSort.cpp`

### Enfoque

Se implementó un **heap binario máximo** propio sobre un `std::vector<std::string>` (sin `std::priority_queue`, `make_heap` ni `sort_heap`). El padre de la posición `i` es `(i-1)/2` y sus hijos son `2i+1` y `2i+2`.

El ordenamiento tiene dos fases:

1. **Construcción** del heap con el algoritmo de Floyd: se "hunden" los nodos internos de abajo hacia arriba. Cuesta **O(n)**.
2. **Extracción**: se intercambia la raíz (el mayor) con el último elemento del heap, el heap se achica en 1 y se hunde la nueva raíz. Se repite *n* veces, y cada extracción cuesta **O(log n)**.

El vector se divide en dos zonas, la del heap (al inicio) y la ya ordenada (al final). Por eso el ordenamiento es **in-place** y el resultado queda en orden ascendente sin usar un arreglo auxiliar.

**Función expuesta:** `void heapSort(std::vector<std::string>& palabras)`, que ordena el vector que recibe.

### Complejidad

| | Resultado |
|---|---|
| Tiempo (mejor, promedio y peor caso) | O(n log n) |
| Memoria adicional | O(1) (in-place) |
| ¿Estable? | No |

### Memoria Estimada

Se calcula con `memoriaPalabras(palabras)`: aproximadamente `n × sizeof(std::string)` más las letras de cada palabra. Es una aproximación, porque no se puede medir el tamaño exacto en bytes de un vector de strings.

---

### 5.3 Árbol AVL (Simon)

**Archivos:** `include/AVLTree.hpp`, `src/AVLTree.cpp`

### Enfoque

Se implementó un **árbol AVL propio** (sin `std::set` ni `std::map`). Cada nodo guarda la palabra, sus dos hijos y su altura. El árbol mantiene la regla AVL: en todo nodo, la diferencia de alturas entre sus subárboles es como máximo 1.

Al insertar una palabra se baja comparando, igual que en un árbol de búsqueda normal, y al regresar se actualiza la altura de cada nodo del camino. Si algún nodo queda con factor de balance de ±2, se corrige con una de las cuatro rotaciones:

| Caso | Corrección |
|---|---|
| Izquierda-Izquierda | rotación simple a la derecha |
| Derecha-Derecha | rotación simple a la izquierda |
| Izquierda-Derecha | rotación doble (izquierda al hijo, luego derecha al nodo) |
| Derecha-Izquierda | rotación doble (derecha al hijo, luego izquierda al nodo) |

El caso se decide con el factor de balance del hijo pesado, no comparando palabras, para que funcione bien con repetidas.

**Proceso de ordenamiento:**

1. Se insertan las 100.000 palabras en el árbol.
2. Se hace un **recorrido inorden** (izquierda, nodo, derecha), que visita las palabras en orden alfabético.
3. El resultado se guarda en un `std::vector<std::string>`.

**Duplicados:** se conservan (van al hijo derecho), de modo que la salida siempre tiene el mismo tamaño que la entrada.

**Función expuesta:** `std::vector<std::string> avlOrdenar(const std::vector<std::string>& palabras, std::size_t* bytesEstimados = nullptr)`. Si se entrega el puntero, deja ahí la memoria estimada del árbol.

### Complejidad

| | Resultado |
|---|---|
| Inserción de una palabra | O(log n), también en el peor caso |
| Insertar las n palabras | O(n log n) |
| Recorrido inorden | O(n) |
| **Total** | **O(n log n)** |
| Altura máxima | ≈ 1,44 · log₂(n) |
| Memoria adicional | O(n) (un nodo por palabra) |

Sin el balanceo, un árbol de búsqueda recibiendo palabras ya ordenadas se degeneraría en una lista de altura n y el ordenamiento costaría O(n²). El AVL evita ese caso.

### Memoria Estimada

`cantidad de nodos × sizeof(Nodo) + letras de todas las palabras`. Con 100.000 palabras y `sizeof(Nodo)` = 56 bytes son unos 6,24 MB.

Es una estimación del **árbol**. Mientras `avlOrdenar` construye la lista inorden también existe el vector de resultado, así que el consumo real máximo es mayor que esa cifra. Además, las palabras cortas caben dentro del propio `std::string` (optimización SSO), por lo que contar las letras aparte puede sobreestimar un poco.

---

## 6. Metodología de medición

**Tiempo:**
- Se usa `std::chrono::steady_clock` (clase `Cronometro`).
- El cronómetro mide **solo el ordenamiento**: la lectura del archivo y la conversión a minúscula quedan por fuera.
- En HeapSort el cronómetro rodea `heapSort`. En el AVL rodea `avlOrdenar`, que incluye insertar las palabras, el recorrido inorden y la liberación del árbol. HeapSort y AVL se midieron con 5 corridas y se reporta el mínimo (promedio entre paréntesis).

**Memoria:**
- Estimación con `sizeof`: `n × sizeof(std::string)` + total de letras (función `memoriaPalabras`).
- Es una aproximación por encima: en g++, las palabras de 15 letras o menos guardan sus letras dentro del mismo `string` (32 bytes).
- Para el AVL no se usa `memoriaPalabras`: se calcula `nodos × sizeof(Nodo) + letras` (56 bytes por nodo). Cubre el árbol, pero no el vector donde se guarda el resultado del inorden.

---

## 7. Resultados

| Algoritmo | Archivo | Palabras | Tiempo (ms) | Memoria (MB) |
|---|---|---|---|---|
| QuickSort | `dataset.txt` | 100.000 | [COMPLETAR] | [COMPLETAR] |
| QuickSort | `dataset_profe.txt` | 100.000 | 25.51 | 3.95 |
| QuickSort | `words_alpha.txt` (ordenado) | 370.105 | 50.46 | 14.63 |
| HeapSort | `dataset.txt` | 100.000 | 81,69 (prom. 106,07) | 3,95 |
| HeapSort | `dataset_profe.txt` | 100.000 | 74,02 (prom. 81,39) | 3,95 |
| AVL | `dataset.txt` | 100.000 | 76,39 (prom. 89,06) | 6,24 |
| AVL | `dataset_profe.txt` | 100.000 | 75,86 (prom. 81,54) | 6,24 |

[COMPLETAR: los tiempos de QuickSort de esta tabla son de una sola ejecución; reemplazarlos por el promedio si se decide hacer varias.]

---

## 8. Análisis comparativo

### 8.1 Complejidad

| Algoritmo | Mejor caso | Promedio | Peor caso | Memoria adicional |
|---|---|---|---|---|
| QuickSort | O(n log n) | O(n log n) | O(n²) | O(log n) promedio (pila de recursión) |
| HeapSort | O(n log n) | O(n log n) | O(n log n) | O(1) (in-place) |
| AVL | O(n log n) | O(n log n) | O(n log n) | O(n) (nodos; más el vector del resultado) |

### 8.2 ¿Qué algoritmo tuvo mejor rendimiento?

[COMPLETAR cuando estén los tres resultados.]

### 8.3 ¿Por qué la teoría difiere de la práctica?

[REDACTAR. Dato para usar:]
- `words_alpha.txt` tiene 3,7 veces más palabras que `dataset_profe.txt`. Según O(n log n) se esperaba ~4 veces más tiempo, pero QuickSort tardó solo ~2 veces más (50.46 ms vs 25.51 ms). Con datos ordenados, el pivote central parte cada rango justo a la mitad y el patrón de comparaciones es predecible para el procesador.
- HeapSort y AVL son ambos O(n log n) y quedaron prácticamente empatados (entre 74 y 82 ms con 100.000 palabras) aunque sus estructuras son muy distintas. La notación O ignora las constantes y el acceso a memoria. Una explicación probable es que el AVL hace 100.000 reservas con `new` y recorre punteros dispersos, lo que aprovecha mal la caché, mientras que el heap trabaja sobre un arreglo contiguo. No se midió con un profiler, por lo que es una hipótesis.

### 8.4 Ventajas y desventajas de cada estructura

- **QuickSort / vector:** [REDACTAR: rápido en la práctica y sin vector adicional; peor caso O(n²); no es estable; se degenera con muchos valores repetidos.]
- **HeapSort / Binary Heap:** ordena in-place (memoria adicional O(1)) y garantiza O(n log n) en todos los casos, sin degradarse con datos repetidos u ordenados. Por otro lado, no es estable, accede a la memoria de forma poco favorable para la caché (salta entre padres e hijos) y solo sirve para ordenar.
- **AVL:** garantiza O(n log n) gracias al balanceo (altura 20 con 100.000 palabras) y el árbol queda disponible para insertar y buscar en O(log n). Por otro lado, usa más memoria (nodo de 56 bytes por palabra, alrededor de un 58 % más que HeapSort), hace 100.000 reservas dinámicas con punteros dispersos y requiere más código (rotaciones).

---

## 9. Problemas encontrados

### 9.1 Codificación UTF-16 de `dataset_profe.txt`

[REDACTAR. Puntos a cubrir:]
- Al leer el archivo, el programa contaba 199.999 palabras en vez de 100.000.
- El archivo venía en UTF-16; cada salto de línea dejaba un carácter nulo que se leía como una "palabra" extra, todas iguales.
- Esas ~100.000 palabras repetidas hacían que la partición de Lomuto se degenerara y el programa se cerraba por desbordamiento de la pila de recursión.
- Solución: convertir el archivo a UTF-8.
- Lección: QuickSort con Lomuto es vulnerable a datos con muchos valores repetidos.

### 9.2 Variación entre corridas (Simon)
- En la primera corrida de HeapSort sobre `dataset.txt` el tiempo fue de 185 ms, mientras que las siguientes estuvieron entre 82 y 90 ms (arranque en frío: caché y memoria todavía sin calentar). Por eso se repitió cada algoritmo 5 veces y se reporta el mínimo, con el promedio entre paréntesis.

---

## 10. Conclusiones

[COMPLETAR entre todos: qué enfoque es el más apropiado para este problema y por qué.]

---

## 11. Fuentes

- Lista de palabras: [dwyl/english-words](https://github.com/dwyl/english-words)
- Inspiración para la partición de QuickSort: [COMPLETAR: enlace]
- [Repositorio del profesor](https://github.com/carlosalvarezh/EstructuraDatosAlgoritmos1).
- Notas de clase, [videos instructivos en Youtube](https://www.youtube.com/watch?v=MkHuwIrWZmI).
