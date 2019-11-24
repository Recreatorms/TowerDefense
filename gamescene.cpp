#include "gamescene.h"

GameScene::GameScene() :
  QGraphicsScene()
{

}

GameScene::~GameScene() {
}

void GameScene::fillMap(size_t _width, std::vector<std::vector<char> > p) {
    map = std::move(p);
    height = map.size();
    width =  _width;
}

void GameScene::createMap() {
  this->setSceneRect(QRectF(QPointF(-square,-square),QPointF(square,square)));
  for (size_t i = 0; i < height; i++) // потом поменять на int
    for (size_t j = 0; j < width; j++) {
        QPointF pos1(-square/2*width+j*square, -square/2*height+i*square),
                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
        this->addTile(pos1, pos2, map[i][j]);
    }
 // Background Texture
  QString path;
  path = ("../TowerDefense/images/Preview.png");
  QPixmap bg(path);
  bg = bg.scaled(QGraphicsScene::height(), QGraphicsScene::height(), Qt::KeepAspectRatioByExpanding,Qt::FastTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, bg);
  this->setPalette(palette);
  this->setBackgroundBrush(QBrush(bg));

}

void GameScene::setGameOptions(QVector<QVector<size_t> > _number) {
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


void GameScene::addInterface() {
    // List of Towers
    // "Musketeer" // lvl 4 (archer) or mage
        QPointF pos1(square*(width+1)/2, -square*(height)/2+0*square),
                pos2(square*(width+10)/2,-square*(height)/2+(0+1)*square);
        Interface *interface = new Interface(this, pos1, pos2, "Musketeer");
        this->addItem(interface);
        interfaces.push_back(interface);

    // Rapid // mage or artillery
        pos1 = QPointF(square*(width+1)/2, -square*(height)/2+1*square);
        pos2 = QPointF(square*(width+10)/2,-square*(height)/2+(1+1)*square);
        interface = new Interface(this, pos1, pos2, "Rapid");
        this->addItem(interface);
        interfaces.push_back(interface);
    // Archer
        pos1 = QPointF(square*(width+1)/2, -square*(height)/2+2*square);
        pos2 = QPointF(square*(width+10)/2,-square*(height)/2+(2+1)*square);
        interface = new Interface(this, pos1, pos2, "Archer");
        this->addItem(interface);
        interfaces.push_back(interface);
    // Support
        pos1 = QPointF(square*(width+1)/2, -square*(height)/2+3*square);
        pos2 = QPointF(square*(width+10)/2,-square*(height)/2+(3+1)*square);
        interface = new Interface(this, pos1, pos2, "Support");
        this->addItem(interface);
        interfaces.push_back(interface);

    // Upgrade Menu
    pos1 = QPointF(square*(width+1)/2, -square*(height)/2+4*square);
    pos2 = QPointF(square*(width+10)/2,-square*(height)/2+6*square);
    interface = new Interface(this, pos1, pos2, "Upgrade");
    this->addItem(interface);
    interfaces.push_back(interface);
    // Info Menu
    pos1 = QPointF(square*(width+1)/2, -square*(height)/2+6*square);
    pos2 = QPointF(square*(width+10)/2,square*(height)/2);
    interface = new Interface(this, pos1, pos2, "Info");
    this->addItem(interface);
    interfaces.push_back(interface);

}

QGraphicsItem* GameScene::getItem(size_t x, size_t y) { // Зачем мне нужен этот метод??????????
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



void GameScene::addTile(QPointF pos1, QPointF pos2, QChar type) {
  Tile *tile = new Tile(this, pos1, pos2, type);
  this->addItem(tile);

}

void GameScene::addUnit(QPointF _start, int _startPos, QString type) {
  Unit *unit = new Unit(this, _start, _startPos, type, path);
  qreal speed = 1;
  unit->setOptions(1/speed, 5,1); // speed/hp/attackPower
  this->addItem(unit);
  units.push_back(unit);
  for (int i = 0; i < towers.size(); i++)
      towers[i]->updateUnits(units);
}

void GameScene::addTower(QPointF pos1, QPointF pos2, QString type, qreal radius) {
  QTransform trans;
  QList<QGraphicsItem*> items = this->items((pos1+pos2)/2);
  Tile *tile = nullptr;
  for (int i = 0; i < items.size(); i++)
    tile= static_cast<Tile*>(items[i]);
  if (!tile->hasTower) {
    Tower *tower = new Tower(this, pos1, pos2, type, radius, units, interfaces);
    this->addItem(tower);
    towers.push_back(tower);
    tile->hasTower = true;
  } else
    this->addText("can't place same tower on same tile",QFont("Comic Sans MS", 40,-1,false));


}


void GameScene::spawnUnit() {
  if (playerHP != 0) {
    if (numberOfUnitsToSpawn[numberOfUnitsToSpawn.size()-1][numberOfUnitsToSpawn[numberOfUnitsToSpawn.size()-1].size()-1] == 0 && units.size() == 0) {
        this->addText("victory",QFont("Comic Sans MS", 40,-1,false));
        return;
    }
    if (currentWave < numberOfUnitsToSpawn[startingPoint].size() && numberOfUnitsToSpawn[startingPoint][currentWave] != 0) {
        QString type = "default";
         this->addUnit(path[startingPoint][0], startingPoint, type);
         numberOfUnitsToSpawn[startingPoint][currentWave]--;
    } else {
         if (currentWave < numberOfUnitsToSpawn[startingPoint].size() && units.size() == 0) {
             currentWave++;
             if (currentWave == numberOfUnitsToSpawn[startingPoint].size() && startingPoint + 1 < numberOfUnitsToSpawn.size()) {
                startingPoint++;
                currentWave = 0;
             }
         }
    }

    }
}

void GameScene::gameTimerSlot() {
   if (playerHP != 0) {
    for(int k = 0; k < start.size(); k++) {
        for (int i = 0; i < units.size(); i++) {
            if(units[i]->startPos == k) {
                if(units[i]->currentPos == path[k].size()-2)
                    units[i]->moveTo(path[k][path[k].size()-1]);
                else if (units[i]->pos() != path[k][units[i]->currentPos +1])
                    units[i]->moveTo(path[k][units[i]->currentPos]);


                if(units[i]->pos() == end || units[i]->hp <= 0) {
                    if (units[i]->pos() == end)
                      playerHP -= units[i]->attackBaseValue;

                    int index = i;
                    units[i]->~Unit();
                    if (index == units.size()-1)
                      units.pop_back();
                    else {
                    if (units.size() > 1) {
                        for (int j = index; j < units.size()-1; j++)
                            units[j] = units[j+1];
                        units[units.size()-2] = units[units.size()-1];
                        units.pop_back();
                    } else
                        units.pop_back();
                    }
                    for (int t = 0; t < towers.size(); t++)
                        towers[t]->updateUnits(units);
                }
            }
        }
    }
      } else {
        this->addText("ggwp",QFont("Comic Sans MS", 40,-1,false));
        return;
      }
}


void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if(playerHP != 0) { // Если игрок ещё не проиграл
    // Выбрать башню для постройки
   QString type;
   for (int i = 0; i < interfaces.size(); i++)
      if (interfaces[i]->selectingMode) {
         selectingMode = true;
         type = interfaces[i]->typeOfTower;
         break;
      }
      else
         selectingMode = false;

    // Выбрать определенный тайл
    if (selectingMode)
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
                    if (map[i][j] == 'b') {
                        QPointF pos1(-square/2*width+j*square, -square/2*height+i*square),
                                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
                        if (mouseEvent->scenePos().x() >= pos1.x() && mouseEvent->scenePos().x() <= pos2.x() &&
                            mouseEvent->scenePos().y() >= pos1.y() && mouseEvent->scenePos().y() <= pos2.y()) {

                                addTower(pos1,pos2, type, 3);
                                for (int k = 0; k < interfaces.size(); k++)
                                  interfaces[k]->selectingMode = false;
                                break;
                        }
                    }
  }
}

void GameScene::makeWavePath() {
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

