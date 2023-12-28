#include "GameScene.h"
#include "game.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_iteration_value(1000.0f/60.0f),
    m_leftMove(false), m_rightMove(false),m_upMove(false), m_downMove(false), m_fishXpos(500), m_fishYpos(200),
    m_deltaX(3), m_deltaY(3), m_height(200), m_facingRight(true)
{
    game::init();
    srand(time(0));
    setSceneRect(0, 0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height());
    //
    setBackgroundBrush(Qt::white);
    m_fishPixmap.load(m_game.PATH_TO_FISH1_PIXMAP);
    m_fishItem = new QGraphicsPixmapItem(QPixmap(m_fishPixmap));
    m_fishTransform = m_fishItem->transform();
    addItem(m_fishItem);
    //
    m_numberPixmap.load(m_game.PATH_TO_ALL_NUMBERS_PIXMAP);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    m_timer->start(m_iteration_value);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    {
        if( m_game.STATE == game::State::Active )
        {
            m_leftMove = true;
        }
    }

    break;
    case Qt::Key_Right:
    {
        if( m_game.STATE == game::State::Active)
        {
            m_rightMove = true;
        }
    }

    break;
    case Qt::Key_Up:
    {
        if( m_game.STATE == game::State::Active )
        {
            m_upMove = true;
        }
    }

    break;
    case Qt::Key_Down:
    {
        if( m_game.STATE == game::State::Active)
        {
            m_downMove = true;
        }
    }

    break;
    case Qt::Key_P:
    {
        if(m_game.STATE == game::State::Active)
        {
            m_game.STATE = game::State::Paused;
        }
        else if(m_game.STATE == game::State::Paused)
        {
            m_game.STATE = game::State::Active;
        }
    }
    break;
    case Qt::Key_R:
    {
        if(m_game.STATE == game::State::Game_Over)
        {
            reset();
        }
    }
    break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_rightMove = false;
        m_leftMove = false;
        break;

    case Qt::Key_Down:
    case Qt::Key_Up:
        m_upMove = false;
        m_downMove = false;
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::drawScore()
{
    int unityPartVal = 0;

    QGraphicsPixmapItem* unityPartScoreItem = new QGraphicsPixmapItem(m_numberPixmap.copy(unityPartVal * game::NUMBER_SIZE.width(), 0, game::NUMBER_SIZE.width(), game::NUMBER_SIZE.width()));
    unityPartScoreItem->moveBy( game::RESOLUTION.width() - game::NUMBER_SIZE.width(), 0);
    addItem(unityPartScoreItem);
}

void GameScene::reset()
{
    m_fishXpos = 100;
    m_fishYpos = 100;
    m_height = 200;

    m_game.STATE = game::State::Active;
    m_game.POINTS = 0;
}

void GameScene::update()
{
    clear();
    m_fishItem = new QGraphicsPixmapItem(QPixmap(m_fishPixmap).scaled(100,80));
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(QPixmap(m_game.PATH_TO_BACKGROUND_PIXMAP).scaled(game::RESOLUTION.width(), game::RESOLUTION.height()));

    addItem(bgItem);
    m_time_since_last_iteration += m_iteration_value;
    while(m_time_since_last_iteration > game::DELAY && m_game.STATE == game::State::Active)
    {
        m_time_since_last_iteration = -game::DELAY;
        if(m_leftMove)
        {
            m_fishXpos -= m_deltaX;
            if(m_fishTransform.m11() != -1)
            {
                m_fishTransform = m_fishTransform.scale(-1, 1);
                m_facingRight = false;
                m_fishXpos += m_fishItem->boundingRect().width();
            }

        }
        if(m_rightMove)
        {
            m_fishXpos += m_deltaX;
            if(m_fishTransform.m11() != 1)
            {
                m_fishTransform = m_fishItem->transform();
                m_facingRight = true;
                m_fishXpos -= m_fishItem->boundingRect().width();
            }
        }
        if(m_upMove)
        {
            m_fishYpos -= m_deltaY;
            if(m_fishTransform.m33() != 1)
            {
                m_fishYpos += m_fishItem->boundingRect().width();
            }
        }
        if(m_downMove)
        {
            m_fishYpos += m_deltaY;
            if(m_fishTransform.m33() != 1)
            {
                m_fishYpos -= m_fishItem->boundingRect().width();
            }

        }
    }

    m_fishItem->setTransform(m_fishTransform);
    m_fishItem->setPos(m_fishXpos, m_fishYpos);
    addItem(m_fishItem);
    drawScore();

    if(m_game.STATE == game::State::Paused)
    {
        QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(QPixmap(m_game.PATH_TO_PAUSED_BG).scaled(game::RESOLUTION.width(), game::RESOLUTION.height()));
        addItem(bgItem);
    }
    else if(m_game.STATE == game::State::Game_Over)
    {
        QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(QPixmap(m_game.PATH_TO_GAME_OVER_BG).scaled(game::RESOLUTION.width(), game::RESOLUTION.height()));
        addItem(bgItem);
    }

    QGraphicsRectItem* rItem = new QGraphicsRectItem();
    rItem->setBrush(backgroundBrush().color());
    rItem->setPen(backgroundBrush().color());
    rItem->setRect(0,0, 100, m_game.RESOLUTION.height());
    rItem->setPos(m_game.RESOLUTION.width(), 0);
    addItem(rItem);

    QGraphicsRectItem* bItem = new QGraphicsRectItem();
    bItem->setBrush(backgroundBrush().color());
    bItem->setPen(backgroundBrush().color());
    bItem->setRect(0,0, m_game.RESOLUTION.width()+100, 100);
    bItem->setPos(0, m_game.RESOLUTION.height());
    addItem(bItem);
}
