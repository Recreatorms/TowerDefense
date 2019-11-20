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
  Bullet(QObject * parent, QPointF _originPos, QPointF _destination, QChar _type, qreal _radiusOfTower, qreal _damage);
  ~Bullet() override {
    moveTimer->~QTimer();}
public slots:
  void move();
private:
  bool canDealDamage = true;
  qreal Vo;
  QTimer *moveTimer;
  QPointF originPos;
  QPointF destination;

  QChar type;
  qreal radiusOfTower;
  qreal damage;
  qreal Vx, Vy;
  double flightTime = 0;
  double launchTime;
  double time;
};

#endif // BULLET_H
