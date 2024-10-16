#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estructura del Nodo del árbol de Huffman
struct Nodo {
    char caracter;   // Caracter que representa el nodo
    int frecuencia;  // Frecuencia de aparición del caracter
    Nodo* izquierda; // Puntero al hijo izquierdo
    Nodo* derecha;   // Puntero al hijo derecho

    Nodo(char c, int f) : caracter(c), frecuencia(f), izquierda(nullptr), derecha(nullptr) {}
};

// Sobreccarga de operadores de comparación para la cola de prioridad 
// Compara nodos en función de la frecuencia, ordenando de menor a mayor
struct Comparador {
    bool operator()(Nodo* a, Nodo* b) {
        return a->frecuencia > b->frecuencia;
    }
};

// Función para generar los códigos de Huffman a partir del árbol
void generarCodigos(Nodo* raiz, string codigo, unordered_map<char, string>& codigos) {
    if (!raiz) return; // Si el nodo es nulo, terminar
    if (!raiz->izquierda && !raiz->derecha) { // Si es una hoja (caracter final)
        codigos[raiz->caracter] = codigo; // Guardar el código correspondiente al caracter
    }
    // Llamada recursiva para los subárboles izquierdo y derecho
    generarCodigos(raiz->izquierda, codigo + "0", codigos);
    generarCodigos(raiz->derecha, codigo + "1", codigos);
}

// Función para construir el árbol de Huffman a partir de las frecuencias de los caracteres
Nodo* construirArbolHuffman(const unordered_map<char, int>& frecuencias) {
    // Cola de prioridad que almacenará los nodos según la frecuencia
    priority_queue<Nodo*, vector<Nodo*>, Comparador> pq;

    // Insertar todos los caracteres y sus frecuencias en la cola de prioridad
    for (auto& par : frecuencias) {
        pq.push(new Nodo(par.first, par.second));
    }

    // Construir el árbol de Huffman combinando nodos hasta que solo quede uno
    while (pq.size() > 1) {
        Nodo* izquierda = pq.top(); // Extraer nodo con menor frecuencia
        pq.pop();
        Nodo* derecha = pq.top(); // Extraer el siguiente nodo con menor frecuencia
        pq.pop();

        // Crear un nuevo nodo que combina los dos anteriores
        Nodo* nuevoNodo = new Nodo('\0', izquierda->frecuencia + derecha->frecuencia);
        nuevoNodo->izquierda = izquierda;
        nuevoNodo->derecha = derecha;

        // Insertar el nuevo nodo en la cola
        pq.push(nuevoNodo);
    }

    // Devolver la raíz del árbol de Huffman
    return pq.top();
}

// Función principal para obtener los códigos de Huffman en su forma canónica
unordered_map<char, string> huffmanCanonico(const string& palabra) {
    unordered_map<char, int> frecuencias;

    // Contar la frecuencia de cada caracter en la palabra
    for (char c : palabra) {
        frecuencias[c]++;
    }

    // Construir el árbol de Huffman basado en las frecuencias
    Nodo* raiz = construirArbolHuffman(frecuencias);

    // Generar los códigos de Huffman para cada caracter
    unordered_map<char, string> codigos;
    generarCodigos(raiz, "", codigos);

    // Ordenar los códigos de Huffman por longitud y valor lexicográfico
    vector<pair<string, char>> codigosOrdenados;
    for (auto& par : codigos) {
        codigosOrdenados.push_back({par.second, par.first});
    }

    // Ordenar los códigos primero por longitud y luego por su valor en binario
    sort(codigosOrdenados.begin(), codigosOrdenados.end(), [](const pair<string, char>& a, const pair<string, char>& b) {
        if (a.first.length() == b.first.length()) {
            return a.first < b.first;
        }
        return a.first.length() < b.first.length();
    });

    // Generar los códigos canónicos
    unordered_map<char, string> codigosCanonicamenteOrdenados;
    string codigoActual = "";
    for (auto& par : codigosOrdenados) {
        if (codigoActual.empty()) {
            // Iniciar el primer código con ceros
            codigoActual = string(par.first.length(), '0');
        } else {
            // Generar el siguiente código incrementando el binario actual
            int i = codigoActual.length() - 1;
            while (i >= 0 && codigoActual[i] == '1') {
                codigoActual[i] = '0';
                i--;
            }
            if (i >= 0) {
                codigoActual[i] = '1';
            } else {
                codigoActual = "1" + codigoActual;
            }
        }
        codigosCanonicamenteOrdenados[par.second] = codigoActual;
    }

    // Devolver el map con los códigos canónicos
    return codigosCanonicamenteOrdenados;
}

int main() {
    string palabra;
    cout << "Ingrese una palabra: ";
    cin >> palabra;

    // Obtener los códigos de Huffman canónicos para la palabra ingresada
    unordered_map<char, string> codigos = huffmanCanonico(palabra);

    // Mostrar los códigos de Huffman canónicos 
    cout << "\nCodigos de Huffman canonicos:\n";
    cout << "Caracter | Codigo\n";
    cout << "-----------------\n";
    for (auto& par : codigos) {
        cout << "   " << par.first << "    | " << par.second << "\n";
    }

    // Mostrar los códigos concatenados de cada caracter en la palabra original
    cout << "\nCodigos concatenados:\n";
    for (char c : palabra) {
        cout << codigos[c] << " ";
    }
    cout << "\n";

    return 0;
}