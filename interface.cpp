#include "interface.h"
#include <QPushButton>
Interface::Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type) :
  QObject(parent), QGraphicsItem()
{
  pos1 = _pos1;
  pos2 = _pos2;
  type = _type;
  if (type == "Game")
    typeOfEntity = "default";
  // screen = new InfoScreen(this, pos1, pos2);
}

void Interface::addGameInfo(int _hp, int _waveNumber, int _playerMoney, int _maxWaves)
{
  playerHP = _hp;
  playerMoney = _playerMoney;
  waveNumber = _waveNumber;
  maxWaves = _maxWaves;
  update();
}

void Interface::entityInfo(int _hp, int _dmg, int _attackBase, qreal _radius, int _attackSpeed, int _price, int _sellPrice/*, int hpRegen*/)
{
  hp = _hp;
  dmg = _dmg;
  attackBase = _attackBase;
  attackSpeed = _attackSpeed;
  radius = _radius;
  price = _price;
  sellPrice = _sellPrice;
}



QRectF Interface::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Interface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //  painter->setBrush(QBrush(Qt::DiagCrossPattern));
  delete spriteImage;
  spriteImage = new QPixmap("../TowerDefense/images/Interface/table.png");
  painter->setPen(Qt::white);
  QFont font;
  font.setStyleStrategy(QFont::StyleStrategy::PreferQuality);
  //  font.setHintingPreference(QFont::HintingPreference::PreferFullHinting);
  font.setFamily("Comic Sans MS");
  font.setPointSize(23);
  font.setBold(false);
  font.setWeight(1);
  painter->setFont(font);

  if (type == "Game") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/table2.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x(),pos1.y()-15),QPointF(pos2.x(),pos2.y()+15)), *spriteImage, spriteImage->rect());
      painter->drawPixmap(QRectF(QPointF(pos1.x() + 30, (pos1.y()+pos2.y())/2 - 15), QPointF(pos1.x() + 60, (pos1.y()+pos2.y())/2 + 15)), heart, heart.rect());
      painter->drawText(QPointF(pos1.x()+ 70,(pos1.y()+pos2.y())/2 + 10), QString::number(playerHP));
      painter->drawPixmap(QRectF(QPointF(pos1.x() + 140, (pos1.y()+pos2.y())/2 - 15), QPointF(pos1.x() + 170, (pos1.y()+pos2.y())/2 + 15)), money, money.rect());
      painter->drawText(QPointF(pos1.x()+180,(pos1.y()+pos2.y())/2 + 10), QString::number(playerMoney));
      if (waveNumber+1 != maxWaves)
        painter->drawText(QPointF(pos1.x()+280,(pos1.y()+pos2.y())/2 + 10), QString("Wave = " + QString::number(waveNumber+1) + "/" + QString::number(maxWaves)));
      else
        painter->drawText(QPointF(pos1.x()+280,(pos1.y()+pos2.y())/2 + 10), QString("Wave = " + QString::number(maxWaves) + "/" + QString::number(maxWaves)));
      return;
    }
  if (type == "Archer") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/ArcherTable.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      painter->drawText(QPointF(pos2.x()-200,pos2.y()-40), ("Archer"));
      return;
    }
  if (type == "Support") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/SupportTable.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      painter->drawText(QPointF(pos2.x()-200,pos2.y()-40), "Support");
      return;
    }
  if (type == "Mage") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/MageTable.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      painter->drawText(QPointF(pos2.x()-200,pos2.y()-40), "Mage");
      return;
    }
  if (type == "Artillery") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/ArtilleryTable.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      painter->drawText(QPointF(pos2.x()-200,pos2.y()-40), "Artillery");
      return;
    }
  if (type == "Info") {
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      if (typeOfEntity != "default") {
          if (typeOfEntity == "Tower") {
              painter->drawText(QPointF(pos1.x()+30,pos2.y()-50), typeOfTower + " Tower (Level " + QString::number(level) + ")");
              if (selectingMode)
                painter->drawText(QPointF(pos1.x()+30,pos1.y()+200), QString("Build Cost = " + QString::number(price)));
              else {
                  if (typeOfTower != "Archer") {
                      if (level != 3 && price != 0 && typeOfTower != "Musketeer") {
                          painter->drawText(QPointF(pos1.x()+30,pos1.y()+200), QString("Upgrade Cost = " + QString::number(price)));
                          painter->drawText(QPointF(pos1.x()+30,pos1.y()+250), QString("Sell Cost = " + QString::number(sellPrice)));
                        } else
                        painter->drawText(QPointF(pos1.x()+30,pos1.y()+200), QString("Sell Cost = " + QString::number(sellPrice)));
                    } else if (typeOfTower == "Archer") {
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+200), QString("Upgrade Cost = " + QString::number(price)));
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+250), QString("Sell Cost = " + QString::number(sellPrice)));
                    }
                }
              if (typeOfTower != "Support") {
                  painter->drawText(QPointF(pos1.x()+30, pos1.y()+50), QString("Damage = " + QString::number(dmg)));
                  // attack speed
                  if (attackSpeed <= 400) {
                      if (attackSpeed <= 300) {
                          if (attackSpeed <= 150)
                            painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Attack Speed = Very Fast"/*+ QString::number(attackSpeed)*/));
                          else
                            painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Attack Speed = Fast"/*+ QString::number(attackSpeed)*/));
                        } else
                        painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Attack Speed = Average"/*+ QString::number(attackSpeed)*/));
                    } else
                    if (attackSpeed <= 700)
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Attack Speed = Slow"/*+ QString::number(attackSpeed)*/));
                    else
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Attack Speed = Very Slow"/*+ QString::number(attackSpeed)*/));
                  // range

                  if (radius*100 <= 500) {
                      if (radius*100 <= 300) {
                          if (radius*100 <= 200)
                            painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Range = Really Small"/*+ QString::number(attackSpeed)*/));
                          else
                            painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Range = Small"/*+ QString::number(attackSpeed)*/));
                        } else
                        painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Range = Average"/*+ QString::number(attackSpeed)*/));
                    } else
                    if (radius*100 <= 600)
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Range = Big"/*+ QString::number(attackSpeed)*/));
                    else
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Range = Huge"/*+ QString::number(attackSpeed)*/));
                } else {
                  painter->drawText(QPointF(pos1.x()+30, pos1.y()+50), QString("Defender's max HP = " + QString::number(hp)));
                  painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Damage = " + QString::number(dmg)));
                  painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Attack Speed = Average"));
                }
            } else {
              if (typeOfEntity == "Unit" && hp > 0) {
                  painter->drawText(QPointF(pos1.x()+30, pos1.y()+50), QString("HP = " + QString::number(hp)));
                  painter->drawText(QPointF(pos1.x()+30,pos1.y()+100), QString("Damage = " + QString::number(dmg)));
                  if (typeOfUnit != "Defender") {
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+350), typeOfUnit);
//                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Movement speed = " + QString::number(movementSpeed)));
                      painter->drawText(QPointF(pos1.x()+30,pos1.y()+150), QString("Damage To Base = " + QString::number(attackBase)));
                    } else
                    painter->drawText(QPointF(pos1.x()+30,pos1.y()+350), QString(typeOfUnit + " (Level " + QString::number(level) + ")"));
                }
            }
          return;
        }
    }
  if (type == "Upgrade") {
      delete spriteImage;
      spriteImage = new QPixmap("../TowerDefense/images/Interface/EmptySquareTable.png");
      painter->drawPixmap(QRectF(QPointF(pos1.x()-10,pos1.y()),QPointF(pos2.x()+10,pos2.y())), *spriteImage, spriteImage->rect());
      return;
    }
  if (type != "Upgrade" && type != "Info" && type != "Game" && selectingMode) {
//      painter->setPen(Qt::yellow);
      painter->setBrush(QBrush(Qt::yellow));
      painter->drawRect(QRectF(pos1,pos2));
    }
  //  painter->drawRect(QRectF(pos1,pos2));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Interface::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (type == "Mage") {
      selectingMode = true;
      typeOfTower = "Mage";
      dmg = 2;
      attackSpeed = 500;
      radius = 3*1.1;
      price = 150;
      sellPrice = 75;
      this->update();
      return;
    }
  if (type == "Artillery") {
      selectingMode = true;
      typeOfTower = "Artillery";
      dmg = 2;
      attackSpeed = 1000;
      radius = 3;
      price = 200;
      sellPrice = 100;
      this->update();
      return;
    }
  if (type == "Archer") {
      selectingMode = true;
      typeOfTower = "Archer";
      dmg = 1;
      attackSpeed = 500;
      radius = 3*1.6;
      price = 100;
      sellPrice = 50;
      this->update();
      return;
    }
  if (type == "Support") {
      selectingMode = true;
      typeOfTower = "Support";
      hp = 8;
      dmg = 1;
      radius = 3;
      attackSpeed = 250;
      price = 75;
      sellPrice = 37;
      this->update();
      return;
    }
  Q_UNUSED(event)
}

void Interface::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if (selectingMode) {
      if (type == "Mage")
        selectingMode = false;
      if (type == "Archer")
        selectingMode = false;
      if (type == "Support")
        selectingMode = false;
      if (type == "Artillery")
        selectingMode = false;
    }
}
