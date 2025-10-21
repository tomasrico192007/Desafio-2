#include "Album.h"
#include <iostream>

// NOTA: Asumimos que la declaración de estas funciones está en Album.h,
// como hicimos con Credito.h/Credito.cpp.

// Función auxiliar para copiar cadenas (sin usar strncpy de la STL)
void Album::copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Función auxiliar para copiar el arreglo de géneros (4x30)
void Album::copyGeneros(char dest[4][30], const char src[4][30]) {
    for (int i = 0; i < 4; ++i) {
        copyString(dest[i], src[i], 30);
    }
}

// ----------------------------------------------------
// DEFINICIÓN DE CONSTRUCTORES Y OPERADORES
// ----------------------------------------------------

// Constructor principal
Album::Album(const char* nom, const char generosArr[4][30], const char* fecha, const char* id,
             const char* disq, const char* portada, int punt)
    : duracionTotalSegundos(0), puntuacion(punt) { // Inicialización de miembros

    copyString(nombre, nom, 100);
    copyGeneros(generos, generosArr);
    copyString(fechaLanzamiento, fecha, 11);
    copyString(identificador, id, 4);
    copyString(disquera, disq, 50);
    copyString(rutaPortadaPng, portada, 256);
    // 'canciones' se inicializa automáticamente con el constructor por defecto de MiLista
}

// Destructor
Album::~Album() {
    // No hay punteros directos que liberar.
    // El destructor de 'canciones' (MiLista) se llama automáticamente
    // para liberar la memoria dinámica de las Canciones.
}

// Constructor de copia (Regla del Tres/Cinco)
Album::Album(const Album& other)
    : duracionTotalSegundos(other.duracionTotalSegundos),
    puntuacion(other.puntuacion),
    canciones(other.canciones) { // MiLista usa su Constructor de Copia (Copia Profunda)

    // Copia de campos de cadena de caracteres y arreglos multidimensionales
    copyString(nombre, other.nombre, 100);
    copyGeneros(generos, other.generos);
    copyString(fechaLanzamiento, other.fechaLanzamiento, 11);
    copyString(identificador, other.identificador, 4);
    copyString(disquera, other.disquera, 50);
    copyString(rutaPortadaPng, other.rutaPortadaPng, 256);
}

// Operador de asignación (=) (Regla del Tres/Cinco)
Album& Album::operator=(const Album& other) {
    if (this != &other) {
        // Copia de datos primitivos
        duracionTotalSegundos = other.duracionTotalSegundos;
        puntuacion = other.puntuacion;

        // Copia de char[]
        copyString(nombre, other.nombre, 100);
        copyGeneros(generos, other.generos);
        copyString(fechaLanzamiento, other.fechaLanzamiento, 11);
        copyString(identificador, other.identificador, 4);
        copyString(disquera, other.disquera, 50);
        copyString(rutaPortadaPng, other.rutaPortadaPng, 256);

        // Copia Profunda de MiLista<Cancion>
        canciones = other.canciones;
    }
    return *this;
}

// ----------------------------------------------------
// MÉTODOS DE LÓGICA Y SOBRECARGA
// ----------------------------------------------------

// Método para calcular/actualizar la duración total del álbum
void Album::actualizarDuracionTotal() {
    duracionTotalSegundos = 0;
    // Recorremos la lista de canciones usando el operador []
    for (int i = 0; i < canciones.getSize(); ++i) {
        duracionTotalSegundos += canciones[i].getDuracion();
    }
}

// Sobrecarga de '==' para buscar álbumes por ID
bool Album::operator==(const Album& other) const {
    // Comparamos el identificador de 2 dígitos (más el nulo)
    return identificador[0] == other.identificador[0] &&
           identificador[1] == other.identificador[1] &&
           identificador[2] == '\0'; // Asumiendo que el ID es de 2 caracteres
}
