#include "Pez.h"
#include "Acuario.h"
#include <sstream>

// Definición del mapa estático para el patrón Flyweight
std::map<std::string, std::shared_ptr<FishCharacteristics>> Pez::flyweights;

// Constructor de la clase Pez
Pez::Pez(double size, std::string color, std::string species, std::string feeding, double temp, 
         double ph, double salinity, double maxSize, std::string habitat, double oxygenation)
    : currentSize(size), color(color) {
    characteristics = getFlyweight(species, feeding, temp, ph, salinity, maxSize, habitat, oxygenation);
}

// Método estático getFlyweight para el patrón Flyweight
std::shared_ptr<FishCharacteristics> Pez::getFlyweight(std::string species, std::string feeding, 
                                                       double temp, double ph, double salinity, 
                                                       double size, std::string habitat, double oxygenation) {
    std::string key = species + feeding;
    auto it = flyweights.find(key);
    if (it == flyweights.end()) {
        auto charac = std::make_shared<FishCharacteristics>(species, feeding, temp, ph, salinity, size, habitat, oxygenation);
        flyweights[key] = charac;
        return charac;
    }
    return it->second;
}

// Método para obtener información del pez
std::string Pez::getInfo() const {
    std::stringstream info;
    info << "Species: " << characteristics->species << ", Feeding: " << characteristics->feeding
         << ", Ideal Temperature: " << characteristics->idealTemperature << ", Ideal pH: " << characteristics->idealPh
         << ", Ideal Salinity: " << characteristics->idealSalinity << ", Max Size: " << characteristics->maxSize
         << ", Natural Habitat: " << characteristics->naturalHabitat << ", Required Oxygenation: " << characteristics->requiredOxygenation;
    return info.str();
}

// Método para simular la natación del pez
void Pez::swim() const {
    // Implementación del método de natación
}

// Método para verificar si el pez es compatible con un acuario
bool Pez::isCompatibleWithAquarium(const Acuario& aquarium) const {
    return (aquarium.getTemperature() >= characteristics->idealTemperature && aquarium.getTemperature() <= (characteristics->idealTemperature + 2.0)) &&
           (aquarium.getPh() >= characteristics->idealPh && aquarium.getPh() <= (characteristics->idealPh + 0.2)) &&
           (aquarium.getSalinity() >= characteristics->idealSalinity && aquarium.getSalinity() <= (characteristics->idealSalinity + 0.5));
}

// Método para clonar un objeto Pez
std::unique_ptr<Pez> Pez::clone() const {
    return std::make_unique<Pez>(currentSize, color, characteristics->species, characteristics->feeding, characteristics->idealTemperature, characteristics->idealPh, characteristics->idealSalinity, characteristics->maxSize, characteristics->naturalHabitat, characteristics->requiredOxygenation);
}

// Implementación de setters y getters
void Pez::setCurrentSize(double size) {
    currentSize = size;
}

double Pez::getCurrentSize() const {
    return currentSize;
}

void Pez::setColor(const std::string& color) {
    this->color = color;
}

std::string Pez::getColor() const {
    return color;
}

void Pez::setSpecies(const std::string& species) {
    characteristics->species = species;
}

std::string Pez::getSpecies() const {
    return characteristics->species;
}

void Pez::setFeeding(const std::string& feeding) {
    characteristics->feeding = feeding;
}

std::string Pez::getFeeding() const {
    return characteristics->feeding;
}

void Pez::setIdealTemperature(double temp) {
    characteristics->idealTemperature = temp;
}

double Pez::getIdealTemperature() const {
    return characteristics->idealTemperature;
}

void Pez::setIdealPh(double ph) {
    characteristics->idealPh = ph;
}

double Pez::getIdealPh() const {
    return characteristics->idealPh;
}

void Pez::setIdealSalinity(double salinity) {
    characteristics->idealSalinity = salinity;
}

double Pez::getIdealSalinity() const {
    return characteristics->idealSalinity;
}

void Pez::setMaxSize(double maxSize) {
    characteristics->maxSize = maxSize;
}

double Pez::getMaxSize() const {
    return characteristics->maxSize;
}

void Pez::setNaturalHabitat(const std::string& habitat) {
    characteristics->naturalHabitat = habitat;
}

std::string Pez::getNaturalHabitat() const {
    return characteristics->naturalHabitat;
}

void Pez::setRequiredOxygenation(double oxygenation) {
    characteristics->requiredOxygenation = oxygenation;
}

double Pez::getRequiredOxygenation() const {
    return characteristics->requiredOxygenation;
}
