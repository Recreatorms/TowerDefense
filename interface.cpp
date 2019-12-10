#include "interface.h"
#include <QPushButton>
Interface::Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type) :
        QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    type = _type;
    if (type == "Info")
      typeOfEntity = "default";
    // screen = new InfoScreen(this, pos1, pos2);
}

void Interface::addGameInfo(int _hp, int _waveNumber, int _playerMoney)
{
  playerHP = _hp;
  playerMoney = _playerMoney;
  waveNumber = _waveNumber;
}

void Interface::entityInfo(int _hp, int _dmg, int _attackBase, int _radius, int _attackSpeed, int _movementSpeed, int _price /*, int hpRegen*/)
{
  hp = _hp;
  dmg = _dmg;
  attackBase = _attackBase;
  attackSpeed = _attackSpeed;
  radius = _radius;
  movementSpeed = _movementSpeed;
  price = _price;
}



QRectF Interface::boundingRect() const
{
    return QRectF(pos1,pos2);
}

void Interface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//  painter->setBrush(QBrush(Qt::DiagCrossPattern));
  painter->setPen(Qt::black);

  painter->setFont(QFont("Comic Sans MS", 25,-1,false));
  if (type == "Musketeer"){
    painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Musketeer");
  }
  if (type == "Rapid"){
    painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Rapid");
  }
  if (type == "Archer"){
    painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Archer");
  }
  if (type == "Support"){
    painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Support");
  }
  if (type == "Info") {
      if (typeOfEntity != "default") {
           if (typeOfEntity == "Tower") {
             painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), typeOfTower);
             painter->drawText(QPointF(pos1.x()+10,pos1.y()+200), QString("Cost = " + QString::number(price)));
             if (typeOfTower != "Support") {
                 painter->drawText(QPointF(pos1.x()+10, pos1.y()+50), QString("Damage = " + QString::number(dmg)));
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+100), QString("Attack Speed = " + QString::number(attackSpeed)));
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+150), QString("Range = " + QString::number(radius)));
             } else {
                 painter->drawText(QPointF(pos1.x()+10, pos1.y()+50), QString("Defender's max HP = " + QString::number(hp)));
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+100), QString("Damage = " + QString::number(dmg)));
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+150), QString("Attack Speed = " + QString::number(attackSpeed)));
               }
             } else {
             if (typeOfEntity == "Unit" && hp > 0) {
               painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), typeOfUnit);
               painter->drawText(QPointF(pos1.x()+10, pos1.y()+50), QString("HP = " + QString::number(hp)));
               painter->drawText(QPointF(pos1.x()+10,pos1.y()+100), QString("Damage = " + QString::number(dmg)));
               if (typeOfUnit != "Friendly") {
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+150), QString("Movement speed = " + QString::number(movementSpeed)));
                 painter->drawText(QPointF(pos1.x()+10,pos1.y()+200), QString("Damage To Base = " + QString::number(attackBase)));
               } else
               painter->drawText(QPointF(pos1.x()+10,pos1.y()+150), QString("Attack Speed = " + QString::number(attackSpeed)));
             }
           }
        } else {
          painter->drawText(QPointF(pos1.x()+10,pos1.y()+50), QString("Base HP = " + QString::number(playerHP)));
          painter->drawText(QPointF(pos1.x()+10,pos1.y()+100), QString("Money = " + QString::number(playerMoney)));
          painter->drawText(QPointF(pos1.x()+10,pos1.y()+150), QString("Wave = " + QString::number(waveNumber)));
        }/*
      if (typeOfEntity == "Musketeer") {
          painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Musketeer");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfEntity == "Rapid") {
        painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Rapid");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfEntity == "Archer") {
        painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Archer");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfEntity == "Support") {
      painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Support");
        // dmg
        // hp
        // numberOfDefenders
        // speed
        // SellPrice
        // UpgradePrice
        // reroute button
            //QPushButton *changeRoute = new QPushButton(QIcon(QPixmap("../TowerDefense/images/change_route.png")),"ROUTE", this->scene());
        // sell button
        // upgrade button
    }*/
  }
  if (type == "Upgrade") {
      painter->setBrush(Qt::DiagCrossPattern);
  }

  painter->drawRect(QRectF(pos1,pos2));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Interface::upgrade() {
  if (type == "Upgrade") {
    if (typeOfEntity == "Tower") {
      if (typeOfTower != "Support") {
      }
    }
  }
}
void Interface::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (type == "Rapid") {
    selectingMode = true;
    typeOfTower = "Rapid";
    dmg = 1;
    attackSpeed = 100;
    radius = 3;
    price = 50;
  }
  if (type == "Musketeer") {
    selectingMode = true;
    typeOfTower = "Musketeer";
    dmg = 3;
    attackSpeed = 1000;
    radius = 5;
    price = 125;
  }
  if (type == "Archer") {
    selectingMode = true;
    typeOfTower = "Archer";
    dmg = 2;
    attackSpeed = 500;
    radius = 4;
    price = 100;
  }
  if (type == "Support") {
    selectingMode = true;
    typeOfTower = "Support";
    hp = 12;
    dmg = 1;
    attackSpeed = 250;
    price = 75;
  }
  if (type == "Upgrade") {

  }
  this->update();
  Q_UNUSED(event)
}

void Interface::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if (selectingMode) {
    if (type == "Rapid")
      selectingMode = false;
    if (type == "Musketeer")
      selectingMode = false;
    if (type == "Archer")
      selectingMode = false;
    if (type == "Support")
      selectingMode = false;
  }
}
