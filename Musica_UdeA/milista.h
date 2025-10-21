#ifndef MILISTA_H
#define MILISTA_H

// Solo se incluyen librerías básicas y necesarias para la consola
#include <iostream>
#include <stdexcept>
#include <cstdlib> // Para funciones de manejo de memoria si fuera necesario (aunque new/delete son suficientes)

/**
 * @brief MiLista: Contenedor genérico que implementa un Arreglo Dinámico.
 * * Reemplaza la funcionalidad de std::vector sin usar la STL, con manejo
 * explícito de memoria dinámica para cumplir los requisitos del proyecto.
 */
template <class T>
class MiLista {
private:
    T* data;         // Puntero al arreglo dinámico de objetos (MEMORIA DINÁMICA)
    int capacity;    // Capacidad actual del arreglo
    int size;        // Número de elementos en la lista

    /**
     * @brief Aumenta la capacidad del arreglo dinámico al doble.
     * * Implementa la lógica de redimensionamiento manual.
     */
    void resize() {
        if (capacity == 0) { // Manejar el caso inicial o si se vació completamente
            capacity = 1;
        } else {
            capacity *= 2;
        }

        T* newData = new T[capacity];

        // Copiar los datos antiguos a la nueva ubicación
        for (int i = 0; i < size; ++i) {
            // Utilizamos la asignación, asumiendo que el tipo T tiene
            // un constructor de copia o asignación apropiado.
            newData[i] = data[i];
        }

        delete[] data; // Liberar la memoria antigua
        data = newData;
        std::cout << "[MiLista::resize] Capacidad aumentada a " << capacity << " elementos.\n";
    }

public:
    // Constructor
    MiLista(int initialCapacity = 10) : size(0) {
        // Asegurar que la capacidad inicial sea positiva
        capacity = (initialCapacity > 0) ? initialCapacity : 10;
        // Inicializamos la memoria dinámica
        data = new T[capacity];
    }

    // ----------------------------------------------------
    // REGLA DE LOS TRES/CINCO: Gestión de Memoria Dinámica
    // ----------------------------------------------------

    // 1. Destructor
    ~MiLista() {
        delete[] data; // Liberar el arreglo completo
        data = nullptr;
    }

    // 2. Constructor de Copia (Copia Profunda)
    MiLista(const MiLista& other) : capacity(other.capacity), size(other.size) {
        // Asignación de nueva memoria
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            // Copia profunda elemento por elemento
            data[i] = other.data[i];
        }
    }

    // 3. Operador de Asignación (=) (Copia Profunda)
    MiLista& operator=(const MiLista& other) {
        if (this != &other) { // Autocomprobación
            // 1. Liberar los recursos antiguos
            delete[] data;

            // 2. Copiar los atributos y asignar nueva memoria
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];

            // 3. Copiar en profundidad los elementos
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // ----------------------------------------------------
    // Métodos esenciales
    // ----------------------------------------------------

    // Agregar un elemento al final (simulando push_back)
    void add(const T& item) {
        if (size == capacity) {
            resize(); // Aumentar capacidad si está lleno
        }
        // Usamos la sobrecarga de asignación de T (o el constructor de copia)
        data[size++] = item;
    }

    // Eliminar un elemento en un índice específico
    void removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::runtime_error("Indice de eliminacion fuera de rango.");
        }
        // Mover los elementos a la izquierda para cubrir el hueco
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    // Verifica si la lista contiene un elemento (requiere la sobrecarga de operator== en T)
    bool contains(const T& item) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == item) {
                return true;
            }
        }
        return false;
    }

    // Acceder a un elemento por índice (simulando operator[])
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::runtime_error("Indice fuera de rango en MiLista.");
        }
        return data[index];
    }

    // Versión const del operador []
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::runtime_error("Indice fuera de rango en MiLista (const).");
        }
        return data[index];
    }

    // Getters básicos
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }
};

#endif // MILISTA_H
