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
    explicit Tile(QObject *parent, QPointF pos1, QPointF pos2, QBrush brush, QPen _pen);
    ~Tile();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QBrush brush;
    QPen pen;
    QPointF pos1, pos2;
};

#endif // TILE_H
