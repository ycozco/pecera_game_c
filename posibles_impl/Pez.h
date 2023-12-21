#ifndef PEZ_H
#define PEZ_H

#include <string>

class Pez {
private:
    std::string especie;
    std::string alimentacion;
    double temperaturaIdeal;
    double phIdeal;
    double salinidadIdeal;
    double tamañoMaximo;
    std::string habitatNatural;
    double oxigenacionNecesaria;

public:
    // Constructor de la clase Pez
    Pez(std::string especie, std::string alimentacion, double temp, double ph, double salinidad, double tamaño, std::string habitat, double oxigenacion)
        : especie(especie), alimentacion(alimentacion), temperaturaIdeal(temp), phIdeal(ph), salinidadIdeal(salinidad), tamañoMaximo(tamaño), habitatNatural(habitat), oxigenacionNecesaria(oxigenacion) {
    }

    // Getter y Setter para la especie del pez
    void setEspecie(const std::string& especie) { this->especie = especie; }
    std::string getEspecie() const { return especie; }

    // Otros setters y getters para los atributos del pez
    void setAlimentacion(const std::string& alimentacion) { this->alimentacion = alimentacion; }
    std::string getAlimentacion() const { return alimentacion; }

    void setTemperaturaIdeal(double temp) { temperaturaIdeal = temp; }
    double getTemperaturaIdeal() const { return temperaturaIdeal; }

    void setPhIdeal(double ph) { phIdeal = ph; }
    double getPhIdeal() const { return phIdeal; }

    void setSalinidadIdeal(double salinidad) { salinidadIdeal = salinidad; }
    double getSalinidadIdeal() const { return salinidadIdeal; }

    void setTamañoMaximo(double tamaño) { tamañoMaximo = tamaño; }
    double getTamañoMaximo() const { return tamañoMaximo; }

    void setHabitatNatural(const std::string& habitat) { habitatNatural = habitat; }
    std::string getHabitatNatural() const { return habitatNatural; }

    void setOxigenacionNecesaria(double oxigenacion) { oxigenacionNecesaria = oxigenacion; }
    double getOxigenacionNecesaria() const { return oxigenacionNecesaria; }

    // Destructor virtual para herencia
    virtual ~Pez() = default;

    // Sobrecarga del operador de igualdad
    bool operator==(const Pez& otro) const {
        return especie == otro.especie && alimentacion == otro.alimentacion && temperaturaIdeal == otro.temperaturaIdeal &&
               phIdeal == otro.phIdeal && salinidadIdeal == otro.salinidadIdeal && tamañoMaximo == otro.tamañoMaximo &&
               habitatNatural == otro.habitatNatural && oxigenacionNecesaria == otro.oxigenacionNecesaria;
    }

    // Método adicional para que el pez nade
    virtual void nadar() const {
        // Implementación de la función de nadar
    }

    // Método para obtener información del pez
    virtual std::string obtenerInformacion() const {
        // Implementación de la función para obtener información
        return "Especie: " + especie + ", Alimentación: " + alimentacion + ", Tamaño Máximo: " + std::to_string(tamañoMaximo);
    }
};

#endif // PEZ_H
