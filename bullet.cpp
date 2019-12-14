#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
const qreal g = 10 * 150;
Bullet::Bullet(QObject * parent, QPointF _originPos,  QPointF _destination,/* QVector<Unit*> _units,*/ QString _type, qreal _radiusOfTower, int _damage) :
  QObject(parent)
{
    if (_type != "Artillery")
      setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    else {
      setPixmap(QPixmap("../TowerDefense/images/Towers/Artillery/50.png"));
      this->setScale(0.25);
    }
    originPos = _originPos;
    setPos(originPos);
    setRotation(-90);
//    units = _units;
    destination = _destination;
    type = _type;
    radiusOfTower = _radiusOfTower;
    damage = _damage;
    overallDistance = QLineF(originPos,destination);
    if (type == "Archer" || type == "Artillery") {
      if (type == "Artillery")
        flightTime = overallDistance.length()/radiusOfTower + 0.1; //  seconds

      else
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
            Vo = 3;
            launchTime = 1;
        }
        if (type == "Rapid") {
            Vo = 1;
            launchTime = 1;
        }
    }

}

void Bullet::updateUnits(QVector<Unit*> &_units)
{
    units = _units;
}

void Bullet::move()
{
  QLineF distanceToTarget(this->pos(), destination);
  double alpha = -overallDistance.angle();
  if (type == "Archer" || type == "Artillery") {
    lastPos = QPointF(originPos.rx() + dx, originPos.ry() - dy);
    elapsedTime += launchTime*0.001;
    dx = Vox*elapsedTime;
    dy = Voy*elapsedTime - g*pow(elapsedTime,2)*0.5;
    if (distanceToTarget.length() > 5)
    setPos(originPos.rx() + dx, originPos.ry() - dy);
    if (type == "Archer")
      setRotation(-QLineF(lastPos, pos()).angle());
//    else {
//        rotation++;
//        QTransform t;
//        t.translate(boundingRect().center().x(), boundingRect().center().y());
//        t.rotate(rotation);
//        t.translate(-boundingRect().center().x(), -boundingRect().center().y());
//        setTransform(t);
//      }
  } else {
    lastPos = pos();
    dx = Vo * qCos(qDegreesToRadians(alpha));
    dy = Vo * qSin(qDegreesToRadians(alpha));
    setPos(x() + dx, y() + dy);
    setRotation(-QLineF(lastPos, pos()).angle());
  }

  QLineF distance(originPos,pos());
  if  (distance.length() > radiusOfTower) {
    if (type != "Archer")
      Vo = Vo * 0.1;
    else
      if (dy < 10)
        Vo = Vo * 0.1;
    }
  if (Vo < 0.3 && type != "Artillery") {
      setOpacity(opacity()-0.15);
      canDealDamage = false;
  }
  if (opacity()== 0.0)
      this->~Bullet();

  if (type != "Artillery") {
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
  if (distanceToTarget.length() < 10) {
//    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
//    attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
//    attackArea->hide();
      QPointF pos1(-radiusOfExplosion,-radiusOfExplosion),
              pos2(radiusOfExplosion,radiusOfExplosion);
      QGraphicsEllipseItem *explosionArea = new QGraphicsEllipseItem(QRectF(pos1,pos2), this);
      explosionArea->setPos(boundingRect().center() - explosionArea->rect().center());
//      explosionArea->hide();


      QList<Unit*> collidingUnits;
      for (int i = 0; i < units.size(); i++) {
          QLineF line(units[i]->pos(),pos());
          if (line.length() < radiusOfExplosion && !collidingUnits.contains(units[i]))
              collidingUnits.push_back(units[i]);
      }

      for (int i = 0; i < collidingUnits.size(); i++) {
          if (canDealDamage)
            collidingUnits[i]->hp -= damage;
      }
      canDealDamage = false;
      this->~Bullet();
  }
}
