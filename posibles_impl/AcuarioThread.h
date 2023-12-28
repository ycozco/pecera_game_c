#ifndef ACUARIO_THREAD_H
#define ACUARIO_THREAD_H

#include <QThread>
#include <mutex>
#include "Pez.h"
#include "Acuario.h"           // 
#include "BaseDatosAcuario.h"  // 

class AcuarioThread : public QThread {
    Q_OBJECT

private:
    Acuario* acuario;
    std::mutex& acuarioMutex;
    BaseDatosAcuario* baseDatos;
    double intensidadIluminacion;
    bool continuarEjecucion;

signals:
    void actividadRegistrada(const std::string& actividad);

public:
    explicit AcuarioThread(Acuario* acuario, std::mutex& acuarioMutex, BaseDatosAcuario* baseDatos);
    void run() override;

    void generarEventoAleatorio();
    void ajustarIluminacion(double intensidad);
    void simularCicloDiaNoche();
    void registrarActividad(const std::string& actividad);

    void detenerEjecucion(); // Para detener el hilo de manera segura.
};

#endif // ACUARIO_THREAD_H
