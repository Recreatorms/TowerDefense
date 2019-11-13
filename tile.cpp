#include "tile.h"

Tile::Tile(QObject *parent, QPointF _pos1, QPointF _pos2, QBrush _brush, QPen _pen) :
           QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    pen = _pen;
    brush = _brush;
}

Tile::~Tile()
{

}

QRectF Tile::boundingRect() const {
    return QRectF(pos1,pos2);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(QRectF(pos1,pos2));
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
