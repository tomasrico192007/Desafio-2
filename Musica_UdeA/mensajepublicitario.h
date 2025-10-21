#ifndef MENSAJEPUBLICITARIO_H
#define MENSAJEPUBLICITARIO_H

#include <iostream>

// Enumeración para representar las categorías de los mensajes (A, B, C)
// Se menciona en el documento que las categorías tienen diferentes prioridades.
enum CategoriaMensaje {
    AAA,
    B,
    C,
    SIN_CATEGORIA
};

class MensajePublicitario {
private:
    char texto[501]; // Hasta 500 caracteres + '\0'
    CategoriaMensaje categoria;
    double probabilidadVisualizacion; // Probabilidad de visualización calculada

    // Función auxiliar para copiar cadenas (definida en el .cpp)
    void copyString(char* dest, const char* src, int maxLen);

public:
    // Constructor
    MensajePublicitario(const char* txt, CategoriaMensaje cat);

    // ----------------------------------------------------
    // REGLA DE LOS TRES/CINCO: Gestión de Copia
    // ----------------------------------------------------

    // Destructor (simple, no hay punteros internos)
    ~MensajePublicitario();

    // Constructor de copia
    MensajePublicitario(const MensajePublicitario& other);

    // Operador de asignación (=)
    MensajePublicitario& operator=(const MensajePublicitario& other);

    // ----------------------------------------------------
    // Getters y Lógica
    // ----------------------------------------------------
    const char* getTexto() const { return texto; }
    CategoriaMensaje getCategoria() const { return categoria; }
    double getProbabilidadVisualizacion() const { return probabilidadVisualizacion; }

    // Método para calcular la probabilidad inicial basado en la categoría
    void calcularProbabilidadBase(double probC);

    // Método para obtener la categoría como cadena (ej. "AAA", "B", "C")
    const char* getCategoriaStr() const;
};

#endif // MENSAJEPUBLICITARIO_H
