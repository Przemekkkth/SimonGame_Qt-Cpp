#include "view.h"
#include <QKeyEvent>
#include <QApplication>
#include <QKeyEvent>

View::View(QWidget *parent)
    : QGraphicsView{parent}, m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(sceneRect().width() + 2, sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(m_gameScene, &GameScene::changePattern, m_gameScene, &GameScene::setPattern);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::instance()->quit();
    }
    QGraphicsView::keyPressEvent(event);
}
