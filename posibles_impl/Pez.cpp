#include "Pez.h"

Pez::Pez(std::string especie, std::string alimentacion, double temp, double ph, double salinidad, double tamaño, std::string habitat)
    : especie(especie), alimentacion(alimentacion), temperaturaIdeal(temp), phIdeal(ph), salinidadIdeal(salinidad), tamañoMaximo(tamaño), habitatNatural(habitat) {}

std::string Pez::obtenerInformacion() const {
    std::stringstream info;
    info << "Especie: " << especie << ", Alimentación: " << alimentacion
         << ", Temperatura Ideal: " << temperaturaIdeal << ", PH Ideal: " << phIdeal
         << ", Salinidad Ideal: " << salinidadIdeal << ", Tamaño Máximo: " << tamañoMaximo
         << ", Hábitat Natural: " << habitatNatural;
    return info.str();
}
