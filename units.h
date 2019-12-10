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
    explicit Unit(QObject *parent, QPointF _start, int _startPos, QString _type, QVector<QVector<QPointF> > _path, QVector<Interface *> _interfaces);
    ~Unit();
    void setOptions(int _speed, int _hp, int _attackBaseValue);
    void moveTo(QPointF point);
    int startPos;
    int currentPos;

    int damage;
    int reloading = 0;
    int cooldown;
    int maxHP;
    int hp;
    int speed;
    int attackBaseValue;
    bool isBlocked;

    int goldValue;
    bool clicked = false;

    QString type;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//public slots:
//    void completePath();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QVector<Interface *> interfaces;
//    int offset;
    int dx = 0;
    QPixmap *spriteImage;
    QVector<QVector<QPointF> > path;
};

#endif // UNITS_H
