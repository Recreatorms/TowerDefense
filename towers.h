#ifndef TOWERS_H
#define TOWERS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <thread>
#include <chrono>

#include <QTimer>
#include "mythread.h"
#include <QtDebug>
#include "bullet.h"
#include "units.h"
#include "tile.h"
#include "friendlynpc.h"
#include "interface.h"


class Tower : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  explicit Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type, int _price, int _index, QVector<Unit*> &_units, QVector<Interface *> &_interfaces, QVector<QVector<QString> >&_map);
  ~Tower();
  bool deleted = false;
  void setOptions(QVector<QVector<QString> > &map);

  //    void showRadius();
  //    void buyTower();
  //    void sellTower();
  void upgradeTower();
  void changeRouteTower(QPointF _routePoint);


  void updateUnits(QVector<Unit*> &_units);
  qreal distanceTo(QGraphicsItem *item);
  void attackTarget(QPointF destination);
  void spawnFriendlyNPC();


  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
  //    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  bool IsPaused = false;
  int level = 1;
  int price;
  int sellPrice;
  int index;
  int damage;
  QString type;
  QGraphicsEllipseItem * attackArea;
  QPointF pos1, pos2;
public slots:
  void acquireTarget();
  void spawnNPC();
signals:
  void spawned();
protected:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
  QPointF routePoint;
  QVector<Unit*> &units;
  QVector<FriendlyNPC *> npcs;
  QVector<Interface *> &interfaces;
  qreal attackRadius;
  qreal initialRadius;
  bool onCooldown;
  int reloadSpeed;
  int reloading;
  bool hasTarget;
  int slowTimer = 0;
  // npc
  //(this->npcs[0]->maxHP, this->npcs[0]->damage, 0, 0, this->npcs[0]->coolDown, 0, this->price)
  int maxHP, coolDown;
  int numberOfNPCs;
  int respawnTimer;
  int respawning;
  bool respawn;
  //    QThread *threadthread = new QThread();
  //  MyThread *myThread;
  //    QTimer *actionTimer;
  //    QTimer *spawnNPCtimer;
  //    QTimer *attackTimer;
  QVector<QVector<QString> > &map;
  QPointF attackDest;
  QPixmap spriteImage;
};

#endif // TOWERS_H
