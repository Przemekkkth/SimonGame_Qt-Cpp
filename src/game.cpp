#include "game.h"

QColor Game::BGCOLOR = BLACK;
const QString Game::PATH_TO_BEEP_SOUNDS[4] =
{
    QString(":/res/beep1.ogg"),
    QString(":/res/beep2.ogg"),
    QString(":/res/beep3.ogg"),
    QString(":/res/beep4.ogg")
};

const QString Game::PATH_TO_BASIC_FONT = QString(":/res/freesansbold.ttf");


Game::Game()
{

}
