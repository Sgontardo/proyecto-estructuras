#include <iostream> // insertar y desplegar por consola, métodos
#include <stack>

using namespace std;


struct nodo {
    int dato;
    nodo *siguiente;
} *primero;


void insertarNodo();

void insertarNodo() {
    nodo *nuevo = new nodo();
    cout << "Ingrese el dato: ";
    cin >> nuevo -> dato;

    nuevo -> siguiente = primero;
    primero = nuevo;

    cout << "Nodo ingresado con éxito" << endl;
}


void desplegarPila();

void desplegarPila() {
    nodo *actual = new nodo();
    actual = primero;
    if (primero != NULL) {
        while (actual != NULL) {
            cout << endl << " " << actual -> dato;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La pila se encuentra vacía" << endl;
    }
}


void buscarNodo();

void buscarNodo() {
    nodo *actual = new nodo();
    actual = primero;
    bool encontrado = false;
    int nodoBuscado = 0;
    cout << "Ingrese el dato del nodo a buscar: ";
    cin >> nodoBuscado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> dato == nodoBuscado) {
                cout << "Nodo con el dato " << nodoBuscado << " encontrado" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Nodo no encontrado" << endl;
        }
    } else {
        cout << "La pila se encuentra vacía" << endl;
    }
}


void modificarNodo();

void modificarNodo() {
    nodo *actual = new nodo();
    actual = primero;
    bool encontrado = false;
    int nodoBuscado = 0;
    cout << "Ingrese el dato del nodo a buscar para modificar: ";
    cin >> nodoBuscado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> dato == nodoBuscado) {
                cout << "Nodo con el dato " << nodoBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo dato para este nodo: ";
                cin >> actual -> dato;
                cout << "Nodo modificado con éxito" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Nodo no encontrado" << endl;
        }
    } else {
        cout << "La pila se encuentra vacía" << endl;
    }
}


void eliminarNodo();

void eliminarNodo() {
    nodo *actual = new nodo();
    actual = primero;
    nodo *anterior = new nodo();
    anterior = NULL;
    bool encontrado = false;
    int nodoBuscado = 0;
    cout << "Ingrese el dato del nodo a buscar para eliminar: ";
    cin >> nodoBuscado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> dato == nodoBuscado) {
                cout << "Nodo con el dato " << nodoBuscado << " encontrado" << endl;
                if (actual == primero) {
                    primero = primero -> siguiente;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Nodo eliminado con éxito" << endl;
                encontrado = true;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Nodo no encontrado" << endl;
        }
    } else {
        cout << "La pila se encuentra vacía" << endl;
    }
}


// Pila  9 -> 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> NULL
// print sería 9 8 7 6 5 4 3 2 1 La pila se encuentra vacía

// primero es un apuntador que va a null si no está apuntando a nada
// nodo se crea para ir agregando datos, ejemplo: 10, 20, 30
// al crear un struct nodo se crea un apuntador a la dirección de memoria con un dato entero y un apuntador a la siguiente dirección de memoria

int main() {

    return 0;


    /* std::stack<int> pila;

    // Agregar elementos a la pila
    pila.push(10);
    pila.push(20);
    pila.push(30);

    // Obtener el tamaño de la pila
    std::cout << "Tamaño de la pila: " << pila.size() << std::endl;

    // Acceder al elemento en la parte superior de la pila
    std::cout << "Elemento en la parte superior de la pila: " << pila.top() << std::endl;

    // Eliminar el elemento en la parte superior de la pila
    pila.pop();

    // Verificar si la pila está vacía
    if (pila.empty()) {
        std::cout << "La pila está vacía" << std::endl;
    } else {
        std::cout << "La pila no está vacía" << std::endl;
    }

    return 0; */
}