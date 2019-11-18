#include "interface.h"

Interface::Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type) :
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

  if (type == 't'){
    painter->setFont(QFont("Comic Sans MS", 25,-1,false));
    painter->drawText(QPointF(pos2.x()-200,pos2.y()-50), "sampleText");
  }
  if (type == 'u'){
      painter->setBrush(Qt::DiagCrossPattern);
  }

  painter->drawRect(QRectF(pos1,pos2));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Interface::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (type == 't')
    selectingMode = true;
    typeOfTower = 't';
}
