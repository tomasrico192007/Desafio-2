#ifndef UDEATUNES_H
#define UDEATUNES_H

// Incluimos todas las clases que vamos a gestionar
#include "MiLista.h"
#include "Usuario.h"
#include "Cancion.h"
#include "Album.h"
#include "Artista.h"
#include "MensajePublicitario.h"

// Requerimiento para la medición del consumo de recursos
#include <iostream>
#include <stdexcept>

class UdeATunes {
private:
    // Colecciones globales que gestionan toda la información de la plataforma.
    // Usamos punteros para gestionar la memoria dinámica de los objetos
    // que se deben persistir durante la ejecución del programa.
    MiLista<Usuario*>* usuarios;
    MiLista<Album*>* albumes;
    MiLista<Artista*>* artistas;
    MiLista<Cancion*>* canciones; // Lista global de todas las canciones para reproducción aleatoria
    MiLista<MensajePublicitario*>* mensajesPublicitarios;

    // Contador para la lógica de publicidad (cada dos canciones)
    int contadorReproduccionesEstandar;

    // Función auxiliar para buscar usuarios (implementación en UdeATunes.cpp)
    Usuario* buscarUsuario(const char* nickname);

    // Función auxiliar para cargar datos desde archivos (Funcionalidad I - Carga/actualización de datos)
    bool cargarDatos();

    // Función auxiliar para liberar TODA la memoria dinámica
    void liberarTodasColecciones();

public:
    // Constructor: Inicializa las MiLista
    UdeATunes();

    // ----------------------------------------------------
    // REGLA DEL TRES/CINCO: Gestión de Memoria
    // ----------------------------------------------------

    // Destructor: OBLIGATORIO para liberar las listas y los objetos apuntados (deep delete)
    ~UdeATunes();

    // Constructor de copia y Operador de asignación se omiten temporalmente.
    // En una clase controladora grande, implementarlos para copia profunda es complejo
    // y generalmente innecesario, siguiendo el principio de "no hacer más de lo necesario".
    // Si la funcionalidad no lo requiere, se declaran como 'deleted' o se omiten.

    // ----------------------------------------------------
    // FUNCIONALIDADES PRINCIPALES (Requisito 4)
    // ----------------------------------------------------

    // II. Ingreso a la plataforma
    Usuario* iniciarSesion(const char* nickname, const char* password);

    // III. Reproducción Aleatoria
    void reproducirAleatorio(Usuario* usuario);

    // IV. Mi lista de favoritos (Editar)
    void editarListaFavoritos(UsuarioPremium* usuario, const char* idCancion, bool agregar);

    // IV. Mi lista de favoritos (Ejecutar)
    void ejecutarListaFavoritos(UsuarioPremium* usuario, bool ordenAleatorio);

    // IV. Seguir otra lista de favoritos (Opcional para Premium)
    void seguirListaFavoritos(UsuarioPremium* usuario, const char* nicknameASeguir);

    // V. Medición del consumo de recursos (parte del requisito)
    void medirConsumoRecursos(const char* funcionalidad, int iteraciones, long totalMemoria);
};

#endif // UDEATUNES_H
