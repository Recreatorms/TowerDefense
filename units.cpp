#include "units.h"


Unit::Unit(QObject *parent, QPointF _start, int _startPos) :
  QObject(parent)
{
    startPos = _startPos;
    setPos(_start);
    currentPos = 0;
    angle = 0;
    setRotation(angle);
}

Unit::~Unit(){
}

QRectF Unit::boundingRect() const
{
    return QRectF(-25,-40,50,8000);
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
