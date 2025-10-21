#ifndef USUARIOPREMIUM_H
#define USUARIOPREMIUM_H

#include "Usuario.h"
// No es estrictamente necesario incluir MiLista.h aquí si ya está en Usuario.h
// y solo se usa MiLista<Cancion*>* pero lo incluiremos para ser explícitos
#include "MiLista.h"

class UsuarioPremium : public Usuario {
private:
    MiLista<Cancion*>* favoritos; // Lista de favoritos (máximo 10000)
    int retrocesosDisponibles = 6; // Límite de retrocesos M=6

public:
    // Constructor
    // Recibe los datos base y llama al constructor de la clase base.
    UsuarioPremium(const char* nick, const char* ciu, const char* pai, const char* fecha)
        : Usuario(nick, "premium", ciu, pai, fecha) {

        // Inicializamos la lista de favoritos con un tamaño inicial
        // (el máximo es 10000, pero empezamos con un tamaño eficiente, ej. 100)
        favoritos = new MiLista<Cancion*>(100);
    }

    // Destructor: OBLIGATORIO para liberar la memoria dinámica asignada por el 'new'
    ~UsuarioPremium() override {
        // Debemos liberar la memoria de la lista de favoritos
        delete favoritos;
    }

    // ----------------------------------------------------
    // Implementación de métodos virtuales (Beneficios Premium)
    // ----------------------------------------------------

    // Puede retroceder si le quedan intentos.
    bool puedeRetroceder() const override { return retrocesosDisponibles > 0; }

    // NO debe ver publicidad.
    bool debeVerPublicidad() const override { return false; }

    // Escucha a 320 kbps.
    int getCalidadAudio() const override { return 320; }

    // Devuelve el puntero a la lista de favoritos.
    MiLista<Cancion*>* getListaFavoritos() const override { return favoritos; }

    // ----------------------------------------------------
    // Métodos de Lógica Premium
    // ----------------------------------------------------

    // Método para consumir un intento de retroceso (usado en la funcionalidad de reproducción)
    void consumirRetroceso() {
        if (retrocesosDisponibles > 0) {
            retrocesosDisponibles--;
            std::cout << "[Premium] Retroceso usado. Quedan " << retrocesosDisponibles << " retrocesos." << std::endl;
        }
    }

    // Resetear retrocesos (se puede usar al inicio de una nueva sesión de reproducción o al cambiar de lista)
    void resetearRetrocesos() {
        retrocesosDisponibles = 6;
    }

    // Getters para el estado actual de retrocesos
    int getRetrocesosDisponibles() const { return retrocesosDisponibles; }
};

#endif // USUARIOPREMIUM_H
