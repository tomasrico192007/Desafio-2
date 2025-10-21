#include "Credito.h"
#include <iostream> // Solo para posible depuración, no estrictamente necesario

// Implementación de la función auxiliar de copiado de cadenas
void Credito::copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    // Copia hasta el terminador nulo o hasta el límite (maxLen - 1)
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Asegurar el nulo terminador
}

// ----------------------------------------------------
// DEFINICIÓN DE CONSTRUCTORES Y OPERADORES
// ----------------------------------------------------

// Constructor principal
Credito::Credito(const char* n, const char* a, const char* cod, TipoCredito t) : tipo(t) {
    copyString(nombre, n, 50);
    copyString(apellidos, a, 50);
    copyString(codigoAfiliacion, cod, 11);
}

// Constructor de copia (Regla del Tres/Cinco)
Credito::Credito(const Credito& other) {
    // Reutilizamos el operador de asignación para la lógica de copia profunda
    *this = other;
}

// Operador de asignación (=) (Regla del Tres/Cinco)
Credito& Credito::operator=(const Credito& other) {
    if (this != &other) {
        tipo = other.tipo;

        // Copia manual de los campos de cadena de caracteres (copia profunda de char[])
        copyString(nombre, other.nombre, 50);
        copyString(apellidos, other.apellidos, 50);
        copyString(codigoAfiliacion, other.codigoAfiliacion, 11);
    }
    return *this;
}

// Destructor (simple, no hay punteros internos que liberar)
Credito::~Credito() {
    // El compilador se encarga de liberar los char[] automáticamente
}

// ----------------------------------------------------
// DEFINICIÓN DE GETTERS AUXILIARES
// ----------------------------------------------------

// Getter para obtener el tipo de crédito como cadena
const char* Credito::getTipoStr() const {
    switch (tipo) {
    case PRODUCTOR: return "Productor";
    case MUSICO: return "Musico";
    case COMPOSITOR: return "Compositor";
    default: return "Desconocido";
    }
}
