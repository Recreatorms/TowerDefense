#include "background.h"

Background::Background(QObject *parent) :
  QObject(parent)
{
  scene = new QGraphicsScene();
  square = 100;
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
        if (map[i/square][j/square] != 1) {
            //scene->itemAt(pos1, trans)->setOpacity(0.1);
           // QPaintDevice *device;
            //QPainter *painter;
           // painter->begin(device);
                //QStyleOptionGraphicsItem *option;
           // painter->setBrush(Qt::green);

          getItem(pos1)->setOpacity(0.2);
          }
      }
}

QGraphicsItem* Background::getItem(QPointF &pos) {
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



