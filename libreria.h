#include <iostream>
#include <fstream>

using namespace std;

struct raza {
    string nombre;
    int energia;
    int salud;
    string ambiente;
    raza *siguiente;
} *primeroRaza, *ultimoRaza;

struct accesorio {
    string nombre;
    string tipo;
    int valor;
    int energia;
    string contenedor;
    accesorio *siguiente;
} *primeroAccesorio, *ultimoAccesorio;

struct ambiente {
    string nombre;
    ambiente *siguiente;
} *primeroAmbiente, *ultimoAmbiente;

accesorio* accesorios[5];

struct soldado {
    string nombre;
    raza *raza;
    accesorio *accesorios[5];
    ambiente *ambiente;
};


void leerArchivo() {
    ifstream archivo;
    string texto;
    archivo.open("datos.txt", ios::in);
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    while (!archivo.eof()) {
        getline(archivo, texto);
        cout << texto << endl;
    }
    archivo.close();
}

void guardarEnArchivo() {
    ofstream archivo;
    archivo.open("datos.txt", ios::out);
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    raza *actualRaza = new raza();
    actualRaza = primeroRaza;
    if (primeroRaza != NULL) {
        while (actualRaza != NULL) {
            archivo << "Raza" << endl;
            archivo << "Nombre: " << actualRaza -> nombre << endl;
            archivo << "Energía: " << actualRaza -> energia << endl;
            archivo << "Salud: " << actualRaza -> salud << endl;
            archivo << "Ambiente: " << actualRaza -> ambiente << endl;
            actualRaza = actualRaza -> siguiente;
        }
    }
    accesorio *actualAccesorio = new accesorio();
    actualAccesorio = primeroAccesorio;
    if (primeroAccesorio != NULL) {
        while (actualAccesorio != NULL) {
            archivo << "Accesorio" << endl;
            archivo << "Nombre: " << actualAccesorio -> nombre << endl;
            archivo << "Tipo: " << actualAccesorio -> tipo << endl;
            archivo << "Valor: " << actualAccesorio -> valor << endl;
            archivo << "Energía: " << actualAccesorio -> energia << endl;
            archivo << "Contenedor: " << actualAccesorio -> contenedor << endl;
            actualAccesorio = actualAccesorio -> siguiente;
        }
    }
    ambiente *actualAmbiente = new ambiente();
    actualAmbiente = primeroAmbiente;
    if (primeroAmbiente != NULL) {
        while (actualAmbiente != NULL) {
            archivo << "Ambiente" << endl;
            archivo << "Nombre: " << actualAmbiente -> nombre << endl;
            actualAmbiente = actualAmbiente -> siguiente;
        }
    }
    archivo.close();
}

void crearRaza() {
    raza *nuevo = new raza();
    cout << "Ingrese el nombre de la raza: ";
    cin >> nuevo -> nombre;
    cout << "Ingrese la energía de la raza: ";
    cin >> nuevo -> energia;
    nuevo -> salud = 100;
    cout << "Ingrese el ambiente de la raza: ";
    cin >> nuevo -> ambiente;

    if (primeroRaza == NULL) {
        primeroRaza = nuevo;
        primeroRaza -> siguiente = NULL;
        ultimoRaza = nuevo;
    } else {
        ultimoRaza -> siguiente = nuevo;
        nuevo -> siguiente = NULL;
        ultimoRaza = nuevo;
    }
    guardarEnArchivo();
    cout << "Raza ingresada" << endl;
}

void leerRaza() {
    raza *actual = new raza();
    actual = primeroRaza;
    if (primeroRaza != NULL) {
        while (actual != NULL) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            cout << "Energía: " << actual -> energia << endl;
            cout << "Salud: " << actual -> salud << endl;
            cout << "Ambiente: " << actual -> ambiente << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}

void modificarRaza() {
    raza *actual = new raza();
    actual = primeroRaza;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a modificar: ";
    cin >> razaBuscada;
    if (primeroRaza != NULL) {
        while (actual != NULL && encontrado != true) {
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
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}

void eliminarRaza() {
    raza *actual = new raza();
    actual = primeroRaza;
    raza *anterior = new raza();
    anterior = NULL;
    bool encontrado = false;
    string razaBuscada;
    cout << "Ingrese el nombre de la raza a eliminar: ";
    cin >> razaBuscada;
    if (primeroRaza != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> nombre == razaBuscada) {
                cout << "Raza con el nombre " << razaBuscada << " encontrada" << endl;
                if (actual == primeroRaza) {
                    primeroRaza = primeroRaza -> siguiente;
                } else if (actual == ultimoRaza) {
                    anterior -> siguiente = NULL;
                    ultimoRaza = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Raza eliminada" << endl;
                encontrado = true;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Raza no encontrada" << endl;
        }
    } else {
        cout << "La lista de razas se encuentra vacía" << endl;
    }
}


void crearAccesorio() {
    accesorio *nuevo = new accesorio();
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

    if (primeroAccesorio == NULL) {
        primeroAccesorio = nuevo;
        primeroAccesorio -> siguiente = NULL;
        ultimoAccesorio = nuevo;
    } else {
        ultimoAccesorio -> siguiente = nuevo;
        nuevo -> siguiente = NULL;
        ultimoAccesorio = nuevo;
    }
    guardarEnArchivo();
    cout << "Accesorio ingresado" << endl;
}

void leerAccesorio() {
    accesorio *actual = new accesorio();
    actual = primeroAccesorio;
    if (primeroAccesorio != NULL) {
        while (actual != NULL) {
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
    accesorio *actual = new accesorio();
    actual = primeroAccesorio;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a modificar: ";
    cin >> accesorioBuscado;
    if (primeroAccesorio != NULL) {
        while (actual != NULL && encontrado != true) {
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
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}

void eliminarAccesorio() {
    accesorio *actual = new accesorio();
    actual = primeroAccesorio;
    accesorio *anterior = new accesorio();
    anterior = NULL;
    bool encontrado = false;
    string accesorioBuscado;
    cout << "Ingrese el nombre del accesorio a eliminar: ";
    cin >> accesorioBuscado;
    if (primeroAccesorio != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> nombre == accesorioBuscado) {
                cout << "Accesorio con el nombre " << accesorioBuscado << " encontrado" << endl;
                if (actual == primeroAccesorio) {
                    primeroAccesorio = primeroAccesorio -> siguiente;
                } else if (actual == ultimoAccesorio) {
                    anterior -> siguiente = NULL;
                    ultimoAccesorio = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Accesorio eliminado" << endl;
                encontrado = true;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Accesorio no encontrado" << endl;
        }
    } else {
        cout << "La lista de accesorios se encuentra vacía" << endl;
    }
}


void crearAmbiente() {
    ambiente *nuevo = new ambiente();
    cout << "Ingrese el nombre del ambiente: ";
    cin >> nuevo -> nombre;

    if (primeroAmbiente == NULL) {
        primeroAmbiente = nuevo;
        primeroAmbiente -> siguiente = NULL;
        ultimoAmbiente = nuevo;
    } else {
        ultimoAmbiente -> siguiente = nuevo;
        nuevo -> siguiente = NULL;
        ultimoAmbiente = nuevo;
    }
    guardarEnArchivo();
    cout << "Ambiente ingresado" << endl;
}

void leerAmbiente() {
    ambiente *actual = new ambiente();
    actual = primeroAmbiente;
    if (primeroAmbiente != NULL) {
        while (actual != NULL) {
            cout << endl << "Nombre: " << actual -> nombre << endl;
            actual = actual -> siguiente;
        }
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void modificarAmbiente() {
    ambiente *actual = new ambiente();
    actual = primeroAmbiente;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a modificar: ";
    cin >> ambienteBuscado;
    if (primeroAmbiente != NULL) {
        while (actual != NULL && encontrado != true) {
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
    } else {
        cout << "La lista de ambientes se encuentra vacía" << endl;
    }
}

void eliminarAmbiente() {
    ambiente *actual = new ambiente();
    actual = primeroAmbiente;
    ambiente *anterior = new ambiente();
    anterior = NULL;
    bool encontrado = false;
    string ambienteBuscado;
    cout << "Ingrese el nombre del ambiente a eliminar: ";
    cin >> ambienteBuscado;
    if (primeroAmbiente != NULL) {
        while (actual != NULL && encontrado != true) {
            if (actual -> nombre == ambienteBuscado) {
                cout << "Ambiente con el nombre " << ambienteBuscado << " encontrado" << endl;
                if (actual == primeroAmbiente) {
                    primeroAmbiente = primeroAmbiente -> siguiente;
                } else if (actual == ultimoAmbiente) {
                    anterior -> siguiente = NULL;
                    ultimoAmbiente = anterior;
                } else {
                    anterior -> siguiente = actual -> siguiente;
                }
                cout << "Ambiente eliminado" << endl;
                encontrado = true;
            }
            anterior = actual;
            actual = actual -> siguiente;
        }
        if (!encontrado) {
            cout << "Ambiente no encontrado" << endl;
        }
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