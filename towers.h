#ifndef TOWERS_H
#define TOWERS_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QPen>

class Tower : public QObject, public QGraphicsItem
{
      Q_OBJECT
public:
    explicit Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QBrush _brush, QPen _pen, int radius);
    ~Tower();


//    void attack();
//    void showRadius();
//    void buyTower();
//    void sellTower();


//    int damage;
//    int attackSpeed;
//    int attackRadius;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
    QBrush brush;
    QPen pen;
    QPointF pos1, pos2;
    int radius;
};

#endif // TOWERS_H
