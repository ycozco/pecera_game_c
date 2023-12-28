#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "Acuario.h"
#include "Pez.h"
#include "game.h"
#include <QPixmap>

class QGraphicsPixmapItem;
class QTimer;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private:
    void drawScore();
    void reset();

    game m_game;
    float m_time_since_last_iteration;
    const float m_iteration_value;

    bool m_leftMove;
    bool m_rightMove;
    bool m_upMove;
    bool m_downMove;

    int m_fishXpos;
    int m_fishYpos;
    const int m_deltaX;
    const int m_deltaY;
    int m_height;

    QGraphicsPixmapItem* m_fishItem;
    QTransform m_fishTransform;
    bool m_facingRight;
    QGraphicsPixmapItem* m_bgItem;

    QTimer *m_timer;

    QPixmap m_fishPixmap;
    QPixmap m_numberPixmap;

    Acuario m_acuario;           // Agrega una instancia de Acuario
    QList<std::unique_ptr<Pez>> m_listaPeces;  // Lista para contener instancias de Pez

private slots:
    void update();
};

#endif // GAMESCENE_H
