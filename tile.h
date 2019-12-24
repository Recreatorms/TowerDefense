#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

class Tile: public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Tile(QObject *parent, QPointF pos1, QPointF pos2, QString _backgroundTheme, QString _type, int rotation);
    ~Tile();
    QString type;
    bool hasTower = false;
    bool towerSelected = false;
    QPointF pos1, pos2;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QString backgroundTheme;
    QPixmap spriteImage;
};

#endif // TILE_H
