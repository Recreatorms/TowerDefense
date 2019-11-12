#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <vector>
#include <queue>
#include "units.h"
const qreal square = 100; // размер одного квадрата
                      // 100x100 pixels
const int WALL   = -1;
const int BLANK  = -2;
const int W      =  8;         // ширина рабочего поля
const int H      =  8;         // высота рабочего поля
class Background : public QObject
{
  Q_OBJECT
public:
     Background();
    ~Background();

    QGraphicsScene* getScene() {
      return scene;
    }

    void fillMap(size_t _n, size_t _m, std::vector<std::vector<char> > p);
    void createMap();
    void setGameOptions(size_t _number);
    void makePath(QPointF currentPoint);
    void makeChanges();

    void makeWavePath();
    bool waveCompleted();
    void addUnit();

    QGraphicsItem* getItem(size_t x, size_t y);
   // Unit* getUnit(int x, int y);

    std::vector<std::vector<char> > map;

    size_t n;      // число строк
    size_t m ;     // число столбиков
  //  qreal square; // размер одного квадрата
    QPointF start, end;
    std::vector<Unit*> units;
    QVector<QPointF> path;
public slots:
  void gameTimerSlot();
  void spawnUnit();
private:
    size_t numberOfUnits;
    QGraphicsScene *scene;

};







#endif // BACKGROUND_H
