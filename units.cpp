#include "units.h"

Unit::Unit(QObject *parent) :
    QObject(parent)
{
    angle = 0;
    setRotation(angle);
}

Unit::~Unit(){
}

QRectF Unit::boundingRect() const
{
    return QRectF(-25,-40,50,20000);
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(-10, -10) <<  QPoint(-10, 10) << QPoint(10, 10) << QPoint(10,-10) << QPoint(0,-40);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Unit::gameTimerSlot() {
  //qreal angle = triangle->getAngle()
  if (GetAsyncKeyState(VK_LEFT)){
        angle -=10;
      setRotation(angle);
  }
  if (GetAsyncKeyState(VK_RIGHT)){
        angle += 10;
        setRotation(angle);
  }
  if (GetAsyncKeyState(VK_UP)){
        setPos(mapToParent(0, -5));
   }
  if (GetAsyncKeyState(VK_DOWN)){
        setPos(mapToParent(0, 5));
  }

  if (this->x() - 10 < -250) {
        this->setX(-240);
   }
  if (this->x() + 10 > 250) {
        this->setX(240);
   }
  if (this->y() - 10 < -250) {
        this->setY(-240);
   }
  if (this->y() + 10 > 250) {
        this->setY(240);
   }

}

//void Unit::setPosition(const QPointF &pos, Background *back){
//  back->map[x()][y()] = 0;
//  this->setPos(pos);
//  back->map[pos.x()][pos.y()] = 1;
//}


