#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type, qreal _radius) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    attackRadius = _radius+4;
    type = _type;
    QTimer *attackTimer;
    attackTimer = new QTimer();
    attackTimer->start(400);
    connect(attackTimer, &QTimer::timeout, this, &Tower::acquireTarget);

    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius),this);
    attackArea->setPos(((pos1+pos2)/2)-attackArea->rect().center());

}

qreal Tower::distanceTo(QGraphicsItem *item)
{
  QLineF line (pos(), item->pos());
  return line.length();
}

void Tower::attackTarget() {
  Bullet *bullet = new Bullet(this,attackArea->rect().width()/2);
  QPointF centerOfTower((pos1.x()+pos2.x())/2,(pos1.y()+pos2.y())/2);
  bullet->setPos(centerOfTower);

  QLineF line(QPointF(centerOfTower), attackDest);
  double angle = -1 *(line.angle());
  bullet->setRotation(angle);
  this->scene()->addItem(bullet);
}

void Tower::acquireTarget() {
 // QList<QGraphicsItem *> collidingItems;
  QVector<Unit*>  collidingUnits;
  for(int i = 0; i < attackArea->collidingItems().size(); i++){
    Unit *unit = dynamic_cast<Unit*>(attackArea->collidingItems()[i]);
    if (unit)
    collidingUnits.push_back(unit);
  }
  hasTarget = false;
  if (collidingUnits.size() == 0) {
    hasTarget = false;
    return;
  }
  else {
  qreal closestDist = attackArea->rect().width()/2 - 10;
  QPointF closestPoint(0,0);
  for (int i = 0; i < collidingUnits.size(); i++) {

      qreal thisDist = distanceTo(collidingUnits[i]);
      if (thisDist < closestDist) {
         closestDist = thisDist;
         closestPoint = collidingUnits[i]->pos();
         hasTarget = true;
      }

  }
  attackDest = closestPoint;
  if (hasTarget)
   attackTarget();
}
}




////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//  if (type == 'd')
//      spriteImage = new QPixmap("../TowerDefense/images/6.png");
//  painter->drawPixmap(QPointF(pos1.x(),pos1.y()-100), *spriteImage, QRectF(QPointF(0,0),QPointF(200,200)));
  painter->drawRoundedRect(QRectF(pos1,pos2), 100, 100, Qt::AbsoluteSize);
  painter->drawLine(QLineF((pos1+pos2)/2,QPointF((pos1.x()+pos2.x())/2,((pos1.y()+pos2.y()))/2-50)));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
