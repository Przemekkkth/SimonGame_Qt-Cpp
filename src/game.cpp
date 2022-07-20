#include "game.h"

QColor Game::BGCOLOR = BLACK;
QString PATH_TO_BEEP_SOUNDS[4] =
{
    QString(":/res/beep1.ogg"),
    QString(":/res/beep2.ogg"),
    QString(":/res/beep3.ogg"),
    QString(":/res/beep4.ogg")
};

Game::Game()
{

}
