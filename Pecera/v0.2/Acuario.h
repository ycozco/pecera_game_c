#ifndef ACUARIO_H
#define ACUARIO_H

#include <vector>
#include <memory>
#include <mutex>
class Pez; 
class Acuario {
private:
    std::vector<std::unique_ptr<Pez>> peces;
    double temperatura;
    double ph;
    double salinidad;
    mutable std::mutex acuarioMutex;

public:
    Acuario();
    void agregarPez(std::unique_ptr<Pez> pez);
    void ajustarTemperatura(double temperatura);
    void ajustarPH(double ph);
    void ajustarSalinidad(double salinidad);
    std::string obtenerInformacion() const;
    Acuario clonar() const;

    // Métodos adicionales
    bool necesitaAjusteTemperatura() const;
    double getTemperaturaDeseada() const;
    bool necesitaAjustePH() const;
    double getPHDeseado() const;
    bool necesitaAjusteSalinidad() const;
    double getSalinidadDeseada() const;
    double getTemperatura() const;
    double getPH() const;
    double getSalinidad() const;
    // Sobrecarga de operadores
    Acuario& operator=(const Acuario& otro);

    // Destructor
    ~Acuario() = default;
    
    // Método para obtener una copia de los peces
    std::vector<std::unique_ptr<Pez>> obtenerPeces() const;
};
#endif // ACUARIO_H
