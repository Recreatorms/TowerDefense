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
  Bullet(QObject * parent, qreal _radiusOfTower);
  ~Bullet() override {
    moveTimer->~QTimer();}
public slots:
  void move();
private:
  bool canDealDamage;
  qreal stepSize = 75;
  QTimer *moveTimer;
  QPointF originPos;
  qreal radiusOfTower;
};

#endif // BULLET_H
