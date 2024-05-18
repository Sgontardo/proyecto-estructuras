/*
Primera parte proyecto Estructura de Datos
Integrantes:
    Sergio Gontardo
    Leonardo Chacón
    Daniel Vasquez
*/

/*
Estructuras que tenemos que añadir:
    Raza:
        Nombre
        Energía
        Salud: 100%
        Ambiente
        Fidelidad
    Accesorios:
        Nombre
        Tipo (ataque, defensa, supervivencia y adaptación)
        Valor
        Energía
        Contenedor
    Ambiente (Elección aleatoria):
        Nombre
*/

/*
Creación de soldados con su mochila
    Soldado (Nombre del player, elegir raza)
        Salud: 100%
        Energía: Según la raza
    Mochila (Elegir 5 accesorios para mochila)
        Accesorios
    Equipo (Aleatorio)
*/

/*
Manejo de Menú
    1. Acciones para raza
        1.1 Crear raza
        1.2 Consultar raza
        1.3 Modificar raza
        1.4 Eliminar raza
    2. Acciones para accesorio
        2.2 Crear accesorio
        2.3 Consultar accesorio
        2.4 Modificar accesorio
        2.5 Eliminar accesorio
    3. Acciones para ambiente
        3.3 Crear ambiente
        3.4 Consultar ambiente
        3.5 Modificar ambiente
        3.6 Eliminar ambiente
    4. Crear Soldado
        4.1 Soldado
            4.1.1 Asignar raza
            4.1.2 Agregar accesorios a mochila
            4.1.3 Asignar ambiente
    5. Salir
*/

/*
Uso de lista enlazada
    Crear
    Leer
    Modificar
    Eliminar
*/

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct nodo {
    int dato;
    nodo *siguiente;
} *primero, *ultimo;

void crearNodo(int dato) {
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;

    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    cout << "Nodo ingresado" << endl;
}

void leerNodo() {
    nodo *actual = primero;
    if (actual!= nullptr) {
        while (actual!= nullptr) {
            cout << " " << actual->dato;
            actual = actual->siguiente;
        }
        cout << endl;
    } else {
        cout << "La lista se encuentra vacía" << endl;
    }
}

void modificarNodo(int datoBuscado, int datoNuevo) {
    nodo *actual = primero;
    bool encontrado = false;
    while (actual!= nullptr &&!encontrado) {
        if (actual->dato == datoBuscado) {
            actual->dato = datoNuevo;
            cout << "Nodo modificado" << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) {
        cout << "Nodo no encontrado" << endl;
    }
}

void borrarNodo(int datoBuscado) {
    nodo *actual = primero, *anterior = nullptr;
    bool encontrado = false;
    while (actual!= nullptr &&!encontrado) {
        if (actual->dato == datoBuscado) {
            if (anterior == nullptr) {
                primero = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            if (actual == ultimo) {
                ultimo = anterior;
            }
            delete actual;
            encontrado = true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    if (!encontrado) {
        cout << "Nodo no encontrado" << endl;
    }
}

void escribirDatosEnArchivo(nodo* primerNodo) {
    ofstream archivo("datos.txt");
    if (archivo.is_open()) {
        nodo* actual = primerNodo;
        while (actual!= nullptr) {
            archivo << actual->dato << "\n";
            actual = actual->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void leerDatosDesdeArchivo() {
    ifstream archivo("datos.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            int dato = stoi(linea);
            crearNodo(dato);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}

void menu() {
    int opcion;
    char seguirMenu = 's';
    do {
        cout << "Manejo de Menú" << endl;
        cout << "1. Acciones para raza" << endl;
        cout << "2. Acciones para accesorio" << endl;
        cout << "3. Acciones para ambiente" << endl;
        cout << "4. Crear soldado" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                int opcionraza;
                do {
                    cout << "1 Crear raza" << endl;
                    cout << "2 Consultar raza" << endl;
                    cout << "3 Modificar raza" << endl;
                    cout << "4 Eliminar raza" << endl;
                    cout << "5 Regresar al menú principal" << endl;
                    cin >> opcionraza;
                    switch(opcionraza) {
                        case 1:
                            int dato;
                            cout << "Ingrese el dato del nodo: ";
                            cin >> dato;
                            crearNodo(dato);
                            break;
                        case 2:
                            leerNodo();
                            break;
                        case 3:
                            int datoBuscado, datoNuevo;
                            cout << "Ingrese el dato del nodo a modificar: ";
                            cin >> datoBuscado;
                            cout << "Ingrese el nuevo dato del nodo: ";
                            cin >> datoNuevo;
                            modificarNodo(datoBuscado, datoNuevo);
                            break;
                        case 4:
                            int datoBorrar;
                            cout << "Ingrese el dato del nodo a borrar: ";
                            cin >> datoBorrar;
                            borrarNodo(datoBorrar);
                            break;
                        case 5:
                            cout << "¿Desea regresar al menú principal? (s/n): ";
                            cin >> seguirMenu;
                            if (seguirMenu == 'n') {
                                break;
                            } else {
                                cout << "Regresando al menú principal" << endl;
                            }
                            break;
                        default:
                            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                            break;
                    }
                } while (opcionraza != 5);
                break;
            case 2:
                int opcionaccesorio;
                do {
                    cout << "1 Crear accesorio" << endl;
                    cout << "2 Consultar accesorio" << endl;
                    cout << "3 Modificar accesorio" << endl;
                    cout << "4 Eliminar accesorio" << endl;
                    cout << "5 Regresar al menú principal" << endl;
                    cin >> opcionaccesorio;
                    switch(opcionaccesorio) {
                        case 1:
                            int dato;
                            cout << "Ingrese el dato del nodo: ";
                            cin >> dato;
                            crearNodo(dato);
                            break;
                        case 2:
                            leerNodo();
                            break;
                        case 3:
                            int datoBuscado, datoNuevo;
                            cout << "Ingrese el dato del nodo a modificar: ";
                            cin >> datoBuscado;
                            cout << "Ingrese el nuevo dato del nodo: ";
                            cin >> datoNuevo;
                            modificarNodo(datoBuscado, datoNuevo);
                            break;
                        case 4:
                            int datoBorrar;
                            cout << "Ingrese el dato del nodo a borrar: ";
                            cin >> datoBorrar;
                            borrarNodo(datoBorrar);
                            break;
                        case 5:
                            cout << "¿Desea regresar al menú principal? (s/n): ";
                            cin >> seguirMenu;
                            if (seguirMenu == 'n') {
                                break;
                            } else {
                                cout << "Regresando al menú principal" << endl;
                            }
                        default:
                            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                            break;
                    }
                } while (opcionaccesorio != 5);
            case 3:
                int opcionambiente;
                do {
                    cout << "1 Crear ambiente" << endl;
                    cout << "2 Consultar ambiente" << endl;
                    cout << "3 Modificar ambiente" << endl;
                    cout << "4 Eliminar ambiente" << endl;
                    cout << "5 Regresar al menú principal" << endl;
                    cin >> opcionambiente;
                    switch(opcionambiente) {
                        case 1:
                            int dato;
                            cout << "Ingrese el dato del nodo: ";
                            cin >> dato;
                            crearNodo(dato);
                            break;
                        case 2:
                            leerNodo();
                            break;
                        case 3:
                            int datoBuscado, datoNuevo;
                            cout << "Ingrese el dato del nodo a modificar: ";
                            cin >> datoBuscado;
                            cout << "Ingrese el nuevo dato del nodo: ";
                            cin >> datoNuevo;
                            modificarNodo(datoBuscado, datoNuevo);
                            break;
                        case 4:
                            int datoBorrar;
                            cout << "Ingrese el dato del nodo a borrar: ";
                            cin >> datoBorrar;
                            borrarNodo(datoBorrar);
                            break;
                        case 5:
                            cout << "¿Desea regresar al menú principal? (s/n): ";
                            cin >> seguirMenu;
                            if (seguirMenu == 'n') {
                                break;
                            } else {
                                cout << "Regresando al menú principal" << endl;
                            }
                        default:
                            cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                            break;
                    }
                } while (opcionambiente != 5);
            case 4:
                // Crear soldado
                cout << "Soldado" << endl;
                cout << "1 Asignar raza" << endl;
                cout << "2 Agregar accesorios a mochila (5 accesorios)" /*desplegar los accesorios disponibles y añadir con número*/ << endl;
                cout << "3 Asignar ambiente base" << endl;
                break;
            case 5:
                // Salir
                cout << "Salir" << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                break;
        }
    } while (seguirMenu == 's');
}

int main() {
    leerDatosDesdeArchivo();
    menu();
    return 0;
}