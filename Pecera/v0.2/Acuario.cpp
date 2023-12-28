#include "Acuario.h"
#include "Pez.h"
#include <sstream>

// Constructor de la clase Acuario
Acuario::Acuario() : temperatura(25.0), ph(7.0), salinidad(30.0) {
  // Inicializa los valores predeterminados de temperatura, pH y salinidad
}

// Método para agregar un pez al acuario
void Acuario::agregarPez(std::unique_ptr<Pez> pez) {
    std::lock_guard<std::mutex> lock(acuarioMutex);
    peces.push_back(std::move(pez)); // Utiliza std::move para mover el unique_ptr
}


// Método para ajustar la temperatura del acuario
void Acuario::ajustarTemperatura(double nuevaTemperatura) {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);
  temperatura = nuevaTemperatura;
}

// Método para ajustar el pH del acuario
void Acuario::ajustarPH(double nuevoPH) {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);
  ph = nuevoPH;
}

// Método para ajustar la salinidad del acuario
void Acuario::ajustarSalinidad(double nuevaSalinidad) {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);
  salinidad = nuevaSalinidad;
}

// Método para obtener información del acuario y sus peces
std::string Acuario::obtenerInformacion() const {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);

  std::stringstream info;
  info << "Información del Acuario:" << std::endl;
  info << "Temperatura: " << temperatura << " °C" << std::endl;
  info << "pH: " << ph << std::endl;
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

// Sobrecarga del operador de asignación
Acuario& Acuario::operator=(const Acuario& otro) {

  return *this;
}
std::vector<std::unique_ptr<Pez>> Acuario::obtenerPeces() const {
    std::lock_guard<std::mutex> lock(acuarioMutex);
    std::vector<std::unique_ptr<Pez>> copiaPeces;
    for (const auto& pez : peces) {
        copiaPeces.push_back(std::make_unique<Pez>(*pez)); // Copia cada Pez en un nuevo unique_ptr
    }
    return copiaPeces;
}


// Métodos adicionales para ajuste de parámetros

bool Acuario::necesitaAjusteTemperatura() const {
    // Ejemplo de lógica simplificada: ajustar si la temperatura es demasiado alta o baja
    return temperatura > getTemperaturaDeseada() + 2.0 || temperatura < getTemperaturaDeseada() - 2.0;
}

double Acuario::getTemperaturaDeseada() const {
    // Ejemplo: la temperatura deseada es de 25.0 °C
    return 25.0;
}

bool Acuario::necesitaAjustePH() const {
    // Ejemplo de lógica simplificada: ajustar si el pH es demasiado ácido o básico
    return ph > getPHDeseado() + 0.2 || ph < getPHDeseado() - 0.2;
}

double Acuario::getPHDeseado() const {
    // Ejemplo: el pH deseado es de 7.0
    return 7.0;
}

bool Acuario::necesitaAjusteSalinidad() const {
    // Ejemplo de lógica simplificada: ajustar si la salinidad es demasiado alta o baja
    return salinidad > getSalinidadDeseada() + 5.0 || salinidad < getSalinidadDeseada() - 5.0;
}

double Acuario::getSalinidadDeseada() const {
    // Ejemplo: la salinidad deseada es de 30.0 ppt
    return 30.0;
}

double Acuario::getTemperatura() const {
    return temperatura;
}

double Acuario::getPH() const {
    return ph;
}

double Acuario::getSalinidad() const {
    return salinidad;
}
