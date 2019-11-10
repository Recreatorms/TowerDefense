#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

const qreal square = 100; // размер одного квадрата
                      // 100x100 pixels


class Background : public QObject
{
  Q_OBJECT
public:
    explicit Background(QObject *parent = nullptr);
    ~Background();

    QGraphicsScene* getScene() {
      return scene;
    }

    void fillMap(size_t _n, size_t _m, std::vector<std::vector<int> > p);
    void makeChanges();
    QGraphicsItem* getItem(int x, int y);
    void createMap();

    std::vector<std::vector<int> > map;

    size_t n;      // число строк
    size_t m ;     // число столбиков
  //  qreal square; // размер одного квадрата

private:
    QGraphicsScene *scene;
};







#endif // BACKGROUND_H
