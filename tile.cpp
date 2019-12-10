#include "tile.h"

Tile::Tile(QObject *parent, QPointF _pos1, QPointF _pos2, QString _backgroundTheme, QString _type) :
           QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    setPos(pos1);
    backgroundTheme = _backgroundTheme;
    type = _type;
}

Tile::~Tile()
{

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasTower)
      return;
    else if (towerSelected)
      hasTower = true;
}

QRectF Tile::boundingRect() const {
    return QRectF(0, 0, 100, 100);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    spriteImage = new QPixmap("../TowerDefense/images/Map/game_background_" + backgroundTheme + type);
    if (type == "/layers/road_1.png")
        painter->drawPixmap(QRect(0,0,150,150), *spriteImage, spriteImage->rect());
    else
      if (type == "/layers/road_2.png")
        painter->drawPixmap(QRectF(-50,0,150,150), *spriteImage, spriteImage->rect());
    else
      if (type == "/layers/road_3.png")
        painter->drawPixmap(QRectF(0,-50,150,150), *spriteImage, spriteImage->rect());
    else
      if (type == "/layers/road_4.png")
        painter->drawPixmap(QRectF(-50,-50,150,150), *spriteImage, spriteImage->rect());
    else
        painter->drawPixmap(boundingRect(), *spriteImage, spriteImage->rect());
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


