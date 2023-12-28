#include "Pez.h"
#include "Acuario.h"
#include "BaseDatosAcuario.h"
#include <iostream>
#include <sstream>
#include <mutex>

// Constructor predeterminado
Acuario::Acuario() : temperatura(25.0), pH(7.0), salinidad(30.0) {
    // Inicializa los valores predeterminados
}

// Constructor de copia
Acuario::Acuario(const Acuario& other) {
    std::lock_guard<std::mutex> lock(other.mutexAcuario);
    temperatura = other.temperatura;
    pH = other.pH;
    salinidad = other.salinidad;
    for (const auto& pez : other.peces) {
        peces.push_back(std::make_unique<Pez>(*pez));
    }
}

// Operador de asignación de copia
Acuario& Acuario::operator=(const Acuario& other) {
    if (this != &other) {
        std::unique_lock<std::mutex> lockThis(mutexAcuario);
        std::unique_lock<std::mutex> lockOther(other.mutexAcuario);
        temperatura = other.temperatura;
        pH = other.pH;
        salinidad = other.salinidad;
        peces.clear();
        for (const auto& pez : other.peces) {
            peces.push_back(std::make_unique<Pez>(*pez));
        }
    }
    return *this;
}

// Método para agregar un pez al acuario
void Acuario::agregarPez(std::unique_ptr<Pez> pez) {
    std::lock_guard<std::mutex> lock(mutexAcuario);
    peces.push_back(std::move(pez)); // Utiliza std::move para mover el unique_ptr
}

// Método para ajustar la temperatura del acuario
void Acuario::ajustarTemperatura(double nuevaTemperatura) {
    std::lock_guard<std::mutex> lock(mutexAcuario);
    temperatura = nuevaTemperatura;
}

// Método para ajustar el pH del acuario
void Acuario::ajustarPh(double nuevoPh) {
    std::lock_guard<std::mutex> lock(mutexAcuario);
    pH = nuevoPh;
}

// Método para ajustar la salinidad del acuario
void Acuario::ajustarSalinidad(double nuevaSalinidad) {
    std::lock_guard<std::mutex> lock(mutexAcuario);
    salinidad = nuevaSalinidad
    ;
}

// Método para obtener información sobre el acuario y sus peces
std::string Acuario::obtenerInformacion() const {
    std::lock_guard<std::mutex> lock(mutexAcuario);

    std::stringstream info;
    info << "Información del Acuario:" << std::endl;
    info << "Temperatura: " << temperatura << " °C" << std::endl;
    info << "pH: " << pH << std::endl;
    info << "Salinidad: " << salinidad << " ppt" << std::endl;

    if (!peces.empty()) {
        info << "Peces en el Acuario:" << std::endl;
        for (const auto& pez : peces) {
            info << " - " << pez->getInfo() << std::endl;
        }
    } else {
        info << "No hay peces en el Acuario." << std::endl;
    }

    return info.str();
}
