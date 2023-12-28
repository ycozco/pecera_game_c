#include "Pez.h"
#include "Acuario.h"
#include <sstream>

Pez::Pez(std::string species, std::string feeding, double temp, double ph, double salinity, double maxSize, std::string habitat, double oxygenation)
    : species(species), feeding(feeding), idealTemperature(temp), idealPh(ph), idealSalinity(salinity), maxSize(maxSize), naturalHabitat(habitat), requiredOxygenation(oxygenation) {}

void Pez::setSpecies(const std::string& species) {
    this->species = species;
}

std::string Pez::getSpecies() const {
    return species;
}

void Pez::setFeeding(const std::string& feeding) {
    this->feeding = feeding;
}

std::string Pez::getFeeding() const {
    return feeding;
}

void Pez::setIdealTemperature(double temp) {
    idealTemperature = temp;
}

double Pez::getIdealTemperature() const {
    return idealTemperature;
}

void Pez::setIdealPh(double ph) {
    idealPh = ph;
}

double Pez::getIdealPh() const {
    return idealPh;
}

void Pez::setIdealSalinity(double salinity) {
    idealSalinity = salinity;
}

double Pez::getIdealSalinity() const {
    return idealSalinity;
}

void Pez::setMaxSize(double maxSize) {
    this->maxSize = maxSize;
}

double Pez::getMaxSize() const {
    return maxSize;
}

void Pez::setNaturalHabitat(const std::string& habitat) {
    naturalHabitat = habitat;
}

std::string Pez::getNaturalHabitat() const {
    return naturalHabitat;
}

void Pez::setRequiredOxygenation(double oxygenation) {
    requiredOxygenation = oxygenation;
}

double Pez::getRequiredOxygenation() const {
    return requiredOxygenation;
}

void Pez::swim() const {
    // Implementation of the swim method
}

std::string Pez::getInfo() const {
    std::stringstream info;
    info << "Species: " << species << ", Feeding: " << feeding
         << ", Ideal Temperature: " << idealTemperature << ", Ideal pH: " << idealPh
         << ", Ideal Salinity: " << idealSalinity << ", Max Size: " << maxSize
         << ", Natural Habitat: " << naturalHabitat << ", Required Oxygenation: " << requiredOxygenation;
    return info.str();
}

bool Pez::operator==(const Pez& other) const {
    return species == other.species && feeding == other.feeding &&
           idealTemperature == other.idealTemperature && idealPh == other.idealPh &&
           idealSalinity == other.idealSalinity && maxSize == other.maxSize &&
           naturalHabitat == other.naturalHabitat && requiredOxygenation == other.requiredOxygenation;
}

bool Pez::esCompatibleConAcuario(const Acuario& acuario) const {
    // Lógica para determinar si el pez es compatible con el acuario
    // Ejemplo de lógica simplificada: verifica la temperatura, el pH y la salinidad
    return (acuario.getTemperatura() >= idealTemperature && acuario.getTemperatura() <= (idealTemperature + 2.0)) &&
           (acuario.getPH() >= idealPh && acuario.getPH() <= (idealPh + 0.2)) &&
           (acuario.getSalinidad() >= idealSalinity && acuario.getSalinidad() <= (idealSalinity + 0.5));
}
