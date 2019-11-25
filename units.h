#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <queue>

#include <QGraphicsSceneMouseEvent>
#include <QTimer>
//#include <QRandomGenerator>
class Unit : public QObject, public QGraphicsItem
{
   Q_OBJECT
public:
    explicit Unit(QObject *parent, QPointF _start, int _startPos, QString type, QVector<QVector<QPointF> > _path);
    ~Unit();
    void setOptions(qreal _speed, int _hp, int _attackBaseValue);
    void moveTo(QPointF point);
    int startPos;
    int currentPos;

    int damage;
    int reloading = 0;
    int cooldown;
    int maxHP;
    int hp;
    int attackBaseValue;
    bool isBlocked;

    int goldValue;



    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//public slots:
//    void completePath();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
   // QGraphicsItem *item;
//    int offset;
    int dx = 0;
    qreal speed;
    QPixmap *spriteImage;
    QVector<QVector<QPointF> > path;
    QString type;
};

#endif // UNITS_H
