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
 //   void setPosition(const QPointF &pos, Background *back);
    void moveTo(QPointF point);
 //   void completePath(std::vector<QPointF> path);
    int currentPos;
    int startPos;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QGraphicsItem *item;
    int hp;
    qreal angle;
    QLabel *label;
};

#endif // UNITS_H
