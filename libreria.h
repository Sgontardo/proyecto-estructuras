#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct raza {
    string nombre;
    int energia;
    int salud;
    string ambiente;
    raza* siguiente;
} *primeroRaza, *ultimoRaza;

struct accesorio {
    string nombre;
    string tipo;
    int valor;
    string recuperacion;
    int energia;
    int contenedor;
    accesorio* siguiente;
} *primeroAccesorio, *ultimoAccesorio;

struct ambiente {
    string nombre;
    ambiente* siguiente;
} *primeroAmbiente, *ultimoAmbiente;

accesorio* accesorios[5];

struct soldado {
    string nombre;
    raza* raza;
    accesorio* accesorios[5];
    ambiente* ambiente;
};


void leerArchivoRazas() {
    ifstream archivo("razas.inv");
    if (archivo.is_open()) {
        string linea;
        raza* nuevaRaza = nullptr;
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
                nuevaRaza = new raza();
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
        raza* actualRaza = primeroRaza;
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
        cout << "No se pudo abrir el archivo de razas para escritura" << endl;
    }
}

void crearRaza() {
    raza* nuevo = new raza();
    cout << "Ingrese el nombre de la raza: ";
    cin >> nuevo -> nombre;
    cout << "Ingrese la energía de la raza: ";
    cin >> nuevo -> energia;
    nuevo -> salud = 100;
    cout << "Ingrese el ambiente de la raza: ";
    cin >> nuevo -> ambiente;

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
    cout << "Raza ingresada" << endl;
}

void leerRaza() {
    raza* actual = primeroRaza;
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
    raza* actual = primeroRaza;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a modificar: ";
    cin >> razaBuscada;
    if (primeroRaza != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                cout << "Ingrese el nuevo nombre: ";
                cin >> actual -> nombre;
                cout << "Ingrese la nueva energía: ";
                cin >> actual -> energia;
                cout << "Ingrese el nuevo ambiente: ";
                cin >> actual -> ambiente;
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
    raza* actual = primeroRaza;
    raza* anterior = nullptr;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a eliminar: ";
    cin >> razaBuscada;
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
        accesorio* nuevoAccesorio = nullptr;
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
                nuevoAccesorio = new accesorio();
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
        accesorio* actualAccesorio = primeroAccesorio;
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
        cout << "No se pudo abrir el archivo de accesorios para escritura" << endl;
    }
}

void crearAccesorio() {
    accesorio* nuevo = new accesorio();
    cout << "Ingrese el nombre del accesorio: ";
    cin >> nuevo -> nombre;
    cout << "Ingrese el tipo del accesorio: ";
    cin >> nuevo -> tipo;
    cout << "Ingrese el valor del accesorio: ";
    cin >> nuevo -> valor;
    cout << "Ingrese la energía del accesorio: ";
    cin >> nuevo -> energia;
    cout << "Ingrese el contenedor del accesorio: ";
    cin >> nuevo -> contenedor;

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
    cout << "Accesorio ingresado" << endl;
}

void leerAccesorio() {
    accesorio* actual = primeroAccesorio;
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
    accesorio* actual = primeroAccesorio;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a modificar: ";
    cin >> accesorioBuscado;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                cin >> actual -> nombre;
                cout << "Ingrese el nuevo tipo: ";
                cin >> actual -> tipo;
                cout << "Ingrese el nuevo valor: ";
                cin >> actual -> valor;
                cout << "Ingrese la nueva energía: ";
                cin >> actual -> energia;
                cout << "Ingrese el nuevo contenedor: ";
                cin >> actual -> contenedor;
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
    accesorio* actual = primeroAccesorio;
    accesorio* anterior = nullptr;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a eliminar: ";
    cin >> accesorioBuscado;
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
        ambiente* nuevoAmbiente = nullptr;
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
                nuevoAmbiente = new ambiente();
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
        ambiente* actualAmbiente = primeroAmbiente;
        while (actualAmbiente != nullptr) {
            archivo << "Nombre:" << actualAmbiente->nombre << endl;
            archivo << "--" << endl;
            actualAmbiente = actualAmbiente->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes para escritura" << endl;
    }
}

void crearAmbiente() {
    ambiente* nuevo = new ambiente();
    cout << "Ingrese el nombre del ambiente: ";
    cin >> nuevo -> nombre;

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
    cout << "Ambiente ingresado" << endl;
}

void leerAmbiente() {
    ambiente* actual = primeroAmbiente;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void modificarAmbiente() {
    ambiente* actual = primeroAmbiente;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a modificar: ";
    cin >> ambienteBuscado;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                cin >> actual -> nombre;
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
    ambiente* actual = primeroAmbiente;
    ambiente* anterior = nullptr;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a eliminar: ";
    cin >> ambienteBuscado;
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


void cargarAccesorios() {
    accesorio *actual = new accesorio();
    actual = primeroAccesorio;
    int i = 0;
    if (primeroAccesorio != NULL) {
        while (actual != NULL) {
            accesorios[i] = actual;
            i++;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}


void crearSoldado() {
    soldado *nuevo = new soldado();
    cout << "Ingrese el nombre del soldado: ";
    cin >> nuevo -> nombre;
    cout << "Razas disponibles: " << endl;
    leerRaza();
    cout << "Ingrese la raza del soldado: ";
    cin >> nuevo -> raza -> nombre;
    cout << "Ambientes disponibles: " << endl;
    leerAmbiente();
    cout << "Ingrese el ambiente del soldado: ";
    cin >> nuevo -> ambiente -> nombre;
    cargarAccesorios();
    for (int i = 0; i < 5; i++) {
        cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
        cin >> nuevo -> accesorios[i] -> nombre;
    }
}
