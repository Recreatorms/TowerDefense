#ifndef TOWERS_H
#define TOWERS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

#include "bullet.h"
#include "units.h"
#include "tile.h"
#include "friendlynpc.h"
#include "interface.h"
class Tower : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString type, qreal radius, QVector<Unit*> _units, QVector<Interface *> _interfaces);
    ~Tower() {}

    void showRadius();
    void buyTower();
    void sellTower();

    void updateUnits(QVector<Unit*> _units);
    qreal distanceTo(QGraphicsItem *item);
    void attackTarget(QPointF destination);
    void spawnFriendlyNPC();


    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);


    qreal damage;
    int attackSpeed;
public slots:
    void acquireTarget();
    void spawnNPC();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
    QPointF pos1, pos2;
    QVector<Unit*> units;
    QVector<FriendlyNPC *> npcs;
    QVector<Interface *> interfaces;
    QString type;
    qreal attackRadius;

    bool onCooldown;
    int reloadSpeed;
    int reloading;
    bool hasTarget;

    int numberOfNPCs;
    int respawnTimer;
    int respawning;
    bool respawn;

    QPointF attackDest;
    QGraphicsEllipseItem * attackArea;
    QPixmap *spriteImage;
};

#endif // TOWERS_H
