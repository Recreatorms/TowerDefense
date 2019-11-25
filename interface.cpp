#include "interface.h"
#include <QPushButton>
Interface::Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type) :
        QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    type = _type;
   // screen = new InfoScreen(this, pos1, pos2);
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
      if (typeOfTower == "Musketeer") {
        painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Musketeer");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfTower == "Rapid") {
        painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Rapid");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfTower == "Archer") {
        painter->drawText(QPointF(pos2.x()-250,pos2.y()-50), "Archer");
        // dmg
        // range
        // speed
        // SellPrice
        // UpgradePrice
        // sell button
        // upgrade button
      }
      if (typeOfTower == "Support") {
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
    }
  }
//  if (type == "Upgrade"){
//      painter->setBrush(Qt::DiagCrossPattern);
//  }

  painter->drawRect(QRectF(pos1,pos2));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Interface::mousePressEvent(QGraphicsSceneMouseEvent *event) {

  if (type == "Musketeer") {
    selectingMode = true;
    typeOfTower = "Musketeer";
    this->update();
  }
  if (type == "Rapid") {
    selectingMode = true;
    typeOfTower = "Rapid";
    this->update();
  }
  if (type == "Archer") {
    selectingMode = true;
    typeOfTower = "Archer";
    this->update();
  }
  if (type == "Support") {
    selectingMode = true;
    typeOfTower = "Support";
    this->update();
  }
  Q_UNUSED(event)
}
