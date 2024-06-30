#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

struct Raza {
    string nombre;
    int energia;
    int salud;
    string ambiente;
    Raza* siguiente;
} *primeroRaza = nullptr, *ultimoRaza = nullptr;

struct Accesorio {
    string nombre;
    string tipo;
    int valor;
    string recuperacion;
    Accesorio* siguiente;
} *primeroAccesorio = nullptr, *ultimoAccesorio = nullptr;

struct Ambiente {
    string nombre;
    Ambiente* siguiente;
} *primeroAmbiente = nullptr, *ultimoAmbiente = nullptr;

struct Soldado {
    string nombre;
    Raza* raza;
    Accesorio* mochila[5];
    string ambiente;
    int salud;
    int energia;
    Soldado* siguiente;
    int equipo;
} *primeroSoldado = nullptr, *ultimoSoldado = nullptr;

struct Equipo {
    Soldado* soldados[3];
};

// Funciones de validación y entrada
string validarString() {
    string texto;
    while (true) {
        getline(cin, texto);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un dato válido: " << endl;
        } else if (texto.length() == 0) {
            cout << "Ingrese un dato válido: " << endl;
        }
        else {
            return texto;
        }
    }
}

int validarNumero(string mensaje) {
    int numero;
    cout << mensaje;
    while (true) {
        cin >> numero;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un dato valido: " << endl;
        } else {
            return numero;
        }
    }
}

// Funciones para leer y manejar archivos
void leerArchivoRazas() {
    ifstream archivo("razas.inv");
    if (archivo.is_open()) {
        int cantidadRazas;
        string linea;
        archivo >> cantidadRazas;
        getline(archivo, linea);
        getline(archivo, linea);
        Raza* nuevaRaza = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevaRaza != nullptr) {
                    if (primeroRaza == nullptr) {
                        primeroRaza = nuevaRaza;
                        ultimoRaza = nuevaRaza;
                    } else {
                        ultimoRaza->siguiente = nuevaRaza;
                        ultimoRaza = nuevaRaza;
                    }
                }
                nuevaRaza = new Raza();
            } else if (nuevaRaza != nullptr) {
                size_t pos = linea.find(":");
                if (pos != string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Energia") nuevaRaza->energia = stoi(value);
                    else if (key == "Salud") nuevaRaza->salud = stoi(value);
                    else if (key == "Ambiente") nuevaRaza->ambiente = value;
                    else nuevaRaza->nombre = key;
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void guardarEnArchivoRazas() {
    ofstream archivo("razas.inv", ios::out);
    if (archivo.is_open()) {
        int cantidadRazas = 0;
        Raza* tempRaza = primeroRaza;
        while (tempRaza != nullptr) {
            cantidadRazas++;
            tempRaza = tempRaza->siguiente;
        }
        archivo << cantidadRazas << endl;
        archivo << "--" << endl;
        Raza* actualRaza = primeroRaza;
        while (actualRaza != nullptr) {
            archivo << actualRaza->nombre << endl;
            archivo << "Energia:" << actualRaza->energia << endl;
            archivo << "Salud:" << actualRaza->salud << endl;
            archivo << "Ambiente:" << actualRaza->ambiente << endl;
            archivo << "--" << endl;
            actualRaza = actualRaza->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void leerArchivoAccesorios() {
    ifstream archivo("accesorios.inv");
    if (archivo.is_open()) {
        int cantidadAccesorios;
        string linea;
        archivo >> cantidadAccesorios;
        getline(archivo, linea);
        getline(archivo, linea);
        Accesorio* nuevoAccesorio = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevoAccesorio != nullptr) {
                    if (primeroAccesorio == nullptr) {
                        primeroAccesorio = nuevoAccesorio;
                        ultimoAccesorio = nuevoAccesorio;
                    } else {
                        ultimoAccesorio->siguiente = nuevoAccesorio;
                        ultimoAccesorio = nuevoAccesorio;
                    }
                }
                nuevoAccesorio = new Accesorio();
            } else if (nuevoAccesorio != nullptr) {
                size_t pos = linea.find(":");
                if (pos != string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Tipo") nuevoAccesorio->tipo = value;
                    else if (key == "Valor") nuevoAccesorio->valor = stoi(value);
                    else if (key == "Recuperacion") nuevoAccesorio->recuperacion = value;
                    else nuevoAccesorio->nombre = key;
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de accesorios" << endl;
    }
}

void guardarEnArchivoAccesorios() {
    ofstream archivo("accesorios.inv", ios::out);
    if (archivo.is_open()) {
        int cantidadAccesorios = 0;
        Accesorio* tempAccesorio = primeroAccesorio;
        while (tempAccesorio != nullptr) {
            cantidadAccesorios++;
            tempAccesorio = tempAccesorio->siguiente;
        }
        archivo << cantidadAccesorios << endl;
        archivo << "--" << endl;
        Accesorio* actualAccesorio = primeroAccesorio;
        while (actualAccesorio != nullptr) {
            archivo << actualAccesorio->nombre << endl;
            archivo << "Tipo:" << actualAccesorio->tipo << endl;
            archivo << "Valor:" << actualAccesorio->valor << endl;
            archivo << "Recuperacion:" << actualAccesorio->recuperacion << endl;
            archivo << "--" << endl;
            actualAccesorio = actualAccesorio->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de accesorios" << endl;
    }
}

void leerArchivoAmbientes() {
    ifstream archivo("ambientes.inv");
    if (archivo.is_open()) {
        int cantidadAmbientes;
        string linea;
        archivo >> cantidadAmbientes;
        getline(archivo, linea);
        getline(archivo, linea);
        Ambiente* nuevoAmbiente = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevoAmbiente != nullptr) {
                    if (primeroAmbiente == nullptr) {
                        primeroAmbiente = nuevoAmbiente;
                        ultimoAmbiente = nuevoAmbiente;
                    } else {
                        ultimoAmbiente->siguiente = nuevoAmbiente;
                        ultimoAmbiente = nuevoAmbiente;
                    }
                }
                nuevoAmbiente = new Ambiente();
            } else if (nuevoAmbiente != nullptr) {
                nuevoAmbiente->nombre = linea;
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}

void guardarEnArchivoAmbiente() {
    ofstream archivo("ambientes.inv", ios::out);
    if (archivo.is_open()) {
        int cantidadAmbientes = 0;
        Ambiente* tempAmbiente = primeroAmbiente;
        while (tempAmbiente != nullptr) {
            cantidadAmbientes++;
            tempAmbiente = tempAmbiente->siguiente;
        }
        archivo << cantidadAmbientes << endl;
        archivo << "--" << endl;
        Ambiente* actualAmbiente = primeroAmbiente;
        while (actualAmbiente != nullptr) {
            archivo << actualAmbiente->nombre << endl;
            archivo << "--" << endl;
            actualAmbiente = actualAmbiente->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}

// Funciones para crear entidades
void crearRaza() {
    Raza* nuevo = new Raza();
    cout << "Ingrese el nombre de la raza: ";
    nuevo->nombre = validarString();
    nuevo




#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

struct Raza {
    string nombre;
    int energia;
    int salud;
    string ambiente;
    Raza* siguiente;
} *primeroRaza = nullptr, *ultimoRaza = nullptr;

struct Accesorio {
    string nombre;
    string tipo;
    int valor;
    string recuperacion;
    int energia;
    int contenedor;
    Accesorio* siguiente;
} *primeroAccesorio = nullptr, *ultimoAccesorio = nullptr;

struct Ambiente {
    string nombre;
    Ambiente* siguiente;
} *primeroAmbiente = nullptr, *ultimoAmbiente = nullptr;

struct Soldado {
    string nombre;
    Raza* raza;
    Accesorio* mochila[5];
    string ambiente;
    int salud;
    int energia;
    Soldado* siguiente;
    int equipo;
} *primeroSoldado = nullptr, *ultimoSoldado = nullptr;

struct Equipo {
    Soldado* soldados[3];
};

string validarString() {
    string texto;
    while (true) {
        getline(cin, texto);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un dato válido: " << endl;
        } else if (texto.length() == 0) {
            cout << "Ingrese un dato válido: " << endl;
        } else {
            return texto;
        }
    }
}

int validarNumero(string mensaje) {
    int numero;
    cout << mensaje;
    while (true) {
        cin >> numero;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un dato valido: " << endl;
        } else {
            return numero;
        }
    }
}

void leerAmbiente() {
    Ambiente* actual = primeroAmbiente;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual->nombre << endl;
            actual = actual->siguiente;
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void mostrarAmbientes() {
    ifstream archivo("ambiente.inv");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                cout << endl;
            } else {
                cout << linea << endl;
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}

void verificarAmbiente(string ambiente) {
    Ambiente* actual = primeroAmbiente;
    bool encontrado = false;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual->nombre == ambiente) {
                encontrado = true;
            }
            actual = actual->siguiente;
        }
        if (!encontrado) {
            while (!encontrado) {
                cout << "Ambiente no encontrado" << endl;
                cout << "Ambientes disponibles: " << endl;
                mostrarAmbientes();
                cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
                ambiente = validarString();
                actual = primeroAmbiente;
                while (actual != nullptr && encontrado != true) {
                    if (actual->nombre == ambiente) {
                        encontrado = true;
                    }
                    actual = actual->siguiente;
                }
            }
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void leerArchivoRazas() {
    ifstream archivo("razas.inv");
    if (archivo.is_open()) {
        int cantidadRazas;
        string linea;
        archivo >> cantidadRazas;
        getline(archivo, linea);
        getline(archivo, linea);
        Raza* nuevaRaza = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevaRaza != nullptr) {
                    if (primeroRaza == nullptr) {
                        primeroRaza = nuevaRaza;
                        ultimoRaza = nuevaRaza;
                    } else {
                        ultimoRaza->siguiente = nuevaRaza;
                        ultimoRaza = nuevaRaza;
                    }
                }
                nuevaRaza = new Raza();
            } else if (nuevaRaza != nullptr) {
                size_t pos = linea.find(":");
                if (pos != string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Energia") nuevaRaza->energia = stoi(value);
                    else if (key == "Salud") nuevaRaza->salud = stoi(value);
                    else if (key == "Ambiente") nuevaRaza->ambiente = value;
                    else nuevaRaza->nombre = key;
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void guardarEnArchivoRazas() {
    ofstream archivo("razas.inv", ios::out);
    if (archivo.is_open()) {
        int cantidadRazas = 0;
        Raza* tempRaza = primeroRaza;
        while (tempRaza != nullptr) {
            cantidadRazas++;
            tempRaza = tempRaza->siguiente;
        }
        archivo << cantidadRazas << endl;
        archivo << "--" << endl;
        Raza* actualRaza = primeroRaza;
        while (actualRaza != nullptr) {
            archivo << actualRaza->nombre << endl;
            archivo << "Energia:" << actualRaza->energia << endl;
            archivo << "Salud:" << actualRaza->salud << endl;
            archivo << "Ambiente:" << actualRaza->ambiente << endl;
            archivo << "--" << endl;
            actualRaza = actualRaza->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void crearRaza() {
    Raza* nuevo = new Raza();
    cout << "Ingrese el nombre de la raza: ";
    nuevo->nombre = validarString();
    nuevo->energia = validarNumero("Ingrese la energía de la raza: ");
    nuevo->salud = 100;
    cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
    mostrarAmbientes();
    nuevo->ambiente = validarString();
    verificarAmbiente(nuevo->ambiente);

    if (primeroRaza == nullptr) {
        primeroRaza = nuevo;
        primeroRaza->siguiente = nullptr;
        ultimoRaza = nuevo;
    } else {
        ultimoRaza->siguiente = nuevo;
        nuevo->siguiente = nullptr;
        ultimoRaza = nuevo;
    }
    guardarEnArchivoRazas();
    cout << "Raza creada" << endl;
}

void leerRaza() {
    Raza* actual = primeroRaza;
    if (primeroRaza != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual->nombre << endl;
            cout << "Energia: " << actual->energia << endl;
            cout << "Salud: " << actual->salud << endl;
            cout << "Ambiente: " << actual->ambiente << endl;
            actual = actual->siguiente;
        }
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}

void modificarRaza() {
    Raza* actual = primeroRaza;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a modificar: ";
    razaBuscada = validarString();
    if (primeroRaza != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual->nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual->nombre = validarString();
                actual->energia = validarNumero("Ingrese la nueva energía: ");
                cout << "Ingrese el nuevo ambiente: ";
                actual->ambiente = validarString();
                verificarAmbiente(actual->ambiente);
                cout << "Raza modificada" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "Raza no encontrada" << endl;
        }
        guardarEnArchivoRazas();
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}

void eliminarRaza() {
    Raza* actual = primeroRaza;
    Raza* anterior = nullptr;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a eliminar: ";
    razaBuscada = validarString();
    if (primeroRaza != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual->nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                if (actual == primeroRaza) {
                    primeroRaza = primeroRaza->siguiente;
                } else if (actual == ultimoRaza) {
                    anterior->siguiente = nullptr;
                    ultimoRaza = anterior;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                cout << "Raza eliminada" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "Raza no encontrada" << endl;
        }
        guardarEnArchivoRazas();
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}

bool ambienteVacio() {
    Ambiente* actual = primeroAmbiente;
    if (primeroAmbiente == nullptr) {
        return true;
    } else {
        return false;
    }
}

bool RazaVacio() {
    Raza* actual = primeroRaza;
    if (primeroRaza == nullptr) {
        return true;
    } else {
        return false;
    }
}

void leerArchivoAccesorios() {
    ifstream archivo("accesorios.inv");
    if (archivo.is_open()) {
        int