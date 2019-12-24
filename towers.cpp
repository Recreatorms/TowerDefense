#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type, int _price, int _index, QVector<Unit*> &_units, QVector<Interface *> &_interfaces, QVector<QVector<QString> > &_map) :
  QObject(parent), QGraphicsItem(), units(_units), interfaces(_interfaces), map(_map)
{
  pos1 = _pos1;
  pos2 = _pos2;
  type = _type;
  index = _index;
  price = _price;

  hasTarget = false;
  onCooldown = true;
  reloading = 0;
  initialRadius = 3;



  this->setOptions(map);
  //    if (type != "Support") {
  attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
  attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
  attackArea->hide();
  //    }
}

Tower::~Tower()
{
  delete attackArea;
  deleted = true;
  if (type == "Support") {
      for (int i = 0; i < npcs.size(); i++) {
          npcs[i]->~FriendlyNPC();
          npcs.removeAt(i);
          respawning = 0;
          respawn = true;
        }
      npcs.clear();

    }
  this->scene()->removeItem(this);
}

void Tower::upgradeTower()
{

  level++;
  if (type == "Support") {
      if (level == 2)
        price = 400;
      if (level == 3)
        price = 600;
      sellPrice = price/2;
      if (npcs.size() != 0) {
          npcs[0]->level = level;
          npcs[0]->updateStats();
          maxHP = npcs[0]->maxHP;
          damage = npcs[0]->damage;
          coolDown = npcs[0]->coolDown;
        } else respawning = 2500;
    } else {
      if (type == "Archer") {
          if (level == 2) {
            price = 600;
            sellPrice = 270;
            }
          if (level == 3) {
            price = 800;
            sellPrice = 630;
            }
          attackRadius *= 1.15;
          reloadSpeed -= 100;
          damage++;
          if (level > 3) {
              type = "Musketeer";
              setOptions(map);
              this->update();
            }
        }
      if (type == "Mage") {
          attackRadius *= 1.185;
          reloadSpeed -=50;
          damage +=2;
          slowTimer +=50;
          if (level == 2) {
            price = 1000;
            sellPrice = 250;
          }
          if (level == 3)
            sellPrice = 500;

        }
      if (type == "Artillery") {
          sellPrice = price;
          if (level == 2)
            price = 800;
          attackRadius *=1.25;
          reloadSpeed -= 150;
          damage++;
        }
      attackArea->~QGraphicsEllipseItem();
      attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
      attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
    }
  this->update();
}

void Tower::setOptions(QVector<QVector<QString> > &map)
{
  if (type == "Artillery") {
      attackRadius = initialRadius;
      reloadSpeed = 1000;
      reloading = reloadSpeed/2;
      damage = 2;
      sellPrice = price/2;
      price *=3;
      price /=2;
    }
  if (type == "Mage") {
      damage = 2;
      reloadSpeed = 500;
      reloading = reloadSpeed/2;
      attackRadius = initialRadius*1.1;
      sellPrice = price/2;
      price = 300;
      slowTimer = 100;
    }
  if (type == "Musketeer") {
      attackRadius = initialRadius*3.3;
      reloadSpeed = 750;
      reloading = reloadSpeed/2;
      damage = 15;
      sellPrice = 800;
      price = 0;
    }
  if (type == "Archer") {
      attackRadius = initialRadius*1.4;
      reloadSpeed = 500;
      reloading = reloadSpeed/2;
      damage = 1;
      sellPrice = 90;
      price = price * 2;
    }
  if (type == "Support") {
      attackRadius = initialRadius;
      numberOfNPCs = 1;
      respawning = 3000;
      respawnTimer = 3000;
      respawn = false;
      sellPrice = 50;
      price *= 3;
      int i = ((pos1+pos2)/2).y()/100 + 11/2,
          j = (((pos1+pos2)/2).x() + 261)/100 + 15/2;
      if (j > 0)
        if (map[i][j-1] == 'r') {
            routePoint = QPointF(((pos1+pos2)/2).x()-100, ((pos1+pos2)/2).y());
            return;
          }
      if (j < 15)
        if (map[i][j+1] == 'r') {
            routePoint = QPointF(((pos1+pos2)/2).x()+100, ((pos1+pos2)/2).y());
            return;
          }
      if (i > 0)
        if (map[i-1][j] == 'r') {
            routePoint = QPointF(((pos1+pos2)/2).x(), ((pos1+pos2)/2).y()-100);
            return;
          } if (i < 10)
        if (map[i+1][j] == 'r') {
            routePoint = QPointF(((pos1+pos2)/2).x(), ((pos1+pos2)/2).y()+100);
            return;
          }
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
          npcs[0]->routePoint = _routePoint;
        }
    }

}
void Tower::updateUnits(QVector<Unit *> &_units) {
  if (!this->QObject::d_ptr->wasDeleted || !this->QObject::d_ptr->deleteLaterCalled) {
      units = _units;
      if (type == "Support") {
          for (int i = 0; i < npcs.size(); i++) {
              npcs[i]->updateUnits(units);
            }
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
  Bullet *bullet = new Bullet(nullptr, centerOfTower, destination, slowTimer, type, attackArea->rect().width()/2, damage, units);
  //  bullet->updateUnits(units);
  std::thread thread([bullet, this]()
  {
      Signal sig;
      connect(&sig, &Signal::sig, bullet, &Bullet::move);
      while (!bullet->deleted || deleted) {
          std::this_thread::sleep_for(std::chrono::milliseconds(bullet->launchTime));
          if (!IsPaused || deleted)
            emit sig.sig();
        }
    }
  );
  thread.detach();
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
  QList<Unit*> collidingUnits;
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
        if (npcs[i]->currentEnemy->isBlocked)
          npcs[i]->currentEnemy->isBlocked = false;
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

  FriendlyNPC *npc = new FriendlyNPC(this, ((pos1+pos2)/2), routePoint, attackRadius*50, units, interfaces, level);
  //  emit spawned();
  //  thread->start();
  //this->thread()->exit();
  std::thread thread([npc, this]()
  {
      Signal sig;
      connect(&sig, &Signal::sig, npc, &FriendlyNPC::checkForEnemies);
      while (true) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          if (!IsPaused)
            emit sig.sig();
        }
      /*doSOMEJOB*/
    }
  );
  thread.detach();
  if (npc->deleted)
    thread.~thread();
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
      interfaces[5]->entityInfo(0, this->damage, 0, this->attackRadius, this->reloadSpeed, this->price, this->sellPrice);
    } else
    interfaces[5]->entityInfo(maxHP, damage, 0, 0, coolDown,  this->price, this->sellPrice);
  interfaces[5]->update();

  Q_UNUSED(mouseEvent)
}

//void Tower::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
////  if (this->type != "Support")
////      attackArea->hide();
//}

////////// Графика ///////////////////////
QRectF Tower::boundingRect() const
{
  return QRectF(pos1, pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type == "Archer")
    spriteImage =  QPixmap("../TowerDefense/images/Towers/Archer/level" + QString::number(level) + ".png");
  else
    if (type == "Artillery")
      spriteImage =  QPixmap("../TowerDefense/images/Towers/Artillery/level" + QString::number(level) + ".png");
    else
      if (type == "Mage") {
          spriteImage =  QPixmap("../TowerDefense/images/Towers/Mage/level" + QString::number(level) + ".png");
        } else
        if (type == "Musketeer")
          spriteImage =  QPixmap("../TowerDefense/images/Towers/Archer/level" + QString::number(4) + ".png");
        else
          if (type == "Support")
            spriteImage =  QPixmap("../TowerDefense/images/Towers/Support/level" + QString::number(level) + ".png");
  painter->drawPixmap(boundingRect(), spriteImage, spriteImage.rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
