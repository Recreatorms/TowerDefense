#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <queue>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include "interface.h"
//#include <QRandomGenerator>

class Unit : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Unit(QObject *parent, int _startPos, QString _type, QVector<QPointF>  &_path, QVector<Interface *>& _interfaces);
    ~Unit();

    void moveTo(QPointF point);
    int startPos;
    int currentPos = 0;

    int damage;
    int reloading = 0;
    int cooldown;

    int maxHP;
    int hp;
    qreal initialSpeed;
    int attackBaseValue;

    bool isBlocked;
    int currentFrame = 0;
    bool slowedDown = false;
    int slowingDown = 0;
    int slowTimer;
    bool deleted = false;
    int income;
    bool clicked = false;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVector<QPointF> &path;
    qreal dx = 0;
//public slots:
//    void completePath();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = nullptr, QWidget *widget = nullptr);
private:
    QVector<Interface *> &interfaces;
//    int offset;
    QString type;
    qreal speed;
    QPixmap *spriteImage;
};

#endif // UNITS_H
