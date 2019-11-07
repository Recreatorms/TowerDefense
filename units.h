#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <windows.h>
//#include "background.h"

class Unit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Unit(QObject *parent = nullptr);
    ~Unit();
 //   void setPosition(const QPointF &pos, Background *back);

signals:
public slots:
  void gameTimerSlot();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QGraphicsItem *item;
    int hp;
    qreal angle;
    QPoint position;
    QLabel *label;
};

#endif // UNITS_H
