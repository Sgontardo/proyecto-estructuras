/*
Proyecto Estructura de Datos
Integrantes:
    Sergio Gontardo
    Leonardo Chacón
*/

#include <iostream>
#include <string>
#include "libreria (1).h"

using namespace std;

void menu() {
    int opcion;
    do {
        cout << endl << "Menú" << endl;
        cout << "1. Acciones para raza" << endl;
        cout << "2. Acciones para accesorio" << endl;
        cout << "3. Acciones para ambiente" << endl;
        cout << "4. Crear soldado" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        bool opcionvalida = false;


        while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5)

        {
            cout << "Porfavor ingrese una opcion valida: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> opcion;
        }

        switch (opcion) {
            case 1:
                int opcionRaza;
                do {
                    cout << "1. Crear raza" << endl;
                    cout << "2. Leer razas" << endl;
                    cout << "3. Modificar razas" << endl;
                    cout << "4. Eliminar raza" << endl;
                    cout << "5. Volver" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionRaza;
                    while (opcionRaza != 1 && opcionRaza != 2 && opcionRaza != 3 && opcionRaza != 4 && opcionRaza != 5)

                    {
                        cout << "Porfavor ingrese una opcion valida: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> opcionRaza;
                    }
                    if (opcionRaza == 1) {
                        if (ambienteVacio() == true) {
                            cout
                                    << "La lista de ambientes esta vacia y se requiere de por lo menos uno para crear una raza."
                                    << endl;
                            cout << "Ingrese un ambiente";
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
                    cout << "Ingrese una opción: ";
                    cin >> opcionAccesorio;
                    while (opcionAccesorio != 1 && opcionAccesorio != 2 && opcionAccesorio != 3 && opcionAccesorio != 4 && opcionAccesorio != 5)

                    {
                        cout << "Porfavor ingrese una opcion valida: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> opcionAccesorio;
                    }
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
                    cout << "Ingrese una opción: ";
                    cin >> opcionAmbiente;
                    while (opcionAmbiente != 1 && opcionAmbiente != 2 && opcionAmbiente != 3 && opcionAmbiente != 4 && opcionAmbiente != 5)

                    {
                        cout << "Porfavor ingrese una opcion valida: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> opcion;
                    }
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
                crearSoldado();
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
    menu();
  return 0;
}