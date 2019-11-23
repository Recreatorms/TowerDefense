#include "friendlynpc.h"

FriendlyNPC::FriendlyNPC(QObject *parent, QPointF _routePoint, QChar _type, QVector<Unit*> _units) :
    QObject(parent), QGraphicsItem()
{
    units = _units;
    QTimer *checkingTimer = new QTimer();
    checkingTimer->start(1);
    connect(checkingTimer, &QTimer::timeout, this, &FriendlyNPC::checkForEnemies);
}

void FriendlyNPC::attackEnemy(Unit* enemy) {

}

void FriendlyNPC::updateUnits(QVector<Unit *> _units) {
    units = _units;
}

void FriendlyNPC::checkForEnemies() {
    for (int i = 0; i < units.size(); i++) {
        QLineF line(units[i]->pos(), pos());
        if (line.length() < checkRadius && !collidingUnits.contains(units[i]))
            collidingUnits.push_back(units[i]);
    }
    if (blockingAnEnemy) {
        attackEnemy(collidingUnits[currentEnemy]);
    }
    if (collidingUnits.size() == 0) {
        blockingAnEnemy = false;
        return;
    } else {
        qreal closestDist = checkRadius*100*0.5;
        for (int i = 0; i < collidingUnits.size(); i++) {
            QLineF distance(pos(),collidingUnits[i]->pos());
            qreal thisDist = distance.length();
            if (thisDist < closestDist) {
                closestDist = thisDist;
                currentEnemy = i;
                blockingAnEnemy = true;
            }
        }
    }
}
