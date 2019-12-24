#include "tile.h"

Tile::Tile(QObject *parent, QPointF _pos1, QPointF _pos2, QString _backgroundTheme, QString _type, int rotation) :
           QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    QPointF center = this->boundingRect().center();
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(rotation);
    t.translate(-center.x(), -center.y());
    setTransform(t);
    setPos(pos1);
    backgroundTheme = _backgroundTheme;
    type = _type;
    spriteImage = QPixmap("../TowerDefense/images/Map/game_background_" + backgroundTheme + type);
//    if (type != "/layers/dot.png")
//      this->
}

Tile::~Tile()
{
//  delete spriteImage;
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasTower)
      return;
    else if (towerSelected)
      hasTower = true;
    Q_UNUSED(event)
}

QRectF Tile::boundingRect() const {
    return QRectF(0,0,100,100);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (type == "/layers/Base.png")
        painter->drawPixmap(QRectF(-60,-110,210,210), spriteImage, spriteImage.rect());
    else
        painter->drawPixmap(QRect(0,0,100,100), spriteImage, spriteImage.rect());

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


