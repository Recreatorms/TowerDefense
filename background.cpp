#include "background.h"

Background::Background()
{
  this->scene = new QGraphicsScene();

}

Background::~Background() {
}

void Background::createMap() {
  scene->setSceneRect(-square/2, -square/2, square, square);
  for (qreal i = 0; i < square*n; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*m; j +=square) {
        QPointF pos1(-square/2*m+j, -square/2*n+i),
                pos2(-square/2*(m-2)+j,-square/2*(n-2)+i);
        scene->addRect(QRectF(pos1,pos2), QPen(Qt::black), QBrush(Qt::BDiagPattern));


    }
}

void Background::fillMap(size_t _n, size_t _m, std::vector<std::vector<int> > p) {
    n = _n;
    m = _m;
    map = std::move(p);
}


void Background::makeChanges() {
    for (qreal i = 0; i < n; i++)
        for (qreal j = 0; j < m; j++) {
            QPointF pos1(-square/2*m+j*square, -square/2*n+i*square);
            if (map[i][j] == 1)
            //    getItem(pos1)->setOpacity(0.0);
            this->scene->removeItem(getItem(j,i));
        }
//         scene->itemAt(pos1, trans)->setOpacity(0.1);
//         QPaintDevice *device;
//         QPainter *painter;
//         painter->begin(device);
//         QStyleOptionGraphicsItem *option;
//         painter->setBrush(Qt::green);

}
QGraphicsItem* Background::getItem(size_t x, size_t y) {
  QPointF pos1(-square/2*m + x*square, -square/2*n +y*square);
  for (qreal i = 0; i < square*n; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*m; j +=square) {
        QPointF pos2(-square/2*m+j, -square/2*n+i);
    if (pos1 == pos2) {
        QTransform trans;
        return scene->itemAt(pos1, trans);
      }
  }
  return nullptr;
}

void Background::gameTimerSlot() { // путь строится правильно,  но перемещение сделано не правильно
 // units[0]->completePath(path);
  for (int i = 1; i < path.size(); i++)
    //if (units[0]->pos() != path[i])
      units[0]->moveTo(path[i]);

  if(units[0]->pos() == end)
    units[0]->~Unit();

}

void Background::setStartEndPos() {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      if (map[i][j] == 2) {
          start = QPointF(-square/2*(m-1) +j*square,-square/2*(n-1) +i*square);
          getItem(j,i)->setOpacity(0.2);
      }
      if (map[i][j] == 3) {
          end = QPointF(-square/2*(m-1) +j*square,-square/2*(n-1) +i*square);
          getItem(j,i)->setOpacity(0.2);
      }
    }
}

void Background::makePath(QPointF currentPoint) { // путь строится правильно,  но перемещение сделано не правильно
  path.push_back(currentPoint);
  if (currentPoint != end) {
        size_t x = currentPoint.x()/square + m/2,  // столбик
            y = currentPoint.y()/square + m/2;     // строка
        QPointF newPoint;
        if (x!=m-1) { // right
            if(map[y][x+1] == 1 || map[y][x+1] == 3) {
              newPoint = QPointF(currentPoint.x() + square,currentPoint.y());
              if (!path.contains(newPoint))
                 //if (newPoint != end)
                    makePath(newPoint);
              }
        }
        if(x!=0) { // left
            if(map[y][x-1] == 1 || map[y][x-1] == 3) {
              newPoint = QPointF(currentPoint.x() - square, currentPoint.y());
             if (!path.contains(newPoint))
                 //if (newPoint != end)
                    makePath(newPoint);
            }
        }
        if(y!=m-1) { // down
            if(map[y+1][x] == 1 || map[y+1][x] == 3) {
              newPoint = QPointF(currentPoint.x(),currentPoint.y() + square);
              if (!path.contains(newPoint))
                // if (newPoint != end)
                   makePath(newPoint);
              }
        }
        if(y!=0) { // up
            if(map[y-1][x] == 1 || map[y-1][x] == 3) {
              newPoint = QPointF(currentPoint.x(),currentPoint.y() - square);
              if (!path.contains(newPoint))
                // if (newPoint != end)
                    makePath(newPoint);
              }
        }
    }
}



void Background::addUnit() {

  Unit *unit = new Unit(this, start);
  this->scene->addItem(unit);
  units.push_back(unit);
}

//Unit* Background::getUnit(int x, int y) {

//}

