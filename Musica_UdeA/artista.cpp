#include "Artista.h"
#include <iostream>

// Función auxiliar para copiar cadenas (sin usar strncpy de la STL)
void Artista::copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// ----------------------------------------------------
// DEFINICIÓN DE CONSTRUCTORES Y OPERADORES
// ----------------------------------------------------

// Constructor principal
Artista::Artista(const char* nom, const char* cod, const char* pais, long long seguidores, const char* pos)
    : cantidadSeguidores(seguidores) {

    copyString(nombreArtistico, nom, 100);
    copyString(codigoIdentificador, cod, 6);
    copyString(paisOrigen, pais, 50);
    copyString(posicionTendencias, pos, 50);
    // 'albumes' se inicializa automáticamente con el constructor por defecto de MiLista
}

// Destructor
Artista::~Artista() {
    // IMPORTANTE: Solo liberamos la memoria de la lista (MiLista),
    // NO liberamos los objetos Album* apuntados, ya que se asume que
    // UdeATunes gestiona esos objetos.
}

// Constructor de copia (Regla del Tres/Cinco)
Artista::Artista(const Artista& other)
    : cantidadSeguidores(other.cantidadSeguidores),
    albumes(other.albumes) { // MiLista usa su Constructor de Copia (copia superficial de punteros)

    // Copia de campos de cadena de caracteres
    copyString(nombreArtistico, other.nombreArtistico, 100);
    copyString(codigoIdentificador, other.codigoIdentificador, 6);
    copyString(paisOrigen, other.paisOrigen, 50);
    copyString(posicionTendencias, other.posicionTendencias, 50);

    // NOTA: La línea 'albumes(other.albumes)' realiza la copia superficial de los punteros.
}

// Operador de asignación (=) (Regla del Tres/Cinco)
Artista& Artista::operator=(const Artista& other) {
    if (this != &other) {
        // Copia de datos primitivos
        cantidadSeguidores = other.cantidadSeguidores;

        // Copia de char[]
        copyString(nombreArtistico, other.nombreArtistico, 100);
        copyString(codigoIdentificador, other.codigoIdentificador, 6);
        copyString(paisOrigen, other.paisOrigen, 50);
        copyString(posicionTendencias, other.posicionTendencias, 50);

        // Copia Superficial de MiLista<Album*> (MiLista::operator=)
        albumes = other.albumes;
    }
    return *this;
}

// ----------------------------------------------------
// MÉTODOS DE LÓGICA Y SOBRECARGA
// ----------------------------------------------------

// Sobrecarga de Operador '==' para buscar artistas por ID
bool Artista::operator==(const Artista& other) const {
    // Comparamos el código identificador de 5 dígitos
    int i = 0;
    while (codigoIdentificador[i] != '\0') {
        if (codigoIdentificador[i] != other.codigoIdentificador[i]) {
            return false;
        }
        i++;
    }
    // Asegurar que ambos terminan igual (código de 5 caracteres)
    return other.codigoIdentificador[i] == '\0';
}
