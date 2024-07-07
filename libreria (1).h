#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <ctime>


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
                    else if (key == "Ambiente") nuevaRaza->ambiente = value;
                    else nuevaRaza->nombre = key;
                } else {
                    nuevaRaza->nombre = linea;
                }
            } else {
                nuevaRaza = new Raza{linea, 0, 0, "", nullptr};
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
            cout << "Ambiente: " <<actual->ambiente << endl;
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
    } else if (nuevo->raza->ambiente.empty()) {
        cout << "Ambiente string está vacía." << endl;
    } else {
        cout << "El ambiente del soldado por su raza es: " << nuevo->raza->ambiente << endl;
        nuevo->ambiente = nuevo->raza->ambiente;
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