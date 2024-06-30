/*
Proyecto Estructura de Datos
Integrantes:
    Sergio Gontardo
    Leonardo Chacón
*/

#include <iostream>
#include <string>
#include "libreria.h"

using namespace std;


void menu() {
    int opcion;
    do {
        cout << endl << "Menú" << endl;
        cout << "1. Acciones para razas" << endl;
        cout << "2. Acciones para accesorios" << endl;
        cout << "3. Acciones para ambientes" << endl;
        cout << "4. Ir a la Guerra!!" << endl;
        cout << "5. Salir" << endl;
        opcion = validarNumero("Ingrese una opción: ");
        switch (opcion) {
            case 1:
                int opcionRaza;
                do {
                    cout << "1. Crear raza" << endl;
                    cout << "2. Leer razas" << endl;
                    cout << "3. Modificar razas" << endl;
                    cout << "4. Eliminar raza" << endl;
                    cout << "5. Volver" << endl;
                    opcionRaza = validarNumero("Ingrese una opción: ");
                    if (opcionRaza == 1) {
                        if (ambienteVacio() == true) {
                            cout
                                    << "La lista de ambientes esta vacia y se requiere de por lo menos uno para crear una raza."
                                    << endl;
                            crearAmbiente();
                            cout << endl;
                            cout << "Ahora si! Cree la raza" << endl;
                            crearRaza();
                        }
                        else{
                            crearRaza();
                        }
                    } else if (opcionRaza == 2) {
                        leerRaza();
                    } else if (opcionRaza == 3) {
                        modificarRaza();
                    } else if (opcionRaza == 4) {
                        eliminarRaza();
                    } else if (opcionRaza == 5) {
                        cout << "Volviendo" << endl;
                        break;
                    } else {
                        cout << "Ingrese una opción válida" << endl;
                    }
                } while(opcionRaza != 5);
                break;
            case 2:
                int opcionAccesorio;
                do {
                    cout << "1. Crear accesorio" << endl;
                    cout << "2. Leer accesorios" << endl;
                    cout << "3. Modificar accesorios" << endl;
                    cout << "4. Eliminar accesorio" << endl;
                    cout << "5. Volver" << endl;
                    opcionAccesorio = validarNumero("Ingrese una opción: ");
                    if (opcionAccesorio == 1) {
                        crearAccesorio();
                    } else if (opcionAccesorio == 2) {
                        leerAccesorio();
                    } else if (opcionAccesorio == 3) {
                        modificarAccesorio();
                    } else if (opcionAccesorio == 4) {
                        eliminarAccesorio();
                    } else if (opcionAccesorio == 5) {
                        cout << "Volviendo" << endl;
                        break;
                    } else {
                        cout << "Ingrese una opción válida" << endl;
                    }
                } while(opcionAccesorio != 5);
                break;
            case 3:
                int opcionAmbiente;
                do {
                    cout << "1. Crear ambiente" << endl;
                    cout << "2. Leer ambientes" << endl;
                    cout << "3. Modificar ambientes" << endl;
                    cout << "4. Eliminar ambiente" << endl;
                    cout << "5. Volver" << endl;
                    opcionAmbiente = validarNumero("Ingrese una opción: ");
                    if (opcionAmbiente == 1) {
                        crearAmbiente();
                    } else if (opcionAmbiente == 2) {
                        leerAmbiente();
                    } else if (opcionAmbiente == 3) {
                        modificarAmbiente();
                    } else if (opcionAmbiente == 4) {
                        eliminarAmbiente();
                    } else if (opcionAmbiente == 5) {
                        cout << "Volviendo" << endl;
                        break;
                    } else {
                        cout << "Ingrese una opción válida" << endl;
                    }
                } while(opcionAmbiente != 5);
                break;
            case 4:
                int opcionSoldado;
                do {
                    cout << "1. Crear soldados" << endl;
                    cout << "2. Leer soldados" << endl;
                    cout << "5. Volver" << endl;
                    opcionSoldado = validarNumero("Ingrese una opción: ");
                    if (opcionSoldado == 1) {
                        if (RazaVacio() == true) {
                            cout
                                    << "La lista de razas esta vacia y se requiere de por lo menos una para crear un soldado."
                                    << endl;
                            if (ambienteVacio() == true) {
                                cout
                                        << "La lista de ambientes esta vacia y se requiere de por lo menos uno para crear una raza."
                                        << endl;
                                crearAmbiente();
                                cout << endl;
                                cout << "Ahora si! Cree la raza" << endl;
                                crearRaza();
                            }
                            else{
                                crearRaza();
                            }
                            cout << endl;
                            cout << "Ahora si! Cree su soldado" << endl;
                            // crearSoldado();
                        }
                        else{
                            // crearSoldado();
                        }
                        break;

                    } else if (opcionSoldado == 2) {
                        leerSoldado();
                    } else if (opcionSoldado == 5) {
                        cout << "Volviendo" << endl;
                        break;
                    } else {
                        cout << "Ingrese una opción válida" << endl;
                    }
                } while(opcionAmbiente != 5);
                break;
            case 5:
                cout << "Saliendo" << endl;
                break;
                exit;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while(opcion != 5);
}

int main() {

    leerArchivoRazas(primeroRaza, ultimoRaza);
    leerArchivoAccesorios(primeroAccesorio, ultimoAccesorio);
    leerArchivoAmbientes(primeroAmbiente, ultimoAmbiente);

    menu();
    return 0;
}