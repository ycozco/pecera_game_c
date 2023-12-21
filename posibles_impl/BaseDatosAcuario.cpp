#include "BaseDatosAcuario.h"

BaseDatosAcuario* BaseDatosAcuario::instance = nullptr;

BaseDatosAcuario::BaseDatosAcuario() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("acuarios");
    db.setUserName("usuario");
    db.setPassword("contraseña");
    if (!db.open()) {
        qDebug() << "Error al conectar con la base de datos: " << db.lastError().text();
    }
}

BaseDatosAcuario::~BaseDatosAcuario() {
    if (db.isOpen()) {
        db.close();
    }
}

BaseDatosAcuario* BaseDatosAcuario::getInstance() {
    std::lock_guard<std::mutex> guard(dbMutex);
    if (!instance) {
        instance = new BaseDatosAcuario();
    }
    return instance;
}

bool BaseDatosAcuario::insertarPez(const Pez& pez) {
    std::lock_guard<std::mutex> guard(dbMutex);
    QSqlQuery query;
    query.prepare("INSERT INTO peces (especie, alimentacion, ...) VALUES (?, ?, ...)");
    query.addBindValue(QString::fromStdString(pez.getEspecie()));
    query.addBindValue(QString::fromStdString(pez.getAlimentacion()));
    // ... añadir otros valores ...
    return query.exec();
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
    return query.exec();
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
    return query.exec();
}