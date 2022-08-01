#ifndef RECTITEM_H
#define RECTITEM_H
#include <QGraphicsRectItem>
#include <QObject>
#include <QPropertyAnimation>
#include <QSoundEffect>

class RectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal alpha READ alpha WRITE setAlpha)
public:
    explicit RectItem(QString pathToSoundEffect, QObject *parent = nullptr);
    qreal alpha();
    void startAnim();
    void play();
signals:
    void finishAlphaAnim();
public slots:
    void setAlpha(qreal newVal);
private:
    qreal m_alpha;
    QPropertyAnimation *m_appearAnim, *m_fadeOutAnim;
    QSoundEffect m_soundEffect;
};

#endif // RECTITEM_H
