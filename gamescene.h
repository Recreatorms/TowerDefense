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

    void fillMap(size_t _width, std::vector<std::vector<char> > p);
    void createMap();
    void setGameOptions(QVector<QVector<size_t> > _number);

    void addInterface();

    void addTile(QPointF pos1, QPointF pos2, QChar type);
    void addUnit(QPointF _start, int startPos);
    void addTower(QPointF pos1, QPointF pos2, QChar type, qreal radius);

    void makeWavePath();

    QGraphicsItem* getItem(size_t x, size_t y); // зачем?
    int currentWave = 0;
    int wave = 0;
    bool selectingMode = false;

    //void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
  void gameTimerSlot();
  void spawnUnit();
private:
    std::vector<std::vector<char> > map;
    size_t height;      // число строк
    size_t width;     // число столбиков
    QVector<QPointF> start;
    QPointF end;

    QVector<QVector<QPointF> > path;

    QVector<QVector<size_t> > numberOfUnitsToSpawn;
    QVector<Unit*>  units;
    QVector<Tower*> towers;

    int playerHP = 20;
    QVector<Interface*> interfaces;
};







#endif // BACKGROUND_H
