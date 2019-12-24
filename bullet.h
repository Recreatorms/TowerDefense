#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPixmap>
#include <QGraphicsItem>
#include "units.h"
#include "tile.h"
//#include <QTimer>
//#include <QThread>
class Explosion : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  explicit Explosion(QObject *parent, QPointF _pos);
  ~Explosion() override;
private slots:
  void nextFrame();
private:
  QTimer *lifeTimer;
  QPixmap explosionPixmap;
  int currentFrame = 0;
protected:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

//==============================================================================//

class Bullet : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  Bullet(QObject * parent, QPointF _originPos, QPointF _destination, int _slowTimer, QString _type, qreal _radiusOfTower, int _damage, QVector<Unit*> &_units);
  ~Bullet() override {
//      timer->stop();
//      if (!timer->isActive())
//      delete timer;
      deleted = true;
//      this->scene()->removeItem(this);
//      if (spriteImage != nullptr)
//       delete spriteImage;
//      delete this;
  }
  bool deleted = false;
  int launchTime;
  int slowTimer;
public slots:
  void move();
protected:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
  QVector<Unit*> &units;
  bool canDealDamage = true;
//  QTimer *moveTimer;
//  QTimer *timer;
  QPointF originPos;
  QPointF destination;
  QPixmap spriteImage;
//  QVector<Unit*> units;
  int radiusOfExplosion;
  QString type;
  qreal radiusOfTower;
  int damage;
  QLineF overallDistance;
  QPointF lastPos;
  qreal dx, dy;
  qreal Vox, Voy;
  qreal Vo;
  //double alpha;
  double flightTime = 0;
  double elapsedTime;
};

#endif // BULLET_H
