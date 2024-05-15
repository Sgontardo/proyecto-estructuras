/* Para hacer las funciones CRUD (Crear, Leer, Modificar, Borrar) genéricas en C++ para cualquier estructura que tenga un puntero siguiente como lista, necesitas definir una interfaz o clase abstracta que represente la operación común entre todas estas estructuras. Luego, puedes implementar esta interfaz en cada una de tus estructuras específicas (raza, accesorio, ambiente). Aquí te muestro cómo podrías hacerlo:

Primero, define una clase abstracta llamada Lista que incluya los métodos CRUD genéricos. Esta clase debe tener un puntero a un objeto de la estructura específica como miembro, permitiendo así que las operaciones sean genéricas pero aún así específicas para cada tipo de estructura. */

#include <iostream>
#include <string>

// Clase abstracta Lista
template<typename T>
class Lista {
public:
    virtual ~Lista() {}
    virtual void crear(T* nuevoElemento) = 0; // Método para crear un nuevo elemento
    virtual void leer() const = 0; // Método para leer todos los elementos
    virtual void modificar(int indice, T* nuevoElemento) = 0; // Método para modificar un elemento existente
    virtual void borrar(int indice) = 0; // Método para borrar un elemento existente
};

/* Luego, implementa esta clase abstracta en cada una de tus estructuras específicas. Asegúrate de que cada estructura tenga un puntero siguiente para formar parte de la lista.*/

// Implementación para raza
class Raza : public Lista<Raza> {
private:
    struct NodoRaza {
        Raza* datos;
        NodoRaza* siguiente;
    };
    NodoRaza* primero;
    NodoRaza* ultimo;

public:
    Raza() : primero(nullptr), ultimo(nullptr) {}

    void crear(Raza* nuevoElemento) override {
        // Implementación para crear un nuevo nodo
    }

    void leer() const override {
        // Implementación para leer todos los nodos
    }

    void modificar(int indice, Raza* nuevoElemento) override {
        // Implementación para modificar un nodo existente
    }

    void borrar(int indice) override {
        // Implementación para borrar un nodo existente
    }
};

// Similarmente, implementa Raza, Accesorio, Ambiente siguiendo el mismo patrón

/* Finalmente, en tu función main o donde sea que desees utilizar estas clases, puedes instanciar objetos de Raza, Accesorio, Ambiente y usar sus métodos CRUD sin preocuparte por los detalles específicos de cada estructura, ya que están encapsulados dentro de la implementación de cada clase.

Este enfoque te permite mantener el código DRY (Don't Repeat Yourself) y facilita la extensibilidad de tu programa, ya que agregar nuevas estructuras que requieran manejo de listas solo implica implementar la clase abstracta Lista para esa nueva estructura. */