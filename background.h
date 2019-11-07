#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
class Background : public QObject
{
  Q_OBJECT
public:
    explicit Background(QObject *parent = nullptr);
    ~Background();

    QGraphicsScene* getScene() {
      return scene;
    }

    std::vector<std::vector<int> > map;
    void fillMap(size_t _n, size_t _m, std::vector<std::vector<int> > p) {
      n = _n;
      m = _m;
      map = std::move(p);
    }
    QGraphicsItem* getItem(QPointF &pos);
    void createMap();
private:
    size_t n;      // число строк
    size_t m ;     // число столбиков
    qreal square; // размер одного квадрата
    QGraphicsScene *scene;
};







#endif // BACKGROUND_H
