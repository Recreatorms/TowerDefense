#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>

class Tile: public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Tile(QObject *parent, QPointF pos1, QPointF pos2, QChar type);
    ~Tile();
    QChar type;
    bool hasTower = false;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap *spriteImage;
    QPointF pos1, pos2;
};

#endif // TILE_H
