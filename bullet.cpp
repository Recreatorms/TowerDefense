#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
const qreal g = 10 * 150;
Bullet::Bullet(QObject * parent, QPointF _originPos,  QPointF _destination,/* QVector<Unit*> _units,*/ QString _type, qreal _radiusOfTower, int _damage) :
  QObject(parent)
{

    setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    originPos = _originPos;
    setPos(originPos);
    setRotation(-90);
//    units = _units;
    destination = _destination;
    type = _type;
    radiusOfTower = _radiusOfTower;
    damage = _damage;
    overallDistance = QLineF(originPos,destination);
    if (type == "Archer") {
      flightTime = overallDistance.length()/radiusOfTower - 0.2; //  seconds
      double dx = overallDistance.dx(),
             dy = -overallDistance.dy();
      Vox = dx/flightTime;
      Voy = (dy + g*pow(flightTime,2)*0.5)/flightTime;
      Vo = sqrt(Vox*Vox+Voy*Voy);
      elapsedTime = 0;
      launchTime = 10; // milliseconds
    }
    else {
        if (type == "Musketeer") {
            Vo = 5;
            launchTime = 1;
        }
        if (type == "Rapid") {
            Vo = 1;
            launchTime = 1;
        }
    }

}

void Bullet::move()
{
  double alpha = -overallDistance.angle();
  if (type == "Archer") {
    lastPos = QPointF(originPos.rx() + dx, originPos.ry() - dy);
    elapsedTime += launchTime*0.001;
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

  QLineF distance(originPos,pos());
  if  (distance.length() > radiusOfTower && type != "Archer")
    Vo = Vo * 0.1;
  if (Vo < 0.3) {
      setOpacity(opacity()-0.15);
      canDealDamage = false;
  }
  if (opacity()== 0.0)
      this->~Bullet();

  QLineF distanceToTarget(this->pos(), destination);
////  if (distanceToTarget.length() <= 10) {
//     for (int i = 0; i < units.size(); i++) {
//         qreal length = QLineF(this->pos(),units[i]->pos()).length();
//         if (length <= 10 && canDealDamage) {
//            units[i]->hp -= damage;
//            canDealDamage = false;
//            setOpacity(0);
//            break;
//         }
//     }
////  }
//  QLineF line(pos(),destination);
  if (distanceToTarget.length() < 50) { // небольшая оптимизация
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
