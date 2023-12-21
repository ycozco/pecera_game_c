#include "Pez.h"
#include <iostream>  // Agregar inclusión para std::cout

// Constructor de la clase Pez
Pez::Pez(std::string especie, std::string alimentacion, double temp, double ph, double salinidad, double tamaño, std::string habitat, double oxigenacion)
    : especie(especie), alimentacion(alimentacion), temperaturaIdeal(temp), phIdeal(ph), salinidadIdeal(salinidad), tamañoMaximo(tamaño), habitatNatural(habitat), oxigenacionNecesaria(oxigenacion) {}

// Implementación del método para obtener información del pez
std::string Pez::obtenerInformacion() const {
    std::stringstream info;
    info << "Especie: " << especie << ", Alimentación: " << alimentacion
         << ", Temperatura Ideal: " << temperaturaIdeal << ", pH Ideal: " << phIdeal
         << ", Salinidad Ideal: " << salinidadIdeal << ", Tamaño Máximo: " << tamañoMaximo
         << ", Hábitat Natural: " << habitatNatural << ", Oxigenación Necesaria: " << oxigenacionNecesaria;
    return info.str();
}

// Implementación del método para clonar un pez (patrón Prototype)
Pez* Pez::clonar() const {
    return new Pez(*this);
}

// Implementación del método para que el pez nade
void Pez::nadar() const {
    std::cout << "El pez " << especie << " está nadando." << std::endl;
}

// Implementaciones de setters y getters
void Pez::setEspecie(const std::string& especie) {
    this->especie = especie;
}

std::string Pez::getEspecie() const {
    return especie;
}

void Pez::setAlimentacion(const std::string& alimentacion) {
    this->alimentacion = alimentacion;
}

std::string Pez::getAlimentacion() const {
    return alimentacion;
}

// Implementa setters y getters para otros atributos aquí
void Pez::setTemperaturaIdeal(double temp) {
    temperaturaIdeal = temp;
}

double Pez::getTemperaturaIdeal() const {
    return temperaturaIdeal;
}

void Pez::setPhIdeal(double ph) {
    phIdeal = ph;
}

double Pez::getPhIdeal() const {
    return phIdeal;
}

void Pez::setSalinidadIdeal(double salinidad) {
    salinidadIdeal = salinidad;
}

double Pez::getSalinidadIdeal() const {
    return salinidadIdeal;
}

void Pez::setTamañoMaximo(double tamaño) {
    tamañoMaximo = tamaño;
}

double Pez::getTamañoMaximo() const {
    return tamañoMaximo;
}

void Pez::setHabitatNatural(const std::string& habitat) {
    habitatNatural = habitat;
}

std::string Pez::getHabitatNatural() const {
    return habitatNatural;
}

void Pez::setOxigenacionNecesaria(double oxigenacion) {
    oxigenacionNecesaria = oxigenacion;
}

double Pez::getOxigenacionNecesaria() const {
    return oxigenacionNecesaria;
}

// Sobrecarga del operador de igualdad
bool Pez::operator==(const Pez& otro) const {
    return especie == otro.especie && alimentacion == otro.alimentacion &&
           temperaturaIdeal == otro.temperaturaIdeal && phIdeal == otro.phIdeal &&
           salinidadIdeal == otro.salinidadIdeal && tamañoMaximo == otro.tamañoMaximo &&
           habitatNatural == otro.habitatNatural && oxigenacionNecesaria == otro.oxigenacionNecesaria;
}

// Sobrecarga del operador de desigualdad (!=)
bool Pez::operator!=(const Pez& otro) const {
    return !(*this == otro);
}
