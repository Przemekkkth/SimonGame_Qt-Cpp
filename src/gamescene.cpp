#include "gamescene.h"
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(1.0f/float(Game::FPS))
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
