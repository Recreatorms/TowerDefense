#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Interface : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QChar _type);
    ~Interface() {}
    bool selectingMode = false;
    QChar typeOfTower;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPixmap *spriteImage;
    QPointF pos1, pos2;
    QChar type;
};

#endif // INTERFACE_H
