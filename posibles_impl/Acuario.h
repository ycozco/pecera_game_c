#ifndef ACUARIO_H
#define ACUARIO_H

#include "Pez.h"
#include <vector>
#include <string>
#include <mutex>

class Acuario {
private:
    std::vector<Pez> peces;
    double temperatura;
    double ph;
    double salinidad;
    std::mutex acuarioMutex;

public:
    Acuario();
    void agregarPez(const Pez& pez);
    void ajustarTemperatura(double temperatura);
    void ajustarPH(double ph);
    void ajustarSalinidad(double salinidad);
    std::string obtenerInformacion() const;
    Acuario clonar() const;
};

#endif // ACUARIO_H
