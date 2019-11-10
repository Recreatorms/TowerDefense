#include "background.h"

Background::Background(QObject *parent) :
  QObject(parent)
{
  scene = new QGraphicsScene();

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
            scene->removeItem(getItem(j,i));
        }
    getItem(2,4)->setOpacity(0.1);
//         scene->itemAt(pos1, trans)->setOpacity(0.1);
//         QPaintDevice *device;
//         QPainter *painter;
//         painter->begin(device);
//         QStyleOptionGraphicsItem *option;
//         painter->setBrush(Qt::green);

}
QGraphicsItem* Background::getItem(int x, int y) {
    QPointF pos(-square/2*m + x*square, -square/2*n +y*square);
  for (qreal i = 0; i < square*n; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*m; j +=square) {
        QPointF pos2(-square/2*m+j, -square/2*n+i);
    if (pos == pos2) {
        QTransform trans;
        return scene->itemAt(pos, trans);
      }
  }
  return nullptr;
}



