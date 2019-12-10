#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type, qreal _radius, int _price, QVector<Unit*> _units, QVector<Interface *> _interfaces) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    type = _type;
    price = _price;
    units = _units;
    interfaces = _interfaces;
    hasTarget = false;
    onCooldown = true;
    reloading = 0;
    attackRadius = 1;


//    QTimer *actionTimer = new QTimer();


    if (type != "Support") {
//        connect(actionTimer, &QTimer::timeout, this, &Tower::acquireTarget);
    if (type == "Musketeer") {
        attackRadius = _radius*2.1;
        reloadSpeed = 1000;
        reloading = reloadSpeed/2;
        damage = 3;

//        actionTimer->start(1);
    }
    if (type == "Rapid") { // delet dis
        attackRadius = _radius*1.1;
        reloadSpeed = 100;
        reloading = reloadSpeed/2;
        damage = 1;

//        actionTimer->start(1);
    }
    if (type == "Archer") {
        attackRadius = _radius*1.6;
        reloadSpeed = 500;
        reloading = reloadSpeed/2;
        damage = 2;

//        actionTimer->start(10);
    }
//    actionTimer->start(1);
    attackArea = new QGraphicsEllipseItem(QRectF(pos1*attackRadius,pos2*attackRadius), this);
    attackArea->setPos((pos1+pos2)/2-attackArea->rect().center());
    attackArea->hide();
    } else {
//        connect(actionTimer, &QTimer::timeout, this, &Tower::spawnNPC);
        numberOfNPCs = 1;
        respawning = 3000;
        respawnTimer = 3000;
        respawn = false;



//        actionTimer->start(1);
//        connect(this, &Tower::spawned, spawnNPCtimer, &QTimer::stop);

      }
//    setPos((_pos1+_pos2)/2);
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
  QPointF centerOfTower((pos1+pos2)/2);
  QPointF route(centerOfTower.x()-100, centerOfTower.y());
//  qDebug() << "Tower:\t" <<this->thread();


//   qDebug() << myThread->thread();

  FriendlyNPC *npc = new FriendlyNPC(nullptr, centerOfTower, route, "default", units, interfaces);
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
    if (this->type != "Support") {
        if (!attackArea->isVisible())
          attackArea->show();
        else
          attackArea->hide();
        interfaces[5]->entityInfo(0, this->damage, 0, this->attackRadius, this->reloadSpeed, 0, this->price);
    } else
        interfaces[5]->entityInfo(this->npcs[0]->maxHP, this->npcs[0]->damage, 0, 0, this->npcs[0]->coolDown, 0, this->price);
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
  if (type == "Archer" /*|| type == "Support"*/) {
//      spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/61.png");
//      painter->drawPixmap(QPointF(boundingRect().x(), boundingRect().y()-100), *spriteImage, spriteImage->rect());
      spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/6.png");
    }
     else
      if (type == "Rapid")
          spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/2.png");
     else
      if (type == "Musketeer")
          spriteImage = new QPixmap("../TowerDefense/images/Towers/Archer/12.png");
     else
      if (type == "Support")
        spriteImage = new QPixmap("../TowerDefense/images/Towers/Support/5.png");


  painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
