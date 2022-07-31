#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include <QSoundEffect>
#include <QTime>
#include <QFont>
#include <QGraphicsSimpleTextItem>

#include "game.h"
#include "rectitem.h"
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:
private slots:
    void loop();
private:
    void drawInfoText();
    void drawScoreText();
    void drawButtons();
    void loadSoundEffects();
    QString getButtonClicked(QPointF clickedPoint);
    void flashButtonAnimation(QString color, int animationSpeed = 50);
    void setPattern();
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;
    QSoundEffect m_beep1SEffect, m_beep2SEffect, m_beep3SEffect, m_beep4SEffect;
    QStringList m_pattern;

    int m_currentStep;
    QTime m_lastClickTime;

    int m_score;
    bool m_waitingForInput;
    QFont m_basicFont;

    QString m_clickedPoint;
    const QString MOVE_PATTERN[4];
    // QGraphicsScene interface
    QGraphicsSimpleTextItem *m_scoreText;
    RectItem *m_yellowRectItem, *m_redRectItem, *m_greenRectItem, *m_blueRectItem;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
