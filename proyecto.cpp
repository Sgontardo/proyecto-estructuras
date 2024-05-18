/*
Primera parte proyecto Estructura de Datos
Integrantes:
    Sergio Gontardo
    Leonardo Chacón
    Daniel Vasquez
*/

/*
Estructuras que tenemos que añadir:
    Raza:
        Nombre
        Energía
        Salud: 100%
        Ambiente
        Fidelidad
    Accesorios:
        Nombre
        Tipo (ataque, defensa, supervivencia y adaptación)
        Valor
        Energía
        Contenedor
    Ambiente (Elección aleatoria):
        Nombre
*/

/*
Creación de soldados con su mochila
    Soldado (Nombre del player, elegir raza)
        Salud: 100%
        Energía: Según la raza
    Mochila (Elegir 5 accesorios para mochila)
        Accesorios
    Equipo (Aleatorio)
*/

/*
Manejo de Menú
    1. Acciones para raza
        1.1 Crear raza
        1.2 Consultar raza
        1.3 Modificar raza
        1.4 Eliminar raza
    2. Acciones para accesorio
        2.2 Crear accesorio
        2.3 Consultar accesorio
        2.4 Modificar accesorio
        2.5 Eliminar accesorio
    3. Acciones para ambiente
        3.3 Crear ambiente
        3.4 Consultar ambiente
        3.5 Modificar ambiente
        3.6 Eliminar ambiente
    4. Crear Soldado
        4.1 Soldado
            4.1.1 Asignar raza
            4.1.2 Agregar accesorios a mochila
            4.1.3 Asignar ambiente
    5. Salir
*/

/*
Uso de lista enlazada
    Crear
    Leer
    Modificar
    Eliminar
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


void menu() {
    int opcion;
    do {
        cout << endl << "Menú" << endl;
        cout << "1. Acciones para raza" << endl;
        cout << "2. Acciones para accesorio" << endl;
        cout << "3. Acciones para ambiente" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                int opcionRaza;
                do {
                    cout << "1. Crear raza" << endl;
                    cout << "2. Leer razas" << endl;
                    cout << "3. Modificar razas" << endl;
                    cout << "4. Eliminar raza" << endl;
                    cout << "5. Salir" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionRaza;
} while(opcionRaza != 5);
                break;
            case 2:
                int opcionAccesorio;
                do {
                    cout << "1. Crear accesorio" << endl;
                    cout << "2. Leer accesorios" << endl;
                    cout << "3. Modificar accesorios" << endl;
                    cout << "4. Eliminar accesorio" << endl;
                    cout << "5. Salir" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionAccesorio;
                } while(opcionAccesorio != 5);
                break;
            case 3:
                int opcionAmbiente;
                do {
                    cout << "1. Crear ambiente" << endl;
                    cout << "2. Leer ambientes" << endl;
                    cout << "3. Modificar ambientes" << endl;
                    cout << "4. Eliminar ambiente" << endl;
                    cout << "5. Salir" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionAmbiente;
                } while(opcionAmbiente != 5);
                break;
            case 4:
                cout << "Saliendo" << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while(opcion != 4);
}

int main() {
    menu();
    return 0;
}