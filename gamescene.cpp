#include "background.h"

Background::Background() : QGraphicsScene() {
//  QBrush *ibrush = new QBrush;
//  ibrush->setTextureImage(QImage(":/images/Sprite_FX_Grass_0001"));
//  scene->drawBackground(ibrush);

}

Background::~Background() {
}

void Background::fillMap(size_t _width, std::vector<std::vector<char> > p) {
    map = std::move(p);
    height = map.size();
    width =  _width;
}

void Background::createMap() {
  this->setSceneRect(QRectF(QPointF(-square,-square),QPointF(square,square)));
  for (size_t i = 0; i < height; i++) // потом поменять на int
    for (size_t j = 0; j < width; j++) {
        QPointF pos1(-square/2*width+j*square, -square/2*height+i*square),
                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
//        QColor color;
//        QPen pen;
//        QBrush brush;
//        if (map[i][j] == 'b') {
//          color = Qt::green;
//          pen = Qt::SolidLine;
//        }
//        if (map[i][j] == 'r') {
//          color = Qt::yellow;
//          pen = Qt::NoPen;
//        }
//        if (map[i][j] == 'e' || map[i][j] == 's') {
//          color = Qt::gray;
//          pen = Qt::NoPen;
//        }
//        brush = QBrush(color, Qt::DiagCrossPattern);
       // QBrush brush(color, Qt::DiagCrossPattern);
//        this->addRect(QRectF(pos1,pos2), pen, brush);
        this->addTile(pos1, pos2, map[i][j]);
    }
 // Background Texture
  QString path;
 // path = ("../TowerDefense/images/Preview.jpg");
  QPixmap bg(path);
  bg = bg.scaled(QGraphicsScene::height(), QGraphicsScene::height(), Qt::KeepAspectRatioByExpanding,Qt::FastTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, bg);
  this->setPalette(palette);
  this->setBackgroundBrush(QBrush(bg));

}

void Background::setGameOptions(QVector<QVector<size_t> > _number) {
  for (size_t i = 0; i < height; i++)
    for (size_t j = 0; j < width; j++) {
      if (map[i][j] == 's') {
          start.push_back(QPointF(-square/2*(width-1) +j*square,-square/2*(height-1) +i*square));
          getItem(j,i)->setOpacity(0.2);
      }
      if (map[i][j] == 'e') {
          end = QPointF(-square/2*(width-1) +j*square,-square/2*(height-1) +i*square);
          getItem(j,i)->setOpacity(0.2);
      }
    }
  numberOfUnitsToSpawn = _number;
}


void Background::addInterface() {
    this->addRect(QRectF(QPointF(square*(width+1)/2,-square*(height)/2),QPointF(square*(width+10)/2,square*(height)/2)), QPen(Qt::black), Qt::NoBrush);

}

QGraphicsItem* Background::getItem(size_t x, size_t y) { // Зачем мне нужен этот метод??????????
  QPointF pos1(-square/2*width + x*square, -square/2*height +y*square);
  for (qreal i = 0; i < square*height; i+=square) // потом поменять на int
    for (qreal j = 0; j < square*width; j +=square) {
        QPointF pos2(-square/2*width+j, -square/2*height+i);
    if (pos1 == pos2) {
        QTransform trans;
        QGraphicsItem* item = this->itemAt(pos1, trans);
        if (item != nullptr)
            return item;
      }
    }
  return nullptr;
}



void Background::addTile(QPointF pos1, QPointF pos2, QChar type) {
  Tile *tile = new Tile(this, pos1, pos2, type);
  this->addItem(tile);
}

void Background::addUnit(QPointF _start, int startPos) {
  Unit *unit = new Unit(this, _start, startPos);
  this->addItem(unit);
  units.push_back(unit);

}

void Background::addTower(QPointF pos1, QPointF pos2, QChar type, int radius) {
  type = 'd';
  Tower *tower = new Tower(this, pos1, pos2, type, radius);
  this->addItem(tower);
}

void Background::makeWavePath() {
    const int WALL   = -1;
    const int BLANK  = -2;
    for (int current = 0; current < start.size(); current++) {
    std::vector<std::vector<int> > labyrinth (height, std::vector<int> (width));
    for(size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
          if (map[i][j] == 'b')
              labyrinth[i][j] = WALL;
            else if (map[i][j] == 'r' || map[i][j] == 'e' || map[i][j] == 's')
              labyrinth[i][j] = BLANK;
  ///////
      QVector<QPointF> currentPath;
      int ay = start[current].y()/square + height/2,
          ax = start[current].x()/square + width/2,
          by = end.y()/square + height/2,
          bx = end.x()/square + width/2;
      int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
      int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
      int d, x, y, k;
      bool stop;


      // распространение волны
      d = 0;
      labyrinth[ay][ax] = 0;            // стартовая ячейка помечена 0
      do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for (y = 0; y < height; ++y)
          for (x = 0; x < width; ++x)
            if (labyrinth[y][x] == d)                         // ячейка (x, y) помечена числом d
            {
              for ( k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
              {
                 int iy = y + dy[k],
                     ix = x + dx[k];
                 if (iy >= 0 && iy < height && ix >= 0 && ix < width && labyrinth[iy][ix] == BLANK)
                 {
                    stop = false;              // найдены непомеченные клетки
                    labyrinth[iy][ix] = d + 1;      // распространяем волну
                 }
              }
            }
        d++;
      } while ( !stop && labyrinth[by][bx] == BLANK );


      // восстановление пути
      d = labyrinth[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
      x = bx;
      y = by;
      while ( d > 0 ) {
        currentPath.push_front(QPointF(x*square - square*(width-1)/2, y*square - (height-1) * square/2));                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k) {
           int iy = y + dy[k],
               ix = x + dx[k];
           if (iy >= 0 && iy < height && ix >= 0 && ix < width && labyrinth[iy][ix] == d) {
              x = x + dx[k];
              y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
              break;
          }
        }
      }
      currentPath.push_front(QPointF(ax*square - square*(width-1)/2, ay*square - (height-1) * square/2));        // теперь px[0..len] и py[0..len] - координаты ячеек пути
      path.push_back(currentPath);
    }
}

void Background::spawnUnit() {
    if (currentWave < numberOfUnitsToSpawn[wave].size() && numberOfUnitsToSpawn[wave][currentWave] != 0) {
         this->addUnit(path[wave][0], wave);
         numberOfUnitsToSpawn[wave][currentWave]--;
    } else {
         if (currentWave + 1 <= numberOfUnitsToSpawn[wave].size() && units.size() == 0) {
             currentWave++;
             if (currentWave == numberOfUnitsToSpawn[wave].size() && wave + 1 < numberOfUnitsToSpawn.size()) {
                wave++;
                currentWave = 0;
             }
         }
    }
}

void Background::gameTimerSlot() {
    for(int k = 0; k < start.size(); k++) {
        for (int i = 0; i < units.size(); i++) {
            if(units[i]->startPos == k) {
                if(units[i]->currentPos == path[k].size()-2)
                    units[i]->moveTo(path[k][path[k].size()-1]);
                else if (units[i]->pos() != path[k][units[i]->currentPos +1])
                    units[i]->moveTo(path[k][units[i]->currentPos]);


                if(units[i]->pos() == end) {
                    units[i]->~Unit();
                    if (units.size() > 1) {
                        for (int j = 0; j < units.size()-1; j++)
                            units[j] = units[j+1];
                        units[units.size()-2] = units[units.size()-1];
                        units.pop_back();
                    } else
                        units.pop_back();

                }
            }
        }
    }
}


void Background::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // Выбрать башню для постройки
    if (mouseEvent->scenePos().x() >= square*(width+1)/2 && mouseEvent->scenePos().x() <= square*(width+10)/2 &&
        mouseEvent->scenePos().y() >= -square*height/2 && mouseEvent->scenePos().y() <= square*height/2) {
        selectingMode = true;
    }
    // Выбрать определенный тайл
    if (selectingMode)
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
                    if (map[i][j] == 'b') {
                        QPointF pos1(-square/2*width+j*square, -square/2*height+i*square),
                                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
                        if (mouseEvent->scenePos().x() >= pos1.x() && mouseEvent->scenePos().x() <= pos2.x() &&
                            mouseEvent->scenePos().y() >= pos1.y() && mouseEvent->scenePos().y() <= pos2.y()) {
                                QChar type = 'd';
                                addTower(pos1,pos2, type, square);
                                selectingMode = false;
                                break;
                        }
                    }
}


bool Background::waveCompleted() {
//  if (numberOfUnitsToSpawn == 0)
//    return true;
//  else
//    return false;
}


//void Background::makePath(QPointF currentPoint) { // путь строится правильно,  но перемещение сделано не правильно
//  path.push_back(currentPoint);
//  if (currentPoint != end) {
//        size_t x = currentPoint.x()/square + m/2,  // столбик
//               y = currentPoint.y()/square + m/2;     // строка
//        QPointF newPoint;
//        if (x!=m-1) { // right
//            if(map[y][x+1] == 'r' || map[y][x+1] == 'e') {
//              newPoint = QPointF(currentPoint.x() + square,currentPoint.y());
//              if (!path.contains(newPoint))
//                 //if (newPoint != end)
//                    makePath(newPoint);
//              }
//        }
//        if(x!=0) { // left
//            if(map[y][x-1] == 'r' || map[y][x-1] == 'e') {
//              newPoint = QPointF(currentPoint.x() - square, currentPoint.y());
//             if (!path.contains(newPoint))
//                 //if (newPoint != end)
//                    makePath(newPoint);
//            }
//        }
//        if(y!=m-1) { // down
//            if(map[y+1][x] == 'r' || map[y+1][x] == 'e') {
//              newPoint = QPointF(currentPoint.x(),currentPoint.y() + square);
//              if (!path.contains(newPoint))
//                // if (newPoint != end)
//                   makePath(newPoint);
//              }
//        }
//        if(y!=0) { // up
//            if(map[y-1][x] == 'r' || map[y-1][x] == 'e') {
//              newPoint = QPointF(currentPoint.x(),currentPoint.y() - square);
//              if (!path.contains(newPoint))
//                // if (newPoint != end)
//                    makePath(newPoint);
//              }
//        }
//    }
//}




//Unit* Background::getUnit(int x, int y) {

//}

