#include "BaseDatosAcuario.h"
#include "Acuario.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery> // Agregado el include de QSqlQuery

std::mutex BaseDatosAcuario::dbMutex;

BaseDatosAcuario::BaseDatosAcuario(QSqlDatabase db) : db(db) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("35.224.128.88");
    db.setDatabaseName("pecera");
    db.setUserName("root");
    db.setPassword("112358");
    if (!db.open()) {
        qDebug() << "Error al conectar con la base de datos: " << db.lastError().text();
    }
}

BaseDatosAcuario::~BaseDatosAcuario() {
    if (db.isOpen()) {
        db.close();
    }
}

bool BaseDatosAcuario::insertarPez(const Pez& pez) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("INSERT INTO peces (especie, alimentacion, ...) VALUES (?, ?, ...)");
    query.addBindValue(QString::fromStdString(pez.getSpecies()));
    query.addBindValue(QString::fromStdString(pez.getFeeding()));
    // ... añadir otros valores ...
    if (!query.exec()) {
        qDebug() << "Error al insertar pez: " << query.lastError().text();
        return false; // Agregada la comprobación de error y retorno
    }
    return true;
}

void BaseDatosAcuario::registrarEnBaseDatos(const std::string& actividad) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("INSERT INTO registro_actividades (actividad) VALUES (?)");
    query.addBindValue(QString::fromStdString(actividad));
    if (!query.exec()) {
        qDebug() << "Error al registrar actividad: " << query.lastError().text();
    }
}

bool BaseDatosAcuario::actualizarDetallesPez(int pezId, const std::string& detalles) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("UPDATE peces SET detalles = ? WHERE id = ?");
    query.addBindValue(QString::fromStdString(detalles));
    query.addBindValue(pezId);
    if (!query.exec()) {
        qDebug() << "Error al actualizar detalles del pez: " << query.lastError().text();
        return false; // Agregada la comprobación de error y retorno
    }
    return true;
}

std::string BaseDatosAcuario::obtenerDetallesPez(int pezId) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("SELECT detalles FROM peces WHERE id = ?");
    query.addBindValue(pezId);
    if (query.exec() && query.first()) {
        return query.value(0).toString().toStdString();
    }
    return "";
}

bool BaseDatosAcuario::eliminarPez(int pezId) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("DELETE FROM peces WHERE id = ?");
    query.addBindValue(pezId);
    if (!query.exec()) {
        qDebug() << "Error al eliminar pez: " << query.lastError().text();
        return false; // Agregada la comprobación de error y retorno
    }
    return true;
}
