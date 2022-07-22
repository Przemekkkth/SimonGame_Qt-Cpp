#include "gamescene.h"
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QThread>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_deltaTime(0.0f), m_loopTime(0.0f),
      m_loopSpeed(1.0f/float(Game::FPS)), m_score(0), m_waitingForInput(false), m_clickedPoint("NONE"),
      MOVE_PATTERN{QString("YELLOW"), QString("RED"), QString("BLUE"), QString("GREEN")}
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(m_loopSpeed);
    m_elapsedTimer.start();

    loadSoundEffects();
    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_BASIC_FONT);
    m_basicFont = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 15, 0);
    m_pattern.clear();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
        setBackgroundBrush(QBrush(Game::BGCOLOR));
        drawInfoText();
        drawScoreText();
        drawButtons();
        if(!m_waitingForInput)
        {
            QThread::currentThread()->msleep(1000);
            m_pattern.append(MOVE_PATTERN[rand()%MOVE_PATTERN->size()]);
            foreach(QString button, m_pattern)
            {
                flashButtonAnimation(button);
                QThread::currentThread()->msleep(Game::FLASHDELAY);
            }
        }
        else
        {

        }
    }
}

void GameScene::drawInfoText()
{
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem();
    text->setFont(m_basicFont);
    text->setPos(10, Game::RESOLUTION.height()-25);
    text->setPen(QPen(Game::DARKGRAY));
    text->setBrush(QBrush(Game::DARKGRAY));
    text->setText("Match the pattern by clicking on the button or using the Q, W, A, S keys.");
    addItem(text);
}

void GameScene::drawScoreText()
{
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem();
    text->setFont(m_basicFont);
    text->setPos(Game::RESOLUTION.width() - 100, 10);
    text->setPen(QPen(Game::WHITE));
    text->setBrush(QBrush(Game::WHITE));
    text->setText("Score: " + QString::number(m_score));
    addItem(text);
}

void GameScene::drawButtons()
{
    QGraphicsRectItem* yellowItem = new QGraphicsRectItem();
    yellowItem->setBrush(QBrush(Game::YELLOW));
    yellowItem->setPen(QPen(Game::YELLOW));
    yellowItem->setRect(0,0, Game::YELLOWRECT.width(), Game::YELLOWRECT.height());
    yellowItem->setPos(Game::YELLOWRECT.x(), Game::YELLOWRECT.y());
    addItem(yellowItem);

    QGraphicsRectItem* blueItem = new QGraphicsRectItem();
    blueItem->setBrush(QBrush(Game::BLUE));
    blueItem->setPen(QPen(Game::BLUE));
    blueItem->setRect(0,0, Game::BLUERECT.width(), Game::BLUERECT.height());
    blueItem->setPos(Game::BLUERECT.x(), Game::BLUERECT.y());
    addItem(blueItem);

    QGraphicsRectItem* redItem = new QGraphicsRectItem();
    redItem->setBrush(QBrush(Game::RED));
    redItem->setPen(QPen(Game::RED));
    redItem->setRect(0,0, Game::REDRECT.width(), Game::REDRECT.height());
    redItem->setPos(Game::REDRECT.x(), Game::REDRECT.y());
    addItem(redItem);

    QGraphicsRectItem* greenItem = new QGraphicsRectItem();
    greenItem->setBrush(QBrush(Game::GREEN));
    greenItem->setPen(QPen(Game::GREEN));
    greenItem->setRect(0,0, Game::GREENRECT.width(), Game::GREENRECT.height());
    greenItem->setPos(Game::GREENRECT.x(), Game::GREENRECT.y());
    addItem(greenItem);
}

void GameScene::loadSoundEffects()
{
    m_beep1SEffect.setSource(QUrl("qrc:/res/beep1.ogg"));
    m_beep2SEffect.setSource(QUrl("qrc:/res/beep2.ogg"));
    m_beep3SEffect.setSource(QUrl("qrc:/res/beep3.ogg"));
    m_beep4SEffect.setSource(QUrl("qrc:/res/beep4.ogg"));
}

QString GameScene::getButtonClicked(QPointF clickedPoint)
{
    if(Game::YELLOWRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = "YELLOW";
    }
    else if(Game::BLUERECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = "BLUE";
    }
    else if(Game::REDRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = "RED";
    }
    else if(Game::GREENRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = "GREEN";
    }

    return "NONE";
}

void GameScene::flashButtonAnimation(QString color, int animationSpeed)
{
    int type;
    QRect rectangle;
    QColor flashColor;
    if(color == "YELLOW")
    {
        type = 1;
        flashColor = Game::BRIGHTYELLOW;
        rectangle = Game::YELLOWRECT;
    }
    else if(color == "BLUE")
    {
        type = 2;
        flashColor = Game::BRIGHTBLUE;
        rectangle = Game::BLUERECT;
    }
    else if(color == "RED")
    {
        type = 3;
        flashColor = Game::BRIGHTRED;
        rectangle = Game::REDRECT;
    }
    else {
        type = 4;
        flashColor = Game::BRIGHTBLUE;
        rectangle = Game::BLUERECT;
    }

    switch (type) {
    case 1:
        m_beep1SEffect.play();
        break;
    case 2:
        m_beep2SEffect.play();
        break;
    case 3:
        m_beep3SEffect.play();
        break;
    case 4:
        m_beep4SEffect.play();
        break;
    }

    QGraphicsRectItem rectItem;
    rectItem.setRect(0,0, rectangle.width(), rectangle.height());
    addItem(&rectItem);
    for(int start = 0, end = 255, step = 0; start < 255 && end > 0; ++start, ++end, ++step)
    {
        for(int alpha = 0; alpha > end; alpha += (animationSpeed * step))
        {
            rectItem.setPos(rectangle.topLeft());
            rectItem.setBrush(QBrush(QColor(flashColor.red(), flashColor.green(), flashColor.blue(), alpha)));
            QThread::currentThread()->msleep(1000.0f/Game::FPS);
        }
    }
    removeItem(&rectItem);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Q:
        m_clickedPoint = "YELLOW";
        break;
    case Qt::Key_W:
        m_clickedPoint = "BLUE";
        break;
    case Qt::Key_A:
        m_clickedPoint = "RED";
        break;
    case Qt::Key_S:
        m_clickedPoint = "GREEN";
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    QGraphicsScene::mousePressEvent(event);
}
