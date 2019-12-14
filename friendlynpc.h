#ifndef FRIENDLYNPC_H
#define FRIENDLYNPC_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include <QPainter>
#include <QPen>

#include "qmath.h"
#include "units.h"

class FriendlyNPC : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FriendlyNPC(QObject *parent, QPointF _spawnPoint, QPointF _routePoint, QVector<Unit*> _units, QVector<Interface *> _interfaces, int _level);
    ~FriendlyNPC() {}

    void attackEnemy(Unit* enemy);

    void updateUnits(QVector<Unit *> _units);
    void updateStats();
    void moveTo(QPointF pos);

    bool blockingAnEnemy;
    int level;
    int damage;
    int coolDown;
    int maxHP;
    int hp;
    bool clicked = false;

    bool changingRoute = false;
    QPointF routePoint;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void checkForEnemies();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    bool readyToStrike;
    QPointF spawnPoint;
    QString type;
    qreal movementSpeed;
    int hpRegen = 1;
    int regenSpeed;
    int regenerating;
    int reloading;
    int checkRadius;

//    int currentEnemy;
    qreal dx = 0, dy = 0;
    QVector<Interface *> interfaces;
    QVector<Unit*> units;
    Unit* currentEnemy;


    QPixmap *spriteImage;
};

#endif // FRIENDLYNPC_H
