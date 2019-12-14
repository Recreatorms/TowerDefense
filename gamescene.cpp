#include "gamescene.h"

GameScene::GameScene() :
  QGraphicsScene()
{

}

GameScene::~GameScene() {
}

void GameScene::fillMap(size_t _width, std::vector<std::vector<QString> > p) {
    map = std::move(p);
    height = map.size();
    width =  _width;
}

void GameScene::createMap(QString _backgroundTheme) { // такого ужасного кода я ещё никогда не писал .-.
  backgroundTheme = _backgroundTheme;
  QString type;
  int rotation = 0;
  this->setSceneRect(QRectF(QPointF(-square,-square),QPointF(square,square)));
  for (size_t i = 1; i < height-1; i++) // потом поменять на int
    for (size_t j = 1; j < width-1; j++) {
        QPointF pos1(-square/2*width +  j*square, -square/2*height+i*square),
                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
        rotation = 0;
        type = "/layers/";
        if (map[i][j] == "b")
          type += "dot.png";
        else
        if (map[i][j] == "r") {
            type += "road_";
//            if (map[i][j] == "e" && (map[i][j-1] == "r" || map[i][j+1] == "r"))
//              type += "5.png";
//            else
            if (map[i][j-1] == 'r' && map[i][j+1] == 'r' && map[i-1][j] == 'r' && map[i+1][j] == 'r')
              type += "9.png";
            else
            if (map[i][j-1] == 'r' && map[i][j+1] == 'r') {
              if (map[i-1][j] == 'r') {
                    type += "8.png";
                    rotation = 180;
                  } else
                      if (map[i+1][j] == 'r') {
                        type += "8.png";
//                      rotation = 0;
                      } else
                        type += "5.png";
            } else
            if (map[i-1][j] == 'r' && map[i+1][j] == 'r') {
              if (map[i][j-1] == 'r') {
                    type += "8.png";
                  rotation = 90;
                } else
                      if (map[i][j+1] == 'r') {
                        type += "8.png";
                      rotation = -90;
                      } else
                        type += "6.png";
            } else
            if (map[i][j+1] == 'r' && map[i+1][j] == 'r') {
              type += "1.png";
              rotation = 0;
            } else
            if (map[i][j-1] == 'r' && map[i+1][j] == 'r') {
              type += "1.png";
              rotation = 90;
            } else
            if (map[i][j+1] == 'r' && map[i-1][j] == 'r') {
              type += "1.png";
              rotation = -90;
            } else
            if (map[i][j-1] == 'r' && map[i-1][j] == 'r') {
              type += "1.png";
              rotation = 180;
            }
//            } else
          }

        this->addTile(pos1, pos2, type, rotation);
  }
  rotation = 0;
  for (size_t i = 0; i < height; i++) {
    if (map[i][0] == "r") {
        QPointF pos1(-square/2*width, -square/2*height+i*square),
                pos2(-square/2*(width-2),-square/2*(height-2)+i*square);
          type = "/layers/road_5.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[i][width-1] == "r") {
        QPointF pos1(-square/2*width +(width-1)*square, -square/2*height+i*square),
                pos2(-square/2*(width-2) +(width-1)*square,-square/2*(height-2)+i*square);
        type = "/layers/road_5.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[i][0] == "b") {
        QPointF pos1(-square/2*width, -square/2*height+i*square),
                pos2(-square/2*(width-2),-square/2*(height-2)+i*square);
        type = "/layers/dot.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[i][width-1] == "b") {
        QPointF pos1(-square/2*width +(width-1)*square, -square/2*height+i*square),
                pos2(-square/2*(width-2) +(width-1)*square,-square/2*(height-2)+i*square);
        type = "/layers/dot.png";
        this->addTile(pos1, pos2, type, rotation);
    }
  }
  for (size_t j = 0; j < width; j++) {
    if (map[0][j] == "r") {
        QPointF pos1(-square/2*width + j*square, -square/2*height),
                pos2(-square/2*(width-2) + j*square,-square/2*(height-2));
          type = "/layers/road_6.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[height-1][j] == "r") {
        QPointF pos1(-square/2*width + j*square, -square/2*height+(height-1)*square),
                pos2(-square/2*(width-2) + j*square,-square/2*(height-2)+(height-1)*square);
        type = "/layers/road_6.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[0][j] == "b") {
        QPointF pos1(-square/2*width + j*square, -square/2*height),
                pos2(-square/2*(width-2) + j*square,-square/2*(height-2));
        type = "/layers/dot.png";
        this->addTile(pos1, pos2, type, rotation);
    }
    if (map[height-1][j] == "b") {
        QPointF pos1(-square/2*width + j*square, -square/2*height+(height-1)*square),
                pos2(-square/2*(width-2) + j*square,-square/2*(height-2)+(height-1)*square);
        type = "/layers/dot.png";
        this->addTile(pos1, pos2, type, rotation);
    }
  }

 // Background Texture
  QString path;
  path = ("../TowerDefense/images/Map/game_background_"+backgroundTheme+"/layers/land.png");
  QPixmap bg(path);
  bg = bg.scaled(QGraphicsScene::width(), QGraphicsScene::height(), Qt::KeepAspectRatioByExpanding,Qt::FastTransformation);
  QPalette palette;
  palette.setBrush(QPalette::Background, bg);
  this->setPalette(palette);
  this->setBackgroundBrush(QBrush(bg));

}


void GameScene::setGameOptions(QVector<QVector<size_t> > _number, int _playerMoney) {
  for (size_t i = 0; i < height; i++)
    for (size_t j = 0; j < width; j++) {
      if (map[i][j] == "s") {
          start.push_back(QPointF(-square/2*(width-1) +j*square,-square/2*(height-1) +i*square));
          map[i][j] = "r";
//          getItem(j,i)->setOpacity(0.2);
      }
      if (map[i][j] == "e") {
          end = QPointF(-square/2*(width-1) +j*square,-square/2*(height-1) +i*square);
//          getItem(j,i)->setOpacity(0.2);
          map[i][j] = "r";
          QPointF pos1(-square/2*width +j*square, -square/2*height+i*square),
                  pos2(-square/2*(width-2) +j*square,-square/2*(height-2)+i*square);
          addTile(pos1, pos2, "/layers/dot.png", 0);
      }
    }
  playerMoney = _playerMoney;
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

    // Rapid // mage or artillery or superarcher
        pos1 = QPointF(square*(width+1)/2, -square*(height)/2+1*square);
        pos2 = QPointF(square*(width+10)/2,-square*(height)/2+(1+1)*square);
        interface = new Interface(this, pos1, pos2, "Artillery");
        this->addItem(interface);
        interfaces.push_back(interface);
    // Archer or artillery
        pos1 = QPointF(square*(width+1)/2, -square*(height)/2+2*square);
        pos2 = QPointF(square*(width+10)/2,-square*(height)/2+(2+1)*square);
        interface = new Interface(this, pos1, pos2, "Archer");
        this->addItem(interface);
        interfaces.push_back(interface);
    // Support // spawns defenders
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
    interface->addGameInfo(this->playerHP, waveCounter, playerMoney);
    this->addItem(interface);
    interfaces.push_back(interface);

}

//QGraphicsItem* GameScene::getItem(size_t x, size_t y) { // Зачем мне нужен этот метод??????????
//  QPointF pos1(-square/2*width + x*square, -square/2*height +y*square);
//  for (qreal i = 0; i < square*height; i+=square) // потом поменять на int
//    for (qreal j = 0; j < square*width; j +=square) {
//        QPointF pos2(-square/2*width+j, -square/2*height+i);
//    if (pos1 == pos2) {
//        QTransform trans;
//        QGraphicsItem* item = this->itemAt(pos1, trans);
//        if (item != nullptr)
//            return item;
//      }
//    }
//  return nullptr;
//}



void GameScene::addTile(QPointF pos1, QPointF pos2, QString type, int rotation) {
  Tile *tile = new Tile(this, pos1, pos2, backgroundTheme, type, rotation);
  this->addItem(tile);
}

void GameScene::addUnit(QPointF _start, int _startPos, QString type) {
  Unit *unit = new Unit(this, _start, _startPos, type, path, interfaces);
  this->addItem(unit);
  units.push_back(unit);
  for (int i = 0; i < towers.size(); i++)
      towers[i]->updateUnits(units);
}

void GameScene::addTower(QPointF pos1, QPointF pos2, QString type, int price) {
  QTransform trans;
  QList<QGraphicsItem*> items = this->items((pos1+pos2)/2);
  Tile *tile = nullptr;
  for (int i = 0; i < items.size(); i++)
    tile = static_cast<Tile*>(items[i]);
  if (!tile->hasTower) {
    Tower *tower = new Tower(this, pos1, pos2, type, price, towers.size(), units, interfaces);

    if (type == "Support") {
        std::thread([tower]()
        {
            Signal sig;
            connect(&sig, &Signal::sig, tower, &Tower::spawnNPC);
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                emit sig.sig();
            }
         /*doSOMEJOB*/
        }
        ).detach();
    } else {
        std::thread([tower]()
        {
            Signal sig;
            connect(&sig, &Signal::sig, tower, &Tower::acquireTarget);
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                emit sig.sig();
            }
         /*doSOMEJOB*/
        }
        ).detach();
    }
    playerMoney -= interfaces[indexOfSelectedTower]->price;
    this->addItem(tower);
    towers.push_back(tower);
    tile->hasTower = true;
  } else
    this->addText("can't place same tower on same tile", QFont("Comic Sans MS", 40,-1,false));


}


void GameScene::spawnUnitSlot() {
  if (playerHP != 0) {
    if (numberOfUnitsToSpawn[numberOfUnitsToSpawn.size()-1][numberOfUnitsToSpawn[numberOfUnitsToSpawn.size()-1].size()-1] == 0 && units.size() == 0) {
        this->addText("victory",QFont("Comic Sans MS", 40,-1,false));
        return;
    }
    if (currentWave < numberOfUnitsToSpawn[startingPoint].size() && numberOfUnitsToSpawn[startingPoint][currentWave] != 0) {
        interfaces[5]->addGameInfo(this->playerHP, waveCounter, this->playerMoney);
        interfaces[5]->update();
        QString type = "default";
         this->addUnit(path[startingPoint][0], startingPoint, type);
         numberOfUnitsToSpawn[startingPoint][currentWave]--;
    } else {
         if (currentWave < numberOfUnitsToSpawn[startingPoint].size() && units.size() == 0) {
             currentWave++;
             int bonusIncome = playerMoney / 100;
             playerMoney += bonusIncome*10;
//             playerMoney /= 100;
             waveCounter++;
             if (currentWave == numberOfUnitsToSpawn[startingPoint].size() && startingPoint + 1 < numberOfUnitsToSpawn.size()) {
                startingPoint++;
                currentWave = 0;
             }
         }
    }

    }
}

void GameScene::upgradeCurrentTowerSlot()
{
//  interfaces[5]->typeOfEntity = "Tower";
//  selectedTower = interfaces[i]->typeOfTower;
//  indexOfSelectedTower = i;
//  interfaces[5]->typeOfTower = selectedTower;
    int index = interfaces[5]->currentTowerIndex;
    int price = towers[index]->price;

    if (playerMoney > price && towers[index]->level < 4) {
      playerMoney -= price;
    //  towers[index]->upgradeTower();
      interfaces[5]->typeOfEntity = "default";
//      interfaces[5]->level = towers[index]->level;
      interfaces[5]->playerMoney = playerMoney;
      interfaces[5]->update();
      towers[index]->upgradeTower();
//        towers[indexOfSelectedTower];
      interfaces[4]->showingUpgradeButton = false;
      interfaces[4]->showingRouteButton = false;
      interfaces[4]->update();
   }

}

void GameScene::changeRouteSlot()
{
    changingRoutePointScene = true;
    towers[interfaces[5]->currentTowerIndex]->attackArea->show();

}

void GameScene::gameTimerSlot() {
   if (playerHP != 0) {
//       this->addText(QString::number(this->playerHP),QFont("Comic Sans MS", 40,-1,false));

       QString selectedUnit;
       for (int i = 0; i < units.size(); i++)
          if(units[i]->clicked) {
            selectedUnit = units[i]->type;
            interfaces[5]->typeOfEntity = "Unit";
            interfaces[5]->typeOfUnit = selectedUnit;
            interfaces[5]->entityInfo(units[i]->hp, units[i]->damage, units[i]->attackBaseValue, 0, units[i]->cooldown, units[i]->speed, 0);
            interfaces[5]->update();
            break;
          }

       for (int i = 0; i < 4; i++) {
           if (interfaces[i]->selectingMode) {
             buildingTower = true;
             interfaces[5]->selectingMode = true;
             interfaces[5]->typeOfEntity = "Tower";
             interfaces[5]->level = 1;
             selectedTower = interfaces[i]->typeOfTower;
             indexOfSelectedTower = i;
             interfaces[5]->typeOfTower = selectedTower;
             interfaces[5]->entityInfo(interfaces[i]->hp, interfaces[i]->dmg, 0, interfaces[i]->radius, interfaces[i]->attackSpeed, 0, interfaces[i]->price);
             interfaces[5]->update();
             break;
          }
        }
       if (interfaces[4]->showingUpgradeButton && towers[interfaces[5]->currentTowerIndex]->level != 3) {
         emit showUpgradeButton();
       }
       else {
         interfaces[4]->showingUpgradeButton = false;
         emit hideUpgradeButton();
       }
       if (interfaces[4]->showingRouteButton)
         emit showRouteButton();
       else
         emit hideRouteButton();
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
                    if (units[i]->hp <= 0)
                      playerMoney += units[i]->income;
                    interfaces[5]->addGameInfo(this->playerHP, waveCounter, this->playerMoney);
                    interfaces[5]->update();
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
//        for(int i = 0; i < towers.size(); i++)
//          towers[i]->~Tower();

        return;
      }
}


void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if(playerHP != 0) { // Если игрок ещё не проиграл
    // Выбрать башню для постройки
    if (changingRoutePointScene) {
//        int i = mouseEvent->scenePos().x()/square + height/2,
//            j = mouseEvent->scenePos().y()/square + width/2;
//         if (map[i][j] == "r") {
            towers[interfaces[5]->currentTowerIndex]->changeRouteTower(mouseEvent->scenePos());
            changingRoutePointScene = false;
            towers[interfaces[5]->currentTowerIndex]->attackArea->hide();
//           }
    }
    // Выбрать определенный тайл
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++) {

                        QPointF pos1(-square/2*width+j*square, -square/2*height+i*square),
                                pos2(-square/2*(width-2)+j*square,-square/2*(height-2)+i*square);
                        if (mouseEvent->scenePos().x() >= pos1.x() && mouseEvent->scenePos().x() <= pos2.x() &&
                            mouseEvent->scenePos().y() >= pos1.y() && mouseEvent->scenePos().y() <= pos2.y()) {
                            if (interfaces[4]->showingUpgradeButton) {
                              interfaces[4]->showingUpgradeButton = false;
                              interfaces[4]->update();
                              }
                            if (interfaces[4]->showingRouteButton) {
                              interfaces[4]->showingRouteButton = false;
                              interfaces[4]->update();
                              }
                            if (buildingTower && map[i][j] == 'b' && playerMoney >= interfaces[indexOfSelectedTower]->price) {
                                addTower(pos1,pos2, selectedTower, interfaces[indexOfSelectedTower]->price);
                                buildingTower = false;
                                interfaces[5]->selectingMode = false;
                            }
                                interfaces[5]->typeOfEntity = "default";
                                interfaces[5]->playerMoney = playerMoney;
                                interfaces[5]->update();
                                for (int k = 0; k < 4; k++)
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
          if (map[i][j] == 'b' || map[i][j] == '0')
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


