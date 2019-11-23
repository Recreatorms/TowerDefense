#ifndef FRIENDLYNPC_H
#define FRIENDLYNPC_H

#include <QObject>
#include <QGraphicsItem>

#include <QTimer>

#include "units.h"
class FriendlyNPC : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FriendlyNPC(QObject *parent, QPointF _routePoint, QChar _type, QVector<Unit*> _units);
    ~FriendlyNPC() {}

    void attackEnemy(Unit* enemy);

    void updateUnits(QVector<Unit *> _units);


    bool blockingAnEnemy;
public slots:
    void checkForEnemies();
private:
    QPointF routePoint;
    int checkRadius;
    int currentEnemy;
    QList<Unit*> collidingUnits;
    QVector<Unit*> units;
};

#endif // FRIENDLYNPC_H
