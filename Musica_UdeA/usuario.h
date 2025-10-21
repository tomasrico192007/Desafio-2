#ifndef USUARIO_H
#define USUARIO_H

#include "MiLista.h" // Necesario para la declaración del método getListaFavoritos()

// Declaración adelantada para evitar dependencias circulares, ya que MiLista usa Cancion*
class Cancion;

class Usuario {
protected:
    // Atributos base usando char[] para evitar std::string
    char nickname[50];
    char membresia[20]; // "estandar" o "premium"
    char ciudad[50];
    char pais[50];
    char fechaInscripcion[11]; // Formato simple DDMMAAAA + '\0'

    // Función auxiliar para copiar cadenas de char[]
    void copyString(char* dest, const char* src, int maxLen) {
        int i = 0;
        while (src[i] != '\0' && i < maxLen - 1) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0'; // Asegurar el nulo terminador
    }

public:
    // Constructor base
    Usuario(const char* nick, const char* memb, const char* ciu, const char* pai, const char* fecha) {
        copyString(nickname, nick, 50);
        copyString(membresia, memb, 20);
        copyString(ciudad, ciu, 50);
        copyString(pais, pai, 50);
        copyString(fechaInscripcion, fecha, 11);
    }

    // Destructor virtual: Es OBLIGATORIO en clases base con herencia para asegurar
    // que el destructor de la clase derivada (Premium o Estandar) sea llamado correctamente
    // cuando se usa un puntero a la base (Usuario*).
    virtual ~Usuario() {}

    // ----------------------------------------------------
    // MÉTODOS VIRTUALES PUROS (Clase Abstracta)
    // ----------------------------------------------------

    // Indica si el usuario puede retroceder canciones (FALSO para Estándar)
    virtual bool puedeRetroceder() const = 0;

    // Indica si el usuario debe ver publicidad (VERDADERO para Estándar)
    virtual bool debeVerPublicidad() const = 0;

    // Obtiene la calidad de audio (128 kbps para Estándar, 320 kbps para Premium)
    virtual int getCalidadAudio() const = 0;

    // Obtiene la lista de favoritos. Devuelve nullptr para usuarios estándar.
    // El tipo debe ser MiLista<Cancion*> para la gestión de canciones.
    virtual MiLista<Cancion*>* getListaFavoritos() const = 0;

    // ----------------------------------------------------
    // Getters
    // ----------------------------------------------------
    const char* getNickname() const { return nickname; }
    const char* getMembresia() const { return membresia; }
    // ... otros getters según se necesiten
};

#endif // USUARIO_H
