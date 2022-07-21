#include "gamescene.h"
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(1.0f/float(Game::FPS)), m_score(0)
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(m_loopSpeed);
    m_elapsedTimer.start();

    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_BASIC_FONT);
    m_basicFont = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 15, 0);
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
