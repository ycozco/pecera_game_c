#include "Acuario.h"
#include <sstream>

// Constructor de la clase Acuario
Acuario::Acuario() : temperatura(25.0), ph(7.0), salinidad(30.0) {
  // Inicializa los valores predeterminados de temperatura, pH y salinidad
}

// Método para agregar un pez al acuario
void Acuario::agregarPez(std::unique_ptr<Pez> pez) {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);
  peces.push_back(std::move(pez));
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
      info << " - " << pez->obtenerInformacion() << std::endl;
    }
  } else {
    info << "No hay peces en el Acuario." << std::endl;
  }

  return info.str();
}

// Método para clonar el acuario (patrón Prototype)
Acuario Acuario::clonar() const {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);

  Acuario copiaAcuario;
  copiaAcuario.temperatura = temperatura;
  copiaAcuario.ph = ph;
  copiaAcuario.salinidad = salinidad;

  // Clonar los peces
  for (const auto& pez : peces) {
    copiaAcuario.agregarPez(std::make_unique<Pez>(*pez));
  }

  return copiaAcuario;
}

// Sobrecarga del operador de asignación
Acuario& Acuario::operator=(const Acuario& otro) {
  if (this == &otro) {
    return *this;  // Comprobar autoasignación
  }

  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);

  // Clonar los peces
  peces = otro.peces;

  return *this;
}

// Modificación para evitar la fuga de memoria
void Acuario::agregarPez(std::unique_ptr<Pez> pez) {
  // Utiliza un bloque de bloqueo para evitar problemas de concurrencia
  std::lock_guard<std::mutex> lock(acuarioMutex);

  // Clonar el pez para evitar la fuga de memoria
  peces.push_back(std::make_unique<Pez>(*pez));
}
