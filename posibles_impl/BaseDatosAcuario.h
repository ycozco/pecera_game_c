#ifndef BASEDATOSACUARIO_H
#define BASEDATOSACUARIO_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <mutex>
#include "Pez.h"

class BaseDatosAcuario {
private:
    QSqlDatabase db;
    std::mutex dbMutex;

public:
    BaseDatosAcuario();
    bool insertarPez(const Pez& pez);
};

#endif // BASEDATOSACUARIO_H
