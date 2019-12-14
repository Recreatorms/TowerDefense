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
    bool showingUpgradeButton = false;
    bool showingRouteButton = false;
    QString typeOfEntity;
    QString typeOfTower;
    QString typeOfUnit;
    bool unitWasSelected = false;
    int hp;
    int dmg;
    int attackSpeed;
    int attackBase;
    qreal radius;
    int movementSpeed;
    int currentTowerIndex = 0;
    int price;
    int level = 1;
    int playerMoney;
    void addGameInfo(int _hp, int _waveNumber, int _playerMoney);
    void entityInfo(int _hp, int _dmg, int _attackBase, qreal _radius, int _attackSpeed, int _movementSpeed, int _price );
    void upgrade();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int playerHP;
    int waveNumber;
    QPixmap *spriteImage;
    QPointF pos1, pos2;
    QString type;
};

#endif // INTERFACE_H
