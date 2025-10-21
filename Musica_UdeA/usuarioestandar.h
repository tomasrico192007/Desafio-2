#ifndef USUARIOESTANDAR_H
#define USUARIOESTANDAR_H

#include "Usuario.h"

class UsuarioEstandar : public Usuario {
public:
    // Constructor
    // Inicializa la clase base Usuario con la membresía "estandar".
    // Los datos restantes (ciudad, país, fecha) se reciben en el constructor base.
    UsuarioEstandar(const char* nick, const char* ciu, const char* pai, const char* fecha)
        : Usuario(nick, "estandar", ciu, pai, fecha) {}

    // Destructor
    ~UsuarioEstandar() override {}

    // ----------------------------------------------------
    // Implementación de métodos virtuales (Restricciones Estándar)
    // ----------------------------------------------------

    // Un usuario estándar NO puede retroceder canciones.
    bool puedeRetroceder() const override { return false; }

    // Un usuario estándar SI debe ver publicidad.
    bool debeVerPublicidad() const override { return true; }

    // Un usuario estándar escucha a 128 kbps.
    int getCalidadAudio() const override { return 128; }

    // Un usuario estándar NO tiene lista de favoritos, por lo que devuelve nullptr.
    MiLista<Cancion*>* getListaFavoritos() const override { return nullptr; }
};

#endif // USUARIOESTANDAR_H
