#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>


class game
{
public:
    game();
    static void init();
    static QSize RESOLUTION;
    QString PATH_TO_BACKGROUND_PIXMAP;
    QString PATH_TO_FISH1_PIXMAP;
    QString PATH_TO_PAUSED_BG;
    QString PATH_TO_GAME_OVER_BG;
    QString PATH_TO_ALL_NUMBERS_PIXMAP;

    static const float JUMP_FORCE;
    static float DELAY;

    static const QSize FISH_SIZE;

    static const QSize NUMBER_SIZE;
    int POINTS;

    enum class State{
        Active, Paused, Game_Over
    };

    State STATE;
};

#endif // GAME_H
