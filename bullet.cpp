#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
const qreal g = 9.8;
Bullet::Bullet(QObject * parent, QPointF _originPos,  QPointF _destination, QChar _type, qreal _radiusOfTower, qreal _damage) :
  QObject(parent)
{
    setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    setPos(QPointF(x()-10*pixmap().width(),y()-10*pixmap().height()));
    originPos = _originPos;
    destination = _destination;
    type = _type;
    radiusOfTower = _radiusOfTower;
    damage = _damage;
    if (type == '4') {
      Vo = 10;
      QLineF overallDistance(originPos, destination); // degrees
      double alpha = -overallDistance.angle();
      double length = overallDistance.length();
      Vo = radiusOfTower * length;
      flightTime = length;
      alpha = -90;
      Vx = Vo;
      Vy = g*flightTime;
          //Vo * qSin((qDegreesToRadians(alpha)));
      time = 0;
      launchTime = time;
    }
    else Vo = 1;
    moveTimer = new QTimer();
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(1);
}

void Bullet::move()
{
  QLineF overallDistance(originPos, destination); // degrees
  double alpha = -overallDistance.angle();
  qreal dx, dy;
  if (type == '4') {
    time++;
    flightTime = launchTime + time;
    dx = Vx;
    dy = Vy*flightTime - g*pow(flightTime,2)*0.5;
    QPointF newPos(dx,dy);
  // y = ax^2+bx+c
//  theta *=-1;
//  if (theta > 180)
//    theta = -(45+(360-theta));
//  else
//    theta = -(-45+(360-theta));

  setPos(x()+dx,y() +dy);
  } else {
  dx = Vo * qCos(qDegreesToRadians(alpha));
  dy = Vo * qSin(qDegreesToRadians(alpha));
  setPos(x() + dx, y()+ dy);
  }
  // Замедление стрелы
  // if (type == ....) { ...
  QLineF distance(originPos,pos());
//  if  (distance.length() > radiusOfTower)
//    Vo = Vo * 0.1;

//  if (Vo < 0.3) {
//      setOpacity(opacity()-0.15);
//      canDealDamage = false;
//  }
  QLineF line(pos(),destination);
  if (line.length() < 5) { // небольшая оптимизация
      QList<QGraphicsItem*> collidingItem = collidingItems();
      for(int i = 0; i < collidingItem.size(); i++){
        Unit *unit = dynamic_cast<Unit*>(collidingItem[i]);
        if (unit && canDealDamage) {
            unit->hp -= damage;
           canDealDamage = false;
           setOpacity(0);
           break;
        }
      }
    }

  if (opacity()== 0.0)
      this->~Bullet();

}
