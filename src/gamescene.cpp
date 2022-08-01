#include "gamescene.h"
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QThread>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), m_deltaTime(0.0f), m_loopTime(0.0f),
      m_loopSpeed(1.0f/float(Game::FPS)), m_score(0), m_waitingForInput(false), m_clickedPoint(Game::INVALID_STR),
      MOVE_PATTERN{Game::YELLOW_STR, Game::RED_STR, Game::BLUE_STR, Game::GREEN_STR}
{
    loadSoundEffects();
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    // connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(m_loopSpeed);
    m_elapsedTimer.start();


    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_BASIC_FONT);
    m_basicFont = QFont(QFontDatabase::applicationFontFamilies(id).at(0), 15, 0);
    m_pattern.clear();

    setBackgroundBrush(QBrush(Game::BGCOLOR));
    drawInfoText();
    drawScoreText();
    drawButtons();

    connect(this, &GameScene::changePattern, this, &GameScene::setPattern);
    connect(m_yellowRectItem, &RectItem::finishAlphaAnim, this, &GameScene::nextPossibleAnim);
    connect(m_blueRectItem, &RectItem::finishAlphaAnim, this, &GameScene::nextPossibleAnim);
    connect(m_redRectItem, &RectItem::finishAlphaAnim, this, &GameScene::nextPossibleAnim);
    connect(m_greenRectItem, &RectItem::finishAlphaAnim, this, &GameScene::nextPossibleAnim);

    m_currentAnim = 0;
    m_currentStep = 0;
    setPattern();
}

void GameScene::loop()
{
    //    m_deltaTime = m_elapsedTimer.elapsed();
    //    m_elapsedTimer.restart();

    //    m_loopTime += m_deltaTime;
    //    if( m_loopTime > m_loopSpeed)
    //    {
    //        m_loopTime -= m_loopSpeed;
    //        //setBackgroundBrush(QBrush(Game::BGCOLOR));
    //        drawInfoText();
    //        drawScoreText();
    //        drawButtons();
    //        if(!m_waitingForInput)
    //        {
    //            QThread::currentThread()->msleep(1000);
    //            m_pattern.append(MOVE_PATTERN[rand()%MOVE_PATTERN->size()]);
    //            foreach(QString button, m_pattern)
    //            {
    //                flashButtonAnimation(button);
    //                QThread::currentThread()->msleep(Game::FLASHDELAY);
    //            }
    //            m_waitingForInput = true;
    //        }
    //        else
    //        {

    //        }
    //    }
}

void GameScene::nextPossibleAnim()
{
    m_currentAnim++;
    if(m_currentAnim >= m_pattern.size())
    {
        m_waitingForInput = true;
        m_currentAnim = 0;
    }
    else
    {
        flashButtonAnimation(m_pattern[m_currentAnim]);
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
    m_scoreText = new QGraphicsSimpleTextItem();
    m_scoreText->setFont(m_basicFont);
    m_scoreText->setPos(Game::RESOLUTION.width() - 100, 10);
    m_scoreText->setPen(QPen(Game::WHITE));
    m_scoreText->setBrush(QBrush(Game::WHITE));
    m_scoreText->setText("Score: " + QString::number(m_score));
    addItem(m_scoreText);
}

void GameScene::drawButtons()
{
    m_yellowRectItem = new RectItem(Game::PATH_TO_BEEP_SOUNDS[0]);
    m_yellowRectItem->setBrush(QBrush(Game::YELLOW));
    m_yellowRectItem->setPen(QPen(Game::YELLOW));
    m_yellowRectItem->setRect(0,0, Game::YELLOWRECT.width(), Game::YELLOWRECT.height());
    m_yellowRectItem->setPos(Game::YELLOWRECT.x(), Game::YELLOWRECT.y());
    addItem(m_yellowRectItem);

    m_blueRectItem = new RectItem(Game::PATH_TO_BEEP_SOUNDS[1]);
    m_blueRectItem->setBrush(QBrush(Game::BLUE));
    m_blueRectItem->setPen(QPen(Game::BLUE));
    m_blueRectItem->setRect(0,0, Game::BLUERECT.width(), Game::BLUERECT.height());
    m_blueRectItem->setPos(Game::BLUERECT.x(), Game::BLUERECT.y());
    addItem(m_blueRectItem);

    m_redRectItem = new RectItem(Game::PATH_TO_BEEP_SOUNDS[2]);
    m_redRectItem->setBrush(QBrush(Game::RED));
    m_redRectItem->setPen(QPen(Game::RED));
    m_redRectItem->setRect(0,0, Game::REDRECT.width(), Game::REDRECT.height());
    m_redRectItem->setPos(Game::REDRECT.x(), Game::REDRECT.y());
    addItem(m_redRectItem);

    m_greenRectItem = new RectItem(Game::PATH_TO_BEEP_SOUNDS[3]);
    m_greenRectItem->setBrush(QBrush(Game::GREEN));
    m_greenRectItem->setPen(QPen(Game::GREEN));
    m_greenRectItem->setRect(0,0, Game::GREENRECT.width(), Game::GREENRECT.height());
    m_greenRectItem->setPos(Game::GREENRECT.x(), Game::GREENRECT.y());
    addItem(m_greenRectItem);

}

void GameScene::loadSoundEffects()
{
    m_beep1SEffect.setSource(QUrl(Game::PATH_TO_BEEP_SOUNDS[0]));
    m_beep1SEffect.setVolume(1.0f);
    m_beep2SEffect.setSource(QUrl(Game::PATH_TO_BEEP_SOUNDS[1]));
    m_beep2SEffect.setVolume(1.0f);
    m_beep3SEffect.setSource(QUrl(Game::PATH_TO_BEEP_SOUNDS[2]));
    m_beep3SEffect.setVolume(1.0f);
    m_beep4SEffect.setSource(QUrl(Game::PATH_TO_BEEP_SOUNDS[3]));
    m_beep4SEffect.setVolume(1.0f);
}

QString GameScene::getButtonClicked(QPointF clickedPoint)
{
    if(Game::YELLOWRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = Game::YELLOW_STR;
        return m_clickedPoint;
    }
    else if(Game::BLUERECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = Game::BLUE_STR;
        return m_clickedPoint;
    }
    else if(Game::REDRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = Game::RED_STR;
        return m_clickedPoint;
    }
    else if(Game::GREENRECT.contains(QPoint(clickedPoint.x(), clickedPoint.y())))
    {
        m_clickedPoint = Game::GREEN_STR;
        return m_clickedPoint;
    }

    return Game::INVALID_STR;
}

void GameScene::flashButtonAnimation(QString color)
{
    if(color == Game::YELLOW_STR)
    {
        m_yellowRectItem->startAnim();
    }
    else if(color == Game::BLUE_STR)
    {
        m_blueRectItem->startAnim();
    }
    else if(color == Game::RED_STR)
    {
        m_redRectItem->startAnim();
    }
    else if(color == Game::GREEN_STR)
    {
        m_greenRectItem->startAnim();
    }
}

void GameScene::checkClickedPosition()
{
    if(m_clickedPoint == m_pattern[m_currentStep])
    {
        m_currentStep++;
    }
    else
    {
        m_waitingForInput = false;
        m_score = 0;
        m_currentStep = 0;
        m_yellowRectItem->play();
        m_redRectItem->play();
        m_redRectItem->play();
        m_blueRectItem->play();
        setPattern();
    }


    if(m_currentStep == m_pattern.size())
    {
        m_waitingForInput = false;
        setPattern();
        m_score++;
        m_currentStep = 0;

    }
    m_scoreText->setText("Score: " + QString::number(m_score));
}

void GameScene::setPattern()
{
    if(!m_waitingForInput)
    {
        QThread::currentThread()->msleep(1000);
        m_pattern.append(MOVE_PATTERN[rand() % Game::PATTERN_SIZE]);
        flashButtonAnimation(m_pattern[0]);
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(m_waitingForInput)
    {
        switch (event->key()) {
        case Qt::Key_Q:
            m_clickedPoint = Game::YELLOW_STR;
            break;
        case Qt::Key_W:
            m_clickedPoint = Game::BLUE_STR;
            break;
        case Qt::Key_A:
            m_clickedPoint = Game::RED_STR;
            break;
        case Qt::Key_S:
            m_clickedPoint = Game::GREEN_STR;
            break;
        }
        checkClickedPosition();
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_waitingForInput)
    {
        if(getButtonClicked(event->scenePos()) != Game::INVALID_STR)
        {
            checkClickedPosition();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
