#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type, qreal _radius) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    attackRadius = _radius+0.5;
    type = _type;

    hasTarget = false;

    QTimer *attackTimer;
    attackTimer = new QTimer();
    attackTimer->start(150);
    connect(attackTimer, &QTimer::timeout, this, &Tower::acquireTarget);
    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius*2.1,pos2*attackRadius*2.1),this);
    attackArea->setPos(((pos1+pos2)/2)-attackArea->rect().center());

}

qreal Tower::distanceTo(QGraphicsItem *item)
{
  QLineF line ((pos1+pos2)/2, item->pos());
  return line.length();
}

void Tower::attackTarget(QPointF destination) {
  QPointF centerOfTower((pos1.x()+pos2.x())/2,(pos1.y()+pos2.y())/2);
  Bullet *bullet = new Bullet(this,attackArea->rect().width()/2, centerOfTower, destination, type);
  bullet->setPos(centerOfTower);

  QLineF line(QPointF(centerOfTower), attackDest);
  double angle = -1 *(line.angle());
  bullet->setRotation(angle);
  this->scene()->addItem(bullet);
}

void Tower::acquireTarget() {
 // QList<QGraphicsItem *> collidingItems;
  QList<Unit*>  collidingUnits;
  for(int i = 0; i < attackArea->collidingItems().size(); i++){
    Unit *unit = dynamic_cast<Unit*>(attackArea->collidingItems()[i]);
    if (unit) {
      collidingUnits.push_back(unit);
      break;
    }
  }
  hasTarget = false;
  if (collidingUnits.size() == 0) {
    hasTarget = false;
    return;
  }
  else {
  qreal closestDist = attackRadius*50*2.1;
  QPointF closestPoint(0,0);
  for (int i = collidingUnits.size() - 1; i >= 0; i--) {
      qreal thisDist = distanceTo(collidingUnits[i]);
      if (thisDist < closestDist) {
         closestDist = thisDist;
         closestPoint = collidingUnits[i]->pos();
         hasTarget = true;
         break;
      }

  }
  attackDest = closestPoint;
  if (hasTarget)
     attackTarget(attackDest);

  }
}




////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type == 'd')
      spriteImage = new QPixmap("../TowerDefense/images/archer_tower.png");
  painter->drawPixmap(QPointF(pos1.x(),pos1.y()-33), *spriteImage, QRectF(QPointF(0,0),QPointF(200,200)));
//  painter->drawRoundedRect(QRectF(pos1,pos2), 100, 100, Qt::AbsoluteSize);
//  painter->drawLine(QLineF((pos1+pos2)/2,QPointF((pos1.x()+pos2.x())/2,((pos1.y()+pos2.y()))/2-50)));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
