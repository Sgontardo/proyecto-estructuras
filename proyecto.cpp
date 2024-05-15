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
Creación de jugadores con su mochila
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
    4. Crear jugador
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

using namespace std;


struct raza {
    string nombre;
    int energia;
    int salud;
    string ambiente;
    string fidelidad;
    raza *siguiente;
} *primero, *ultimo;


struct accesorio {
    string nombre;
    string tipo;
    int valor;
    int energia;
    string contenedor;
    accesorio *siguiente;
} *primero, *ultimo;


struct ambiente {
    string nombre;
    ambiente *siguiente;
} *primero, *ultimo;


void menu();

void menu() {
    int opcion;
    do {
        cout << "Manejo de Menú" << endl;
        cout << "1. Acciones para raza" << endl;
        cout << "2. Acciones para accesorio" << endl;
        cout << "3. Acciones para ambiente" << endl;
        cout << "4. Crear jugador" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Acciones para raza
                cout << "1 Crear raza" << endl;
                cout << "2 Consultar raza" << endl;
                cout << "3 Modificar raza" << endl;
                cout << "4 Eliminar raza" << endl;
                break;
            case 2:
                // Crear accesorio
                cout << "1 Crear accesorio" << endl;
                cout << "2 Consultar accesorio" << endl;
                cout << "3 Modificar accesorio" << endl;
                cout << "4 Eliminar accesorio" << endl;
                break;
            case 3:
                // Agregar ambiente
                cout << "1 Crear ambiente" << endl;
                cout << "2 Consultar ambiente" << endl;
                cout << "3 Modificar ambiente" << endl;
                cout << "4 Eliminar ambiente" << endl;
                break;
            case 4:
                // Crear jugador
                cout << "Soldado" << endl;
                cout << "1 Asignar raza" << endl;
                cout << "2 Agregar accesorios a mochila (5 accesorios)" /*desplegar los accesorios disponibles y añadir con número*/ << endl;
                cout << "3 Asignar ambiente base" << endl;
                break;
            case 5:
                // Salir
                cout << "Salir" << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                break;
        }
    } while (opcion != 5);
}

int main() {
    menu();
    return 0;
}