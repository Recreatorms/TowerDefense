#include "towers.h"

Tower::Tower(QObject *parent, QPointF _pos1, QPointF _pos2, QBrush _brush, QPen _pen, int _radius) :
             QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
 //   setPos(_pos1-_pos2);
    radius = _radius;
    pen = _pen;
    brush = _brush;
}

Tower::~Tower()
{

}

QRectF Tower::boundingRect() const
{
  return QRectF(pos1,pos2);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->setBrush(brush);
  painter->setPen(pen);
  painter->drawRoundedRect(QRectF(pos1,pos2), radius, radius, Qt::AbsoluteSize);
  Q_UNUSED(option)
  Q_UNUSED(widget)
}
