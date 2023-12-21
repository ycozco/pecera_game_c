#include <QtTest>
#include <QCoreApplication>
#include "GameScene.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

// add necessary includes here

class testCase : public QObject
{
    Q_OBJECT

private:
    GameScene *gameScene;

public:
    testCase();
    ~testCase();

private slots:
    void initTestCase();
    void test_movement_right();
    void test_movement_left();
    void test_movement_up();
    void test_movement_down();
    void test_pause();
    void cleanupTestCase();

};

testCase::testCase()
{

}

testCase::~testCase()
{

}

void testCase::initTestCase()
{
    gameScene = new GameScene();
    gameScene->reset();
}

void testCase::cleanupTestCase()
{
    delete gameScene;
}

void testCase::test_movement_right()
{
    // Guarda la posición inicial del pez
    int initialXpos = gameScene->getFishXpos();

    // Simula la pulsación de la tecla derecha
    QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, pressEvent);

    // Espera 1 segundo
    QTest::qWait(1000);

    // Simula la liberación de la tecla derecha
    QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Right, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, releaseEvent);

    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

    // Verifica que la posición del pez haya cambiado
    QVERIFY(gameScene->getFishXpos() > initialXpos);
    // Restaura la posición inicial del pez
    gameScene->reset();

    // Verifica que la posición del pez haya vuelto a su posición inicial
    QVERIFY(gameScene->getFishXpos() == initialXpos);
}
void testCase::test_movement_left()
{
    int initialXpos = gameScene->getFishXpos();

    QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, pressEvent);

    QTest::qWait(1000);

    QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Left, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, releaseEvent);

    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

    QVERIFY(gameScene->getFishXpos() < initialXpos);
    gameScene->reset();
    QVERIFY(gameScene->getFishXpos() == initialXpos);
}
void testCase::test_movement_up()
{
    int initialYpos = gameScene->getFishYpos();

    QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, pressEvent);

    QTest::qWait(1000);

    QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Up, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, releaseEvent);

    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

    QVERIFY(gameScene->getFishYpos() < initialYpos);
    gameScene->reset();
    QVERIFY(gameScene->getFishYpos() == initialYpos);
}
void testCase::test_movement_down()
{
    int initialYpos = gameScene->getFishYpos();

    QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, pressEvent);

    QTest::qWait(1000);

    QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Down, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, releaseEvent);

    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

    QVERIFY(gameScene->getFishYpos() > initialYpos);
    gameScene->reset();
    QVERIFY(gameScene->getFishYpos() == initialYpos);
}

void testCase::test_pause()
{
    // Estado inicial del juego
    game::State initialState = gameScene->getCurrentGameState();

    // Pulsación de la tecla de pausa
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_P, Qt::NoModifier);
    QCoreApplication::sendEvent(gameScene, event);

    QVERIFY(gameScene->getCurrentGameState() != initialState);

    // Simula la pulsación de la tecla de pausa nuevamente
    QCoreApplication::sendEvent(gameScene, event);

    // Verifica que el estado haya vuelto a su estado inicial
    QVERIFY(gameScene->getCurrentGameState() == initialState);
}

QTEST_MAIN(testCase)

#include "tst_testcase.moc"
