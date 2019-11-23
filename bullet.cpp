#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
const qreal g = 9.8 * 100;
Bullet::Bullet(QObject * parent, QPointF _originPos,  QPointF _destination, QChar _type, qreal _radiusOfTower, qreal _damage) :
  QObject(parent)
{
    setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    originPos = _originPos;
    setPos(originPos);
    setRotation(-90);
    destination = _destination;
    type = _type;
    radiusOfTower = _radiusOfTower;
    damage = _damage;
    overallDistance = QLineF(originPos,destination);
    if (type == '4') {
      flightTime = overallDistance.length()/radiusOfTower; //  seconds
      Vo = sqrt(g*radiusOfTower);
      double dx = overallDistance.dx(),
             dy = -overallDistance.dy();
      Vox = dx/flightTime;
      Voy = (dy + g*pow(flightTime,2)*0.5)/flightTime;

      elapsedTime = 0;
      launchTime = 10; // milliseconds
    }
    else {
        Vo = 1;
        launchTime = 1;
    }
    moveTimer = new QTimer();
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(launchTime);
}

void Bullet::move()
{
  double alpha = -overallDistance.angle();
  if (type == '4') {
    lastPos = QPointF(originPos.rx() + dx, originPos.ry() - dy);
    elapsedTime += launchTime/1000;
    dx = Vox*elapsedTime;
    dy = Voy*elapsedTime - g*pow(elapsedTime,2)*0.5;
    setPos(originPos.rx() + dx, originPos.ry() - dy);
    setRotation(-QLineF(lastPos, pos()).angle());
  } else {
    lastPos = pos();
    dx = Vo * qCos(qDegreesToRadians(alpha));
    dy = Vo * qSin(qDegreesToRadians(alpha));
    setPos(x() + dx, y() + dy);
    setRotation(-QLineF(lastPos, pos()).angle());
  }
/////   Замедление стрелы
/////   if (type == ....) { ...
  QLineF distance(originPos,pos());
  if  (distance.length() > radiusOfTower)
    Vo = Vo * 0.1;
  if (Vo < 0.3) {
      setOpacity(opacity()-0.15);
      canDealDamage = false;
  }
  if (opacity()== 0.0)
      this->~Bullet();
  QLineF line(pos(),destination);
  if (line.length() < 50) { // небольшая оптимизация
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

}
