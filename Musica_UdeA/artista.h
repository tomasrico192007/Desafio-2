#ifndef ARTISTA_H
#define ARTISTA_H

#include "MiLista.h"
#include "Album.h" // Necesario porque MiLista<Album*> almacena punteros a Album

class Artista {
private:
    char nombreArtistico[100];
    char codigoIdentificador[6]; // 5 dígitos de identificación + '\0'
    char paisOrigen[50];
    long long cantidadSeguidores;
    char posicionTendencias[50]; // Posición actual en tendencias (ej. "Top 10 Global")

    // Lista de álbumes: Usamos punteros a Album (Album*) para que el Artista
    // "conozca" sus álbumes, pero la gestión de memoria de los objetos Album
    // probablemente recaiga en la clase controladora UdeATunes.
    MiLista<Album*> albumes;

    // Función auxiliar para copiar cadenas (definida en el .cpp)
    void copyString(char* dest, const char* src, int maxLen);

public:
    // Constructor principal
    Artista(const char* nom, const char* cod, const char* pais, long long seguidores, const char* pos);

    // ----------------------------------------------------
    // REGLA DE LOS TRES/CINCO: Gestión de Memoria
    // ----------------------------------------------------

    // Destructor: Importante para liberar la MiLista, pero NO los punteros Album*
    ~Artista();

    // Constructor de copia (OBLIGATORIO por MiLista<Album*>)
    // Realiza una copia superficial (shallow copy) de los punteros Album*
    Artista(const Artista& other);

    // Operador de asignación (=) (OBLIGATORIO por MiLista<Album*>)
    // Realiza una copia superficial (shallow copy) de los punteros Album*
    Artista& operator=(const Artista& other);

    // ----------------------------------------------------
    // Getters y Métodos
    // ----------------------------------------------------
    const char* getNombreArtistico() const { return nombreArtistico; }
    const char* getCodigoIdentificador() const { return codigoIdentificador; }
    long long getCantidadSeguidores() const { return cantidadSeguidores; }

    MiLista<Album*>& getAlbumes() { return albumes; }
    const MiLista<Album*>& getAlbumes() const { return albumes; }

    void incrementarSeguidores(long long incremento) { cantidadSeguidores += incremento; }

    // Sobrecarga de Operador '==' para buscar artistas por ID
    bool operator==(const Artista& other) const;
};

#endif // ARTISTA_H
