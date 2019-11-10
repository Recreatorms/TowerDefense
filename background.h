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


class Background : public QObject
{
  Q_OBJECT
public:
     Background();
    ~Background();

    QGraphicsScene* getScene() {
      return scene;
    }

    void fillMap(size_t _n, size_t _m, std::vector<std::vector<int> > p);
    void createMap();
    void setStartEndPos();
    void makePath(QPointF currentPoint);
    void makeChanges();

    void addUnit();

    QGraphicsItem* getItem(int x, int y);
   // Unit* getUnit(int x, int y);

    std::vector<std::vector<int> > map;

    size_t n;      // число строк
    size_t m ;     // число столбиков
  //  qreal square; // размер одного квадрата
    QPointF start, end;
    std::vector<Unit*> units;
    QVector<QPointF> path;

public slots:
  void gameTimerSlot();
private:

    QGraphicsScene *scene;

};







#endif // BACKGROUND_H
