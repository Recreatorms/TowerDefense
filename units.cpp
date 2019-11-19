#include "units.h"


Unit::Unit(QObject *parent, QPointF _start, int _startPos) :
  QObject(parent)
{
    setPos(_start);
    startPos = _startPos;
    currentPos = 0;
}

Unit::~Unit(){
}

void Unit::setOptions(qreal _speed, int _hp, int _attackBaseValue)
{
  speed = _speed;
  hp = _hp;
  attackBaseValue = _attackBaseValue;
}

QRectF Unit::boundingRect() const
{
    return QRectF(-15,-15,30,30); // иначе говоря хитбокс
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(-10, -10) <<  QPoint(-10, 10) << QPoint(10, 10) << QPoint(10,-10);// << QPoint(0,-40);
    if (hp <= 4)
        painter->setBrush(Qt::blue);
    if (hp <= 3)
        painter->setBrush(Qt::green);
    if (hp <= 2)
        painter->setBrush(Qt::yellow);
    if (hp == 1)
        painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Unit::moveTo(QPointF point) {
    if (x() < point.x() && y() == point.y()) //right
        setPos(mapToScene(speed,0));
    else if (x() > point.x() && y() == point.y()) //left
        setPos(mapToScene(-speed,0));
    if (x() == point.x() && y() < point.y()) //down
        setPos(mapToScene(0,speed));
    else if (x() == point.x() && y() > point.y()) //up
        setPos(mapToScene(0,-speed));
    if (pos() == point) {
        currentPos++;
    }
}
