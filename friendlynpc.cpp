#include "friendlynpc.h"
#include <QEvent>
FriendlyNPC::FriendlyNPC(QObject *parent, QPointF _spawnPoint, QPointF _routePoint, QString _type, QVector<Unit*> _units) :
    QObject(parent), QGraphicsItem()
{
    spawnPoint = _spawnPoint;
    units = _units;
    routePoint = _routePoint;
    blockingAnEnemy = false;
    readyToStrike = false;
    reloading = 0;
    hp = 5;
    //if (type == ...) {
      checkRadius = 100;
      damage = 0;
      coolDown = 250;
      setPos(spawnPoint);

    QTimer *checkingTimer = new QTimer();
    checkingTimer->start(1);
    connect(checkingTimer, &QTimer::timeout, this, &FriendlyNPC::checkForEnemies);
}

void FriendlyNPC::moveTo(QPointF pos) {
    qreal Vo = 0.25,
          alpha = -QLineF(this->pos(), pos).angle();
    dx = Vo * qCos(qDegreesToRadians(alpha));
    dy = Vo * qSin(qDegreesToRadians(alpha));
    setPos(x() + dx, y() + dy);

    if (this->pos() == routePoint)
      readyToStrike = true;
}


void FriendlyNPC::attackEnemy(Unit* enemy) {
      enemy->isBlocked = true;
      QLineF distance(pos(), enemy->pos());
      if (distance.length() >= 10) {
        this->moveTo(enemy->pos());
        return;
      }
      if (reloading == coolDown) {
        enemy->hp -= this->damage;
        reloading = 0;
      } else
          reloading++;

      if (enemy->reloading == enemy->cooldown) {
          this->hp -= enemy->damage;
          enemy->reloading = 0;
      } else
        enemy->reloading++;

      if (this->hp <= 0)
          enemy->isBlocked = false;
      if (enemy->hp <= 0) {
        blockingAnEnemy = false;
        readyToStrike = false;
        if (collidingUnits.indexOf(enemy) == collidingUnits.size() - 1)
          collidingUnits.pop_back();
        else {
          if (collidingUnits.size() > 1) {
            for (int j = collidingUnits.indexOf(enemy); j < collidingUnits.size()-1; j++)
              collidingUnits[j] = collidingUnits[j+1];
            collidingUnits[collidingUnits.size()-2] = collidingUnits[collidingUnits.size()-1];
            collidingUnits.pop_back();
          } else
            collidingUnits.pop_back();
        }
      }
//    enemy->blocked = true;
//    enemy->hp -=damage;
//    if (enemy->cooldown == enemy->attackSpeed) {
//        this->hp -=enemy->attackBaseValue;
//        enemy->cooldown = 0;
//    }
}

void FriendlyNPC::updateUnits(QVector<Unit *> _units) {
    units = _units;
}

void FriendlyNPC::checkForEnemies() {
    if (!readyToStrike)
      moveTo(routePoint);
    else {
      for (int i = 0; i < units.size(); i++) {
        QLineF line(routePoint, units[i]->pos());
        if (line.length() < checkRadius && !collidingUnits.contains(units[i]))
            collidingUnits.push_back(units[i]);
        else {
            if (line.length() > checkRadius && collidingUnits.contains(units[i])) {
                if (collidingUnits.indexOf(units[i]) == collidingUnits.size() - 1)
                  collidingUnits.pop_back();
                else {
                  if (collidingUnits.size() > 1) {
                    for (int j = collidingUnits.indexOf(units[i]); j < collidingUnits.size()-1; j++)
                      collidingUnits[j] = collidingUnits[j+1];
                    collidingUnits[collidingUnits.size()-2] = collidingUnits[collidingUnits.size()-1];
                    collidingUnits.pop_back();
                  } else
                    collidingUnits.pop_back();
                }
             }
          }
      }
      if (blockingAnEnemy && !collidingUnits.isEmpty()) {
        attackEnemy(collidingUnits[currentEnemy]);
        return;
      }
      if (collidingUnits.size() == 0) {
        blockingAnEnemy = false;
        return;
      } else {
        qreal closestDist = checkRadius;
        for (int i = 0; i < collidingUnits.size(); i++) {
            QLineF distance(routePoint,collidingUnits[i]->pos());
            qreal thisDist = distance.length();
            if (thisDist < closestDist) {
                closestDist = thisDist;
                currentEnemy = i;
                blockingAnEnemy = true;
            }
        }
      }
      if (blockingAnEnemy) {
        attackEnemy(collidingUnits[currentEnemy]);
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
    spriteImage = new QPixmap("../TowerDefense/images/knight.png");
    if (dx <= 0) {
      QTransform transf = painter->transform();
      transf.scale(-1,1);
      painter->setTransform(transf);
    }
    painter->drawPixmap(boundingRect(), *spriteImage, QRectF(0,0,100,100));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
