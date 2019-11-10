#include "units.h"

Unit::Unit(QObject *parent) :
    QObject(parent)
{

    setPos(-250,-85);
    angle = 90;
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

   moveTo(QPoint(0,-85));


// границы
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

void Unit::moveTo(QPoint point) {

    if (pos() != point)
        setPos(mapToParent(0,-1));
    else if(angle != 180) {
        angle +=1;
        this->setRotation(angle);
    }
}

//void Unit::setPosition(const QPointF &pos, Background *back){
//  back->map[x()][y()] = 0;
//  this->setPos(pos);
//  back->map[pos.x()][pos.y()] = 1;
//}


