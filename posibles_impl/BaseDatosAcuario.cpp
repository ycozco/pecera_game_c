#include "BaseDatosAcuario.h"

BaseDatosAcuario::BaseDatosAcuario() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.100"); // IP ficticia
    db.setDatabaseName("acuarios");
    db.setUserName("usuario"); // Nombre de usuario ficticio
    db.setPassword("contraseña"); // Contraseña ficticia

    if (!db.open()) {
        qDebug() << "Error al conectar con la base de datos:" << db.lastError().text();
    }
}

bool BaseDatosAcuario::insertarPez(const Pez& pez) {
    std::lock_guard<std::mutex> guard(dbMutex);

    QSqlQuery query;
    query.prepare("INSERT INTO peces (especie, alimentacion, temperaturaIdeal, phIdeal, salinidadIdeal) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(pez.especie));
    query.addBindValue(QString::fromStdString(pez.alimentacion));
    query.addBindValue(pez.temperaturaIdeal);
    query.addBindValue(pez.phIdeal);
    query.addBindValue(pez.salinidadIdeal);

    if (!query.exec()) {
        qDebug() << "Error al insertar en la base de datos:" << query.lastError().text();
        return false;
    }
    return true;
}
