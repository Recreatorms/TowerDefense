#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#include <vector>
#include <queue>

#include "bullet.h"
#include "units.h"
#include "tile.h"
#include "towers.h"
#include "interface.h"
const qreal square = 100; // размер одного квадрата
                          // 100x100 pixels

class GameScene : public QGraphicsScene
{
  Q_OBJECT
public:
     GameScene();
    ~GameScene();

    void fillMap(size_t _width, std::vector<std::vector<QString> > p);
    void createMap(QString _backgroundTheme);
    void setGameOptions(QVector<QVector<size_t> > _number, int _playerMoney);

    void addInterface();

    void addTile(QPointF pos1, QPointF pos2, QString type, int rotation);
    void addUnit(QPointF _start, int startPos, QString type);
    void addTower(QPointF pos1, QPointF pos2, QString type, int price);

    void makeWavePath();

//    QGraphicsItem* getItem(size_t x, size_t y); // зачем?

    int currentWave = 0;
    int waveCounter = 1;
    int startingPoint = 0;
    bool buildingTower = false;
    QString selectedTower;
    int indexOfSelectedTower;
    int playerMoney;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    QVector<Interface*> interfaces;
signals:
    void showUpgradeButton();
    void hideUpgradeButton();
    void showRouteButton();
    void hideRouteButton();
public slots:
  void gameTimerSlot();
  void spawnUnitSlot();
  void upgradeCurrentTowerSlot();
  void changeRouteSlot();
private:
    std::vector<std::vector<QString> > map;

    size_t height;      // число строк
    size_t width;     // число столбиков
    QVector<QPointF> start;
    QPointF end;
    bool changingRoutePointScene = false;
    QPointF routePoint;
    QString backgroundTheme;
    QVector<QVector<QPointF> > path;

    QVector<QVector<size_t> > numberOfUnitsToSpawn;
    QVector<Unit*>  units;
    QVector<Tower*> towers;
    int playerHP = 20;
};


#endif // BACKGROUND_H
