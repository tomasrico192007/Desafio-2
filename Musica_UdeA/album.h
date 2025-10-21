#ifndef ALBUM_H
#define ALBUM_H

#include "MiLista.h"
#include "Cancion.h" // Necesario porque MiLista<Cancion> almacena objetos Cancion

class Album {
private:
    char nombre[100];
    char generos[4][30];    // Hasta 4 géneros musicales
    char fechaLanzamiento[11]; // Formato simple DDMMAAAA + '\0'
    int duracionTotalSegundos;
    char identificador[4];  // Identificador único del álbum (2 dígitos) + '\0'
    char disquera[50];
    char rutaPortadaPng[256]; // Ruta al archivo de imagen de portada (.png)
    int puntuacion;         // Puntuación del 1 al 10

    // MiLista que contiene las canciones. Se usa el objeto completo (no puntero)
    // para cumplir la composición si la vida de la canción depende del álbum.
    MiLista<Cancion> canciones;

    // Función auxiliar para copiar cadenas (definida en el .cpp)
    void copyString(char* dest, const char* src, int maxLen);
    void copyGeneros(char dest[4][30], const char src[4][30]);

public:
    // Constructor principal
    // Los géneros se reciben como un arreglo de char* (ej. char* generos[4])
    Album(const char* nom, const char generosArr[4][30], const char* fecha, const char* id,
          const char* disq, const char* portada, int punt);

    // ----------------------------------------------------
    // REGLA DE LOS TRES/CINCO: Gestión de Memoria
    // ----------------------------------------------------

    // Destructor (simple, MiLista maneja su propia memoria)
    ~Album();

    // Constructor de copia (OBLIGATORIO por MiLista<Cancion>)
    Album(const Album& other);

    // Operador de asignación (=) (OBLIGATORIO por MiLista<Cancion>)
    Album& operator=(const Album& other);

    // ----------------------------------------------------
    // Getters y Métodos
    // ----------------------------------------------------
    const char* getNombre() const { return nombre; }
    const char* getIdentificador() const { return identificador; }
    int getPuntuacion() const { return puntuacion; }

    MiLista<Cancion>& getCanciones() { return canciones; }
    const MiLista<Cancion>& getCanciones() const { return canciones; }

    // Método para calcular/actualizar la duración total
    void actualizarDuracionTotal();

    // Sobrecarga de '==' para buscar álbumes por ID (si fuera necesario, requisito de sobrecarga)
    bool operator==(const Album& other) const;
};

#endif // ALBUM_H
