#include "Pez.h"
#include "Acuario.h"
#include "BaseDatosAcuario.h"
#include "AcuarioThread.h"

#include <thread>
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
            // Lógica para monitorear y ajustar las condiciones del acuario.
            if (acuario->necesitaAjusteTemperatura()) {
                acuario->ajustarTemperatura(acuario->obtenerTemperaturaDeseada());
                registrarActividad("Ajuste automático de temperatura realizado.");
            }

            // Lógica para monitorear y ajustar las condiciones del acuario.
            if (acuario->necesitaAjustePh()) {
                acuario->ajustarPh(acuario->obtenerPhDeseado());
                registrarActividad("Ajuste automático de pH realizado.");
            }
            if (acuario->necesitaAjusteSalinidad()) {
                acuario->ajustarSalinidad(acuario->obtenerSalinidadDeseada());
                registrarActividad("Ajuste automático de salinidad realizado.");
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
    if (evento <= 10) { // Probabilidad del 10% de un evento
        std::string actividad = "Evento aleatorio ocurrió en el acuario.";
        registrarActividad(actividad);
    }
}

void AcuarioThread::ajustarIluminacion(double intensidad) {
    std::lock_guard<std::mutex> guard(acuarioMutex);
    intensidadIluminacion = intensidad;
    std::cout << "Intensidad de iluminación ajustada a " << intensidad << std::endl;
    registrarActividad("Iluminación ajustada a " + std::to_string(intensidad));
}

void AcuarioThread::simularCicloDiaNoche() {
    using std::chrono::system_clock;
    auto ahora = system_clock::to_time_t(system_clock::now());
    std::tm* ahora_tm = std::localtime(&ahora);

    if (ahora_tm->tm_hour >= 6 && ahora_tm->tm_hour < 18) {
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
