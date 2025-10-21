#include <iostream>
#include <cstdlib> // Para generar números aleatorios (rand)
#include <ctime>   // Para inicializar la semilla (time)

// Incluimos todos los archivos de cabecera de nuestras clases
#include "MiLista.h"
#include "Credito.h"
#include "Usuario.h"
#include "UsuarioEstandar.h"
#include "UsuarioPremium.h"
#include "Cancion.h"
// NOTA: Una vez que implementemos Album, Artista, MensajePublicitario y UdeATunes,
// estos también deberán incluirse aquí.

using namespace std;

// DECLARACIÓN ADELANTADA DE LA CLASE CONTROLADORA
// (Implementaremos esta clase como 'fachada' en pasos posteriores)
class UdeATunes {
public:
    // SIMULACIÓN: Método que buscaría un usuario en las listas cargadas.
    Usuario* iniciarSesion(const char* nickname) {
        // En la versión final, esta función cargará los datos de archivos y
        // buscará el usuario. Por ahora, creamos usuarios de prueba.
        if (strcmp(nickname, "estandar_u") == 0) {
            // Usamos new para crear la instancia en memoria dinámica
            return new UsuarioEstandar("estandar_u", "Medellin", "Colombia", "01012024");
        } else if (strcmp(nickname, "premium_u") == 0) {
            return new UsuarioPremium("premium_u", "Bogota", "Colombia", "15032024");
        } else {
            return nullptr;
        }
    }

    // SIMULACIÓN: Función de reproducción (implementación real en UdeATunes.cpp)
    void reproducirAleatorio(Usuario* usuario) {
        cout << "\n=====================================" << endl;
        cout << "  REPRODUCCIÓN ALEATORIA - UdeATunes" << endl;
        cout << "=====================================" << endl;

        if (usuario->debeVerPublicidad()) {
            cout << "\n[MENSAJE PUBLICITARIO]: ¡Disfruta la musica!" << endl;
            cout << "Categoria del mensaje: C" << endl;
        }

        cout << "Calidad de Audio: " << usuario->getCalidadAudio() << " kbps" << endl;

        // Simulación de una Canción (Temporal, hasta tener datos reales)
        Cancion c("Mi Cancion de Prueba", "123450101", 180, "/ruta/audio.ogg");

        cout << "Cantante: Artista X (Simulacion)" << endl;
        cout << "Album: Album de Prueba (Simulacion)" << endl;
        cout << "Titulo de la cancion reproducida: " << c.getNombre() << endl;
        cout << "Ruta al archivo de audio: " << c.getRutaArchivoOgg() << endl;
        cout << "Duracion: " << c.getDuracion() << " segundos" << endl;

        cout << "\nOpciones de reproduccion:" << endl;
        cout << "1.- Detener" << endl;
        if (usuario->getMembresia()[0] == 'p' || usuario->getMembresia()[0] == 'P') {
            cout << "2.- Pista Siguiente" << endl;
            cout << "3.- Pista Anterior (Retrocesos restantes: "
                 << dynamic_cast<UsuarioPremium*>(usuario)->getRetrocesosDisponibles() << ")" << endl;
            cout << "4.- Repetir cancion" << endl;
        }
        cout << "-------------------------------------" << endl;
    }

    // SIMULACIÓN: Función para editar favoritos (implementación real en UdeATunes.cpp)
    void editarFavoritos(UsuarioPremium* usuario) {
        if (!usuario) return;
        cout << "\n=====================================" << endl;
        cout << "  EDITAR LISTA DE FAVORITOS (Premium)" << endl;
        cout << "=====================================" << endl;
        cout << "Lista actual tiene: " << usuario->getListaFavoritos()->getSize() << " canciones." << endl;
        // Aquí iría la lógica de búsqueda por ID y el MiLista::add
        cout << "Funcionalidad pendiente: Buscar cancion por ID y agregar/eliminar." << endl;
    }

    // Función para mostrar el consumo de recursos (parte del requisito)
    void medirConsumoRecursos(const char* funcionalidad, int iteraciones, long totalMemoria) {
        cout << "\n[MEDICION DE RECURSOS - " << funcionalidad << "]" << endl;
        cout << "Iteraciones de busqueda/operacion: " << iteraciones << endl;
        cout << "Memoria consumida (Estimada/Simulada): " << totalMemoria << " Bytes" << endl;
    }
};

// ----------------------------------------------------
// FUNCIONES DE MENÚ
// ----------------------------------------------------

void mostrarMenuPrincipal() {
    cout << "\n=====================================" << endl;
    cout << "     UdeATunes - Streaming Musical" << endl;
    cout << "=====================================" << endl;
    cout << "1. Ingresar a la plataforma (Login)" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarMenuFuncionalidades(Usuario* usuario) {
    cout << "\n=====================================" << endl;
    cout << "     MENU DE USUARIO (" << usuario->getMembresia() << ")" << endl;
    cout << "=====================================" << endl;
    cout << "1. Reproduccion aleatoria" << endl;

    // Opciones solo para Premium
    if (strcmp(usuario->getMembresia(), "premium") == 0) {
        cout << "2. Mi Lista de Favoritos (Editar)" << endl;
        cout << "3. Mi Lista de Favoritos (Ejecutar)" << endl;
        cout << "4. Seguir otra Lista de Favoritos" << endl;
    }

    cout << "0. Cerrar sesion" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}


// ----------------------------------------------------
// FUNCION PRINCIPAL
// ----------------------------------------------------
int main() {
    // Inicializar la semilla para números aleatorios (usado en publicidad/selección)
    srand(time(0));

    UdeATunes plataforma; // Instancia de la clase controladora
    Usuario* usuarioActual = nullptr;
    int opcionPrincipal;
    int opcionFuncionalidad;
    char nickTemp[50];

    // Bucle principal del programa
    do {
        // Si no hay sesión activa, muestra el menú principal
        if (usuarioActual == nullptr) {
            mostrarMenuPrincipal();
            if (!(cin >> opcionPrincipal)) {
                cin.clear();
                cin.ignore(10000, '\n');
                opcionPrincipal = -1; // Opción inválida
            }

            if (opcionPrincipal == 1) {
                cout << "Ingrese nickname (estandar_u / premium_u): ";
                cin >> nickTemp;

                usuarioActual = plataforma.iniciarSesion(nickTemp);

                if (usuarioActual != nullptr) {
                    cout << "\n¡Bienvenido/a, " << usuarioActual->getNickname() << "!" << endl;
                } else {
                    cout << "Error: Nickname o clave invalidos (SIMULACION)." << endl;
                }
            } else if (opcionPrincipal != 0) {
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }

        } else {
            // Si hay sesión activa, muestra el menú de funcionalidades
            mostrarMenuFuncionalidades(usuarioActual);
            if (!(cin >> opcionFuncionalidad)) {
                cin.clear();
                cin.ignore(10000, '\n');
                opcionFuncionalidad = -1; // Opción inválida
            }

            if (opcionFuncionalidad == 1) {
                // Funcionalidad I: Reproducción aleatoria
                plataforma.reproducirAleatorio(usuarioActual);
                // Ejemplo de medición (SIMULACIÓN)
                plataforma.medirConsumoRecursos("Reproduccion", 10, 5000);

            } else if (opcionFuncionalidad == 2 && strcmp(usuarioActual->getMembresia(), "premium") == 0) {
                // Funcionalidad IIa: Editar Mi Lista de Favoritos
                plataforma.editarFavoritos(dynamic_cast<UsuarioPremium*>(usuarioActual));
                plataforma.medirConsumoRecursos("Editar Favoritos", 25, 8000);

            } else if (opcionFuncionalidad == 0) {
                // Cerrar sesión: Liberar memoria del usuario actual
                delete usuarioActual;
                usuarioActual = nullptr;
                cout << "Sesion cerrada. Hasta pronto." << endl;
                opcionPrincipal = -1; // Para que el bucle principal continúe

            } else {
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
    } while (opcionPrincipal != 0);

    cout << "\nSaliendo del programa UdeATunes. ¡Adios!" << endl;
    return 0;
}
