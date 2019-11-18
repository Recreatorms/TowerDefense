#ifndef TOWERS_H
#define TOWERS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include "bullet.h"
#include "units.h"
#include "tile.h"
class Tower : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QChar type, qreal radius, QVector<Unit*> _units);
    ~Tower() {}

    void shoot();
    void showRadius();
    void buyTower();
    void sellTower();

    void updateUnits(QVector<Unit*> _units);
    int damage;
    int attackSpeed;
    qreal distanceTo(QGraphicsItem *item);
    void attackTarget(QPointF destination);
public slots:
    void acquireTarget();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    QPointF pos1, pos2;
    QVector<Unit*> units;
    QChar type;
    qreal attackRadius;
    bool onCooldown;
    int reloadSpeed;
    int reloading;
    bool hasTarget;
    QPointF attackDest;
    QGraphicsEllipseItem * attackArea;
    QPixmap *spriteImage;
};

#endif // TOWERS_H
