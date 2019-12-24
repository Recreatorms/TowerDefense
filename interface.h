#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
class Interface : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  explicit Interface(QObject *parent, QPointF _pos1, QPointF _pos2, QString _type);
  ~Interface() { delete spriteImage;}
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
//  int movementSpeed;
  int currentTowerIndex = 0;
  int price;
  int sellPrice;
  int level = 1;
  int playerMoney;
  QPointF pos1, pos2;
  void addGameInfo(int _hp, int _waveNumber, int _playerMoney, int _maxWaves);
  void entityInfo(int _hp, int _dmg, int _attackBase, qreal _radius, int _attackSpeed, int _price, int _sellPrice);
protected:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
  int playerHP;
  int waveNumber;
  int maxWaves;
  QPixmap heart = QPixmap("../TowerDefense/images/Interface/heart.png");
  QPixmap money = QPixmap("../TowerDefense/images/Interface/gold.png");
  QPixmap *spriteImage = new QPixmap("../TowerDefense/images/Interface/table.png");
  QString type;
};

#endif // INTERFACE_H
