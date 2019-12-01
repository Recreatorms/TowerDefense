#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include <QPushButton>
class Interface : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type);
    ~Interface() {}
    bool selectingMode = false;
    QString typeOfTower;
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPixmap *spriteImage;
    QPointF pos1, pos2;
    QString type;
};

#endif // INTERFACE_H
