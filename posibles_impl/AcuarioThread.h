#ifndef ACUARIO_THREAD_H
#define ACUARIO_THREAD_H

#include <QThread>
#include "Acuario.h"

class AcuarioThread : public QThread {
    Q_OBJECT
private:
    Acuario* acuario;

public:
    explicit AcuarioThread(Acuario* acuario);
    void run() override;
};

#endif // ACUARIO_THREAD_H
