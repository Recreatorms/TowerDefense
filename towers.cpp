#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type, int _radius) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    radius = _radius;
    type = _type;
}

Tower::~Tower()
{

}

QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (type == 'd')
      spriteImage = new QPixmap("../TowerDefense/images/6.png");
  painter->drawPixmap(QPointF(pos1.x(),pos1.y()-100), *spriteImage, QRectF(QPointF(0,0),QPointF(200,200)));
//  painter->drawRoundedRect(QRectF(pos1,pos2), radius, radius, Qt::AbsoluteSize);
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
