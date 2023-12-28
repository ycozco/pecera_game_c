#include "game.h"

QSize game::RESOLUTION;
float game::DELAY;
const QSize game::FISH_SIZE = QSize(30, 30);
const QSize game::NUMBER_SIZE = QSize(32, 32);

game::game()
{
    PATH_TO_BACKGROUND_PIXMAP = ":/images/background.png";
    PATH_TO_FISH1_PIXMAP = ":/images/fish1.png";
    PATH_TO_ALL_NUMBERS_PIXMAP = ":/images/all_numbers.png";
    PATH_TO_PAUSED_BG = ":/images/bg_pause.png";
    PATH_TO_GAME_OVER_BG = ":/images/bg_gameover.png";
    POINTS = 0;
}

void game::init()
{
    RESOLUTION = QSize(1200, 630);
    DELAY = 0.2f;
}
