#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

#include "game.h"
#include <QPixmap>

class QGraphicsPixmapItem;
class QTimer;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    game::State getCurrentGameState() const;
    QGraphicsPixmapItem* getFishItem() const;
    int getFishXpos() const;
    int getFishYpos() const;
    void reset();

signals:

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private:
    void clampXpos();
    void drawScore();


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

    QTimer *m_timer;

    QPixmap m_fishPixmap;
    QPixmap m_numberPixmap;

private slots:
    void update();
};

#endif // GAMESCENE_H
