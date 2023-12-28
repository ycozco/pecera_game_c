#include "AcuarioThread.h"
#include <random>
#include <chrono>
#include <iostream>

AcuarioThread::AcuarioThread(Acuario* acuario, std::mutex& acuarioMutex, BaseDatosAcuario* baseDatos)
    : acuario(acuario), acuarioMutex(acuarioMutex), baseDatos(baseDatos), intensidadIluminacion(0.5), continuarEjecucion(true) {}

void AcuarioThread::run() {
    while (continuarEjecucion) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Espera para reducir la carga del procesador.

        generarEventoAleatorio();
        simularCicloDiaNoche();

        {
            std::lock_guard<std::mutex> guard(acuarioMutex);
            // Lógica para monitorear y ajustar condiciones del acuario.
            if (acuario->necesitaAjusteTemperatura()) {
                acuario->ajustarTemperatura(acuario->getTemperaturaDeseada());
                registrarActividad("Ajuste automático de la temperatura realizado.");
            }

            // Lógica para monitorear y ajustar condiciones del acuario.
            if (acuario->necesitaAjustePH()) {
                acuario->ajustarPH(acuario->getPHDeseado());
                registrarActividad("Ajuste automático del pH realizado.");
            }
            if (acuario->necesitaAjusteSalinidad()) {
                acuario->ajustarSalinidad(acuario->getSalinidadDeseada());
                registrarActividad("Ajuste automático de la salinidad realizado.");
            }
        }
        // Otras operaciones 
    }
}

void AcuarioThread::generarEventoAleatorio() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    int evento = distrib(gen);
    if (evento <= 10) { // 10% de probabilidad de un evento
        std::string actividad = "Evento aleatorio ocurrido en el acuario.";
        registrarActividad(actividad);
    }
}

void AcuarioThread::ajustarIluminacion(double intensidad) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    intensidadIluminacion = intensidad;
    std::cout << "La intensidad de la iluminación ha sido ajustada a " << intensidad << std::endl;
    registrarActividad("Ajuste de iluminación a " + std::to_string(intensidad));
}

void AcuarioThread::simularCicloDiaNoche() {
    using std::chrono::system_clock;
    auto now = system_clock::to_time_t(system_clock::now());
    std::tm* now_tm = std::localtime(&now);

    if (now_tm->tm_hour >= 6 && now_tm->tm_hour < 18) {
        ajustarIluminacion(1.0); // Día
    } else {
        ajustarIluminacion(0.1); // Noche
    }
}

void AcuarioThread::registrarActividad(const std::string& actividad) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    emit actividadRegistrada(actividad);
}

void AcuarioThread::detenerEjecucion() {
    continuarEjecucion = false;
}
