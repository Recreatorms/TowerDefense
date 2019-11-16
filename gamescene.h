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


#include "units.h"
#include "tile.h"
#include "towers.h"

const qreal square = 100; // размер одного квадрата
                     // 100x100 pixels

class Background : public QGraphicsScene
{
  Q_OBJECT
public:
     Background();
    ~Background();

    void fillMap(size_t _width, std::vector<std::vector<char> > p);
    void createMap();
    void setGameOptions(QVector<QVector<size_t> > _number);

    void addInterface();

    void addTile(QPointF pos1, QPointF pos2, QChar type);
    void addUnit(QPointF _start, int startPos);
    void addTower(QPointF pos1, QPointF pos2, QChar type, int radius);

    void makeWavePath();
    bool waveCompleted();

    QGraphicsItem* getItem(size_t x, size_t y);
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
    QPointF end;
    QVector<QPointF> start;
    QVector<QVector<QPointF> > path;
    QVector<QVector<size_t> > numberOfUnitsToSpawn;
    QVector<Unit*>  units;
};







#endif // BACKGROUND_H