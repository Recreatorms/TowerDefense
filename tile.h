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
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap *spriteImage;
    QPointF pos1, pos2;
    QChar type;
};

#endif // TILE_H
