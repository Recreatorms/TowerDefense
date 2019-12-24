#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QTimer>
#include <QTime>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>
#include <queue>

#include "bullet.h"
#include "units.h"
#include "tile.h"
#include "towers.h"
#include "interface.h"

class Wave {
public:
  Wave() {}
  Wave(int _spawnPoint, int _numberOfUnits, QString _typeOfUnits) {
    spawnPoint = _spawnPoint;
    numberOfUnits = _numberOfUnits;
    typeOfUnits = _typeOfUnits;
  }
  int spawnPoint;
  int numberOfUnits;
  QString typeOfUnits;
};

//==============================================================================//

class Indicator : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  Indicator() {
    spriteImage = QPixmap("../TowerDefense/images/Interface/skull.png");
  }
  ~Indicator()  {
    this->scene()->removeItem(this);
//    delete spriteImage;
  }
  QPixmap spriteImage;
protected:
  QRectF boundingRect() const {
    return QRectF(0,0,50,50);
  }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = nullptr, QWidget *widget = nullptr)  {
    painter->drawPixmap(boundingRect(), spriteImage, spriteImage.rect());
    Q_UNUSED(option)
    Q_UNUSED(widget)
  }
};

//==============================================================================//

class GameScene : public QGraphicsScene
{
  Q_OBJECT
public:
  GameScene();
  ~GameScene() override;
  qreal square = 100; // размер одного квадрата // 100x100 pixels
  int offset = 261;
  void fillMap(int _width, QVector<QVector<QString> > p, int _level);
  void createMap(QString _backgroundTheme);
  void setGameOptions(QVector<Wave> _waves, int _playerMoney);

  void addInterface();

  void addTile(QPointF pos1, QPointF pos2, QString type, int rotation);
  void addUnit(int startPos, QString type);
  void addTower(QPointF pos1, QPointF pos2, QString type, int price);

  void makeWavePath();

  void clearLevel();
  bool lost = false;
  bool victoryAchieved = false;
  int currentWave = 0;
  int startingPoint = 0;
  QString selectedTower;
  int indexOfSelectedTower;
  int playerMoney;
  QVector<Interface*> interfaces;
signals:
  void showUpgradeButton();
  void hideUpgradeButton();
  void showSellButton();
  void hideSellButton();
  void showRouteButton();
  void hideRouteButton();
  void showBackToMenuButton();
  void hideBackToMenuButton();
  void pauseSignal();
  void showNextLevelButton();
public slots:
  void paused();
  void gameTimerSlot();
  void spawnUnitSlot();
  void upgradeCurrentTowerSlot();
  void sellCurrentTowerSlot();
  void changeRouteSlot();
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void keyPressEvent(QKeyEvent *event) override;
private:
  int level;
  QVector<QVector<QString> > map;
  int height;    // число строк
  int width;     // число столбиков
  QVector<QPointF> start;
  QPointF end;
  bool changingRoutePointScene = false;
  QPointF routePoint;
  QVector<QVector<QPointF> > path;
  bool indicatorIsActive = false;
  bool indicatorAdded = false;
  Indicator* indicator;
  QVector<Wave> waves;
  QVector<Unit*>  units;
  QVector<Tower*> towers;
  QString backgroundTheme;
  QGraphicsRectItem *grayBackGround;
  QGraphicsPixmapItem *menu;
  bool IsPaused = false;
  int playerHP = 20;
  ulong timeFromPauseToPause;
  Interface* gameInfo;
};


#endif // BACKGROUND_H
