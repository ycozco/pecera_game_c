#ifndef BASEDATOSACUARIO_H
#define BASEDATOSACUARIO_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <mutex>
#include "Pez.h"

class BaseDatosAcuario {
private:
    static BaseDatosAcuario* instance;
    QSqlDatabase db;
    std::mutex dbMutex;

    BaseDatosAcuario();  // Constructor privado
    ~BaseDatosAcuario(); // Destructor privado

public:
    BaseDatosAcuario(const BaseDatosAcuario&) = delete;            // No permitir copia
    BaseDatosAcuario& operator=(const BaseDatosAcuario&) = delete; // No permitir asignación

    static BaseDatosAcuario* getInstance();  // Método para obtener la instancia
    bool insertarPez(const Pez& pez);
    void registrarEnBaseDatos(const std::string& actividad);

    // Métodos para manejar información detallada sobre peces
    bool actualizarDetallesPez(int pezId, const std::string& detalles);
    std::string obtenerDetallesPez(int pezId);
    bool eliminarPez(int pezId);

    // Otros métodos relacionados con la base de datos...
};

#endif // BASEDATOSACUARIO_H
