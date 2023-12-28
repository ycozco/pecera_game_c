#ifndef ACUARIO_H
#define ACUARIO_H

#include "Pez.h"
#include "BaseDatosAcuario.h"
#include <mutex>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Acuario {
public:
    Acuario(); // Constructor predeterminado
    Acuario(const Acuario& other); // Constructor de copia
    Acuario& operator=(const Acuario& other); // Operador de asignación de copia
    void agregarPez(std::unique_ptr<Pez> pez); // Método para agregar un pez al acuario
    void ajustarTemperatura(double nuevaTemperatura); // Método para ajustar la temperatura del acuario
    void ajustarPh(double nuevoPh); // Método para ajustar el pH del acuario
    void ajustarSalinidad(double nuevaSalinidad); // Método para ajustar la salinidad del acuario
    std::string obtenerInformacion() const; // Método para obtener información sobre el acuario y sus peces
    Acuario clonar() const; // Método clonar
    bool necesitaAjusteTemperatura() const; // Método público para determinar si se necesita ajustar la temperatura
    double obtenerTemperaturaDeseada() const; // Método público para obtener la temperatura deseada
    bool necesitaAjustePh() const; // Método público para determinar si se necesita ajustar el pH
    double obtenerPhDeseado() const; // Método público para obtener el pH deseado
    bool necesitaAjusteSalinidad() const; // Método público para determinar si se necesita ajustar la salinidad
    double obtenerSalinidadDeseada() const; // Método público para obtener la salinidad deseada
    double obtenerTemperatura() const; // Método público para obtener la temperatura
    double obtenerPh() const; // Método público para obtener el pH
    double obtenerSalinidad() const; // Método público para obtener la salinidad
    std::vector<std::unique_ptr<Pez>> obtenerPeces() const; // Método público para obtener los peces

private:
    mutable std::mutex mutexAcuario; // Mutex para proteger los datos del acuario
    double temperatura; // Temperatura del acuario en grados Celsius
    double pH; // pH del acuario
    double salinidad; // Salinidad del acuario en ppt
    std::vector<std::unique_ptr<Pez>> peces; // Peces en el acuario
};

#endif // ACUARIO_H
