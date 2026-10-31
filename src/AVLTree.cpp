#include "AVLTree.hpp"

#include <algorithm>  // std::max

AVLTree::AVLTree() : raiz(nullptr), nodos(0), letras(0) {}

AVLTree::~AVLTree() { liberar(raiz); }

// Libera en post-orden: primero los hijos, al final el propio nodo.
void AVLTree::liberar(Nodo* n) {
    if (n == nullptr) return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}


// Alturas y factor de balance

int AVLTree::alturaDe(const Nodo* n) { return n ? n->altura : 0; }

// factor = altura(izq) - altura(der)
//   > 0  : el arbol pesa mas a la izquierda
//   < 0  : pesa mas a la derecha
//   -1,0,1 : balanceado (AVL valido)
int AVLTree::factorBalance(const Nodo* n) {
    return n ? alturaDe(n->izq) - alturaDe(n->der) : 0;
}

void AVLTree::actualizarAltura(Nodo* n) {
    n->altura = 1 + std::max(alturaDe(n->izq), alturaDe(n->der));
}


// Rotacion simple a la DERECHA (caso Izquierda-Izquierda)
/*
         y                x
        / \              / \
       x   C    ==>     A   y
      / \                  / \
     A   B                B   C
*/
// El inorden NO cambia (A x B y C), solo cambia la forma del arbol.
// Se actualiza primero 'y' (quedo mas abajo) y luego 'x'.

Nodo* AVLTree::rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* B = x->der;

    x->der = y;
    y->izq = B;

    actualizarAltura(y);
    actualizarAltura(x);
    return x;  // nueva raiz de este subarbol
}


// Rotacion simple a la IZQUIERDA (caso Derecha-Derecha): espejo de la anterior
/*
       x                    y
      / \                  / \
     A   y      ==>       x   C
        / \              / \
       B   C            A   B
*/

Nodo* AVLTree::rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* B = y->izq;

    y->izq = x;
    x->der = B;

    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}


// balancear: se llama en cada nodo del camino de vuelta de la insercion.
// Actualiza la altura y, si el nodo se desbalanceo (|factor| = 2), aplica
// uno de los 4 casos:
//   Izq-Izq : rotacion simple derecha
//   Izq-Der : rotacion doble  (izquierda al hijo, luego derecha al nodo)
//   Der-Der : rotacion simple izquierda
//   Der-Izq : rotacion doble  (derecha al hijo, luego izquierda al nodo)
// El caso se decide con el factor del HIJO pesado (y no comparando la
// palabra), asi funciona bien aunque haya palabras repetidas.
// Despues de la insercion, a lo sumo UNA rotacion (simple o doble) arregla
// todo el arbol.

Nodo* AVLTree::balancear(Nodo* n) {
    actualizarAltura(n);
    int fb = factorBalance(n);

    if (fb > 1) {                              // pesa a la izquierda
        if (factorBalance(n->izq) < 0)         // caso Izq-Der
            n->izq = rotarIzquierda(n->izq);
        return rotarDerecha(n);                // Izq-Izq (o 2da parte del doble)
    }
    if (fb < -1) {                             // pesa a la derecha
        if (factorBalance(n->der) > 0)         // caso Der-Izq
            n->der = rotarDerecha(n->der);
        return rotarIzquierda(n);              // Der-Der (o 2da parte del doble)
    }
    return n;                                  // ya estaba balanceado
}


// Insercion: igual que en un arbol de busqueda normal (bajar comparando),
// y al regresar de la recursion se rebalancea cada nodo del camino.
// Menores -> izquierda. Mayores o IGUALES -> derecha (conserva duplicados).

Nodo* AVLTree::insertarRec(Nodo* n, const std::string& palabra) {
    if (n == nullptr) {
        ++nodos;
        letras += palabra.size();
        return new Nodo(palabra);
    }

    if (palabra < n->palabra)
        n->izq = insertarRec(n->izq, palabra);
    else
        n->der = insertarRec(n->der, palabra);

    return balancear(n);
}

void AVLTree::insertar(const std::string& palabra) {
    raiz = insertarRec(raiz, palabra);
}


// Recorrido inorden: izquierda -> nodo -> derecha.
// En un arbol de busqueda esto visita las palabras en orden creciente.

void AVLTree::inordenRec(const Nodo* n, std::vector<std::string>& salida) {
    if (n == nullptr) return;
    inordenRec(n->izq, salida);
    salida.push_back(n->palabra);
    inordenRec(n->der, salida);
}

std::vector<std::string> AVLTree::inorden() const {
    std::vector<std::string> salida;
    salida.reserve(nodos);  // evita realocaciones mientras se llena
    inordenRec(raiz, salida);
    return salida;
}


// Consultas

std::size_t AVLTree::cantidadNodos() const { return nodos; }

int AVLTree::altura() const { return alturaDe(raiz); }

// Estimacion pedida en la guia: nodos * sizeof(Nodo) + letras.
// Es aproximada: sizeof(Nodo) ya incluye el objeto std::string, y las
// palabras cortas caben dentro de el (optimizacion SSO), por eso 'letras'
// puede contar un poco de mas.
std::size_t AVLTree::memoriaBytes() const {
    return nodos * sizeof(Nodo) + letras;
}

bool AVLTree::balanceadoRec(const Nodo* n) {
    if (n == nullptr) return true;
    int fb = factorBalance(n);
    if (fb < -1 || fb > 1) return false;
    return balanceadoRec(n->izq) && balanceadoRec(n->der);
}

bool AVLTree::esBalanceado() const { return balanceadoRec(raiz); }


// Funcion de alto nivel para el menu

std::vector<std::string> avlOrdenar(const std::vector<std::string>& palabras,
                                    std::size_t* bytesEstimados) {
    AVLTree arbol;
    for (const std::string& p : palabras) arbol.insertar(p);

    std::vector<std::string> resultado = arbol.inorden();
    if (bytesEstimados != nullptr) *bytesEstimados = arbol.memoriaBytes();
    return resultado;
}   // aqui el destructor libera el arbol