#include "tile.h"

Tile::Tile(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type) :
           QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
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
    return QRectF(pos1,pos2);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (type == 'b')
        spriteImage = new QPixmap("../TowerDefense/images/grass_tile_1.png");
    if (type == 'r' || type == 's' || type == 'e')
        spriteImage = new QPixmap("../TowerDefense/images/sand_tile.png");
    painter->drawPixmap(pos1, *spriteImage, QRectF(QPointF(0,0),QPointF(100,100)));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


