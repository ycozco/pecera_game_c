#ifndef BASEDATOSACUARIO_H
#define BASEDATOSACUARIO_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <mutex>
#include "Pez.h"
#include "Acuario.h"
#include "AcuarioThread.h"
class BaseDatosAcuario {
private:
    static BaseDatosAcuario* instance;
    QSqlDatabase db;
    static std::mutex dbMutex;

    // Constructor privado que recibe una conexión a la base de datos
    BaseDatosAcuario(QSqlDatabase db);

public:
    // No permitir copia ni asignación
    BaseDatosAcuario(const BaseDatosAcuario&) = delete;
    BaseDatosAcuario& operator=(const BaseDatosAcuario&) = delete;

    // Método para obtener la instancia de la base de datos
    static BaseDatosAcuario* getInstance();

    // Destructor
    ~BaseDatosAcuario();

    // Métodos para trabajar con la base de datos
    bool insertarPez(const Pez& pez);
    void registrarEnBaseDatos(const std::string& actividad);

    bool actualizarDetallesPez(int pezId, const std::string& detalles);
    std::string obtenerDetallesPez(int pezId);
    bool eliminarPez(int pezId);
};

#endif // BASEDATOSACUARIO_H
