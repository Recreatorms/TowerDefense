#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "units.h"
#include "tile.h"
#include <QTimer>
class Bullet : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Bullet(QObject * parent, qreal _radiusOfTower, QPointF _originPos, QPointF _destination, QChar _type);
  ~Bullet() override {
    moveTimer->~QTimer();}
public slots:
  void move();
private:
  bool canDealDamage = true;
  qreal stepSize;
  QTimer *moveTimer;
  QPointF originPos;
  QPointF destination;
  qreal radiusOfTower;
  QChar type;
  double time = 0;
};

#endif // BULLET_H
