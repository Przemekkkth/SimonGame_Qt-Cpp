#include "game.h"

QColor Game::BGCOLOR = BLACK;
const QString Game::PATH_TO_BEEP_SOUNDS[4] =
{
    QString("qrc:/res/beep1.wav"),
    QString("qrc:/res/beep2.wav"),
    QString("qrc:/res/beep3.wav"),
    QString("qrc:/res/beep4.wav")
};

const QString Game::PATH_TO_BASIC_FONT = QString(":/res/freesansbold.ttf");

const QString Game::GREEN_STR = "GREEN";
const QString Game::RED_STR = "RED";
const QString Game::YELLOW_STR = "YELLOW";
const QString Game::BLUE_STR = "BLUE";
const QString Game::INVALID_STR = "NONE";

Game::Game()
{

}
