#include "friendlynpc.h"

FriendlyNPC::FriendlyNPC(QObject *parent, QPointF _spawnPoint, QPointF _routePoint, qreal _attackRadius, QVector<Unit*> &_units, QVector<Interface *> &_interfaces, int _level) :
  QObject(parent), QGraphicsItem(), interfaces(_interfaces), units(_units)
{
  spawnPoint = _spawnPoint;
  routePoint = _routePoint;
  setPos(spawnPoint);

  attackRadius = _attackRadius;
  currentEnemy = nullptr;
  blockingAnEnemy = false;
  readyToStrike = false;
  //if (type == ...) {
  level = _level;
  updateStats();
  //    checkingTimer = new QTimer();
  //    checkingTimer->start(100);
  //    connect(checkingTimer, &QTimer::timeout, this, &FriendlyNPC::checkForEnemies);
}

void FriendlyNPC::moveTo(QPointF pos) {
  QLineF distance(this->pos(), pos);
  qreal alpha = -distance.angle();
  dx = movementSpeed * qCos(qDegreesToRadians(alpha));
  dy = movementSpeed * qSin(qDegreesToRadians(alpha));
  setPos(x() + dx, y() + dy);

  if (distance.length() <= 1) {
      readyToStrike = true;
      changingRoute = false;
    }
}

void FriendlyNPC::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  interfaces[5]->typeOfEntity = "Unit";
  interfaces[5]->typeOfUnit = "Defender";//
  interfaces[5]->entityInfo(this->hp, this->damage, 0, 0.0, this->coolDown, 0, 0);
  interfaces[5]->update();
  clicked = true;
  Q_UNUSED(event)
}

void FriendlyNPC::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  clicked = false;
  Q_UNUSED(event)
}




void FriendlyNPC::updateUnits(QVector<Unit *> &_units) {
  units = _units;
}

void FriendlyNPC::updateStats()
{
  switch (level) {
    case 1: {
        maxHP = 8;
        hp = maxHP;
        regenSpeed = 3000;
        regenerating = 0;
        reloading = 0;
        checkRadius = 101;
        damage = 1;
        coolDown = 250;
        spriteImage = QPixmap("../TowerDefense/images/Towers/Support/knight_" + QString::number(level) + ".png");
        break;
      }
    case 2: {
        maxHP = 12;
        hp = maxHP;
        regenSpeed = 2000;
        hpRegen = 2;
        regenerating = 0;
        reloading = 0;
        checkRadius = 101;
        damage = 2;
        coolDown = 250;
        spriteImage = QPixmap("../TowerDefense/images/Towers/Support/knight_" + QString::number(level) + ".png");
        break;
      }
    case 3: {
        maxHP = 25;
        hp = maxHP;
        regenSpeed = 2000;
        hpRegen = 3;
        regenerating = 0;
        reloading = 0;
        checkRadius = 111;
        damage = 4;
        coolDown = 275;
        spriteImage = QPixmap("../TowerDefense/images/Towers/Support/knight_" + QString::number(level) + ".png");
        break;
      }
    }
  this->update();
}
void FriendlyNPC::attackEnemy() {
  if (currentEnemy == nullptr || currentEnemy->deleted) {
      readyToStrike = true;
      //          moveTo(routePoint);
      blockingAnEnemy = false;
      return;
    }
  if (changingRoute) {
      readyToStrike = false;
      currentEnemy->isBlocked = false;
      currentEnemy->update();
      return;
    } else
    currentEnemy->isBlocked = true;
  if (currentEnemy->x() < x() && currentEnemy->dx == 0) {
      dx = -1;
      currentEnemy->dx = 1;
      currentEnemy->update();
    } else
    if (currentEnemy->dx == 0){
        dx = 1;
        currentEnemy->dx = -1;
        currentEnemy->update();
      }

  currentEnemy->update();
  QLineF distance(pos(), currentEnemy->pos());
  if (distance.length() >= 50) {
      movementSpeed = 0.5;
      this->moveTo(currentEnemy->pos());
      return;
    }
  if (reloading == coolDown) {
      currentEnemy->hp -= this->damage;
      reloading = 0;
      currentEnemy->update();
    } else
    reloading++;

  if (currentEnemy->reloading >= currentEnemy->cooldown) {
      this->hp -= currentEnemy->damage;
      currentEnemy->reloading = 0;
      this->update();
    } else
    if (currentEnemy->slowedDown) {
        currentEnemy->reloading++;
      } else {
        currentEnemy->reloading+=2;
      }


  if (this->hp <= 0) {
      currentEnemy->isBlocked = false;
      currentEnemy->dx = 0;
      return;
    }
  if (currentEnemy->hp <= 0) {
      changingRoute = false;
      readyToStrike = false;
      currentEnemy = nullptr;
    }
}

void FriendlyNPC::checkForEnemies() {
  if (changingRoute) {
      if (currentEnemy != nullptr)
        currentEnemy->isBlocked = false;
      currentEnemy = nullptr;
      moveTo(routePoint);
      //      movementSpeed = 0.5;
    }
  else {
      if (blockingAnEnemy) {
          attackEnemy();
          return;
        }
      movementSpeed = 0.33;
      if (!readyToStrike) {
          moveTo(routePoint);
          if (currentEnemy != nullptr)
            currentEnemy->isBlocked = false;
        }
      else {
          for (int i = 0; i < units.size(); i++) {
              QLineF line(pos(), units[i]->pos());
              QLineF distanceFromCurrentPosToSpawnPoint(pos(),spawnPoint);
              if (line.length() < checkRadius && distanceFromCurrentPosToSpawnPoint.length() < checkRadius*1.5 /*&& !collidingUnits.contains(units[i])*/) {
                  currentEnemy = units[i];
                  blockingAnEnemy = true;
                  break;
                }
            }
          if (currentEnemy == nullptr || currentEnemy->deleted) {
              if (QLineF(pos(),routePoint).length() > 1)
                moveTo(routePoint);
              blockingAnEnemy = false;
              if (hp < maxHP) {
                  if (regenerating >= regenSpeed) {
                      if (hp+hpRegen > maxHP)
                        hp = maxHP;
                      else
                        hp += hpRegen;
                      regenerating = regenSpeed-500;
                    } else regenerating++;
                  this->update();
                } else
                regenerating = 0;
              //          return;
            }
        }
    }
}
////////////////////////Graphics/////////////////////
QRectF FriendlyNPC::boundingRect() const
{
  return QRectF(-50,-50, 100, 100);
}

void FriendlyNPC::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  // HP bar
  QPen pen;
  pen.setColor(Qt::black);
  pen.setWidth(11);
  painter->setPen(pen);
  painter->drawLine(-30,-45, 30,-45);
  pen.setWidth(10);
  pen.setColor(Qt::red);
  painter->setPen(pen);
  painter->drawLine(-30,-45,30,-45);
  pen.setColor(Qt::green);
  painter->setPen(pen);
  qreal qrealHP = hp,
      qrealMaxHP = maxHP,
      relation = qrealHP/qrealMaxHP;
  painter->drawLine(-30,-45, relation*60-30,-45);
  if (dx < 0) {
      QTransform transf = painter->transform();
      transf.scale(-1,1);
      painter->setTransform(transf);
    }


  painter->setPen(Qt::PenStyle::NoPen);

  painter->drawPixmap(boundingRect(), spriteImage, spriteImage.rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
