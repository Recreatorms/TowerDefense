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

  painter->setFont(QFont("Comic Sans MS", 25,-1,false));
  if (type == '1'){
    painter->drawText(QPointF(pos2.x()-200,pos2.y()-50), "sampleText1");
  }
  if (type == '2'){
    painter->drawText(QPointF(pos2.x()-200,pos2.y()-50), "sampleText2");
  }
  if (type == '3'){
    painter->drawText(QPointF(pos2.x()-200,pos2.y()-50), "sampleText3");
  }
  if (type == '4'){
    painter->drawText(QPointF(pos2.x()-200,pos2.y()-50), "sampleText4");
  }  if (type == 'u'){
      painter->setBrush(Qt::DiagCrossPattern);
  }

  painter->drawRect(QRectF(pos1,pos2));
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

void Interface::mousePressEvent(QGraphicsSceneMouseEvent *event) {

  if (type == '1') {
    selectingMode = true;
    typeOfTower = '1';
  }
  if (type == '2') {
    selectingMode = true;
    typeOfTower = '2';
  }
  if (type == '3') {
    selectingMode = true;
    typeOfTower = '3';
  }
  if (type == '3') {
    selectingMode = true;
    typeOfTower = '4';
  }

}
