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
  Bullet(QObject * parent, QPointF _originPos, QPointF _destination, /*QVector<Unit*> _units,*/ QString _type, qreal _radiusOfTower, int _damage);
  ~Bullet() override {
    moveTimer->~QTimer();}
public slots:
  void move();
private:
  bool canDealDamage = true;
  QTimer *moveTimer;
  QPointF originPos;
  QPointF destination;

//  QVector<Unit*> units;

  QString type;
  qreal radiusOfTower;
  int damage;
  QLineF overallDistance;
  double launchTime;
  QPointF lastPos;
  qreal dx, dy;
  qreal Vox, Voy;
  qreal Vo;
  //double alpha;
  double flightTime = 0;
  double elapsedTime;
};

#endif // BULLET_H
