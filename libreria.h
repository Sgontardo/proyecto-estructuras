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

Accesorio* accesorios[5] = {nullptr};

struct Soldado {
    string nombre;
    Raza* raza;
    Accesorio* accesorios[5];
    Ambiente* ambiente;
};


string validarString() {
    string texto;
    while (true) {
        cin >> texto;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese un dato valido: " << endl;
        } else if (texto.length() == 0) {
            cout << "Ingrese un dato valido: " << endl;
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

void leerAmbiente() {
    Ambiente* actual = primeroAmbiente;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void verificarAmbiente(string ambiente) {
    Ambiente* actual = primeroAmbiente;
    bool encontrado = false;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == ambiente) {
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Ambiente no encontrado" << endl;
            cout << "Ambientes disponibles: " << endl;
            leerAmbiente();
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}


void leerArchivoRazas() {
    ifstream archivo("razas.inv");
    if (archivo.is_open()) {
        string linea;
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
                    if (key == "Nombre") nuevaRaza->nombre = value;
                    else if (key == "Energia") nuevaRaza->energia = stoi(value);
                    else if (key == "Salud") nuevaRaza->salud = stoi(value);
                    else if (key == "Ambiente") nuevaRaza->ambiente = value;
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
        Raza* actualRaza = primeroRaza;
        while (actualRaza != nullptr) {
            archivo << "Nombre:" << actualRaza->nombre << endl;
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
    nuevo -> nombre = validarString();
    nuevo -> energia = validarNumero("Ingrese la energía de la raza: ");
    nuevo -> salud = 100;
    cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
    nuevo -> ambiente = validarString();
    verificarAmbiente(nuevo -> ambiente);

    if (primeroRaza == nullptr) {
        primeroRaza = nuevo;
        primeroRaza -> siguiente = nullptr;
        ultimoRaza = nuevo;
    } else {
        ultimoRaza -> siguiente = nuevo;
        nuevo -> siguiente = nullptr;
        ultimoRaza = nuevo;
    }
    guardarEnArchivoRazas();
    cout << "Raza creada" << endl;
}

void leerRaza() {
    Raza* actual = primeroRaza;
    if (primeroRaza != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            cout << "Energia: " << actual -> energia << endl;
            cout << "Salud: " << actual -> salud << endl;
            cout << "Ambiente: " <<actual -> ambiente << endl;
            actual = actual -> siguiente;
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
            if (actual -> nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual -> nombre = validarString();
                actual -> energia = validarNumero("Ingrese la nueva energía: ");
                cout << "Ingrese el nuevo ambiente: ";
                actual -> ambiente = validarString();
                verificarAmbiente(actual -> ambiente);
                cout << "Raza modificada" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
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
            if (actual -> nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                if (actual == primeroRaza) {
                    primeroRaza = primeroRaza -> siguiente;
                } else if (actual == ultimoRaza) {
                    anterior -> siguiente = nullptr;
                    ultimoRaza = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Raza eliminada" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Raza no encontrada" << endl;
        }
        guardarEnArchivoRazas();
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}


void leerArchivoAccesorios() {
    ifstream archivo("accesorios.inv");
    if (archivo.is_open()) {
        string linea;
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
                    if (key == "Nombre") nuevoAccesorio->nombre = value;
                    else if (key == "Tipo") nuevoAccesorio->tipo = value;
                    else if (key == "Valor") nuevoAccesorio->valor = stoi(value);
                    else if (key == "Recuperacion") nuevoAccesorio->recuperacion = value;
                    else if (key == "Energia") nuevoAccesorio->energia = stoi(value);
                    else if (key == "Contenedor") nuevoAccesorio->contenedor = stoi(value);
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
        Accesorio* actualAccesorio = primeroAccesorio;
        while (actualAccesorio != nullptr) {
            archivo << "Nombre:" << actualAccesorio->nombre << endl;
            archivo << "Tipo:" << actualAccesorio->tipo << endl;
            archivo << "Valor:" << actualAccesorio->valor << endl;
            archivo << "Recuperacion:" << actualAccesorio->recuperacion << endl;
            archivo << "Energia:" << actualAccesorio->energia << endl;
            archivo << "Contenedor:" << actualAccesorio->contenedor << endl;
            archivo << "--" << endl;
            actualAccesorio = actualAccesorio->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de accesorios" << endl;
    }
}

void crearAccesorio() {
    Accesorio* nuevo = new Accesorio();
    cout << "Ingrese el nombre del accesorio: ";
    nuevo -> nombre = validarString();
    cout << "Ingrese el tipo del accesorio: ";
    nuevo -> tipo = validarString();
    nuevo -> valor = validarNumero("Ingrese el valor del accesorio: ");
    nuevo -> energia = validarNumero("Ingrese la energía del accesorio: ");
    nuevo -> contenedor = validarNumero("Ingrese el contenedor del accesorio: ");

    if (primeroAccesorio == nullptr) {
        primeroAccesorio = nuevo;
        primeroAccesorio -> siguiente = nullptr;
        ultimoAccesorio = nuevo;
    } else {
        ultimoAccesorio -> siguiente = nuevo;
        nuevo -> siguiente = nullptr;
        ultimoAccesorio = nuevo;
    }
    guardarEnArchivoAccesorios();
    cout << "Accesorio creado" << endl;
}

void leerAccesorio() {
    Accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            cout << "Tipo: " << actual -> tipo << endl;
            cout << "Valor: " << actual -> valor << endl;
            cout << "Energía: " << actual -> energia << endl;
            cout << "Contenedor: " << actual -> contenedor << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}

void modificarAccesorio() {
    Accesorio* actual = primeroAccesorio;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a modificar: ";
    accesorioBuscado = validarString();
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual -> nombre = validarString();
                cout << "Ingrese el nuevo tipo: ";
                actual -> tipo = validarString();
                actual -> valor = validarNumero("Ingrese el nuevo valor: ");
                actual -> energia = validarNumero("Ingrese la nueva energía: ");
                actual -> contenedor = validarNumero("Ingrese el nuevo contenedor: ");
                cout << "Accesorio modificado" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Accesorio no encontrado" << endl;
        }
        guardarEnArchivoAccesorios();
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}

void eliminarAccesorio() {
    Accesorio* actual = primeroAccesorio;
    Accesorio* anterior = nullptr;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a eliminar: ";
    accesorioBuscado = validarString();
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                if (actual == primeroAccesorio) {
                    primeroAccesorio = primeroAccesorio -> siguiente;
                } else if (actual == ultimoAccesorio) {
                    anterior -> siguiente = nullptr;
                    ultimoAccesorio = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Accesorio eliminado" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Accesorio no encontrado" << endl;
        }
        guardarEnArchivoAccesorios();
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}


void leerArchivoAmbiente() {
    ifstream archivo("ambiente.inv");
    if (archivo.is_open()) {
        string linea;
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
                size_t pos = linea.find(":");
                if (pos != string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Nombre") nuevoAmbiente->nombre = value;
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}

void guardarEnArchivoAmbiente() {
    ofstream archivo("ambiente.inv", ios::out);
    if (archivo.is_open()) {
        Ambiente* actualAmbiente = primeroAmbiente;
        while (actualAmbiente != nullptr) {
            archivo << "Nombre:" << actualAmbiente->nombre << endl;
            archivo << "--" << endl;
            actualAmbiente = actualAmbiente->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}

void crearAmbiente() {
    Ambiente* nuevo = new Ambiente();
    cout << "Ingrese el nombre del ambiente: ";
    nuevo -> nombre = validarString();

    if (primeroAmbiente == nullptr) {
        primeroAmbiente = nuevo;
        primeroAmbiente -> siguiente = nullptr;
        ultimoAmbiente = nuevo;
    } else {
        ultimoAmbiente -> siguiente = nuevo;
        nuevo -> siguiente = nullptr;
        ultimoAmbiente = nuevo;
    }
    guardarEnArchivoAmbiente();
    cout << "Ambiente creado" << endl;
}

void modificarAmbiente() {
    Ambiente* actual = primeroAmbiente;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a modificar: ";
    ambienteBuscado = validarString();
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual -> nombre = validarString();
                cout << "Ambiente modificado" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Ambiente no encontrado" << endl;
        }
        guardarEnArchivoAmbiente();
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void eliminarAmbiente() {
    Ambiente* actual = primeroAmbiente;
    Ambiente* anterior = nullptr;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a eliminar: ";
    ambienteBuscado = validarString();
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                if (actual == primeroAmbiente) {
                    primeroAmbiente = primeroAmbiente -> siguiente;
                } else if (actual == ultimoAmbiente) {
                    anterior -> siguiente = nullptr;
                    ultimoAmbiente = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Ambiente eliminado" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Ambiente no encontrado" << endl;
        }
        guardarEnArchivoAmbiente();
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}



void crearSoldado() {
    Soldado* nuevo = new Soldado();
    cout << "Ingrese el nombre del soldado: ";
    nuevo -> nombre = validarString();
    cout << "Ingrese la raza del soldado: ";
    string raza = validarString();
    Raza* actualRaza = primeroRaza;
    bool encontradoRaza = false;
    while (actualRaza != nullptr && encontradoRaza != true) {
        if (actualRaza -> nombre == raza) {
            nuevo -> raza = actualRaza;
            encontradoRaza = true;
        }
        actualRaza = actualRaza -> siguiente;
    }
    if (!encontradoRaza) {
        cout << "Raza no encontrada" << endl;
        cout << "Razas disponibles: " << endl;
        leerRaza();
        return;
    }
    cout << "Ingrese el ambiente del soldado: ";
    string ambiente = validarString();
    Ambiente* actualAmbiente = primeroAmbiente;
    bool encontradoAmbiente = false;
    while (actualAmbiente != nullptr && encontradoAmbiente != true) {
        if (actualAmbiente -> nombre == ambiente) {
            nuevo -> ambiente = actualAmbiente;
            encontradoAmbiente = true;
        }
        actualAmbiente = actualAmbiente -> siguiente;
    }
    if (!encontradoAmbiente) {
        cout << "Ambiente no encontrado" << endl;
        cout << "Ambientes disponibles: " << endl;
        leerAmbiente();
        return;
    }
    for (int i = 0; i < 5; i++) {
        cout << "Ingrese el nombre del accesorio " << i + 1 << ": ";
        string accesorio = validarString();
        Accesorio* actualAccesorio = primeroAccesorio;
        bool encontradoAccesorio = false;
        while (actualAccesorio != nullptr && encontradoAccesorio != true) {
            if (actualAccesorio -> nombre == accesorio) {
                nuevo -> accesorios[i] = actualAccesorio;
                encontradoAccesorio = true;
            }
            actualAccesorio = actualAccesorio -> siguiente;
        }
        if (!encontradoAccesorio) {
            cout << "Accesorio no encontrado" << endl;
            cout << "Accesorios disponibles: " << endl;
            leerAccesorio();
            return;
        }
    }
    ofstream archivo("soldados.inv", ios::app);
    if (archivo.is_open()) {
        archivo << "Nombre:" << nuevo->nombre << endl;
        archivo << "Raza:" << nuevo->raza->nombre << endl;
        archivo << "Ambiente:" << nuevo->ambiente->nombre << endl;
        for (int i = 0; i < 5; i++) {
            archivo << "Accesorio" << i + 1 << ":" << nuevo->accesorios[i]->nombre << endl;
        }
        archivo << "--" << endl;
        archivo.close();
        cout << "Soldado creado" << endl;
    } else {
        cout << "No se pudo abrir el archivo de soldados" << endl;
    }
}