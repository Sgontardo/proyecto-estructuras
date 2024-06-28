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