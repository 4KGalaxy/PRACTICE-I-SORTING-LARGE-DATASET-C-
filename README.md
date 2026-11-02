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
├── .vscode/                   ← tasks.json y launch.json (compilar y ejecutar con F5 en VS Code)
├── data/
│   ├── words_alpha.txt        ← fuente original (~370.000 palabras, ordenadas)
│   ├── dataset_profe.txt      ← archivo entregado por el profesor (100.000 palabras)
│   └── dataset.txt            ← generado por DatasetGenerator (100.000 palabras aleatorias)
├── include/                   ← declaraciones (.hpp)
└── src/                       ← implementaciones (.cpp)
    ├── main.cpp
    ├── QuickSort.cpp
    ├── BinaryHeap.cpp
    ├── HeapSort.cpp
    ├── AVLTree.cpp
    ├── DatasetGenerator.cpp
    ├── Metrics.cpp
    └── Utils.cpp
```

| Módulo | Responsable | Qué hace |
|---|---|---|
| QuickSort | Sara | Ordena un `vector<string>` con QuickSort |
| Utils | Sara | Lee y escribe archivos, convierte a minúscula y verifica el orden |
| Metrics | Sara | Mide el tiempo (`chrono`) y estima la memoria (`sizeof`) |
| DatasetGenerator | Sara | Genera `dataset.txt` a partir de `words_alpha.txt` |
| BinaryHeap / HeapSort | Simon | Heap binario máximo propio y HeapSort in-place sobre `vector<string>` |
| AVLTree | Simon | Árbol AVL propio con rotaciones; inserta las palabras y devuelve el recorrido inorden |
| main (menú) | Antuan | Implementa un menu que reune cada funcionalidad en el main |

---

## 3. Compilación y ejecución

Se manejan las siguientes opciones

1.Se puede ejecutar presionando F5 (Gracias a la implementacion de los archivos .json)

2.Desde la carpeta raíz del proyecto:

```
g++ -std=c++17 -O2 -Iinclude src/*.cpp -o programa
```

Ejecutar en Windows con `.\programa.exe` (en Linux/Mac: `./programa`).

- El programa debe ejecutarse desde la carpeta raíz, porque usa rutas relativas como `data/dataset.txt`.
- Todas las mediciones se hicieron compilando con `-O2`.
- Los tiempos reportados se tomaron compilando con
  `g++ -std=c++17 -O2 -Iinclude src/*.cpp -o programa`. El `tasks.json` incluido en el
  repositorio (el que usa F5) compila con `-std=c++11 -g` y sin optimización, por lo que
  los tiempos obtenidos con él serán mayores. F5 además requiere tener instalado el
  depurador gdb y configurada su ruta en `launch.json`.

## Modo de Uso del Menú Interactivo

El programa cuenta con un menú en consola que permite seleccionar el dataset a procesar y evaluar los algoritmos de ordenamiento de forma individual o comparativa.

### Paso 1: Selección del Archivo de Entrada
Al ejecutar el programa, se desplegará el primer menú para cargar el conjunto de datos:
1. **Opción 1 (`dataset.txt`)**: Carga el dataset principal de 100,000 palabras aleatorizadas. Si el archivo no existe en la carpeta `data/`, el programa lo generará automáticamente.
2. **Opción 2 (`dataset_profe.txt`)**: Carga el archivo de prueba suministrado por el docente.
3. **Opción 3 (`words_alpha.txt`)**: Carga el diccionario original completo de palabras en inglés.
4. **Opción 4 (Generar nuevo dataset)**: Genera desde cero un nuevo archivo `dataset.txt` tomando 100,000 palabras aleatorias de `words_alpha.txt`.

### Paso 2: Selección del Algoritmo de Ordenamiento
Una vez cargado el archivo, se desplegará el menú principal de operaciones:
* **Opción 1 (QuickSort)**: Ejecuta el algoritmo QuickSort sobre un `std::vector<std::string>` contiguo en memoria, mide el tiempo exacto en milisegundos y calcula el consumo aproximado en RAM.
* **Opción 2 (HeapSort)**: Construye la estructura de Binary Heap y ejecuta el ordenamiento in-place sobre la lista de palabras.
* **Opción 3 (AVL Tree)**: Realiza la inserción nodo por nodo en el árbol AVL balanceado, ejecuta el recorrido inorden para obtener la secuencia ordenada y calcula la memoria consumida por los nodos y punteros.
* **Opción 4 (Prueba completa)**: Corre de forma secuencial las tres estrategias sobre el mismo archivo de datos cargado para realizar la comparación directa de tiempos y memoria.
* **Opción 5 (Cambiar archivo / Regenerar)**: Permite alternar a otro archivo de la carpeta `data/` o generar un nuevo orden aleatorio sin necesidad de reiniciar el programa.
* **Opción 0 (Salir)**: Libera los recursos y finaliza la ejecución.

---

## 4. Datos

| Archivo | Contenido | Origen |
|---|---|---|
| `words_alpha.txt` | ~370.105 palabras en inglés, ordenadas alfabéticamente | Repositorio público [dwyl/english-words](https://github.com/dwyl/english-words) |
| `dataset_profe.txt` | 100.000 palabras desordenadas | Entregado por el profesor |
| `dataset.txt` | 100.000 palabras aleatorias | Generado por `DatasetGenerator` a partir de `words_alpha.txt` |

**Generación de `dataset.txt`:** la función `generarDataset` lee las 370.105 palabras de
`words_alpha.txt` con `leerPalabras`, las baraja con `shuffle` usando el generador
`mt19937` con una semilla tomada de `random_device`, conserva las primeras 100.000 con
`resize` y las escribe en `dataset.txt` con `escribirPalabras`. Como la lista quedó
barajada, esas 100.000 palabras son aleatorias y además quedan desordenadas.

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

Primero se probó con listas pequeñas: una desordenada, una ya ordenada y una ordenada
al revés, para comprobar que el pivote central funcionara con datos ordenados. Después
se probó desde el menú con `dataset.txt` y `dataset_profe.txt` (100.000 palabras cada
uno). En todos los casos la función `estaOrdenado` confirmó que el resultado quedó
ordenado. Los tiempos y la memoria se reportan en la sección 7.

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
- En HeapSort el cronómetro rodea `heapSort`. En el AVL rodea `avlOrdenar`, que incluye insertar las palabras, el recorrido inorden y la liberación del árbol.
- Cada algoritmo se ejecutó 5 veces con cada archivo (`dataset.txt` y `dataset_profe.txt`).
  Se reportan las 5 corridas y el promedio. Todas las mediciones se hicieron en el mismo
  equipo y con la misma compilación (ver sección 7).

**Memoria:**
- Estimación con `sizeof`: `n × sizeof(std::string)` + total de letras (función `memoriaPalabras`).
- Es una aproximación por encima: en g++, las palabras de 15 letras o menos guardan sus letras dentro del mismo `string` (32 bytes).
- Para el AVL no se usa `memoriaPalabras`: se calcula `nodos × sizeof(Nodo) + letras` (56 bytes por nodo). Cubre el árbol, pero no el vector donde se guarda el resultado del inorden.
- Como la memoria es una estimación calculada a partir de los datos (no una medición en
  tiempo de ejecución), da el mismo valor en todas las corridas.

---

## 7. Resultados

### Equipo de pruebas

| Componente | Detalle |
|---|---|
| Equipo | Lenovo Legion |
| Procesador | AMD Ryzen 7 260 |
| Memoria RAM | 32 GB |
| Tarjeta gráfica | NVIDIA GeForce RTX 5060 (no interviene: los algoritmos se ejecutan en el procesador) |
| Sistema operativo | Windows 11 |
| Compilador | g++ 16.1.0 (MSYS2 UCRT64), `-std=c++17 -O2` |

### Tiempo con `dataset_profe.txt` (100.000 palabras)

| Corrida | QuickSort (ms) | HeapSort (ms) | AVL (ms) |
|---|---|---|---|
| 1 | 26,00 | 48,94 | 37,84 |
| 2 | 26,37 | 41,65 | 34,20 |
| 3 | 24,68 | 45,33 | 33,40 |
| 4 | 24,95 | 53,35 | 37,77 |
| 5 | 26,58 | 42,10 | 36,88 |
| **Promedio** | **25,72** | **46,27** | **36,02** |

### Tiempo con `dataset.txt` (100.000 palabras, generado)

| Corrida | QuickSort (ms) | HeapSort (ms) | AVL (ms) |
|---|---|---|---|
| 1 | 26,70 | 59,66 | 35,08 |
| 2 | 26,68 | 51,09 | 41,11 |
| 3 | 26,70 | 48,47 | 36,30 |
| 4 | 27,64 | 46,68 | 44,21 |
| 5 | 26,57 | 48,85 | 35,14 |
| **Promedio** | **26,86** | **50,95** | **38,37** |

### Memoria estimada (igual para ambos archivos)

| Algoritmo | Memoria estimada | Observación |
|---|---|---|
| QuickSort | 3,95 MB | Ordena dentro del mismo vector (más la pila de recursión, O(log n)) |
| HeapSort | 3,95 MB | Ordena dentro del mismo vector (O(1) adicional) |
| AVL | 6,24 MB | Solo el árbol. Al construir la lista inorden también existe el vector resultado (3,95 MB), así que el consumo adicional máximo ronda los 10,19 MB |

---

## 8. Análisis comparativo

### 8.1 Complejidad

| Algoritmo | Mejor caso | Promedio | Peor caso | Memoria adicional |
|---|---|---|---|---|
| QuickSort | O(n log n) | O(n log n) | O(n²) | O(log n) promedio (pila de recursión) |
| HeapSort | O(n log n) | O(n log n) | O(n log n) | O(1) (in-place) |
| AVL | O(n log n) | O(n log n) | O(n log n) | O(n) (nodos; más el vector del resultado) |

### 8.2 ¿Qué algoritmo tuvo mejor rendimiento?

**QuickSort** fue el más rápido con ambos archivos (25,72 ms y 26,86 ms en promedio),
seguido por el **AVL** (36,02 ms y 38,37 ms) y por último **HeapSort** (46,27 ms y
50,95 ms). HeapSort tardó entre 1,8 y 1,9 veces más que QuickSort, y el AVL alrededor de
1,4 veces más.

En memoria, QuickSort y HeapSort empatan con la menor estimación (3,95 MB), porque ambos
ordenan dentro del mismo vector. El AVL es el que más usa: 6,24 MB solo en nodos, más el
vector donde guarda el resultado.

Los resultados con los dos archivos son muy parecidos, lo cual tiene sentido: ambos tienen
100.000 palabras en orden aleatorio.

### 8.3 ¿Por qué la teoría difiere de la práctica?

Los tres algoritmos son O(n log n) en el caso promedio y, aun así, HeapSort tardó casi el
doble que QuickSort. La notación O describe cómo crece el tiempo cuando crece n, pero
ignora las constantes y la forma en que cada algoritmo accede a la memoria.

- **QuickSort** recorre el vector de forma secuencial durante la partición. El procesador
  lee la memoria en bloques, así que los datos siguientes ya están en caché cuando se
  necesitan.
- **HeapSort** salta de la posición `i` a `2i+1` o `2i+2`, cada vez más lejos en el
  arreglo, y en cada nivel de `hundir` compara la palabra con **dos** hijos y hace un
  intercambio.
- **AVL** fue más rápido que HeapSort a pesar de trabajar con punteros dispersos y de hacer
  100.000 reservas con `new`, que en teoría aprovechan peor la caché. Una explicación
  probable es la cantidad de comparaciones: al insertar, el AVL compara una vez por nivel
  (altura de 20 con 100.000 palabras), mientras que HeapSort compara dos veces por nivel en
  cada una de las n extracciones. Como comparar palabras es la operación más costosa aquí,
  hacer menos comparaciones compensa el peor acceso a memoria. No se midió con un
  profiler, por lo que es una hipótesis.

### 8.4 Ventajas y desventajas de cada estructura

- **QuickSort / vector:** fue el más rápido en la práctica y ordena dentro del mismo
  vector, sin estructura adicional (solo la pila de recursión, O(log n) en promedio).
  Como el vector es memoria contigua, aprovecha bien la caché del procesador. Su
  desventaja es el peor caso O(n²): el pivote central lo evita con datos ordenados, pero
  no lo elimina en teoría. Además no es estable y, con la partición de Lomuto, se degenera
  cuando hay muchos valores repetidos (ver sección 9.1).
- **HeapSort / Binary Heap:** ordena in-place (memoria adicional O(1)) y garantiza O(n log n) en todos los casos, sin degradarse con datos repetidos u ordenados. Por otro lado, no es estable, accede a la memoria de forma poco favorable para la caché (salta entre padres e hijos) y solo sirve para ordenar.
- **AVL:** garantiza O(n log n) gracias al balanceo (altura 20 con 100.000 palabras) y el árbol queda disponible para insertar y buscar en O(log n). Por otro lado, usa más memoria (nodo de 56 bytes por palabra, alrededor de un 58 % más que HeapSort), hace 100.000 reservas dinámicas con punteros dispersos y requiere más código (rotaciones).

---

## 9. Problemas encontrados

### 9.1 Codificación UTF-16 de `dataset_profe.txt`

Al probar QuickSort con `dataset_profe.txt`, el programa reportaba 199.999 palabras en
lugar de 100.000 y se cerraba sin mostrar ningún error durante el ordenamiento.

La causa era la codificación: el archivo venía en UTF-16, donde cada carácter ocupa dos
bytes. `leerPalabras` lee el archivo byte por byte, así que en cada salto de línea quedaba
un carácter nulo suelto que se contaba como una palabra más. Esas 99.999 "palabras" eran
todas iguales, y con tantos valores repetidos la partición de Lomuto deja casi todo del
mismo lado del pivote: la recursión se volvió tan profunda que el programa se cerró por
desbordamiento de la pila.

Se solucionó convirtiendo el archivo a UTF-8 desde VS Code; las palabras no cambian, solo
la forma en que se guardan. Este error mostró en la práctica una debilidad de QuickSort
con Lomuto: su rendimiento se degrada cuando hay muchos valores repetidos.

### 9.2 Variación entre corridas

Los tiempos cambiaron de una corrida a otra aunque los datos fueran los mismos. Por
ejemplo, la primera corrida de HeapSort con `dataset.txt` tardó 59,66 ms, mientras que las
siguientes estuvieron entre 46,68 y 51,09 ms; y una corrida del AVL llegó a 44,21 ms cuando
las demás estuvieron entre 35,08 y 41,11 ms. Estas diferencias se deben a factores externos
al algoritmo, como otros procesos del sistema y el estado de la caché. Por eso cada
algoritmo se ejecutó 5 veces y se reporta el promedio.

---

## 10. Conclusiones

### Sara Castaño Suárez

Para ordenar una sola vez 100.000 palabras en orden aleatorio, QuickSort sobre un vector
fue el enfoque más apropiado: fue el más rápido en todas las pruebas, usó la menor memoria
y su implementación es la más sencilla, y su peor caso O(n²) se evitó eligiendo el pivote
central. La práctica también mostró que la complejidad teórica no basta para elegir un
algoritmo: los tres son $O(n \log n)$, pero la forma en que cada estructura usa la memoria y
la cantidad de comparaciones marcaron diferencias de casi el doble en el tiempo real.

### Simon Lopez Mesa

Hacerr HeapSort y el árbol AVL desde cero me mostró que dos algoritmos con la misma complejidad, pueden comportarse distinto en la práctica. En nuestras pruebas HeapSort fue el más lento aunque ordena sobre el propio vector y no necesita memoria adicional. El AVL fue más rápido pero a cambio usó alrededor de un 58 % más de memoria: 6,24 MB frente a 3,95 MB, solo en nodos y sin contar el vector del resultado.

Para ordenar una sola vez 100.000 palabras, el algoritmo más apropiado fue QuickSort: el más rápido y junto con HeapSort, el de menor memoria. Aun así, HeapSort y el AVL tienen algo que QuickSort no garantiza: $O(n \log n)$ también en el peor caso, algo que el problema de los valores repetidos dejó muy claro. El algoritmo HeapSort es mejor si importan la memoria y el peor caso, y el AVL si además de ordenar se necesita insertar y buscar después.
Algo a destacar es que en mis pruebas individuales Heapsort y AVL qeudaron empatados en los tiempos, lo que sugiere que la diferencia entre los dos depende del hardware.

### Antuan Alejandro Navarro Ortiz

En esta práctica implementé un sistema modular en C++ con menú interactivo por consola y ejecutable en terminal externa que compara QuickSort (std::vector), HeapSort (Binary Heap) y Árbol AVL (inserción + inorden) sobre 100,000 palabras de distintos archivos (dataset.txt, dataset_profe.txt, words_alpha.txt). En las pruebas, QuickSort fue el más veloz por la localidad de referencia en caché del vector contiguo; HeapSort igualó su bajo consumo de RAM al ser in-place pero fue más lento por los cache misses al navegar el heap; y el Árbol AVL logró tiempos competitivos pero consumió ~60% más memoria por el sobrecosto de punteros y alturas en sus nodos, demostrando el impacto real de la gestión de memoria en hardware más allá de la complejidad $O(n \log n)$ teórica.

---

## 11. Fuentes

- Lista de palabras: [dwyl/english-words](https://github.com/dwyl/english-words)
- Inspiración para la partición de QuickSort: [GeeksforGeeks – C++ Program for Quick Sort](https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/)
- [Repositorio del profesor](https://github.com/carlosalvarezh/EstructuraDatosAlgoritmos1).
- Notas de clase, [videos instructivos en Youtube](https://www.youtube.com/watch?v=MkHuwIrWZmI).
