#include "units.h"


Unit::Unit(QObject *parent, QPointF _start, int _startPos, QString _type, QVector<QVector<QPointF> > _path, QVector<Interface *> _interfaces) :
  QObject(parent)
{
    interfaces = _interfaces;
    startPos = _startPos;
    currentPos = 0;
    path = _path;
    setPos(_start);
    isBlocked = false;
    type = "enemy";
    damage = 1;
    cooldown = 100;
//    QTimer *pathTimer = new QTimer();
//    pathTimer->start(1);
//    connect(pathTimer, &QTimer::timeout, this, &Unit::completePath);
}

Unit::~Unit(){
}

void Unit::setOptions(int _speed, int _hp, int _attackBaseValue)
{
  speed = _speed;
  maxHP = _hp;
  hp = _hp;
  attackBaseValue = _attackBaseValue;

}

void Unit::moveTo(QPointF point) {
  this->reloading++;
  if (!isBlocked) {
    if (x() < point.x() && y() == point.y())  {//right
      dx = speed;
      setPos(mapToScene(speed,0));
      }
    else if (x() > point.x() && y() == point.y()) { //left
        dx = -speed;
        setPos(mapToScene(-speed,0));
      }
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
  interfaces[5]->typeOfEntity = type;
  interfaces[5]->update();
  clicked = true;
  Q_UNUSED(event)
}

void Unit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  clicked = false;
  Q_UNUSED(event)
}

////////////////////////////Graphics/////////////////////////
QRectF Unit::boundingRect() const
{
    return QRectF(-50,-50,100,100); // иначе говоря хитбокс
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPolygon polygon;
//    polygon << QPoint(-20, -20) <<  QPoint(-20, 20) << QPoint(20, 20) << QPoint(20,-20);// << QPoint(0,-40);
    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawLine(-30,-45,30,-45);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(-30,-45, 60/maxHP*hp-30,-45);

    painter->setPen(Qt::PenStyle::SolidLine);

    if (dx <= 0) {
      QTransform transf = painter->transform();
      transf.scale(-1,1);
      painter->setTransform(transf);
    }
    spriteImage = new QPixmap("../TowerDefense/images/enemy.png");
    painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());

//    painter->drawPolygon(polygon);
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
