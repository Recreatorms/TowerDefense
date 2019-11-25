#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type, qreal _radius, QVector<Unit*> _units, QVector<Interface *> _interfaces) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    type = _type;
    units = _units;
    interfaces = _interfaces;
    hasTarget = false;
    onCooldown = true;
    reloading = 0;
    attackRadius = 1;
    if (type != "Support") {
    if (type == "Musketeer") {
      attackRadius = _radius*2.1;
      reloadSpeed = 1000;
      damage = 2;
    }
    if (type == "Rapid") { // delet dis
        attackRadius = _radius*1.1;
        reloadSpeed = 100;
        damage = 1;
    }
    if (type == "Archer") {
        attackRadius = _radius*1.6;
        reloadSpeed = 500;
        reloading = 255;
        damage = 1;
    }
    QTimer *attackTimer = new QTimer();
    attackTimer->start(1);
    connect(attackTimer, &QTimer::timeout, this, &Tower::acquireTarget);
    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius),this);
    attackArea->setPos(((pos1+pos2)/2)-attackArea->rect().center());
    } else {
        numberOfNPCs = 1;
        respawning = 3000;
        respawnTimer = 3000;
        respawn = false;
        QTimer *spawnNPCtimer = new QTimer();
        spawnNPCtimer->start(1);
        connect(spawnNPCtimer, &QTimer::timeout, this, &Tower::spawnNPC);

      }
}
void Tower::updateUnits(QVector<Unit *> _units) {
    units = _units;
    if (type == "Support") {
        for (int i = 0; i < npcs.size(); i++) {
           npcs[i]->updateUnits(units);
          }
      }
}

qreal Tower::distanceTo(QGraphicsItem *item)
{
  QLineF line ((pos1+pos2)/2, item->pos());
  return line.length();
}

void Tower::attackTarget(QPointF destination) {
  QPointF centerOfTower((pos1+pos2)/2);
  Bullet *bullet = new Bullet(this, centerOfTower, destination, /*units,*/ type, attackArea->rect().width()/2, damage);
//  bullet->setPos(centerOfTower);
  this->scene()->addItem(bullet);
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  //Interface *info;
  if (type == "Support") {
    interfaces[5]->typeOfTower = "Support";
  }
  Q_UNUSED(mouseEvent)
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
            closestPoint = QPointF(collidingUnits[i]->x(), collidingUnits[i]->y());
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

void Tower::spawnNPC()
{
  for (int i = 0; i < npcs.size(); i++)
    if (npcs[i]->hp <= 0) {
        npcs[i]->~FriendlyNPC();
        npcs.removeAt(i);
        respawning = 0;
        respawn = true;
  }
  if (respawn)
    respawning++;
  if (npcs.size() < numberOfNPCs && respawnTimer <= respawning) {
     respawn = false;
     QPointF centerOfTower((pos1+pos2)/2);
     QPointF route(centerOfTower.x()-100, centerOfTower.y());
     FriendlyNPC *npc = new FriendlyNPC(this, centerOfTower, route, "default", units);
     npcs.push_back(npc);
     this->scene()->addItem(npc);
  }
}




////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type ==  "Musketeer" || type == "Rapid" || type == "Archer" /*|| type == "Support"*/) {
      spriteImage = new QPixmap("../TowerDefense/images/archer_tower.png");
      painter->drawPixmap(QPointF(pos1.x(),pos1.y()-33), *spriteImage, QRectF(QPointF(0,0),QPointF(200,200)));
    } else {
      painter->drawRoundedRect(QRectF(pos1,pos2), 100, 100, Qt::AbsoluteSize);
    }
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
