#include "MensajePublicitario.h"
#include <iostream>

// ----------------------------------------------------
// FUNCIONES AUXILIARES
// ----------------------------------------------------

// Función auxiliar para copiar cadenas (sin usar strncpy de la STL)
void MensajePublicitario::copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Método para calcular la probabilidad inicial basado en la categoría.
// Recibe la probabilidad base de la categoría C.
void MensajePublicitario::calcularProbabilidadBase(double probC) {
    // La lógica de prioridad se implementa aquí:
    // C = Probabilidad simple (probC)
    // B = El doble de prioridad que C (2 * probC)
    // AAA = El triple de prioridad que C (3 * probC)

    switch (categoria) {
    case AAA:
        probabilidadVisualizacion = 3.0 * probC;
        break;
    case B:
        probabilidadVisualizacion = 2.0 * probC;
        break;
    case C:
        probabilidadVisualizacion = probC;
        break;
    default:
        probabilidadVisualizacion = 0.0;
        break;
    }
}

// ----------------------------------------------------
// DEFINICIÓN DE CONSTRUCTORES Y OPERADORES
// ----------------------------------------------------

// Constructor
MensajePublicitario::MensajePublicitario(const char* txt, CategoriaMensaje cat)
    : categoria(cat), probabilidadVisualizacion(0.0) {

    copyString(texto, txt, 501);

    // NOTA: La probabilidad se calcula una vez que la clase controladora
    // (UdeATunes) haya cargado todos los mensajes y pueda normalizar
    // la probabilidad base (probC), así que aquí solo inicializamos a 0.0.
}

// Destructor
MensajePublicitario::~MensajePublicitario() {
    // Simple, no hay punteros que liberar.
}

// Constructor de copia (Regla del Tres/Cinco)
MensajePublicitario::MensajePublicitario(const MensajePublicitario& other) {
    *this = other; // Llama al operador de asignación
}

// Operador de asignación (=) (Regla del Tres/Cinco)
MensajePublicitario& MensajePublicitario::operator=(const MensajePublicitario& other) {
    if (this != &other) {
        categoria = other.categoria;
        probabilidadVisualizacion = other.probabilidadVisualizacion;

        // Copia del char[]
        copyString(texto, other.texto, 501);
    }
    return *this;
}

// ----------------------------------------------------
// DEFINICIÓN DE GETTERS AUXILIARES
// ----------------------------------------------------

// Getter para obtener la categoría como cadena
const char* MensajePublicitario::getCategoriaStr() const {
    switch (categoria) {
    case AAA: return "AAA";
    case B: return "B";
    case C: return "C";
    default: return "N/A";
    }
}
