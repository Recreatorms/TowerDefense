#ifndef FRIENDLYNPC_H
#define FRIENDLYNPC_H

#include <QObject>
#include <QGraphicsItem>

#include <QTimer>
#include <QPainter>

#include "qmath.h"
#include "units.h"

class FriendlyNPC : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FriendlyNPC(QObject *parent, QPointF _spawnPoint, QPointF _routePoint, QString _type, QVector<Unit*> _units);
    ~FriendlyNPC() {}

    void attackEnemy(Unit* enemy);

    void updateUnits(QVector<Unit *> _units);

    void moveTo(QPointF pos);

    bool blockingAnEnemy;
    int hp;
public slots:
    void checkForEnemies();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    bool readyToStrike;
    QPointF routePoint;
    QPointF spawnPoint;
    int damage;
    int coolDown;
    int reloading;
    int checkRadius;
    int currentEnemy;
    qreal dx = 0, dy = 0;
    QList<Unit*> collidingUnits;
    QVector<Unit*> units;
    QPixmap *spriteImage;
};

#endif // FRIENDLYNPC_H
