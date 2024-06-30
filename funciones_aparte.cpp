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


/*
Notas adicionales
Efectos de los Accesorios: Necesitas definir cómo los accesorios afectan la salud y la energía de los soldados.
Ambientes: Los efectos de los ambientes en los soldados deben ser manejados.
Alternar Turnos y Rondas: Asegúrate de alternar correctamente los turnos y considerar los efectos adicionales de los ambientes.
Este es un esquema general para empezar. Necesitarás ajustar los detalles y los efectos específicos de los accesorios y ambientes según tus requisitos.
*/

/*

Efecto de los accesorios: Cada accesorio tiene un tipo de efecto, estos efectos son 4: Ataque, defensa, supervivencia y condicionamiento. Los accesorios de ataque están pensados para restar vida al enemigo dependiendo de su valor. Los accesorios de tipo defensa son para defender la vida del soldado, son los únicos que tienen un valor int en contenedor, ya que significa que se restará ese valor al contenedor hasta que se agote y se empiece a restar vida al soldado. Los accesorios de supervivencia son para ser usados al momento y recuperar energía o vida dependiendo del valor que este en recuperación, solo este tipo de accesorio tiene int en recuperación de energio o vida, es decir salud y energia. Por último, los accesorios de tipo condicionamiento son para los ambientes, que tiene su aplicación dependiendo al ambiente que el soldado se encuentre. Son para aplicar y el detalle a que ambiente pertenece se encuentra en recuperación

El efecto que tiene el ambiente en los soldados es el siguiente, dependiendo del ambiente en donde sucesa la batalla, el soldado tiene su ambiente natural, en su detalle al crearlo. Si el ambiente de la batalla es el mismo que el ambiente natural del soldado, este no tendrá la necesidad de aplicar el tipo de accesorio de supervivencia para no perder vida cada vez que realiza un ataque. Si el ambiente de la batalla es diferente al ambiente natural del soldado, este tendrá o que aplicar un accesorio de supervivencia del tipo de recuperación del ambiente o cada vez que realiza un ataque se le resta vida.

Alternar turnos y rondas: Los turnos se alternan entre los soldados de los equipos, es decir, si el equipo 1 empieza, el equipo 2 sigue y así sucesivamente. Cada ronda es una batalla entre dos soldados, el soldado que gane la batalla absorbe la energía del soldado derrotado. La batalla termina cuando uno de los soldados se queda sin vida o energía.

*/