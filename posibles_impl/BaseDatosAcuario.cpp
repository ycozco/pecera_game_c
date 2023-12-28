#include "BaseDatosAcuario.h"
#include "Pez.h"
#include "Acuario.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

std::mutex BaseDatosAcuario::dbMutex;
BaseDatosAcuario* BaseDatosAcuario::instance = nullptr;

// Constructor privado
BaseDatosAcuario::BaseDatosAcuario(QSqlDatabase db) : db(db) {
    if (!db.isOpen()) {
        db.open();
    }
}

// Destructor
BaseDatosAcuario::~BaseDatosAcuario() {
    if (db.isOpen()) {
        db.close();
    }
}

// Implementación del Singleton
BaseDatosAcuario* BaseDatosAcuario::getInstance() {
    std::lock_guard<std::mutex> guard(dbMutex);
    if (instance == nullptr) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("35.224.128.88");
        db.setDatabaseName("pecera");
        db.setUserName("root");
        db.setPassword("112358");
        instance = new BaseDatosAcuario(db);
    }
    return instance;
}

// Método para insertar un Pez en la base de datos
bool BaseDatosAcuario::insertarPez(const Pez& pez) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query(db);
    query.prepare("INSERT INTO peces (especie, alimentacion, temperaturaIdeal, phIdeal, salinidadIdeal, tamanoMaximo, habitatNatural, oxigenacionNecesaria) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(pez.getSpecies()));
    query.addBindValue(QString::fromStdString(pez.getFeeding()));
    query.addBindValue(pez.getIdealTemperature());
    query.addBindValue(pez.getIdealPh());
    query.addBindValue(pez.getIdealSalinity());
    query.addBindValue(pez.getMaxSize());
    query.addBindValue(QString::fromStdString(pez.getNaturalHabitat()));
    query.addBindValue(pez.getRequiredOxygenation());
    return query.exec();
}

// Método para registrar una actividad en la base de datos
void BaseDatosAcuario::registrarEnBaseDatos(const std::string& actividad) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query(db);
    query.prepare("INSERT INTO registro_actividades (actividad) VALUES (?)");
    query.addBindValue(QString::fromStdString(actividad));
    if (!query.exec()) {
        qDebug() << "Error al registrar actividad: " << query.lastError().text();
    }
}

// Método para actualizar los detalles de un Pez
bool BaseDatosAcuario::actualizarDetallesPez(int pezId, const std::string& detalles) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query(db);
    query.prepare("UPDATE peces SET detalles = ? WHERE id = ?");
    query.addBindValue(QString::fromStdString(detalles));
    query.addBindValue(pezId);
    if (!query.exec()) {
        qDebug() << "Error al actualizar detalles del pez: " << query.lastError().text();
        return false;
    }
    return true;
}

// Método para obtener los detalles de un Pez
std::string BaseDatosAcuario::obtenerDetallesPez(int pezId) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query(db);
    query.prepare("SELECT detalles FROM peces WHERE id = ?");
    query.addBindValue(pezId);
    if (query.exec() && query.first()) {
        return query.value(0).toString().toStdString();
    }
    return "";
}

// Método para eliminar un Pez de la base de datos
bool BaseDatosAcuario::eliminarPez(int pezId) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query(db);
    query.prepare("DELETE FROM peces WHERE id = ?");
    query.addBindValue(pezId);
    if (!query.exec()) {
        qDebug() << "Error al eliminar pez: " << query.lastError().text();
        return false;
    }
    return true;
}
