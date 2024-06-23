#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

struct raza {
    string nombre = "";
    int energia = 0;
    int salud = 100;
    string ambiente;
    raza* siguiente;
} *primeroRaza, *ultimoRaza;

struct accesorio {
    string nombre = "";
    string tipo = "";
    int valor = 0;
    string recuperacion = "";
    int energia = 0;
    int contenedor = 0;
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

string devolverAmbiente(){
    string ambien;
    cout << "Ingrese el ambiente que desea usar: ";
    cin >> ambien;
    ambiente* actual = primeroAmbiente;
    if (primeroAmbiente != nullptr) {
        while (actual != nullptr) {
            if(actual ->nombre == ambien){
                return ambien;
            }
            else {
                actual = actual->siguiente;
            }
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
    cout << " Ambiente ingresado no encontrado." << endl;
    return "x";
}

void crearRaza() {
    raza* nuevo = new raza();
    string tempNombre;
    cout << "Ingrese el nombre de la raza: ";
    cin >> tempNombre;
        if (!tempNombre.empty()){
            nuevo -> nombre = tempNombre;
        }
        else{
            while(tempNombre.empty()) {
                cout << "Dato incorrecto. Ingrese el nombre de la raza: ";
                cin >> tempNombre;
                nuevo->nombre = tempNombre;
            }
        }

    cout << "Ingrese la energía de la raza: ";
    cin >> nuevo -> energia;
    while (cin.fail()){
        cout << "Ingrese un dato valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nuevo -> energia;
    }
    nuevo -> salud = 100;
    cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
    leerAmbiente();
    while (devolverAmbiente() == "x"){
        cout << "Ingrese un ambiente valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nuevo -> ambiente = devolverAmbiente();
        cin >> nuevo -> ambiente;
    }

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
                while (cin.fail()){
                    cout << "Ingrese un dato valido: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> actual -> energia;
                }
                cout << "Ingrese el ambiente de la raza de la lista de ambientes disponibles: ";
                leerAmbiente();
                actual -> ambiente = devolverAmbiente();
                while (devolverAmbiente() == "x"){
                    cout << "Ingrese un ambiente valido: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    actual -> ambiente = devolverAmbiente();
                    cin >> actual -> ambiente;
                }
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
    while (cin.fail()){
        cout << "Ingrese un dato valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nuevo -> valor;
    }
    cout << "Ingrese la energía del accesorio: ";
    cin >> nuevo -> energia;
    while (cin.fail()){
        cout << "Ingrese un dato valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nuevo -> energia;
    }
    cout << "Ingrese el contenedor del accesorio: ";
    cin >> nuevo -> contenedor;
    while (cin.fail()){
        cout << "Ingrese un dato valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> nuevo -> contenedor;
    }
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

bool verificaraccesorios(){
    int i = 0;
    accesorio* actual = primeroAccesorio;
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

int cantidadaccesorios(){
    int i = 0;
    accesorio* actual = primeroAccesorio;
    if (primeroAccesorio != nullptr) {
        while (actual != nullptr) {
            i += 1;
            actual = actual->siguiente;}}
    else{
            cout << "La lista de accesorios se encuentra vacía" << endl;
        }
    return i;



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
                while (cin.fail()){
                    cout << "Ingrese un dato valido: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> actual -> valor;
                }
                cout << "Ingrese la nueva energía: ";
                cin >> actual -> energia;
                while (cin.fail()){
                    cout << "Ingrese un dato valido: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> actual -> energia;
                }
                cout << "Ingrese el nuevo contenedor: ";
                cin >> actual -> contenedor;
                while (cin.fail()){
                    cout << "Ingrese un dato valido: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> actual -> contenedor;
                }
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
bool ambienteVacio(){
    ambiente* actual = primeroAmbiente;
    if (primeroAmbiente == nullptr){
        return true;
    }
    else{
        return false;
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

raza* devolverraza(){
    string nombre1;
    cout << "Ingrese la raza que desea utilizar: ";
    cin >> nombre1;
    raza* actual = primeroRaza;
    if (primeroRaza != nullptr) {
        while (actual != nullptr) {
            if (actual -> nombre == nombre1){
                return actual;
            }

            actual = actual -> siguiente;
        }
    } else {
        cout << "No se encuentra la raza ingresada." << endl;
        return nullptr;
    }

}
accesorio* buscarAccesorio(string nombre) {
    accesorio *actual = primeroAccesorio;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;

}

void crearSoldado() {
    soldado *nuevo = new soldado();
    cout << "Ingrese el nombre del soldado: ";
    cin >> nuevo -> nombre;
    cout << "Razas disponibles: " << endl;
    leerRaza();
    raza* race = devolverraza();
    while (race == nullptr){
        cout << "Ingrese una raza valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        race = devolverraza();
    }
    nuevo -> raza = race;
    cout << "Ambiente del soldado por consecuencia a su raza: "<< nuevo -> raza -> ambiente << endl;

    if (verificaraccesorios()){
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            cin >> accesorioName;
            accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo -> accesorios[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--; // Repeat the loop iteration if the accessory was not found
            }
        }
    }
    else{
        cout << "El soldado necesita minimo 5 accesorios";
        while(cantidadaccesorios() < 5){
            crearAccesorio();
        }
        cargarAccesorios();
        for (int i = 0; i < 5; i++) {
            string accesorioName;
            cout << "Ingrese el accesorio " << i + 1 << " del soldado: ";
            cin >> accesorioName;
            accesorio* acc = buscarAccesorio(accesorioName);
            if (acc != nullptr) {
                nuevo -> accesorios[i] = acc;
            } else {
                cout << "Accesorio no encontrado." << endl;
                i--; // Repeat the loop iteration if the accessory was not found
            }
        }
    }
}

