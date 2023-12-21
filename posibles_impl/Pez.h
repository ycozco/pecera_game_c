#ifndef PEZ_H
#define PEZ_H

#include <string>
#include <sstream>

class Pez {
private:
    std::string especie;
    std::string alimentacion;
    double temperaturaIdeal;
    double phIdeal;
    double salinidadIdeal;
    double tamañoMaximo;
    std::string habitatNatural;

public:
    Pez(std::string especie, std::string alimentacion, double temp, double ph, double salinidad, double tamaño, std::string habitat);

    std::string obtenerInformacion() const;
};

#endif // PEZ_H
