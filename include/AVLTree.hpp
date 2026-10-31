#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <string>
#include <vector>


// Nodo del arbol AVL.
// El struct vive en este .hpp (como se acordo) para poder calcular
// sizeof(Nodo) al estimar la memoria.

struct Nodo {
    std::string palabra;  // dato guardado
    Nodo* izq;            // hijo izquierdo (palabras menores)
    Nodo* der;            // hijo derecho   (palabras mayores o iguales)
    int altura;           // altura del subarbol que cuelga de este nodo
                          // (una hoja vale 1, un puntero nulo vale 0)

    explicit Nodo(const std::string& p)
        : palabra(p), izq(nullptr), der(nullptr), altura(1) {}
};


// AVLTree: arbol binario de busqueda AUTO-BALANCEADO.
// Invariante AVL: en cada nodo, |altura(izq) - altura(der)| <= 1.
// Gracias a eso la altura es siempre O(log n) (maximo ~1.44 * log2(n)),
// y cada insercion cuesta O(log n) incluso en el peor caso.
// Las palabras repetidas SE CONSERVAN (van al hijo derecho), asi la salida
// siempre tiene el mismo tamanio que la entrada.

class AVLTree {
public:
    AVLTree();
    ~AVLTree();                          // libera todos los nodos
    AVLTree(const AVLTree&) = delete;    // evita copias (doble delete)
    AVLTree& operator=(const AVLTree&) = delete;

    void insertar(const std::string& palabra);   // O(log n)

    // Recorrido inorden (izq, nodo, der): entrega las palabras en orden
    // alfabetico. O(n).
    std::vector<std::string> inorden() const;

    std::size_t cantidadNodos() const;
    int altura() const;                  // altura del arbol completo

    // Estimacion: nodos * sizeof(Nodo) + letras de todas las palabras.
    std::size_t memoriaBytes() const;

    // Para pruebas: comprueba que TODOS los nodos cumplan la regla AVL.
    bool esBalanceado() const;

private:
    Nodo* raiz;
    std::size_t nodos;       // cuantos nodos hay
    std::size_t letras;      // suma de la longitud de todas las palabras

    // ---- auxiliares recursivos (la profundidad es O(log n), no hay riesgo) ----
    static int alturaDe(const Nodo* n);
    static int factorBalance(const Nodo* n);
    static void actualizarAltura(Nodo* n);
    static Nodo* rotarDerecha(Nodo* y);
    static Nodo* rotarIzquierda(Nodo* x);
    static Nodo* balancear(Nodo* n);
    Nodo* insertarRec(Nodo* n, const std::string& palabra);
    static void inordenRec(const Nodo* n, std::vector<std::string>& salida);
    static void liberar(Nodo* n);
    static bool balanceadoRec(const Nodo* n);
};


// Funcion que usa el menu: inserta TODAS las palabras en un AVL y devuelve el
// recorrido inorden (la lista ordenada).
// Si se pasa 'bytesEstimados', ahi se deja la estimacion de memoria del arbol
// (nodos * sizeof(Nodo) + letras). Si no, se ignora.

std::vector<std::string> avlOrdenar(const std::vector<std::string>& palabras,
                                    std::size_t* bytesEstimados = nullptr);

#endif