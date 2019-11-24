#include "units.h"


Unit::Unit(QObject *parent, QPointF _start, int _startPos, QString type, QVector<QVector<QPointF> > _path) :
  QObject(parent)
{
    startPos = _startPos;
    currentPos = 0;
    path = _path;
    setPos(_start);
    isBlocked = false;

    damage = 1;
    cooldown = 100;
//    QTimer *pathTimer = new QTimer();
//    pathTimer->start(1);
//    connect(pathTimer, &QTimer::timeout, this, &Unit::completePath);
}

Unit::~Unit(){
}

void Unit::setOptions(qreal _speed, int _hp, int _attackBaseValue)
{
  speed = _speed;
  hp = _hp;
  attackBaseValue = _attackBaseValue;

}

void Unit::moveTo(QPointF point) {
  if (!isBlocked) {
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
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}
////////////////////////////Graphics/////////////////////////
QRectF Unit::boundingRect() const
{
    return QRectF(-20,-20,40,40); // иначе говоря хитбокс
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(-20, -20) <<  QPoint(-20, 20) << QPoint(20, 20) << QPoint(20,-20);// << QPoint(0,-40);
//    if (hp <= 4)
//        painter->setBrush(Qt::blue);
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

//void Unit::completePath() {
//////  for(int k = 0; k < path.size(); k++) {
////////      for (int i = 0; i < units.size(); i++) {
//////     if(this->startPos == k) {
////         if(this->currentPos == path[k].size()-2)
////             this->moveTo(path[k][path[k].size()-1]);
////             else if (this->pos() != path[k][this->currentPos +1])
////                 this->moveTo(path[k][this->currentPos]);
////       }


//}
