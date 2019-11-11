#include "units.h"


Unit::Unit(QObject *parent, QPointF _start) :
  QObject(parent)
{

    setPos(_start);
    currentPos = 0;
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
    polygon << QPoint(-10, -10) <<  QPoint(-10, 10) << QPoint(10, 10) << QPoint(10,-10);// << QPoint(0,-40);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}






void Unit::moveTo(QPointF point) {

////   границы
////    if (this->x() - 10 < -250) {
////          this->setX(-240);
////     }
////    if (this->x() + 10 > 250) {
////          this->setX(240);
////     }
////    if (this->y() - 10 < -250) {
////          this->setY(-240);
////     }
////    if (this->y() + 10 > 250) {
////          this->setY(240);
////     }


  // путь строится правильно,  но перемещение сделано не правильно
    if (x() < point.x() && y() == point.y()) //right
        setPos(mapToScene(1,0));
    else if (x() > point.x() && y() == point.y()) //left
        setPos(mapToScene(-1,0));
    if (x() == point.x() && y() < point.y()) //down
        setPos(mapToScene(0,1));
    else if (x() == point.x() && y() > point.y()) //up
        setPos(mapToScene(0,-1));
    if (pos() == point) {
        currentPos++;
    }
}

//void Unit::completePath(std::vector<QPointF> path) {
////  for (int i = 0; i < path.size(); i++) {
////    while (pos() != path[i]) {
////          moveTo(path[i]);
////    }
////  }
//}

//void Unit::setPosition(const QPointF &pos, Background *back){
//  back->map[x()][y()] = 0;
//  this->setPos(pos);
//  back->map[pos.x()][pos.y()] = 1;
//}


