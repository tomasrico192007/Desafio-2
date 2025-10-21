#include "UdeATunes.h"
#include "UsuarioEstandar.h" // Se necesitan las clases concretas para la simulación
#include "UsuarioPremium.h"
#include <iostream>
#include <cstring> // Para funciones de cadenas (strcmp, etc.)
#include <cstdlib> // Para rand(), srand()

using namespace std;

// Función auxiliar para copiar cadenas (usada en main.cpp)
void copyString_UdeA(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// ----------------------------------------------------
// CONSTRUCTOR Y DESTRUCTOR (Gestión de Memoria Profunda)
// ----------------------------------------------------

UdeATunes::UdeATunes() : contadorReproduccionesEstandar(0) {
    // Inicialización de todas las colecciones con memoria dinámica
    usuarios = new MiLista<Usuario*>(10);
    albumes = new MiLista<Album*>(10);
    artistas = new MiLista<Artista*>(10);
    canciones = new MiLista<Cancion*>(20);
    mensajesPublicitarios = new MiLista<MensajePublicitario*>(5);

    // Llamar a la función de carga inicial de datos
    if (!cargarDatos()) {
        cout << "[UdeATunes] Error al cargar los datos iniciales. El sistema iniciará vacío." << endl;
    }
}

// Destructor: Implementación del Deep Delete
UdeATunes::~UdeATunes() {
    liberarTodasColecciones();
}

// Función auxiliar para liberar toda la memoria dinámica (Deep Delete)
void UdeATunes::liberarTodasColecciones() {
    // 1. Liberar los objetos apuntados por los punteros (Deep Delete)

    // Liberar Usuarios (incluye Estándar y Premium)
    for (int i = 0; i < usuarios->getSize(); ++i) {
        delete (*usuarios)[i];
    }

    // Liberar Álbumes
    for (int i = 0; i < albumes->getSize(); ++i) {
        delete (*albumes)[i];
    }

    // Liberar Artistas
    for (int i = 0; i < artistas->getSize(); ++i) {
        delete (*artistas)[i];
    }

    // Liberar Canciones
    for (int i = 0; i < canciones->getSize(); ++i) {
        delete (*canciones)[i];
    }

    // Liberar Mensajes Publicitarios
    for (int i = 0; i < mensajesPublicitarios->getSize(); ++i) {
        delete (*mensajesPublicitarios)[i];
    }

    // 2. Liberar las MiLista contenedoras
    delete usuarios;
    delete albumes;
    delete artistas;
    delete canciones;
    delete mensajesPublicitarios;
}

// ----------------------------------------------------
// FUNCIONES AUXILIARES DE BÚSQUEDA Y CARGA
// ----------------------------------------------------

// Funcionalidad I: Carga / actualización de datos (Simulación)
bool UdeATunes::cargarDatos() {
    // --- SIMULACIÓN DE CARGA DE USUARIOS ---
    usuarios->add(new UsuarioEstandar("estandar_u", "Medellin", "Colombia", "01012024"));
    usuarios->add(new UsuarioPremium("premium_u", "Bogota", "Colombia", "15032024"));

    // --- SIMULACIÓN DE CARGA DE CANCIONES (Necesario para reproducción) ---
    // NOTA: En la implementación real, la canción se crea al cargar el álbum.
    Cancion* c1 = new Cancion("Cancion Aleatoria 1", "000010101", 200, "/ruta/a/c1.ogg");
    Cancion* c2 = new Cancion("Cancion Aleatoria 2", "000010102", 150, "/ruta/a/c2.ogg");
    canciones->add(c1);
    canciones->add(c2);

    // --- SIMULACIÓN DE CARGA DE MENSAJES PUBLICITARIOS ---
    MensajePublicitario* m1 = new MensajePublicitario("El mejor streaming es UdeATunes!", C);
    MensajePublicitario* m2 = new MensajePublicitario("¡Compra ya la camiseta oficial del artista!", B);
    MensajePublicitario* m3 = new MensajePublicitario("Descuento del 10% si eres Premium.", AAA);
    mensajesPublicitarios->add(m1);
    mensajesPublicitarios->add(m2);
    mensajesPublicitarios->add(m3);

    // Calcular probabilidad base (Ejemplo: si la probabilidad base C es 1.0, Total = 1+2+3=6)
    // En la realidad, se normaliza. Aquí usamos un valor de prueba:
    m1->calcularProbabilidadBase(1.0); // 1.0
    m2->calcularProbabilidadBase(1.0); // 2.0
    m3->calcularProbabilidadBase(1.0); // 3.0

    cout << "[UdeATunes] Datos iniciales de prueba cargados correctamente." << endl;
    return true;
}

// Búsqueda de usuario (simulación de login)
Usuario* UdeATunes::buscarUsuario(const char* nickname) {
    for (int i = 0; i < usuarios->getSize(); ++i) {
        Usuario* u = (*usuarios)[i];
        if (strcmp(u->getNickname(), nickname) == 0) {
            return u;
        }
    }
    return nullptr;
}


// ----------------------------------------------------
// FUNCIONALIDADES (Implementación de la Lógica)
// ----------------------------------------------------

// II. Ingreso a la plataforma (Simulación de búsqueda)
Usuario* UdeATunes::iniciarSesion(const char* nickname, const char* password) {
    // NOTA: El proyecto no pide manejo de clave, solo nickname.
    // Usamos el código de la función auxiliar buscarUsuario.

    Usuario* usuario = buscarUsuario(nickname);
    if (usuario != nullptr) {
        // Reiniciar el contador de publicidad al iniciar sesión
        contadorReproduccionesEstandar = 0;
        // Reiniciar retrocesos para Premium
        if (dynamic_cast<UsuarioPremium*>(usuario)) {
            dynamic_cast<UsuarioPremium*>(usuario)->resetearRetrocesos();
        }
    }
    return usuario;
}

// III. Reproducción Aleatoria
void UdeATunes::reproducirAleatorio(Usuario* usuario) {
    if (canciones->isEmpty()) {
        cout << "[Reproduccion] No hay canciones disponibles en el sistema." << endl;
        return;
    }

    // Seleccionar una canción aleatoria
    int randomIndex = rand() % canciones->getSize();
    Cancion* cancion = (*canciones)[randomIndex];

    // Mostrar información de la canción
    cout << "\n=====================================" << endl;
    cout << "  REPRODUCCIÓN ALEATORIA" << endl;
    cout << "=====================================" << endl;
    cout << "Titulo: " << cancion->getNombre() << endl;
    cout << "ID: " << cancion->getIdentificador() << endl;
    cout << "Ruta de Audio: " << cancion->getRutaArchivoOgg() << endl;
    cout << "Duracion: " << cancion->getDuracion() << " segundos" << endl;

    // Lógica de Publicidad
    if (usuario->debeVerPublicidad()) {
        contadorReproduccionesEstandar++;
        // Requisito: cada dos canciones se muestra un mensaje publicitario
        if (contadorReproduccionesEstandar % 2 == 0) {
            // Seleccionar mensaje publicitario (Lógica simple por ID)
            int randomMsgIndex = rand() % mensajesPublicitarios->getSize();
            MensajePublicitario* msg = (*mensajesPublicitarios)[randomMsgIndex];

            cout << "\n[PUBLICIDAD - " << msg->getCategoriaStr() << "]: " << msg->getTexto() << endl;
        }
    }

    // Simular que la canción se reproduce
    cancion->incrementarReproducciones();

    // Nota: La simulación de un timer y la detención luego de K=5 canciones
    // se maneja en el bucle principal de main.cpp o en una función de reproducción más compleja.
}

// V. Medición del consumo de recursos (Requisito 3)
void UdeATunes::medirConsumoRecursos(const char* funcionalidad, int iteraciones, long totalMemoria) {
    // Requisito: Mostrar dos métricas (Iteraciones y Memoria)
    cout << "\n[MEDICION DE RECURSOS - " << funcionalidad << "]" << endl;
    cout << "a. Cantidad de iteraciones: " << iteraciones << endl;
    cout << "b. Memoria total consumida (Bytes, Simulada): " << totalMemoria << endl;
}

// IV. Mi lista de favoritos (Editar) - Implementación de ejemplo
void UdeATunes::editarListaFavoritos(UsuarioPremium* usuario, const char* idCancion, bool agregar) {
    if (!usuario) return;

    Cancion* cancionAfectada = nullptr;
    int iteraciones = 0;

    // Búsqueda lineal de la canción por ID (Simulando la búsqueda)
    for (int i = 0; i < canciones->getSize(); ++i) {
        iteraciones++;
        // Simulación: Comparamos el ID de la canción
        if (strcmp((*canciones)[i]->getIdentificador(), idCancion) == 0) {
            cancionAfectada = (*canciones)[i];
            break;
        }
    }

    if (cancionAfectada) {
        MiLista<Cancion*>* favoritos = usuario->getListaFavoritos();

        if (agregar) {
            // Requisito: No debe haber canciones repetidas en la lista
            if (!favoritos->contains(cancionAfectada)) {
                favoritos->add(cancionAfectada);
                cout << "[Favoritos] Cancion ID " << idCancion << " agregada a la lista." << endl;
            } else {
                cout << "[Favoritos] La cancion ID " << idCancion << " ya estaba en la lista." << endl;
            }
        } else {
            // Lógica de eliminación (requiere recorrer la lista de favoritos)
            for (int i = 0; i < favoritos->getSize(); ++i) {
                if ((*favoritos)[i] == cancionAfectada) {
                    favoritos->removeAt(i);
                    cout << "[Favoritos] Cancion ID " << idCancion << " eliminada de la lista." << endl;
                    break;
                }
            }
        }
    } else {
        cout << "[Favoritos] Error: Cancion con ID " << idCancion << " no encontrada." << endl;
    }

    // Medición de recursos (SIMULACIÓN)
    medirConsumoRecursos("Editar Favoritos", iteraciones, 8000 + favoritos->getSize() * sizeof(Cancion*));
}

// IV. Mi lista de favoritos (Ejecutar) - Lógica de reproducción
void UdeATunes::ejecutarListaFavoritos(UsuarioPremium* usuario, bool ordenAleatorio) {
    // ... Implementación de reproducción de lista y lógica de retrocesos M=6
    cout << "[Favoritos - Ejecutar] Funcionalidad no implementada: Reproduciendo "
         << (ordenAleatorio ? "ALEATORIO" : "ORDENADO") << "..." << endl;
    medirConsumoRecursos("Ejecutar Favoritos", 5, 5000);
}

// IV. Seguir otra lista de favoritos
void UdeATunes::seguirListaFavoritos(UsuarioPremium* usuario, const char* nicknameASeguir) {
    // ... Implementación de búsqueda de usuario/lista y copia
    cout << "[Favoritos - Seguir] Funcionalidad no implementada: Siguiendo a "
         << nicknameASeguir << "..." << endl;
    medirConsumoRecursos("Seguir Lista", 15, 6000);
}
