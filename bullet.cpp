#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
Bullet::Bullet(QObject * parent, qreal _radiusOfTower) :
  QObject(parent)
{
    setPixmap(QPixmap("../TowerDefense/images/bullet.png"));
    setPos(QPointF(x()-10*pixmap().width(),y()-10*pixmap().height()));
    originPos = pos();
    radiusOfTower = _radiusOfTower;
    moveTimer = new QTimer();
    connect(moveTimer, &QTimer::timeout, this, &Bullet::move);
    moveTimer->start(30);
    canDealDamage = true;
}

void Bullet::move()
{
  double theta = rotation(); // degrees

  qreal dx = stepSize * qCos(qDegreesToRadians(theta)),
        dy = stepSize * qSin(qDegreesToRadians(theta));
  setPos(x() + dx, y()+ dy);
  stepSize = stepSize * 0.75;
  QLineF line(originPos,pos());
//qreal length = line.length();
//if (line.length() < radiusOfTower)
//  setOpacity(0);
  QList<QGraphicsItem*> collidingItem = collidingItems();
  for(int i = 0; i < collidingItem.size(); i++){
    Unit *unit = dynamic_cast<Unit*>(collidingItem[i]);
    if (unit && canDealDamage) {
      unit->hp -=1;
      canDealDamage = false;
    }
//    Tile *tile = dynamic_cast<Tile*>(collidingItem[i]);
//    if (tile)                            // это уже вид сверху получается
//      if(tile->type == 'b') {            // я же хочу сделать мнимую изометрию
//        this->setOpacity(opacity()-0.01);
//        stepSize = 0;
//      }
  }


  if (stepSize < 0.1) {
      setOpacity(opacity()-0.01);
      canDealDamage = false;
  }
  if (opacity()== 0)
      this->~Bullet();

}
