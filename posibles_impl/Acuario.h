#ifndef ACUARIO_H
#define ACUARIO_H

#include "Pez.h"
#include <vector>
#include <memory>
#include <mutex>

class Acuario {
private:
    std::vector<std::unique_ptr<Pez>> peces;
    double temperatura;
    double ph;
    double salinidad;
    std::mutex acuarioMutex;

public:
    Acuario();
    void agregarPez(std::unique_ptr<Pez> pez);
    void ajustarTemperatura(double temperatura);
    void ajustarPH(double ph);
    void ajustarSalinidad(double salinidad);
    std::string obtenerInformacion() const;
    Acuario clonar() const;  // Para el patrón Prototype

    // Sobrecarga de operadores
    Acuario& operator=(const Acuario& otro);

    // Destructor
    ~Acuario() = default;
};

#endif // ACUARIO_H
