#include "background.h"

Background::Background()
{
  this->scene = new QGraphicsScene();
//  QBrush *ibrush = new QBrush;
//  ibrush->setTextureImage(QImage(":/images/Sprite_FX_Grass_0001"));

//  scene->drawBackground();
}

Background::~Background() {
}

void Background::createMap() {
  scene->setSceneRect(-square/2, -square/2, square, square);
  for (qreal i = 0; i < square*n; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*m; j +=square) {
        QPointF pos1(-square/2*m+j, -square/2*n+i),
                pos2(-square/2*(m-2)+j,-square/2*(n-2)+i);
        QColor color;
        if (map[i/square][j/square] == 'b')
          color = Qt::green;
        if (map[i/square][j/square] == 'r')
          color = Qt::yellow;
        if (map[i/square][j/square] == 'e' || map[i/square][j/square] == 's')
          color = Qt::gray;
        scene->addRect(QRectF(pos1,pos2), QPen(Qt::black), QBrush(color, Qt::DiagCrossPattern));


    }
}

void Background::fillMap(size_t _n, size_t _m, std::vector<std::vector<char> > p) {
    n = _n;
    m = _m;
    map = std::move(p);
}


void Background::makeChanges() {
    for (qreal i = 0; i < n; i++)
        for (qreal j = 0; j < m; j++) {
            QPointF pos1(-square/2*m+j*square, -square/2*n+i*square);
            if (map[i][j] == 'r')
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

void Background::makeWavePath()
{
    std::vector<std::vector<int> > labyrinth (n, std::vector<int> (m));
    for(size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
          if (map[i][j] == 'b')
              labyrinth[i][j] = WALL;
            else if (map[i][j] == 'r' || map[i][j] == 'e')
              labyrinth[i][j] = BLANK;
  ///////
      int ay = start.y()/square + m/2,
          ax = start.x()/square + m/2,
          by = end.y()/square + m/2,
          bx = end.x()/square + m/2;
      int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
      int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
      int d, x, y, k;
      bool stop;

      ///if (labyrinth[ay][ax] == WALL || labyrinth[by][bx] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена

      // распространение волны
      d = 0;
      labyrinth[ay][ax] = 0;            // стартовая ячейка помечена 0
      do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for (y = 0; y < H; ++y)
          for (x = 0; x < W; ++x)
            if (labyrinth[y][x] == d)                         // ячейка (x, y) помечена числом d
            {
              for ( k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
              {
                 int iy = y + dy[k],
                     ix = x + dx[k];
                 if (iy >= 0 && iy < H && ix >= 0 && ix < W && labyrinth[iy][ix] == BLANK)
                 {
                    stop = false;              // найдены непомеченные клетки
                    labyrinth[iy][ix] = d + 1;      // распространяем волну
                 }
              }
            }
        d++;
      } while ( !stop && labyrinth[by][bx] == BLANK );

      //if (labyrinth[by][bx] == BLANK) return false;  // путь не найден

      // восстановление пути
      int len = labyrinth[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
      x = bx;
      y = by;
      d = len;
      while ( d > 0 ) {
        path.push_front(QPointF(x*square - square*(m-1)/2, y*square - (m-1) * square/2));                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k) {
           int iy = y + dy[k],
               ix = x + dx[k];
           if (iy >= 0 && iy < H && ix >= 0 && ix < W && labyrinth[iy][ix] == d) {
              x = x + dx[k];
              y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
              break;
          }
        }
      }
      path.push_front(QPointF(ax*square - square*(m-1)/2, ay*square - (m-1) * square/2));        // теперь px[0..len] и py[0..len] - координаты ячеек пути
      //return true;
    }


bool Background::waveCompleted() {
  if (numberOfUnits == 0)
    return true;
  else
    return false;
}
QGraphicsItem* Background::getItem(size_t x, size_t y) {
  QPointF pos1(-square/2*m + x*square, -square/2*n +y*square);
  for (qreal i = 0; i < square*n; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*m; j +=square) {
        QPointF pos2(-square/2*m+j, -square/2*n+i);
    if (pos1 == pos2) {
        QTransform trans;
        QGraphicsItem* item = scene->itemAt(pos1, trans);
        if (item != nullptr)
            return item;
      }
  }
  return nullptr;
}

void Background::gameTimerSlot() { // путь строится правильно,  но перемещение сделано не правильно
  for (size_t i = 0; i < units.size(); i++) {
    if(units[i]->currentPos == path.size()-2)
        units[i]->moveTo(path[path.size()-1]);
    else if (units[i]->pos() != path[units[i]->currentPos +1])
          units[i]->moveTo(path[units[i]->currentPos]);

    if(units[i]->pos() == end) {
        units[i]->~Unit();
        for (int j = 0; j < units.size(); j++)
          units[j] = units[j+1];
        units.pop_back();
      }

    }
}

void Background::spawnUnit()
{
  if (units.size() != numberOfUnits && numberOfUnits != 0)
      this->addUnit();
 // else numberOfUnits = 0;
}

void Background::setGameOptions(size_t _number) {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      if (map[i][j] == 's') {
          start = QPointF(-square/2*(m-1) +j*square,-square/2*(n-1) +i*square);
          getItem(j,i)->setOpacity(0.2);
      }
      if (map[i][j] == 'e') {
          end = QPointF(-square/2*(m-1) +j*square,-square/2*(n-1) +i*square);
          getItem(j,i)->setOpacity(0.2);
      }
    }
  numberOfUnits = _number;
}

void Background::makePath(QPointF currentPoint) { // путь строится правильно,  но перемещение сделано не правильно
  path.push_back(currentPoint);
  if (currentPoint != end) {
        size_t x = currentPoint.x()/square + m/2,  // столбик
               y = currentPoint.y()/square + m/2;     // строка
        QPointF newPoint;
        if (x!=m-1) { // right
            if(map[y][x+1] == 'r' || map[y][x+1] == 'e') {
              newPoint = QPointF(currentPoint.x() + square,currentPoint.y());
              if (!path.contains(newPoint))
                 //if (newPoint != end)
                    makePath(newPoint);
              }
        }
        if(x!=0) { // left
            if(map[y][x-1] == 'r' || map[y][x-1] == 'e') {
              newPoint = QPointF(currentPoint.x() - square, currentPoint.y());
             if (!path.contains(newPoint))
                 //if (newPoint != end)
                    makePath(newPoint);
            }
        }
        if(y!=m-1) { // down
            if(map[y+1][x] == 'r' || map[y+1][x] == 'e') {
              newPoint = QPointF(currentPoint.x(),currentPoint.y() + square);
              if (!path.contains(newPoint))
                // if (newPoint != end)
                   makePath(newPoint);
              }
        }
        if(y!=0) { // up
            if(map[y-1][x] == 'r' || map[y-1][x] == 'e') {
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

