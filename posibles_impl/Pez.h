#ifndef PEZ_H
#define PEZ_H
#include "Acuario.h"
#include <string>
#include <memory>
class Pez {
private:
    std::string species;
    std::string feeding;
    double idealTemperature;
    double idealPh;
    double idealSalinity;
    double maxSize;
    std::string naturalHabitat;
    double requiredOxygenation;

public:
    // Constructor
    Pez(std::string species, std::string feeding, double temp, double ph, double salinity, double maxSize, std::string habitat, double oxygenation);

    // Destructor
    virtual ~Pez() = default;

    // Setters and Getters
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

    // Swim method
    virtual void swim() const;

    // Information method
    virtual std::string getInfo() const;

    // Equality operator
    bool operator==(const Pez& other) const;
    // Declaración del método esCompatibleConAcuario en la clase Pez
    bool esCompatibleConAcuario(const Acuario& acuario) const;
    std::unique_ptr<Pez> clonar() const;
};

#endif // PEZ_H
