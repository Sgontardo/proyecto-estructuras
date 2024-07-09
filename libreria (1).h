#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <ctime>


using namespace std;



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

struct Raza {
    string nombre;
    int energia;
    int salud;
    Ambiente* ambiente;
    Raza* siguiente;
} *primeroRaza = nullptr, *ultimoRaza = nullptr;

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
Ambiente* buscarOCrearAmbiente(const string& nombre) {
    Ambiente* actual = primeroAmbiente;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual; // Found existing Ambiente
        }
        actual = actual->siguiente;
    }
    // Not found, create a new Ambiente
    Ambiente* nuevo = new Ambiente();
    nuevo->nombre = nombre;
    nuevo->siguiente = nullptr;
    // Link into the list
    if (ultimoAmbiente != nullptr) {
        ultimoAmbiente->siguiente = nuevo;
    } else {
        primeroAmbiente = nuevo; // First element in the list
    }
    ultimoAmbiente = nuevo;
    return nuevo;
}

void leerArchivoRazas(Raza*& primeroRaza, Raza*& ultimoRaza) {
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
            } else if (nuevaRaza!= nullptr) {
                size_t pos = linea.find(":");
                if (pos!= string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Energia") nuevaRaza->energia = stoi(value);
                    else if (key == "Salud") nuevaRaza->salud = stoi(value);
                    else if (key == "Ambiente") {
                        nuevaRaza->ambiente = buscarOCrearAmbiente(value);
                    }
                    else nuevaRaza->nombre = key;
                } else {
                    nuevaRaza->nombre = linea;
                }
            } else {
                nuevaRaza = new Raza{linea, 0, 0, nullptr, nullptr};
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void guardarEnArchivoRazas() {
    ofstream archivo("razas.inv", ios::out | ios::trunc);
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
            actualRaza = actualRaza->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}
Ambiente* devolverAmbiente() {
    string ambiente;
    cout << "Ingrese el nombre del ambiente: ";
    getline(cin, ambiente);
    Ambiente* actual = primeroAmbiente;
    while (actual != nullptr) {
        if (actual->nombre == ambiente) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}
void crearRaza() {
    Raza* nuevo = new Raza();
    cout << "Ingrese el nombre de la raza: ";
    nuevo->nombre = validarString();
    nuevo->energia = validarNumero("Ingrese la energía de la raza: ");
    nuevo->salud = 100;
    cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
    mostrarAmbientes();
    nuevo->ambiente = devolverAmbiente();


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
            cout << "Ambiente: " <<actual->ambiente->nombre << endl;
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
                mostrarAmbientes();
                actual->ambiente = devolverAmbiente();
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

bool ambienteVacio(){
    Ambiente* actual = primeroAmbiente;
    if (primeroAmbiente == nullptr){
        return true;
    }
    else{
        return false;
    }
}

bool RazaVacio(){
    Raza* actual = primeroRaza;
    if (primeroRaza == nullptr){
        return true;
    }
    else{
        return false;
    }
}

void leerArchivoAccesorios(Accesorio*& primeroAccesorio, Accesorio*& ultimoAccesorio) {
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
                    if (key == "Nombre") nuevoAccesorio->nombre = value;
                    else if (key == "Tipo") nuevoAccesorio->tipo = value;
                    else if (key == "Valor") nuevoAccesorio->valor = stoi(value);
                    else if (key == "Recuperacion") nuevoAccesorio->recuperacion = value;
                    else if (key == "Energia") nuevoAccesorio->energia = stoi(value);
                    else if (key == "Contenedor") nuevoAccesorio->contenedor = stoi(value);

                } else {
                    nuevoAccesorio->nombre = linea;
                }
            } else {
                nuevoAccesorio = new Accesorio{linea, "", 0, "", 0, 0, nullptr};
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de accesorios" << endl;
    }
}

void guardarEnArchivoAccesorios() {
    ofstream archivo("accesorios.inv", ios::out | ios::trunc);
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
            archivo << "Energia:" << actualAccesorio->energia << endl;
            archivo << "Contenedor:" << actualAccesorio->contenedor << endl;
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
    nuevo->nombre = validarString();
    cout << "Ingrese el tipo del accesorio: ";
    nuevo->tipo = validarString();
    nuevo->valor = validarNumero("Ingrese el valor del accesorio: ");
    nuevo->energia = validarNumero("Ingrese la energía del accesorio: ");
    nuevo->contenedor = validarNumero("Ingrese el contenedor del accesorio: ");

    if (primeroAccesorio == nullptr) {
        primeroAccesorio = nuevo;
        primeroAccesorio->siguiente = nullptr;
        ultimoAccesorio = nuevo;
    } else {
        ultimoAccesorio->siguiente = nuevo;
        nuevo->siguiente = nullptr;
        ultimoAccesorio = nuevo;
    }
    guardarEnArchivoAccesorios();
    cout << "Accesorio creado" << endl;
}

void leerAccesorio() {
    Accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual->nombre << endl;
            cout << "Tipo: " << actual->tipo << endl;
            cout << "Valor: " << actual->valor << endl;
            cout << "Energía: " << actual->energia << endl;
            cout << "Contenedor: " << actual->contenedor << endl;
            actual = actual->siguiente;
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
            if (actual->nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual->nombre = validarString();
                cout << "Ingrese el nuevo tipo: ";
                actual->tipo = validarString();
                actual->valor = validarNumero("Ingrese el nuevo valor: ");
                actual->energia = validarNumero("Ingrese la nueva energía: ");
                actual->contenedor = validarNumero("Ingrese el nuevo contenedor: ");
                cout << "Accesorio modificado" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
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
            if (actual->nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                if (actual == primeroAccesorio) {
                    primeroAccesorio = primeroAccesorio->siguiente;
                } else if (actual == ultimoAccesorio) {
                    anterior->siguiente = nullptr;
                    ultimoAccesorio = anterior;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                cout << "Accesorio eliminado" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "Accesorio no encontrado" << endl;
        }
        guardarEnArchivoAccesorios();
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}


void leerArchivoAmbientes(Ambiente*& primeroAmbiente, Ambiente*& ultimoAmbiente) {
    ifstream archivo("ambiente.inv");
    if (archivo.is_open()) {
        int cantidadAmbientes;
        string linea;
        archivo >> cantidadAmbientes;
        getline(archivo, linea);
        getline(archivo, linea);
        Ambiente* nuevoAmbiente = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevoAmbiente!= nullptr) {
                    if (primeroAmbiente == nullptr) {
                        primeroAmbiente = nuevoAmbiente;
                        ultimoAmbiente = nuevoAmbiente;
                    } else {
                        ultimoAmbiente->siguiente = nuevoAmbiente;
                        ultimoAmbiente = nuevoAmbiente;
                    }
                    nuevoAmbiente = nullptr;
                }
            } else if (nuevoAmbiente!= nullptr) {
                nuevoAmbiente->nombre = linea;
            } else {
                nuevoAmbiente = new Ambiente{linea, nullptr};
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de ambientes" << endl;
    }
}


void guardarEnArchivoAmbiente() {
    ofstream archivo("ambiente.inv", ios::out | ios::trunc);
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
    nuevo->nombre = validarString();

    if (primeroAmbiente == nullptr) {
        primeroAmbiente = nuevo;
        primeroAmbiente->siguiente = nullptr;
        ultimoAmbiente = nuevo;
    } else {
        ultimoAmbiente->siguiente = nuevo;
        nuevo->siguiente = nullptr;
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
            if (actual->nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual->nombre = validarString();
                cout << "Ambiente modificado" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
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
            if (actual->nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                if (actual == primeroAmbiente) {
                    primeroAmbiente = primeroAmbiente->siguiente;
                } else if (actual == ultimoAmbiente) {
                    anterior->siguiente = nullptr;
                    ultimoAmbiente = anterior;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                cout << "Ambiente eliminado" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "Ambiente no encontrado" << endl;
        }
        guardarEnArchivoAmbiente();
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}


Raza* devolverRaza() {
    string raza;
    cout << "Ingrese la raza del soldado: ";
    getline(cin, raza); // Correctly reads the full line of input, including spaces.
    Raza* actual = primeroRaza;
    while (actual != nullptr) {
        if (actual->nombre == raza) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}
bool verificarAccesorios(){
    int i = 0;
    Accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            i += 1;
            actual = actual->siguiente;
        }
        if(i > 4){
            return true;
        }
        else{
            return false;
        }
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}

void cargarAccesorios() {
    Accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual->nombre << endl;
            cout << "Tipo: " << actual->tipo << endl;
            cout << "Valor: " << actual->valor << endl;
            cout << "Energía: " << actual->energia << endl;
            cout << "Contenedor: " << actual->contenedor << endl;
            actual = actual->siguiente;
        }
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}

Accesorio* buscarAccesorio(string nombre) {
    Accesorio* actual = primeroAccesorio;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

int cantidadAccesorios() {
    Accesorio* actual = primeroAccesorio;
    int cantidad = 0;
    while (actual != nullptr) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

void mostrarRazas() {
    ifstream archivo("razas.inv");
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
        cout << "No se pudo abrir el archivo de razas" << endl;
    }
}

void crearSoldado() {
    Soldado* nuevo = new Soldado();
    cout << "Ingrese el nombre del soldado: ";
    cin.ignore();
    getline(cin, nuevo->nombre);

    cout << "Razas disponibles: " << endl;
    mostrarRazas();
    Raza* race = devolverRaza();
    while (race == nullptr) {
        cout << "Ingrese una raza válida: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        race = devolverRaza();
    }
    nuevo->raza = race;
    if (nuevo->raza == nullptr) {
        cout << "La raza no está inicializada." << endl;
    } else if (nuevo->raza->ambiente->nombre.empty()) {
        cout << "Ambiente string está vacía." << endl;
    } else {
        cout << "El ambiente del soldado por su raza es: " << nuevo->raza->ambiente->nombre << endl;
        nuevo->ambiente = nuevo->raza->ambiente->nombre;
        nuevo->salud = nuevo->raza->salud;
        nuevo->energia = nuevo->raza->energia;
    }
    if (verificarAccesorios()) {
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            getline(cin, accesorioName);
            Accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo->mochila[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--;
            }
        }
    } else {
        cout << "El soldado necesita mínimo 5 accesorios";
        while (cantidadAccesorios() < 5) {
            crearAccesorio();
        }
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            getline(cin, accesorioName);
            Accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo->mochila[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--;
            }
        }

    }
    if (primeroSoldado == nullptr){
        primeroSoldado = nuevo;
        primeroSoldado->siguiente = nullptr;
        ultimoSoldado = nuevo;
    } else {
        ultimoSoldado->siguiente = nuevo;
        nuevo->siguiente = nullptr;
        ultimoSoldado = nuevo;
    }

    cout << "Soldado creado" << endl;
}

void leerSoldado() {
    Soldado* actual = primeroSoldado;
    if (primeroSoldado != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual->nombre << endl;
            cout << "Raza: " << actual->raza->nombre << endl;
            cout << "Ambiente: " << actual->ambiente << endl;
            cout << "Accesorios: ";
            for (int i = 0; i < 5; i++) {
                if (actual->mochila[i] != nullptr) {
                    cout << actual->mochila[i]->nombre << endl;
                } else {
                    cout << "Accesorio en índice " << i << " es nulo." << endl;
                }
            }
            cout << endl;
            actual = actual->siguiente;
        }
    } else {
        cout << "La lista de soldados se encuentra vacía" << endl;
    }
}
void crearEquipo(Soldado* equipo1[3],Soldado* equipo2[3]){
    Soldado* actual = primeroSoldado;
    int i = 0;
    if (primeroSoldado != nullptr) {
        while (actual != nullptr) {
            if (i < 3){
                equipo1[i] = actual;
            } else {
                equipo2[i - 3] = actual;
            }
            i++;
            actual = actual->siguiente;
        }
        for (int i = 0; i < 3; i++) {
            cout << "Soldado " << i + 1 << " del equipo 1: " << equipo1[i]->nombre << endl;
            cout << "Soldado " << i + 1 << " del equipo 2: " << equipo2[i]->nombre << endl;
        }
    } else {
        cout << "La lista de soldados se encuentra vacía" << endl;
    }
}

int cantidadsoldados(){
    Soldado* actual = primeroSoldado;
    int cantidad = 0;
    while (actual != nullptr) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;

}
/*
void asignarSoldadosEquipos(Equipo* equipo1, Equipo* equipo2) {
    for (int i = 0; i < 3; i++) {
        crearSoldado(equipo1, 0, i);
        cout << equipo1->soldados[i]->nombre;
    }
    for (int i = 0; i < 3; i++) {
        crearSoldado(equipo2, 1, i);
        cout << equipo2->soldados[i]->nombre;
    }
    for (int i = 0; i < 3; i++) {
        cout << "Soldado " << i + 1 << " del equipo 1: " << equipo1->soldados[i]->nombre << endl;
        cout << "Soldado " << i + 1 << " del equipo 2: " << equipo2->soldados[i]->nombre << endl;
    }
}
*/
int seleccionarEquipoEmpieza() {
    return rand() % 2;
}

int calcularEfecto(Soldado& soldado, string ambienteBatalla) {
    int efecto = 0;
    for (int i = 0; i < 5; i++) {
        if (soldado.mochila[i] != nullptr) {
            if (soldado.mochila[i]->tipo == "Ataque") {
                efecto += soldado.mochila[i]->valor;
            } else if (soldado.mochila[i]->tipo == "Defensa") {
                if (soldado.mochila[i]->contenedor > 0) {
                    int valorDefensa = soldado.mochila[i]->contenedor - efecto;
                    if (valorDefensa > 0) {
                        soldado.mochila[i]->contenedor -= efecto;
                        efecto = 0;
                    } else {
                        efecto -= soldado.mochila[i]->contenedor;
                        soldado.mochila[i]->contenedor = 0;
                    }
                }
            } else if (soldado.mochila[i]->tipo == "Supervivencia" && soldado.mochila[i]->recuperacion == ambienteBatalla) {
                soldado.energia += soldado.mochila[i]->energia;
                soldado.salud += soldado.mochila[i]->energia;
            }
        }
    }
    return efecto;
}

void empiezaRonda(Soldado* atacante, Soldado* defensor, string ambienteBatalla) {
    for (int i = 0; i < 2; i++) {
        if (atacante->mochila[i] != nullptr) {
            int efecto = calcularEfecto(*atacante, ambienteBatalla);
            if (efecto < 0) {
                defensor->salud += efecto;
                cout << "El soldado " << atacante->nombre << " ha atacado al soldado " << defensor->nombre << " y le ha quitado " << efecto << " de salud." << endl;
            } else {
                atacante->energia += efecto;
                cout << "El soldado " << atacante->nombre << " ha recuperado " << efecto << " de energía." << endl;
            }
        }
    }
    if (defensor->salud <= 0) {
        atacante->energia += defensor->energia;
        cout << "El soldado " << atacante->nombre << " ha ganado la batalla y absorbe la energía del derrotado." << endl;
    }
}

void gestionarBatalla(Soldado* soldado1, Soldado* soldado2, string ambienteBatalla) {
    int turno = 0;
    while (soldado1->salud > 0 && soldado2->salud > 0 && soldado1->energia > 0 && soldado2->energia > 0) {
        if (turno % 2 == 0) {
            empiezaRonda(soldado1, soldado2, ambienteBatalla);
        } else {
            empiezaRonda(soldado2, soldado1, ambienteBatalla);
        }
        turno++;
    }
    if (soldado1->salud > 0 && soldado1->energia > 0) {
        cout << "El soldado " << soldado1->nombre << " ha ganado la batalla." << endl;
    } else {
        cout << "El soldado " << soldado2->nombre << " ha ganado la batalla." << endl;
    }
}


void gestionarGuerra(Soldado* equipo1[3], Soldado* equipo2[3]) {
    if (!equipo1 || !equipo2 || !primeroAmbiente) {
        cout << "Error: Uno o más parámetros son nulos." << endl;
        return;
    }

    Ambiente* actual = primeroAmbiente;
    int cantidadAmbientes = 0;
    while (actual != nullptr) {
        cantidadAmbientes++;
        actual = actual->siguiente;
    }

    if (cantidadAmbientes == 0) {
        cout << "Error: No hay ambientes disponibles." << endl;
        return;
    }

    int seleccion = rand() % cantidadAmbientes;
    actual = primeroAmbiente;
    for (int i = 0; i < seleccion; i++) {
        actual = actual->siguiente;
    }
    string ambiente = actual->nombre;

    cout << "El ambiente de la batalla es " << ambiente << endl;
    int equipoEmpieza = seleccionarEquipoEmpieza();
    cout << "El equipo que empieza es el " << equipoEmpieza + 1 << endl;

    for (int i = 0; i < 2; i++) {
        if (equipo1[i] == nullptr || equipo2[i] == nullptr) {
            cout << "Error: Uno de los equipos no tiene suficientes soldados." << i+1<< endl;
            break;
        }
        if (equipoEmpieza == 0) {
            gestionarBatalla(equipo1[i], equipo2[i], ambiente);
        } else {
            gestionarBatalla(equipo2[i], equipo1[i], ambiente);
        }
    }
}
Ambiente* lugarPelea(Ambiente* &ambientes, int n){
    srand(time(NULL));
    int num = n;
    int i=1;
    Ambiente* actual=ambientes;

    while (i != num){
        if (actual->siguiente==NULL){
            i=num;
        }
        else{
            actual=actual->siguiente;
            i += 1;
        }

    }

    return actual;
}

int ValidarUso(string opc, Soldado* p){
    int n;
    if (opc=="1"){
        if (p->mochila[0]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 0;
        }
    }
    else if (opc=="2"){
        if (p->mochila[1]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 1;
        }
    }
    else if (opc=="3"){
        if (p->mochila[2]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 2;
        }
    }
    else{
        cout<<"Opcion no valida, ingrese una de las mostradas anteriormente"<<endl;
        getline(cin,opc);
        ValidarUso(opc,p);
    }
    return n;
}

void EliminarPerosnajesPorNombre(Soldado* equipo[3],Soldado* p2) {
    string nombre = p2->nombre;
    for (int i = 0; i < 3; i++) {
        if (equipo[i]->nombre == nombre) {
            equipo[i] = nullptr;
        }
    }
}
bool equipomuerto(Soldado* equipo[3]) {
    for (int j = 0; j < 3; j++) {
        if (equipo[j] != nullptr) {
            // If any soldier is alive, the team is not completely dead.
            return false;
        }
    }
    // If the loop completes without finding an alive soldier, the team is dead.
    return true;
}
void RecuperarVida(Soldado* &p, Raza* &r, Soldado* pa){
    Soldado* actual=p;
    Raza* actualr=r;
    while (actual!=NULL){
        if (actual != pa){
            while(actualr->nombre != actual->raza->nombre){
                actualr=actualr->siguiente;
            }
            if (actual->salud < actualr->salud){
                if (actual->salud > actualr->salud*0.60){
                    actual->salud += actualr->salud*0.15;
                }
                else{
                    actual->salud += actualr->salud*0.05;
                }

                if (actual->salud > actualr->salud){
                    actual->salud = actualr->salud;
                }
            }
        }
        actual=actual->siguiente;
        actualr=r;
    }
}

void RecuperarEnergia(Soldado* p, Raza* &r){
    Soldado* actual=p;
    Raza* actualr=r;

    while(actualr->nombre != actual->raza->nombre){
        actualr=actualr->siguiente;
    }
    if (actual->energia < actualr->energia){
        actual->salud += actualr->salud*0.25;

        if (actual->salud > actualr->salud){
            actual->salud = actualr->salud;
        }
    }

    cout<<p->nombre<<" recupero algo de energia"<<endl;

}




Soldado* elegirJugador(Soldado* equipo[3]){
    int j = 0;
    for (int i=0;i<3;i++){
        if (equipo[i] == nullptr){
            cout<<i+1<<". "<<equipo[i]->nombre<<"esta muerto y no se puede usar en combate"<<endl;
        }
        else{
            cout<<i+1<<". "<<equipo[i]->nombre<<endl;
        }
    }
    do {
        cout << "Elija el numero del jugador" << endl;
        cin >> j;
        if (cin.fail() || j < 1 || j > 3 || equipo[j-1] == nullptr) {
            cout << "Opcion no valida, ingrese una de las mostradas anteriormente" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break; // Valid input, exit the loop
        }
    } while (true);
    j-=1;
    cout<<"El jugador elegido es: "<<equipo[j]->nombre<<endl;
    return equipo[j];
}


void Batalla(Soldado* p1, string j1, Soldado* &prs1, Soldado* p2, string j2, Soldado* &prs2, int turnoi, Ambiente* lugar, Raza* &razas, Soldado* equipo1[3], Soldado* equipo2[3]){
    int efecto1v;
    int efecto1e;
    int efecto2v;
    int efecto2e;
    int conte1=0;
    int def1=0;
    int conte2=0;
    int def2=0;
    int fin=0;
    int t=1;
    int aux_def;
    int daño;
    int opv;
    string opc;
    int turno;

    turnoi+=1;
    turno=turnoi;

    if (p1->raza->ambiente->nombre != lugar->nombre){
        for (int i=0;i<3;i++){
            if (p1->mochila[i]->tipo=="Acondicionamiento" && p1->mochila[i]->recuperacion==lugar->nombre){
                efecto1v=0;
                efecto1e=0;
                cout<<p1->nombre<<" logro ponerse con exito su"<<p1->mochila[i]->nombre<<" ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto1v=(p1->salud)/3;
                efecto1e=(p1->energia)/3;
                turnoi=0;
            }
            if(p1->mochila[i]->tipo=="Acondicionamiento" && p1->mochila[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio "<<p1->mochila[i]->nombre<<" "<<p1->nombre<<" lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }

    if (p2->raza->ambiente->nombre != lugar->nombre){
        for (int i=0;i<3;i++){
            if (p2->mochila[i]->tipo=="Acondicionamiento" && p2->mochila[i]->recuperacion==lugar->nombre){
                efecto2v=0;
                efecto2e=0;
                cout<<p2->nombre<<" logro ponerse con exito su "<<p2->mochila[i]->nombre<<" ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto2v=(p2->salud)/3;
                efecto2e=(p2->energia)/3;
                turnoi=1;
            }

            if(p2->mochila[i]->tipo=="Acondicionamiento" && p2->mochila[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio "<<p2->mochila[i]->nombre<<" "<<p2->nombre<<" lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }


    while(fin==0){
        if (turno%2==0){
            cout<<"TURNO "<<t<<": "<<j1<<endl;
            cout<<p1->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p1->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p1->energia<<endl;

            cout<<""<<endl;

            cout<<p2->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p2->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p2->energia<<endl;


            if (p1->mochila[0]->valor == 0 && p1->mochila[1]->valor == 0 && p1->mochila[2]->valor == 0){
                cout<<"Parece que "<<p1->nombre<<" no tiene nada que usar para la batalla"<<endl;
                cout<<"¡ "<<p2->nombre<<" aprovecho la confusion para matarlo por la espalda!"<<endl;
                p1->salud=0;
            }
            else{
                cout<<"¿Que vas a usar? "<<j1<<endl;
                for (int i=0; i<3; i++){
                    if (p1->mochila[i]->valor != 0){
                        cout<<i+1<<". "<<p1->mochila[i]->nombre<<endl;
                        cout<<p1->mochila[i]->tipo<<endl;
                        cout<<"Valor: "<<p1->mochila[i]->valor<<endl;
                        cout<<"Su uso resta "<<p1->mochila[i]->energia<<" de energia"<<endl;

                        if (p1->mochila[i]->tipo == "Defensa"){
                            cout<<"Cubre "<<p1->mochila[i]->contenedor<<endl;
                        }
                        if (p1->mochila[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p1->mochila[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                opv=ValidarUso(opc,p1);

                if (p1->mochila[opv]->tipo == "Ataque"){
                    daño= p1->mochila[opv]->valor - def2;
                    if (daño<1){
                        cout<<"El ataque no le hizo ni cosquillas a" <<p2->nombre<<" !"<<endl;
                    }
                    else{
                        if (conte2==0){
                            cout<<p2->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            p2->salud= p2->salud - daño;
                        }
                        else{
                            cout<<p2->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            conte2= conte2 - daño;
                            if (conte2 >= 0){
                                cout<<"¡Pero parece que el objeto de defensa de "<<p2->nombre<<" contubo todo el golpe!"<<endl;
                                p2->mochila[aux_def]->contenedor=conte2;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de "<<p2->nombre<<" contubo parte del golpe!"<<endl;
                                p2->salud = p2->salud+conte2;
                                p2->mochila[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p1->nombre<<" perdio "<<p1->mochila[opv]->energia<<" de energia "<<endl;
                    p1->energia=p1->energia - p1-> mochila[opv]->energia;
                    def2=0;
                    conte2=0;
                    daño=0;
                }
                else if (p1->mochila[opv]->tipo == "Defensa"){
                    conte1=p1->mochila[opv]->contenedor;
                    aux_def=opv;
                    def1=p1->mochila[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace "<<p1->mochila[opv]->valor<<" menos de daño"<<endl;
                    cout<<"Optubiste una covertura de "<<p1->mochila[opv]->contenedor<<" de daños"<<endl;
                    cout<<p1->nombre<<" perdio "<<p1->mochila[opv]->energia<<" energia"<<endl;
                    p1->energia=p1->energia - p1->mochila[opv]->energia;

                }
                else if (p1->mochila[opv]->tipo == "Supervivencia"){
                    if (p1->mochila[opv]->recuperacion=="Salud"){
                        cout<<p1->nombre<<" ha recuperado "<<p1->mochila[opv]->valor<<" de vida "<<endl;
                        cout<<p1->nombre<<" perdio "<<p1->mochila[opv]->energia<<" energia "<<endl;
                        p1->salud=p1->salud+p1->mochila[opv]->valor;
                        p1->energia=p1->energia-p1->mochila[opv]->energia;
                        p1->mochila[opv]->valor=0;
                    }
                    else if (p1->mochila[opv]->recuperacion=="Energia"){
                        cout<<p1->nombre<<" ha recuperado "<<p1->mochila[opv]->valor<<" de energia "<<endl;
                        cout<<p1->nombre<<" perdio "<<p1->mochila[opv]->energia<<" energia "<<endl;
                        p1->energia+=p1->mochila[opv]->valor;
                        p1->energia-=p1->mochila[opv]->energia;
                        p1->mochila[opv]->valor=0;
                    }

                }
                if (efecto1e!=0){
                    p1->energia=p1->energia-efecto1e;
                    cout<<p1->nombre<<" perdio"<< efecto1e<< "de energia por no estar  con proteccion"<<endl;
                    p1->salud=p1->salud-efecto1v;
                    cout<<p1->nombre<<" perdio"<< efecto1e<< "de vida por no estar  con proteccion"<<endl;
                }

                cout<<""<<endl;
                cout<<"Resumen del turno:"<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;
                cout<<""<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;
                cout<<""<<endl;

                if (p1->energia <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->energia <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->energia<=0){
                    fin=1;
                }
                else if (p1->salud<=0){
                    fin=1;
                }
                else if (p2->salud<=0){
                    fin=2;
                }
                else if (p2->energia<=0){
                    fin=2;
                }
                else{
                    fin=0;
                    t+=1;
                    turno+=1;
                }

            }

        }
        else{
            cout<<"TURNO "<<t<<": "<<j2<<endl;
            cout<<p2->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p2->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p2->energia<<endl;

            cout<<""<<endl;

            cout<<p1->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p1->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p1->energia<<endl;


            if (p2->mochila[0]->valor == 0 && p2->mochila[1]->valor == 0 && p2->mochila[2]->valor == 0){
                cout<<"Parece que "<<p2->nombre<<" no tiene nada que usar para la batalla"<<endl;
                cout<<"¡ "<<p1->nombre<<" aprovecho la confusion para matarlo por la espalda!"<<endl;
                p2->salud=0;
            }
            else{
                cout<<"¿Que vas a usar? "<<j2<<endl;
                for (int i=0; i<3; i++){
                    if (p2->mochila[i]->valor != 0){
                        cout<<i+1<<". "<<p2->mochila[i]->nombre<<endl;
                        cout<<p2->mochila[i]->tipo<<endl;
                        cout<<"Valor: "<<p2->mochila[i]->valor<<endl;
                        cout<<"Su uso resta "<<p2->mochila[i]->energia<<" de energia"<<endl;

                        if (p2->mochila[i]->tipo == "Defensa"){
                            cout<<"Cubre "<<p2->mochila[i]->contenedor<<endl;
                        }
                        if (p2->mochila[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p2->mochila[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                opv=ValidarUso(opc,p2);

                if (p2->mochila[opv]->tipo == "Ataque"){
                    daño=p1->mochila[opv]->valor - def2;
                    if (daño<1){
                        cout<<"El ataque no le hizo ni cosquillas a" <<p1->nombre<<" !"<<endl;
                    }
                    else{
                        if (conte1==0){
                            cout<<p1->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            p1->salud=p1->salud-daño;
                        }
                        else{
                            cout<<p1->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            conte1=conte1-daño;
                            if (conte1>=0){
                                cout<<"¡Pero parece que el objeto de defensa de "<<p1->nombre<<" contubo todo el golpe!"<<endl;
                                p1->mochila[aux_def]->contenedor=conte2;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de "<<p1->nombre<<" contubo parte del golpe!"<<endl;
                                p1->salud=p1->salud+conte1;
                                p1->mochila[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p2->nombre<<" perdio "<<p2->mochila[opv]->energia<<" de energia "<<endl;
                    p2->energia-=p2->mochila[opv]->energia;
                    def1=0;
                    conte1=0;
                    daño=0;
                }
                else if (p2->mochila[opv]->tipo == "Defensa"){
                    conte2=p2->mochila[opv]->contenedor;
                    aux_def=opv;
                    def2=p2->mochila[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace "<<p2->mochila[opv]->valor<<" menos de daño"<<endl;
                    cout<<"Optubiste una covertura de "<<p2->mochila[opv]->contenedor<<" de daños"<<endl;
                    cout<<p2->nombre<<" perdio "<<p2->mochila[opv]->energia<<" energia"<<endl;
                    p2->energia = p2->energia - p2->mochila[opv]->energia;

                }
                else if (p2->mochila[opv]->tipo == "Supervivencia"){
                    if (p2->mochila[opv]->recuperacion=="Salud"){
                        cout<<p2->nombre<<" ha recuperado "<<p2->mochila[opv]->valor<<" de vida "<<endl;
                        cout<<p2->nombre<<" perdio "<<p2->mochila[opv]->energia<<" energia "<<endl;
                        p2->salud=p2->salud+p2->mochila[opv]->valor;
                        p2->energia=p2->energia-p2->mochila[opv]->energia;
                    }
                    else if (p2->mochila[opv]->recuperacion=="Energia"){
                        cout<<p2->nombre<<" ha recuperado "<<p2->mochila[opv]->valor<<" de energia "<<endl;
                        cout<<p2->nombre<<" perdio "<<p2->mochila[opv]->energia<<" energia "<<endl;
                        p2->energia=p2->energia+p2->mochila[opv]->valor;
                        p2->energia=p2->energia-p2->mochila[opv]->energia;
                    }

                }
                if (efecto2e!=0){
                    p2->energia=p2->energia-efecto2e;
                    cout<<p2->nombre<<" perdio"<< efecto2e<< "de energia por no estar  con proteccion"<<endl;
                    p2->salud=p2->salud-efecto2v;
                    cout<<p2->nombre<<" perdio"<< efecto2e<< "de vida por no estar  con proteccion"<<endl;
                }

                cout<<""<<endl;
                cout<<"Resumen del turno:"<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;
                cout<<""<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;
                cout<<""<<endl;

                if (p1->energia <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->energia <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->energia<=0){
                    fin=1;
                }
                else if (p1->salud<=0){
                    fin=1;
                }
                else if (p2->salud<=0){
                    fin=2;
                }
                else if (p2->energia<=0){
                    fin=2;
                }
                else{
                    fin=0;
                    t+=1;
                    turno+=1;
                }

            }

        }
    }
    if (fin==3){
        cout<<"¡Vaya! parece que ambos han caido en batalla "<<endl<<"¡Ningun bando gana!"<<endl;
    }
    else if(fin==2){
        cout<<"El peleador de "<<j2<<" ha caido en batalla, toda su energia ha sido abasorvida por el peleador de "<<j1<<endl;
        cout<<j1<<" gana el encuentro "<<endl;
        if(p2->energia > 0){
            p1->energia+=p2->energia;
        }
        EliminarPerosnajesPorNombre(equipo2,p2);
        RecuperarEnergia(p1, razas);
    }
    else if(fin==1){
        cout<<"El peleador de "<<j1<<" ha caido en batalla, toda su energia ha sido abasorvida por el peleador de "<<j2<<endl;
        cout<<j2<<" gana el encuentro "<<endl;
        if(p1->energia > 0){
            p2->energia+=p1->energia;
        }
        EliminarPerosnajesPorNombre(equipo1,p1);
        RecuperarEnergia(p2, razas);
    }
    turnoi+=1;
    RecuperarVida(prs1, razas, p1);
    RecuperarVida(prs2, razas, p2);
    cout<<"¡Aviso, los peleadores que no lucharon se recuperaron!"<<endl;

}