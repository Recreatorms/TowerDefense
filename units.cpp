#include "units.h"
#include <cmath>


Unit::Unit(QObject *parent, int _startPos, QString _type, QVector<QPointF> & _path, QVector<Interface *>& _interfaces) :
  QObject(parent), QGraphicsItem(), startPos(_startPos), path(_path), interfaces(_interfaces)
{
  //    currentPos = 0;

  setPos(path[currentPos]);
  isBlocked = false;
  type = _type;

  if (type == "Ogre (Level 1)") {
      damage = 1;
      maxHP = 4;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.6;
      cooldown = 200*2;
      income = 5;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Ogre (Level 2)") {
      damage = 2;
      maxHP = 8;
      hp = 8;
      attackBaseValue = 2;
      initialSpeed = 0.45;
      cooldown = 300*2;
      income = 15;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Dark Ogre") {
      damage = 3;
      maxHP = 10;
      hp = maxHP;
      attackBaseValue = 3;
      initialSpeed = 0.6;
      cooldown = 250*2;
      income = 20;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Orc") {
      damage = 5;
      maxHP = 6;
      hp = maxHP;
      attackBaseValue = 2;
      initialSpeed = 0.65;
      cooldown = 250*2;
      income = 25;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Troll") {
      damage = 2;
      maxHP = 7;
      hp = maxHP;
      attackBaseValue = 2;
      initialSpeed = 0.5;
      cooldown = 225*2;
      income = 10;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Dark Troll") {
      setScale(1.1);
      damage = 4;
      maxHP = 14;
      hp = maxHP;
      attackBaseValue = 5;
      initialSpeed = 0.45;
      cooldown = 225*2;
      income = 30;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Goblin (Level 1)") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units//1_enemies_1_WALK_000.png");
      setScale(0.9);
      damage = 1;
      maxHP = 3;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.8;
      cooldown = 150*2;
      income = 10;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Goblin (Level 2)") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units//1_enemies_1_WALK_000.png");
      setScale(0.9);
      damage = 1;
      maxHP = 6;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.9;
      cooldown = 125*2;
      income = 30;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Bandit (Level 1)") {
      damage = 1;
      maxHP = 9;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.6  ;
      cooldown = 200*2;
      income = 15;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Bandit (Level 2)") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_000.png");
      damage = 2;
      maxHP = 11;
      hp = maxHP;
      attackBaseValue = 2;
      initialSpeed = 0.7;
      cooldown = 160*2;
      income = 20;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Bandit (Level 3)") {
      damage = 3;
      maxHP = 13;
      hp = maxHP;
      attackBaseValue = 3;
      initialSpeed = 0.45;
      cooldown = 225*2;
      income = 25;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "DarkKnight") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units/DarkKnight/1_enemies_1_WALK_000.png");
      damage = 10;
      maxHP = 80;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.3  ;
      cooldown = 300*2;
      income = 250;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "DarkKnight (Boss)") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units/DarkKnight/1_enemies_1_WALK_000.png");
      setScale(1.5);
      damage = 20;
      maxHP = 750;
      hp = maxHP;
      attackBaseValue = 15;
      initialSpeed = 0.1  ;
      cooldown = 450*2;
      income = 1000;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Snowman (Boss)") {
      //      spriteImage = new QPixmap("../TowerDefense/images/Units/DarkKnight/1_enemies_1_WALK_000.png");
      setScale(1.25);
      damage = 50;
      maxHP = 1250;
      hp = maxHP;
      attackBaseValue = 20;
      initialSpeed = 0.15 ;
      cooldown = 1000*2;
      income = 1000;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Bat") {
      damage = 1;
      maxHP = 3;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.65 ;
      cooldown = 200*2;
      income = 5;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Dark Bat") {
      damage = 1;
      maxHP = 6;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.7 ;
      cooldown = 200*2;
      income = 15;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Wizard") {
      damage = 10;
      maxHP = 30;
      hp = maxHP;
      attackBaseValue = 3;
      initialSpeed = 0.4;
      cooldown = 300*2;
      income = 50;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Dark Wizard"){
      damage = 100;
      maxHP = 100;
      hp = maxHP;
      attackBaseValue = 10;
      initialSpeed = 0.35 ;
      cooldown = 300*2;
      income = 300;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  if (type == "Ghost") {
      damage = 10;
      maxHP = 2;
      hp = maxHP;
      attackBaseValue = 1;
      initialSpeed = 0.75 ;
      cooldown = 300*2;
      income = 1;
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/20) + ".png");
      return;
    }
  //    QTimer *pathTimer = new QTimer();
  //    pathTimer->start(1);
  //    connect(pathTimer, &QTimer::timeout, this, &Unit::completePath);
}

Unit::~Unit(){
  spriteImage->~QPixmap();
//  delete spriteImage;
  this->scene()->removeItem(this);
  deleted = true;
  //  if (spriteImage != nullptr)
}


void Unit::moveTo(QPointF point) {
  if (slowedDown) {
      speed = initialSpeed/2;
      slowingDown++;
      if (currentFrame <= 360) {
          currentFrame++;
        } else currentFrame = 0;
      if (slowingDown >= slowTimer)
        slowedDown = false;
    } else {
      if (currentFrame <= 360) {
          currentFrame+=2;
        } else currentFrame = 0;
      slowingDown = 0;
      speed = initialSpeed;
    }
  if (isBlocked)
    return;
  qreal length = std::hypot(pos().x() - point.x(), pos().y() - point.y());
  int x = this->x(); // то что нужно, округляем
  int y = this->y();
  if (QPointF(x,y) == point)
    currentPos++;
  if (x < point.rx() && y == point.ry())  {//right
      dx = speed;
      setPos(mapToScene(speed,0));
      if (length <= 0.1) {
          currentPos++;
          return;
        }
    }
  else if (x > point.rx() && y == point.ry()) { //left
      dx = -speed;
      setPos(mapToScene(-speed,0));
      if (length <= 0.1) {
          currentPos++;
          return;
        }
    }
  if (x == point.rx() && y < point.ry()) { //down
      setPos(mapToScene(0,speed));
      if (length <= 0.1) {
          currentPos++;
          return;
        }
    }
  else if (x == point.rx() && y > point.ry()) {//up
      setPos(mapToScene(0,-speed));
      if (length <= 0.1) {
          currentPos++;
          return;
        }
    }
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  interfaces[5]->typeOfEntity = "Unit";
  interfaces[5]->typeOfUnit = type;//
  interfaces[5]->entityInfo(this->hp, this->damage, this->attackBaseValue, 0, 0.0, 0, 0);
  interfaces[5]->update();
  clicked = true;
  Q_UNUSED(event)
}

void Unit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  clicked = false;
  Q_UNUSED(event)
}

////////////////////////////Graphics/////////////////////////
QRectF Unit::boundingRect() const
{
  return QRectF(-50,-50,100,100); // иначе говоря хитбокс
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPen pen;
  pen.setColor(Qt::black);
  pen.setWidth(11);
  painter->setPen(pen);
  painter->drawLine(-30,-45, 30,-45);
  pen.setWidth(10);
  pen.setColor(Qt::red);
  painter->setPen(pen);
  painter->drawLine(-30,-45,30,-45);
  if (slowedDown)
    pen.setColor(Qt::blue);
  else
    pen.setColor(Qt::green);
  painter->setPen(pen);
  qreal qrealHP = hp,
      qrealMaxHP = maxHP,
      relation = qrealHP/qrealMaxHP*60;
  painter->drawLine(-30,-45, -30+relation,-45);
  painter->setPen(Qt::PenStyle::SolidLine);

  if (dx <= 0) {
      QTransform transf = painter->transform();
      transf.scale(-1,1);
      painter->setTransform(transf);
    }

  spriteImage->~QPixmap();
  if (isBlocked)
      spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_ATTACK_00" + QString::number(currentFrame/40) + ".png");
  else
    spriteImage = new QPixmap("../TowerDefense/images/Units/" + type + "/1_enemies_1_WALK_00" + QString::number(currentFrame/40) + ".png");
  painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());


//  Q_UNUSED(option)
//  Q_UNUSED(widget)
}

//void Unit::completePath() {
//  for(int k = 0; k < path.size(); k++) {
////    for (int i = 0; i < units.size(); i++) {
//     if(this->startPos == k) {
//         if(this->currentPos == path[k].size()-2)
//             this->moveTo(path[k][path[k].size()-1]);
//             else if (this->pos() != path[k][this->currentPos +1])
//                 this->moveTo(path[k][this->currentPos]);
//       }


//}



