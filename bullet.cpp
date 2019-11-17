#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
Bullet::Bullet(QObject * parent, qreal _radiusOfTower, QPointF _originPos,  QPointF _destination, QChar _type) :
  QObject(parent)
{
    setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    setPos(QPointF(x()-10*pixmap().width(),y()-10*pixmap().height()));
    originPos = _originPos;
    destination = _destination;
    type = _type;
    radiusOfTower = _radiusOfTower;
    stepSize = 50 /*radiusOfTower/(3.33)/10*/;
    time = 0;
    moveTimer = new QTimer();
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(30);
}

void Bullet::move()
{
  double theta = rotation(); // degrees
  // y = ax^2+bx+c
  qreal dx, dy; /*dx = stepSize * qCos(qDegreesToRadians(theta)),
        dy = stepSize * qSin(qDegreesToRadians(theta));*/
//  theta *=-1;
//  if (theta > 180)
//    theta = -(45+(360-theta));
//  else
//    theta = -(-45+(360-theta));
  dx = stepSize * qCos(qDegreesToRadians(theta));
  dy = stepSize * qSin(qDegreesToRadians(theta))/*+10*time*/;
  time +=1;

  setPos(x() + dx, y()+ dy);
  // Замедление стрелы
  // if (type == ....) { ...
  QLineF distance(originPos,pos());
  if  (distance.length() > radiusOfTower)
    stepSize = stepSize * 0.1;

  QLineF line(pos(),destination);
  if (line.length() < 30) { // небольшая оптимизация
      QList<QGraphicsItem*> collidingItem = collidingItems();
      for(int i = 0; i < collidingItem.size(); i++){
        Unit *unit = dynamic_cast<Unit*>(collidingItem[i]);
        if (unit && canDealDamage) {
            unit->hp -=1;
           canDealDamage = false;
           break;
        }
      }
    }
  if (stepSize < 0.3) {
      setOpacity(opacity()-0.15);
      canDealDamage = false;
  }

  if (opacity()== 0.0)
      this->~Bullet();

}
