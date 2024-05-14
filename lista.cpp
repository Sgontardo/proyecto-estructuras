#include <iostream>

using namespace std;

struct nodo {
    int dato;
    nodo *siguiente;
} *primero, *ultimo;


void crearNodo();

void crearNodo() {
    nodo *nuevo = new nodo();
    cout << "Ingrese el dato: ";
    cin >> nuevo -> dato;

    if (primero == NULL) {
        primero = nuevo;
        primero -> siguiente = NULL;
        ultimo = nuevo;
    } else {
        ultimo -> siguiente = nuevo;
        nuevo -> siguiente = NULL;
        ultimo = nuevo;
    }

    cout << "Nodo ingresado" << endl;
}


void leerNodo();

void leerNodo() {
    nodo *actual = new nodo();
    actual = primero;
    if (primero != NULL) {
        while (actual != NULL) {
            cout << endl << " " << actual -> dato;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista se encuentra vacía" << endl;
    }
}


void modificarNodo();

void modificarNodo() {
    nodo *actual = new nodo();
    actual = primero;
    bool encontrado = false;
    int nodoBuscado = 0;
    cout << "Ingrese el dato del nodo a modificar: ";
    cin >> nodoBuscado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> dato == nodoBuscado) {
                cout << "Nodo con el dato " << nodoBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo dato: ";
                cin >> actual -> dato;
                cout << "Nodo modificado" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Nodo no encontrado" << endl;
        }
    } else {
        cout << "La lista se encuentra vacía" << endl;
    }
}


void borrarNodo();

void borrarNodo() {
    nodo *actual = new nodo();
    actual = primero;
    nodo *anterior = new nodo();
    anterior = NULL;
    bool encontrado = false;
    int nodoBuscado = 0;
    cout << "Ingrese el dato del nodo a borrar: ";
    cin >> nodoBuscado;
    if (primero != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> dato == nodoBuscado) {
                cout << "Nodo con el dato " << nodoBuscado << " encontrado" << endl;
                if (actual == primero) {
                    primero = primero -> siguiente;
                } else if (actual == ultimo) {
                    anterior -> siguiente = NULL;
                    ultimo = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Nodo eliminado" << endl;
                encontrado = true;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Nodo no encontrado" << endl;
        }
    } else {
        cout << "La lista se encuentra vacía" << endl;
    }
}


int main() {
    return 0;
}