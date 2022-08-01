#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QColor>
#include <QRect>

class Game
{
public:
    Game();
    static constexpr int FPS = 30;
    static constexpr QSize RESOLUTION = QSize(640, 480);
    static constexpr int FLASHSPEED = 500;
    static constexpr int FLASHDELAY = 200;
    static constexpr int BUTTONSIZE = 200;
    static constexpr int BUTTONGAPSIZE = 20;
    static constexpr int TIMEOUT = 4;

    static constexpr QColor WHITE =        QColor(255, 255, 255);
    static constexpr QColor BLACK =        QColor(  0,   0,   0);
    static constexpr QColor BRIGHTRED =    QColor(255,   0,   0);
    static constexpr QColor RED =          QColor(155,   0,   0);
    static constexpr QColor BRIGHTGREEN =  QColor(255, 255, 255);
    static constexpr QColor GREEN =        QColor(0  , 155,   0);
    static constexpr QColor BRIGHTBLUE =   QColor(0  ,   0, 255);
    static constexpr QColor BLUE =         QColor(0  ,   0, 155);
    static constexpr QColor BRIGHTYELLOW = QColor(255, 255,   0);
    static constexpr QColor YELLOW =       QColor(155, 155,   0);
    static constexpr QColor DARKGRAY =     QColor(40,   40,  40);

    static QColor BGCOLOR;

    static constexpr int XMARGIN = int((RESOLUTION.width() - (2 * BUTTONSIZE) - BUTTONGAPSIZE) / 2);
    static constexpr int YMARGIN = int((RESOLUTION.height() - (2 * BUTTONSIZE) - BUTTONGAPSIZE) / 2);

    static constexpr QRect YELLOWRECT = QRect(XMARGIN, YMARGIN, BUTTONSIZE, BUTTONSIZE);
    static constexpr QRect BLUERECT = QRect(XMARGIN + BUTTONSIZE + BUTTONGAPSIZE, YMARGIN, BUTTONSIZE, BUTTONSIZE);
    static constexpr QRect REDRECT = QRect(XMARGIN, YMARGIN + BUTTONSIZE + BUTTONGAPSIZE, BUTTONSIZE, BUTTONSIZE);
    static constexpr QRect GREENRECT = QRect(XMARGIN + BUTTONSIZE + BUTTONGAPSIZE, YMARGIN + BUTTONSIZE + BUTTONGAPSIZE, BUTTONSIZE, BUTTONSIZE);

    static const QString PATH_TO_BEEP_SOUNDS[4];
    static const QString PATH_TO_BASIC_FONT;

    static constexpr int PATTERN_SIZE = 4;

    static const QString GREEN_STR;
    static const QString RED_STR;
    static const QString YELLOW_STR;
    static const QString BLUE_STR;
    static const QString INVALID_STR;
};

#endif // GAME_H
