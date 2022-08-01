#include "rectitem.h"
#include <QBrush>
#include <QPen>

RectItem::RectItem(QString pathToSoundEffect, QObject *parent)
    : QObject{parent}
{
    m_soundEffect.setSource(QUrl(pathToSoundEffect));
    m_soundEffect.setVolume(1.0f);

    m_fadeOutAnim = new QPropertyAnimation(this,"alpha",this);
    m_fadeOutAnim->setStartValue(brush().color().alpha());
    m_fadeOutAnim->setEndValue(0);
    m_fadeOutAnim->setEasingCurve(QEasingCurve::InQuad);
    m_fadeOutAnim->setDuration(500);

    m_appearAnim = new QPropertyAnimation(this,"alpha",this);
    m_appearAnim->setStartValue(brush().color().alpha());
    m_appearAnim->setEndValue(255);
    m_appearAnim->setEasingCurve(QEasingCurve::InQuad);
    m_appearAnim->setDuration(500);

    connect(m_fadeOutAnim, &QPropertyAnimation::finished, [this](){
        m_appearAnim->start();
        m_soundEffect.play();
    });
    connect(m_appearAnim, &QPropertyAnimation::finished, [this](){
        emit finishAlphaAnim();
    });
}

qreal RectItem::alpha()
{
    return m_alpha;
}

void RectItem::startAnim()
{
    m_fadeOutAnim->start();
}

void RectItem::play()
{
    m_soundEffect.play();
}

void RectItem::setAlpha(qreal newVal)
{
    QColor colorRect = brush().color();
    m_alpha = newVal;
    setBrush(QBrush(QColor(colorRect.red(), colorRect.green(), colorRect.blue(), m_alpha)));
    setPen(QPen(QColor(colorRect.red(), colorRect.green(), colorRect.blue(), m_alpha)));
}
