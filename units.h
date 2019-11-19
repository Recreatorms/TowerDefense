#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <queue>


class Unit : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Unit(QObject *parent, QPointF _start, int _startPos);
    ~Unit();
    void setOptions(qreal _speed, int _hp, int _attackBaseValue);
    void moveTo(QPointF point);
    int startPos;
    int currentPos;
    qreal hp;
    int attackBaseValue;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QGraphicsItem *item;

    qreal speed;
};

#endif // UNITS_H
