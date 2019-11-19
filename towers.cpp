#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type, qreal _radius, QVector<Unit*> _units) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    type = _type;
    units = _units;
    hasTarget = false;
    onCooldown = true;
    reloading = 0;
    attackRadius = 1;
    if (type == '1') {
      attackRadius = _radius*2.1;
      reloadSpeed = 1000;
      damage = 2;
    }
    if (type == '2') {
        attackRadius = _radius*1.1;
        reloadSpeed = 100;
        damage = 0.3;
    }
    if (type == '4') {
        attackRadius = _radius*3.1;
        reloadSpeed = 1;
        damage = 1;
    }
    QTimer *attackTimer;
    attackTimer = new QTimer();
    attackTimer->start(1);
    connect(attackTimer, &QTimer::timeout, this, &Tower::acquireTarget);
    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius),this);
    attackArea->setPos(((pos1+pos2)/2)-attackArea->rect().center());
}
void Tower::updateUnits(QVector<Unit *> _units) {
    units = _units;
}

qreal Tower::distanceTo(QGraphicsItem *item)
{
  QLineF line ((pos1+pos2)/2, item->pos());
  return line.length();
}

void Tower::attackTarget(QPointF destination) {
  QPointF centerOfTower((pos1.x()+pos2.x())/2,(pos1.y()+pos2.y())/2);
  Bullet *bullet = new Bullet(this, centerOfTower, destination, type, attackArea->rect().width()/2, damage);
  bullet->setPos(centerOfTower);

  QLineF line(QPointF(centerOfTower), attackDest);
  double angle = -1 *(line.angle());
  bullet->setRotation(angle);
  this->scene()->addItem(bullet);
}

void Tower::acquireTarget() {
    if (reloading >= reloadSpeed)
        onCooldown = false;
    if (onCooldown) {
        reloading++;
        return;
    }
  //QList<QGraphicsItem *> collidingItems = attackArea->collidingItems();
  QPointF centerOfAttackArea(attackArea->pos()+attackArea->rect().center());
  QList<Unit*>  collidingUnits;
  for (int i = 0; i < units.size(); i++) {
      QLineF line(units[i]->pos(),centerOfAttackArea);
      if (line.length() < attackRadius*50 && !collidingUnits.contains(units[i]))
          collidingUnits.push_back(units[i]);
  }
//  for (int i = 0; i < collidingUnits.size(); i++) {
//      QLineF line(collidingUnits[i]->pos(),centerOfAttackArea);
//      if (line.length() > attackRadius*50*2.1 || collidingUnits[i]->hp == 0)
//          collidingUnits.pop_front();
//  }
  hasTarget = false;
  if (collidingUnits.size() == 0) {
    hasTarget = false;
    return;
  }
  else {
    qreal closestDist = attackRadius*50;
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
  }
  if (hasTarget) {
     attackTarget(attackDest);
     onCooldown = true;
     reloading = 0;
  }
}




////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type == '1' || type == '2' || type == '3' || type == '4')
      spriteImage = new QPixmap("../TowerDefense/images/archer_tower.png");
  painter->drawPixmap(QPointF(pos1.x(),pos1.y()-33), *spriteImage, QRectF(QPointF(0,0),QPointF(200,200)));
//  painter->drawRoundedRect(QRectF(pos1,pos2), 100, 100, Qt::AbsoluteSize);
//  painter->drawLine(QLineF((pos1+pos2)/2,QPointF((pos1.x()+pos2.x())/2,((pos1.y()+pos2.y()))/2-50)));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
