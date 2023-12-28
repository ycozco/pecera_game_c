#include "Pez.h"
#include "BaseDatosAcuario.h"
#include "AcuarioThread.h" // Nuevo archivo para manejar operaciones en hilos
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "Acuario.h"

int main() {
    BaseDatosAcuario* bd = BaseDatosAcuario::getInstance();

    // Ejemplo de inserciones múltiples en hilos
    std::vector<std::thread> hilos;
    for (int i = 0; i < 10; i++) {
        hilos.push_back(std::thread([i, &bd]() {
            Pez pez("Especie" + std::to_string(i), "Alimentacion" + std::to_string(i), 20.0 + i, 7.0 + i, 1.0 + i, 5.0 + i, "Habitat" + std::to_string(i), 5.0 + i);
            bd->insertarPez(pez);
            bd->registrarEnBaseDatos("Inserción del pez: " + pez.getInfo());
        }));
    }

    // Esperar a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Leer detalles de los peces insertados
    for (int i = 1; i <= 10; i++) {
        std::string detallesPez = bd->obtenerDetallesPez(i);
        std::cout << "Detalles del pez con ID " << i << ": " << detallesPez << std::endl;
    }

    return 0;
}

// my ip: 172.203.43.113
