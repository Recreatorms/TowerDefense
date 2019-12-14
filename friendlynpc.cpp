#include "friendlynpc.h"

FriendlyNPC::FriendlyNPC(QObject *parent, QPointF _spawnPoint, QPointF _routePoint, QVector<Unit*> _units, QVector<Interface *> _interfaces, int _level) :
    QObject(parent), QGraphicsItem()
{
    spawnPoint = _spawnPoint;
    setPos(spawnPoint);
    units = _units;
    currentEnemy = nullptr;
    routePoint = _routePoint;
    blockingAnEnemy = false;
    readyToStrike = false;
    interfaces = _interfaces;
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
  interfaces[5]->typeOfUnit = "Friendly";
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


void FriendlyNPC::attackEnemy(Unit* enemy) {
      if (enemy == nullptr) {
          readyToStrike = true;
          moveTo(routePoint);

          return;
      }
      enemy->isBlocked = true;
      QLineF distance(pos(), enemy->pos());
      if (distance.length() >= 10) {
        movementSpeed = 0.5;
        this->moveTo(enemy->pos());
        return;

        }
      if (reloading == coolDown) {
        enemy->hp -= this->damage;
        reloading = 0;
        enemy->update();
      } else
          reloading++;

      if (enemy->reloading >= enemy->cooldown) {
          this->hp -= enemy->damage;
          enemy->reloading = 0;
          this->update();
      }

      if (this->hp <= 0)
          enemy->isBlocked = false;
      if (enemy->hp <= 0) {
        readyToStrike = false;
        currentEnemy = nullptr;

      }
}

void FriendlyNPC::updateUnits(QVector<Unit *> _units) {
    units = _units;
    this->update();
}

void FriendlyNPC::updateStats()
{
  switch (level) {
    case 1: {
        maxHP = 5;
        hp = maxHP;
        regenSpeed = 3000;
        regenerating = 0;
        reloading = 0;
        checkRadius = 101;
        damage = 1;
        coolDown = 250;
        break;
    }
    case 2: {
        maxHP = 10;
        hp = maxHP;
        regenSpeed = 3000;
        regenerating = 0;
        reloading = 0;
        checkRadius = 101;
        damage = 2;
        coolDown = 250;
        break;
      }
    case 3: {
        maxHP = 15;
        hp = maxHP;
        regenSpeed = 3000;
        regenerating = 0;
        reloading = 0;
        checkRadius = 101;
        damage = 3;
        coolDown = 250;
        break;
      }
  }
  this->update();
}

void FriendlyNPC::checkForEnemies() {
    if (changingRoute) {
      moveTo(routePoint);
//      movementSpeed = 0.5;
    }
    else {
    movementSpeed = 0.33;
    if (!readyToStrike)
      moveTo(routePoint);
    else {
        if (currentEnemy == nullptr) {
          blockingAnEnemy = false;
          if (hp < maxHP) {
            if (regenerating >= regenSpeed) {
              hp += hpRegen;
              regenerating = 2500;
            } else regenerating++;
            this->update();
          } else
          regenerating = 0;
//          return;
        }
        else if (blockingAnEnemy) {
          attackEnemy(currentEnemy);
          return;
        }
        for (int i = 0; i < units.size(); i++) {
        QLineF line(routePoint, units[i]->pos());
        if (line.length() < checkRadius /*&& !collidingUnits.contains(units[i])*/) {
          currentEnemy = units[i];
          blockingAnEnemy = true;
          break;
        }
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
    spriteImage = new QPixmap("../TowerDefense/images/Towers/Support/knight_" + QString::number(level) + ".png");
    // HP bar
    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawLine(-30,-45,30,-45);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(-30,-45, 60/maxHP*hp-30,-45);
    if (dx <= 0) {
      QTransform transf = painter->transform();
      transf.scale(-1,1);
      painter->setTransform(transf);
    }


    painter->setPen(Qt::PenStyle::NoPen);

    painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
