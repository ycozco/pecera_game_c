#ifndef PEZ_H
#define PEZ_H

#include <string>
#include <map>
#include <memory>
#include "Acuario.h"

class FishCharacteristics {
public:
    std::string species;
    std::string feeding;
    double idealTemperature;
    double idealPh;
    double idealSalinity;
    double maxSize;
    std::string naturalHabitat;
    double requiredOxygenation;

    FishCharacteristics(std::string species, std::string feeding, double temp, double ph, 
                        double salinity, double size, std::string habitat, double oxygenation);
};

class Pez {
private:
    double currentSize;
    std::string color;
    std::shared_ptr<FishCharacteristics> characteristics;

    static std::map<std::string, std::shared_ptr<FishCharacteristics>> flyweights;

public:
    Pez(double size, std::string color, std::string species, std::string feeding, double temp, 
        double ph, double salinity, double max_size, std::string habitat, double oxygenation);

    static std::shared_ptr<FishCharacteristics> getFlyweight(std::string species, std::string feeding, 
                                                             double temp, double ph, double salinity, 
                                                             double size, std::string habitat, double oxygenation);

    void swim() const;
    std::string getInfo() const;
    bool isCompatibleWithAquarium(const Acuario& aquarium) const;

    std::unique_ptr<Pez> clone() const;
    // Setters and Getters
    void setCurrentSize(double size);
    double getCurrentSize() const;
    void setColor(const std::string& color);
    std::string getColor() const;
    void setSpecies(const std::string& species);
    std::string getSpecies() const;
    void setFeeding(const std::string& feeding);
    std::string getFeeding() const;
    void setIdealTemperature(double temp);
    double getIdealTemperature() const;
    void setIdealPh(double ph);
    double getIdealPh() const;
    void setIdealSalinity(double salinity);
    double getIdealSalinity() const;
    void setMaxSize(double maxSize);
    double getMaxSize() const;
    void setNaturalHabitat(const std::string& habitat);
    std::string getNaturalHabitat() const;
    void setRequiredOxygenation(double oxygenation);
    double getRequiredOxygenation() const;
};

#endif // PEZ_H
