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
    Soldado* siguiente;
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
            while (!encontrado) {
                cout << "Ambiente no encontrado" << endl;
                cout << "Ambientes disponibles: " << endl;
                leerAmbiente();
                cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
                ambiente = validarString();
                actual = primeroAmbiente;
                while (actual != nullptr && encontrado != true) {
                    if (actual -> nombre == ambiente) {
                        encontrado = true;
                    }
                    actual = actual -> siguiente;
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
    leerAmbiente();
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


Raza* devolverRaza() {
    string raza;
    cout << "Ingrese la raza del soldado: ";
    cin >> raza;
    Raza* actual = primeroRaza;
    while (actual != nullptr) {
        if (actual -> nombre == raza) {
            return actual;
        }
        actual = actual -> siguiente;
    }
    return nullptr;
}

bool verificarAccesorios(){
    int i = 0;
    Accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            i += 1;
            actual = actual -> siguiente;
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

Accesorio* buscarAccesorio(string nombre) {
    Accesorio* actual = primeroAccesorio;
    while (actual != nullptr) {
        if (actual -> nombre == nombre) {
            return actual;
        }
        actual = actual -> siguiente;
    }
    return nullptr;
}

int cantidadAccesorios() {
    Accesorio* actual = primeroAccesorio;
    int cantidad = 0;
    while (actual != nullptr) {
        cantidad++;
        actual = actual -> siguiente;
    }
    return cantidad;
}


void leerArchivoSoldados() {
    ifstream archivo("soldados.inv");
    if (archivo.is_open()) {
        string linea;
        Soldado* nuevoSoldado = nullptr;
        while (getline(archivo, linea)) {
            if (linea == "--") {
                if (nuevoSoldado != nullptr) {
                    if (primeroSoldado == nullptr) {
                        primeroSoldado = nuevoSoldado;
                        ultimoSoldado = nuevoSoldado;
                    } else {
                        ultimoSoldado->siguiente = nuevoSoldado;
                        ultimoSoldado = nuevoSoldado;
                    }
                }
                nuevoSoldado = new Soldado();
            } else if (nuevoSoldado != nullptr) {
                size_t pos = linea.find(":");
                if (pos != string::npos) {
                    string key = linea.substr(0, pos);
                    string value = linea.substr(pos + 1);
                    if (key == "Nombre") nuevoSoldado->nombre = value;
                    else if (key == "Raza") nuevoSoldado->raza = devolverRaza();
                    else if (key == "Ambiente") nuevoSoldado->ambiente = value;
                    else if (key == "Accesorio") {
                        Accesorio* acc = buscarAccesorio(value);
                        if (acc != nullptr) {
                            for (int i = 0; i < 5; i++) {
                                if (nuevoSoldado->mochila[i] == nullptr) {
                                    nuevoSoldado->mochila[i] = acc;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de soldados" << endl;
    }
}

void guardarEnArchivoSoldados() {
    ofstream archivo("soldados.inv", ios::out);
    if (archivo.is_open()) {
        Soldado* actualSoldado = primeroSoldado;
        while (actualSoldado != nullptr) {
            archivo << "Nombre:" << actualSoldado->nombre << endl;
            archivo << "Raza:" << actualSoldado->raza->nombre << endl;
            archivo << "Ambiente:" << actualSoldado->raza->ambiente << endl;
            for (int i = 0; i < 5; i++) {
                if (actualSoldado->mochila[i] != nullptr) {
                    archivo << "Accesorio:" << actualSoldado->mochila[i]->nombre << endl;
                }
            }
            archivo << "--" << endl;
            actualSoldado = actualSoldado->siguiente;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de soldados" << endl;
    }
}

void crearSoldado() {
    Soldado *nuevo = new Soldado();
    cout << "Ingrese el nombre del soldado: ";
    getline(cin, nuevo -> nombre);
    cin.ignore();
    cout << "Razas disponibles: " << endl;
    leerRaza();
    Raza* race = devolverRaza();
    while (race == nullptr){
        cout << "Ingrese una raza válida: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        race = devolverRaza();
    }
    nuevo -> raza = race;
    if (nuevo->raza == nullptr) {
        cout << "La raza no esta inicializada." << endl;
    } else if (nuevo->raza->ambiente.empty()) {
        cout << "Ambiente string esta vacia." << endl;
    } else {
        cout << "Ambiente del soldado por consecuencia a su raza: "<< nuevo->raza->ambiente << endl;
        nuevo -> ambiente = nuevo -> raza -> ambiente;
    }
    if (verificarAccesorios()){
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            getline(cin, accesorioName);
            Accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo -> mochila[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--;
            }
        }
    }
    else {
        cout << "El soldado necesita minimo 5 accesorios";
        while(cantidadAccesorios() < 5){
            crearAccesorio();
        }
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            getline(cin, accesorioName);
            Accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo -> mochila[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--;
            }
        }
    }
    if (primeroSoldado == nullptr) {
        primeroSoldado = nuevo;
        ultimoSoldado = nuevo;
        nuevo->siguiente = nullptr;
    } else {
        ultimoSoldado->siguiente = nuevo;
        nuevo->siguiente = nullptr;
        ultimoSoldado = nuevo;
    }
    guardarEnArchivoSoldados();
    cout << "Soldado creado" << endl;
}

void leerSoldado() {
    Soldado* actual = primeroSoldado;
    if (primeroSoldado != nullptr) {
        while (actual != nullptr) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            cout << "Raza: " << actual -> raza << endl;
            cout << "Ambiente: " << actual -> ambiente << endl;
            cout << "Accesorios: ";
            for (int i = 0; i < 5; i++) {
                if (actual->mochila[i] != nullptr) {
                    cout << actual->mochila[i]->nombre << endl;
                } else {
                    cout << "Accesorio at index " << i << " is null." << endl;
                }
            }
            cout << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de soldados se encuentra vacía" << endl;
    }
}

void modificarSoldado() {
    Soldado* actual = primeroSoldado;
    bool encontrado = false;
    string soldadoBuscada;
    cout << "Ingrese el nombre del soldado a modificar: ";
    soldadoBuscada = validarString();
    if (primeroSoldado != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == soldadoBuscada) {
                cout << "Soldado con el nombre " << soldadoBuscada << " encontrada" << endl;
                cout << "Ingrese el nuevo nombre: ";
                actual -> nombre = validarString();
                cout << "Razas disponibles: " << endl;
                leerRaza();
                Raza* race = devolverRaza();
                while (race == nullptr){
                    cout << "Ingrese una raza válida: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    race = devolverRaza();
                }
                actual -> raza = race;
                if (actual->raza == nullptr) {
                    cout << "La raza no esta inicializada." << endl;
                } else if (actual->raza->ambiente.empty()) {
                    cout << "Ambiente string esta vacia." << endl;
                } else {
                    cout << "Ambiente del soldado por consecuencia a su raza: "<< actual->raza->ambiente << endl;
                    actual -> ambiente = actual -> raza -> ambiente;
                }
                actual -> ambiente = validarNumero("Ingrese la nueva energía: ");
                cout << "Ingrese el nuevo ambiente: ";
                actual -> ambiente = validarString();
                verificarAmbiente(actual -> ambiente);
                cout << "Raza modificada" << endl;
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Soldado no encontrado" << endl;
        }
    } else {
        cout << "La lista de soldados se encuentra vacía" << endl;
    }
}

void eliminarSoldado() {
    Soldado* actual = primeroSoldado;
    Soldado* anterior = nullptr;
    bool encontrado = false;
    string soldadoBuscada;
    cout << "Ingrese el nombre del soldado a eliminar: ";
    soldadoBuscada = validarString();
    if (primeroSoldado != nullptr) {
        while (actual != nullptr && encontrado != true) {
            if (actual -> nombre == soldadoBuscada) {
                cout << "Soldado con el nombre " << soldadoBuscada << " encontrada" << endl;
                if (actual == primeroSoldado) {
                    primeroSoldado = primeroSoldado -> siguiente;
                } else if (actual == ultimoSoldado) {
                    anterior -> siguiente = nullptr;
                    ultimoSoldado = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Soldado eliminada" << endl;
                encontrado = true;
                delete actual;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Soldado no encontrado" << endl;
        }
    } else {
        cout << "La lista de soldados se encuentra vacía" << endl;
    }
}