#include "Acuario.h"

Acuario::Acuario() : temperatura(0.0), ph(7.0), salinidad(0.0) {}

void Acuario::agregarPez(const Pez& pez) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    peces.push_back(pez);
}

void Acuario::ajustarTemperatura(double temp) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    temperatura = temp;
}

void Acuario::ajustarPH(double pH) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    ph = pH;
}

void Acuario::ajustarSalinidad(double sal) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    salinidad = sal;
}

std::string Acuario::obtenerInformacion() const {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    std::stringstream info;
    info << "Temperatura: " << temperatura << ", PH: " << ph << ", Salinidad: " << salinidad;
    return info.str();
}

Acuario Acuario::clonar() const {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    Acuario clon;
    clon.peces = this->peces;
    clon.temperatura = this->temperatura;
    clon.ph = this->ph;
    clon.salinidad = this->salinidad;
    return clon;
}
