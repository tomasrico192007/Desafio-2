#ifndef CREDITO_H
#define CREDITO_H

#include <iostream>

// Enumeración para representar los tipos de crédito (Productor, Músico, Compositor)
enum TipoCredito {
    PRODUCTOR,
    MUSICO,
    COMPOSITOR,
    DESCONOCIDO
};

class Credito {
private:
    char nombre[50];
    char apellidos[50];
    char codigoAfiliacion[11]; // 10 caracteres + '\0'
    TipoCredito tipo;

    // DECLARACIÓN de la función auxiliar. La implementación va en Credito.cpp
    void copyString(char* dest, const char* src, int maxLen);

public:
    // ----------------------------------------------------
    // DECLARACIONES DE REGLA DEL TRES/CINCO
    // ----------------------------------------------------

    // Constructor principal
    Credito(const char* n, const char* a, const char* cod, TipoCredito t);

    // Constructor de copia
    Credito(const Credito& other);

    // Operador de asignación (=)
    Credito& operator=(const Credito& other);

    // Destructor
    ~Credito();

    // ----------------------------------------------------
    // DECLARACIONES DE GETTERS (Implementaciones simples en línea)
    // ----------------------------------------------------

    // Dejamos estos Getters simples en línea para eficiencia (código de rango medio aceptable)
    const char* getNombre() const { return nombre; }
    const char* getApellidos() const { return apellidos; }
    const char* getCodigoAfiliacion() const { return codigoAfiliacion; }
    TipoCredito getTipo() const { return tipo; }

    // DECLARACIÓN del Getter complejo. La implementación va en Credito.cpp
    const char* getTipoStr() const;
};

#endif // CREDITO_H
