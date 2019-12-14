#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type, int _price, int _index, QVector<Unit*> _units, QVector<Interface *> _interfaces) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    type = _type;
    index = _index;
    price = _price;
    units = _units;
    interfaces = _interfaces;
    hasTarget = false;
    onCooldown = true;
    reloading = 0;
    initialRadius = 3;


//    QTimer *actionTimer = new QTimer();

    this->setOptions();
//    if (type != "Support") {
      attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
      attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
      attackArea->hide();
//    }
}

void Tower::upgradeTower()
{

  level++;
  price *=2;
  if (type == "Support") {
    npcs[0]->level = level;
    npcs[0]->updateStats();
    maxHP = npcs[0]->maxHP;
    damage = npcs[0]->damage;
    coolDown = npcs[0]->coolDown;
    } else {
    if (type == "Archer") {
      attackRadius *= 1.15;
      reloadSpeed -= 100;
      damage++;

      if (level > 3) {
          price = 400;
          type = "Musketeer";
          setOptions();
      }
    }
    if (type == "Artillery") {
      price *= 2;
      attackRadius *=1.25;
      reloadSpeed -= 100;
      damage++;

      }
      attackArea->~QGraphicsEllipseItem();
      attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
      attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
    }
  this->update();
}

void Tower::setOptions()
{
  if (type == "Artillery") {
      attackRadius = initialRadius;
      reloadSpeed = 800;
      reloading = reloadSpeed/2;
      damage = 1;
      price = price*2;
    }
  if (type == "Musketeer") {
      attackRadius = initialRadius*2.1;
      reloadSpeed = 800;
      reloading = reloadSpeed/2;
      damage = 5;
      price = price * 2;

//        actionTimer->start(1);
  }
  if (type == "Rapid") { // delet dis
      attackRadius = initialRadius*1.1;
      reloadSpeed = 100;
      reloading = reloadSpeed/2;
      damage = 1;
              price = price * 2;

//        actionTimer->start(1);
  }
  if (type == "Archer") {
      attackRadius = initialRadius*1.4;
      reloadSpeed = 500;
      reloading = reloadSpeed/2;
      damage = 2;
      price = price * 2;
//        actionTimer->start(10);
  }
  if (type == "Support") {
      attackRadius = initialRadius;
      numberOfNPCs = 1;
      respawning = 3000;
      respawnTimer = 3000;
      respawn = false;
      price = price * 2;

      routePoint = QPointF(((pos1+pos2)/2).x()-100, ((pos1+pos2)/2).y());
    }
}

void Tower::changeRouteTower(QPointF _routePoint)
{
  QLineF distance(_routePoint, (pos1+pos2)/2);
  // max distance = attackRadius
  if (distance.length() <= attackRadius*50) {
     routePoint = _routePoint;
     if (npcs.size() != 0) {
        npcs[0]->changingRoute = true;
        npcs[0]->routePoint = routePoint;
     }
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
//  if (type == "Artillery")
//  bullet->setPos(centerOfTower);
//  connect(actionTimer, &QTimer::timeout, bullet, &Bullet::move);
  std::thread([bullet]()
    {
      Signal sig;
      connect(&sig, &Signal::sig, bullet, &Bullet::move);
      while (true) {
          std::this_thread::sleep_for(std::chrono::milliseconds(bullet->launchTime));
          emit sig.sig();
      }
       /*doSOMEJOB*/
    }
  ).detach();
  bullet->updateUnits(units);
  this->scene()->addItem(bullet);
}

void Tower::acquireTarget() {
    if (reloading >= reloadSpeed)
        onCooldown = false;
    if (onCooldown) {
        reloading++;
        return;
    }

  QPointF centerOfAttackArea(attackArea->pos()+attackArea->rect().center());
  QList<Unit*>  collidingUnits;
  for (int i = 0; i < units.size(); i++) {
      QLineF line(units[i]->pos(),centerOfAttackArea);
      if (line.length() < attackRadius*50 && !collidingUnits.contains(units[i]))
          collidingUnits.push_back(units[i]);
  }

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
      spawnFriendlyNPC();
  }
}

void Tower::spawnFriendlyNPC()
{
//  qDebug() << "Tower:\t" <<this->thread();


//   qDebug() << myThread->thread();

  FriendlyNPC *npc = new FriendlyNPC(nullptr, ((pos1+pos2)/2), routePoint, units, interfaces, level);
//  emit spawned();
//  thread->start();
  //this->thread()->exit();
  std::thread([npc]()
    {
      Signal sig;
      connect(&sig, &Signal::sig, npc, &FriendlyNPC::checkForEnemies);
      while (true) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          emit sig.sig();
      }
       /*doSOMEJOB*/
    }
  ).detach();
  maxHP = npc->maxHP;
  damage = npc->damage;
  coolDown = npc->coolDown;
//  MyThread *myThread = new MyThread(nullptr/*this->thread()->thread()*/);
//  npc->moveToThread(myThread);
//  qDebug() << "NPC:\t"<< npc->thread();
//  connect(myThread, &MyThread::signalStartTimer, npc, &FriendlyNPC::checkForEnemies);
//  myThread->start();
//  actionTimer = new QTimer(nullptr);
//  actionTimer->moveToThread(thread);
//  actionTimer->setInterval(1);
// connect(actionTimer, &QTimer::timeout, npc, &FriendlyNPC::checkForEnemies);
//  thread->quit();
//  actionTimer->start();

  npcs.push_back(npc);
  //thread->exit();
  this->scene()->addItem(npc);
//  spawnNPCtimer->start(1);
  //  emit spawned();
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    interfaces[5]->typeOfEntity = "Tower";
    interfaces[5]->typeOfTower = type;
    interfaces[5]->level = this->level;
    interfaces[5]->currentTowerIndex = index;
    interfaces[4]->showingUpgradeButton = true;
    if (type == "Support")
      interfaces[4]->showingRouteButton = true;
    interfaces[4]->update();
    if (this->type != "Support") {
        if (!attackArea->isVisible())
          attackArea->show();
        else
          attackArea->hide();
        interfaces[5]->entityInfo(0, this->damage, 0, this->attackRadius, this->reloadSpeed, 0, this->price);
    } else
        interfaces[5]->entityInfo(maxHP, damage, 0, 0, coolDown, 0, this->price);
    interfaces[5]->update();

    Q_UNUSED(mouseEvent)
}

void Tower::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//  if (this->type != "Support")
//      attackArea->hide();
}

////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1, pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type == "Archer")
      spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/" + QString::number(2*level) + ".png");
  else
  if (type == "Artillery")
      spriteImage = new QPixmap("../TowerDefense/images/Towers/Artillery/" + QString::number(level) + ".png");
  else
  if (type == "Rapid")
      spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/" + QString::number(2*level) + ".png");
  else
  if (type == "Musketeer")
      spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/" + QString::number(6+level) + ".png");
  else
  if (type == "Support")
    spriteImage = new QPixmap("../TowerDefense/images/Towers/Support/" + QString::number(3+level) + ".png");
  painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
