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
    QLineF overallDistance(originPos, destination); // degrees
    double alpha = -overallDistance.angle();
    Vo = 94;
    double length = overallDistance.length();
    alpha = -45;
    Vx = Vo * qCos(qDegreesToRadians(alpha));
    Vy = Vo * qSin((qDegreesToRadians(alpha)));
    time = 0;
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

    time +=0.3;
    dx = Vx*time;
    dy = Vy*time + g*pow(time,2)/2;
  // y = ax^2+bx+c
//  theta *=-1;
//  if (theta > 180)
//    theta = -(45+(360-theta));
//  else
//    theta = -(-45+(360-theta));


  } else {
  dx = Vo * qCos(qDegreesToRadians(alpha));
  dy = Vo * qSin(qDegreesToRadians(alpha));
  }
  setPos(originPos.x() + dx, originPos.y()+ dy);
  // Замедление стрелы
  // if (type == ....) { ...
  QLineF distance(originPos,pos());
//  if  (distance.length() > radiusOfTower)
//    stepSize = stepSize * 0.1;

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
//  if (stepSize < 0.3) {
//      setOpacity(opacity()-0.15);
//      canDealDamage = false;
//  }

  if (opacity()== 0.0)
      this->~Bullet();

}
