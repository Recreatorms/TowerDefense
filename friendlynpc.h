#ifndef FRIENDLYNPC_H
#define FRIENDLYNPC_H

#include <QObject>
#include <QGraphicsItem>


#include <QPainter>
#include <QPen>
#include "qmath.h"
#include "units.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>
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
    QString type;

    int maxHP;
    int hpRegen = 1;
    int regenSpeed;
    int regenerating = 0;

    int damage;
    int coolDown;
    int reloading;
    int checkRadius;

//    int currentEnemy;
    qreal dx = 0, dy = 0;

    QVector<Unit*> units;
    Unit* currentEnemy;


    QPixmap *spriteImage;
};

#endif // FRIENDLYNPC_H
