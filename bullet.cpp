#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
const qreal g = 10 * 150;
Bullet::Bullet(QObject * parent, QPointF _originPos,  QPointF _destination, int _slowTimer, QString _type, qreal _radiusOfTower, int _damage, QVector<Unit*> &_units) :
  QObject(parent), units(_units)
{
  if (_type == "Archer" || _type == "Musketeer")
    spriteImage =  QPixmap("../TowerDefense/images/Towers/Archer/bullet.png");
  if (_type == "Artillery") {
      if (_damage == 2)
        spriteImage =  QPixmap("../TowerDefense/images/Towers/Artillery/projectile_Level1.png");
      if (_damage == 3)
        spriteImage = QPixmap("../TowerDefense/images/Towers/Artillery/projectile_Level2.png");
      if (_damage == 4)
        spriteImage = QPixmap("../TowerDefense/images/Towers/Artillery/projectile_Level3.png");
      this->setScale(0.25);
    }
  if (_type == "Mage") {
      spriteImage =  QPixmap("../TowerDefense/images/Towers/Mage/22.png");
      QTransform t;
      slowTimer = _slowTimer;
      t.translate(x(), y());
      t.rotate(90);
      t.translate(-x(), -y());
      setTransform(t);
      setScale(0.25);
    }
  originPos = _originPos;
  setPos(originPos);
  setRotation(-90);
  //    units = _units;rr
  destination = _destination;
  type = _type;
  radiusOfTower = _radiusOfTower;
  damage = _damage;
  overallDistance = QLineF(originPos,destination);
  if (type == "Archer" || type == "Artillery") {
      if (type == "Artillery") {
          radiusOfExplosion = 100;
          flightTime = overallDistance.length()/radiusOfTower + 0.1; //  seconds
        }
      else
        flightTime = overallDistance.length()/radiusOfTower - 0.2; //  seconds
      double dx = overallDistance.dx(),
          dy = -overallDistance.dy();
      Vox = dx/flightTime;
      Voy = (dy + g*pow(flightTime,2)*0.5)/flightTime;
      Vo = sqrt(Vox*Vox+Voy*Voy);
      elapsedTime = 0;
      launchTime = 10; // milliseconds
    }
  else {
      if (type == "Musketeer") {
          Vo = 3;
          launchTime = 1;
        }
      if (type == "Rapid") {
          Vo = 1;
          launchTime = 1;
        }
      if (type == "Mage") {
          Vo = 0.5;
          launchTime = 1;
        }
    }


  //    timer = new QTimer();
  //    connect(timer, &QTimer::timeout, this, &Bullet::move);
  //    timer->start(launchTime);
  //    timer->start(launchTime);
}


void Bullet::move()
{  
  QLineF distanceToTarget(this->pos(), destination);
  if (canDealDamage) {
      double alpha = -overallDistance.angle();
      if (type == "Archer" || type == "Artillery") {
          lastPos = QPointF(originPos.rx() + dx, originPos.ry() - dy);
          elapsedTime += launchTime*0.001;
          dx = Vox*elapsedTime;
          dy = Voy*elapsedTime - g*pow(elapsedTime,2)*0.5;
          if (distanceToTarget.length() > 5)
            setPos(originPos.rx() + dx, originPos.ry() - dy);
          if (type == "Archer")
            setRotation(-QLineF(lastPos, pos()).angle());
        } else {
          lastPos = pos();
          dx = Vo * qCos(qDegreesToRadians(alpha));
          dy = Vo * qSin(qDegreesToRadians(alpha));
          setPos(x() + dx, y() + dy);
          setRotation(-QLineF(lastPos, pos()).angle());
        }
    }
  QLineF distance(originPos,pos());
  if  (distance.length() > radiusOfTower) {
      if (type != "Archer")
        Vo = Vo * 0.1;
      else
        if (dy < 10)
          Vo = Vo * 0.5;
    }
  if (Vo < 0.3 && type != "Artillery") {
      setOpacity(opacity()-0.15);
      canDealDamage = false;
    }
  if (opacity()== 0.0)
    this->~Bullet();

  if (type != "Artillery") {
      if (distanceToTarget.length() < 25) { // небольшая оптимизация


          Unit *unit = nullptr;
          if (!this->QObject::d_ptr->wasDeleted) {
              for (int i = 0; i < units.size(); i++) {
                  if (units[i] != nullptr) {
                      QLineF line(units[i]->pos(),pos());
                      if (line.length() < 75) {
                          unit = units[i];
                          break;
                        }
                    }
                }
              if (unit && canDealDamage) {
                  unit->hp -= damage;
                  if (type == "Mage") {
                      unit->slowTimer = this->slowTimer;
                      unit->slowedDown = true;
                    }
                  this->~Bullet();
                }
              if (unit == nullptr) {
                  Vo = 0;
                }
            }

        }
    } else {
      if (distanceToTarget.length() < 10) {

          QPointF pos1(-radiusOfExplosion,-radiusOfExplosion),
              pos2(radiusOfExplosion,radiusOfExplosion);
          QGraphicsEllipseItem *explosionArea = new QGraphicsEllipseItem(QRectF(pos1,pos2), this);
          explosionArea->setPos(boundingRect().center() - explosionArea->rect().center());

          QList<Unit*> collidingUnits;
          for (int i = 0; i < units.size(); i++) {
              QLineF line(units[i]->pos(),pos());
              if (line.length() < radiusOfExplosion && !collidingUnits.contains(units[i]))
                collidingUnits.push_back(units[i]);
            }

          for (int i = 0; i < collidingUnits.size(); i++) {
              if (canDealDamage)
                collidingUnits[i]->hp -= damage;
            }
          canDealDamage = false;
          Explosion *explosion = new Explosion(nullptr, pos());
          this->scene()->addItem(explosion);
          explosionArea->~QGraphicsEllipseItem();
          this->~Bullet();
        }
    }
}

QRectF Bullet::boundingRect() const
{
  return spriteImage.rect();
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawPixmap(boundingRect(), spriteImage, spriteImage.rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

//==============================================================================//

Explosion::Explosion(QObject *parent, QPointF _pos) :
  QObject(parent), QGraphicsItem()
{
  setPos(_pos);
  lifeTimer = new QTimer();
  connect(lifeTimer, &QTimer::timeout, this, &Explosion::nextFrame);
  lifeTimer->start(40);
}

Explosion::~Explosion()
{
  lifeTimer->~QTimer();
  this->scene()->removeItem(this);
}

void Explosion::nextFrame()
{
  if (currentFrame > 5) {
    lifeTimer->stop();
    this->~Explosion();
  }
  else {
      currentFrame++;
      this->update();
    }
}

QRectF Explosion::boundingRect() const
{
  return QRectF(-50,-50,100,100);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  explosionPixmap = QPixmap("../TowerDefense/images/Towers/Artillery/explosion" + QString::number(currentFrame));
  painter->drawPixmap(boundingRect(), explosionPixmap, explosionPixmap.rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
