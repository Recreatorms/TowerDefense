#include "gamescene.h"

GameScene::GameScene() :
  QGraphicsScene()
{
}

GameScene::~GameScene() {
  delete gameInfo;
  if (indicatorIsActive)
    delete indicator;
  QList<QGraphicsItem*> itemsInScene = this->items();
  for (int i = 0; i < itemsInScene.size(); i++) {
      removeItem(itemsInScene[i]);
      itemsInScene[i]->~QGraphicsItem();
    }
  itemsInScene.clear();
  interfaces.clear();
  units.clear();
  towers.clear();
  waves.clear();
  map.clear();
  //  indicator.clear();
  path.clear();
}

void GameScene::fillMap(int _width, QVector<QVector<QString> > p, int _level) {
  map = std::move(p);
  height = map.size();
  width =  _width;
  level = _level;
}

void GameScene::createMap(QString _backgroundTheme) { // такого ужасного кода я ещё никогда не писал .-.
  backgroundTheme = _backgroundTheme;
  QString type;
  QPointF basePos1, basePos2;
  int rotation = 0;
  this->setSceneRect(QRectF(QPointF(-square,-square),QPointF(square,square)));
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {
        if (map[i][j] == "s") {
            start.push_back(QPointF(-square/2*(width-1) -offset +j*square,-square/2*(height-1) +i*square));
            map[i][j] = "r";
            break;
          }
        if (map[i][j] == "e") {
            end = QPointF(-square/2*(width-1) -offset +j*square,-square/2*(height-1) +i*square);
            map[i][j] = "r";
            basePos1 = QPointF(-square/2*width -offset +j*square, -square/2*height+i*square);
            basePos2 = QPointF(-square/2*(width-2) -offset +j*square,-square/2*(height-2)+i*square);
            break;
          }
      }
  for (int i = 1; i < height-1; i++)
    for (int j = 1; j < width-1; j++) {
        QPointF pos1(-square/2*width -offset +  j*square, -square/2*height+i*square),
            pos2(-square/2*(width-2)-offset +j*square,-square/2*(height-2)+i*square);
        rotation = 0;
        type = "/layers/";
        if (map[i][j] == "1" || map[i][j] == "2" || map[i][j] == "3" || map[i][j] == "4") {
            if (map[i][j] == "1")
              type += "decor_1.png";
            if (map[i][j] == "2")
              type += "decor_2.png";
            if (map[i][j] == "3")
              type += "decor_3.png";
            if (map[i][j] == "4")
              type += "tree.png";
          } else
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
  for (int i = 0; i < height; i++) {
      if (map[i][0] == "1" || map[i][0] == "2" || map[i][0] == "3" || map[i][0] == "4") {
          QPointF pos1(-offset -square/2*width, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2),-square/2*(height-2)+i*square);
          if (map[i][0] == "1") {
              type = "/layers/decor_1.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][0] == "2") {
              type = "/layers/decor_2.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][0] == "3") {
              type = "/layers/decor_3.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][0] == "4") {
              type = "/layers/tree.png";
              this->addTile(pos1, pos2, type, rotation);
            }
        }
      if (map[i][width-1] == "1" || map[i][width-1] == "2" || map[i][width-1] == "3"|| map[i][width-1] == "4") {
          QPointF pos1(-offset -square/2*width +(width-1)*square, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2) +(width-1)*square,-square/2*(height-2)+i*square);
          if (map[i][width-1] == "1") {
              type = "/layers/decor_1.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][width-1] == "2") {
              type = "/layers/decor_2.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][width-1] == "3") {
              type = "/layers/decor_3.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[i][width-1] == "4") {
              type = "/layers/tree.png";
              this->addTile(pos1, pos2, type, rotation);
            }
        }
      if (map[i][0] == "r") {
          QPointF pos1(-offset -square/2*width, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2),-square/2*(height-2)+i*square);
          type = "/layers/road_5.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[i][width-1] == "r") {
          QPointF pos1(-offset -square/2*width +(width-1)*square, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2) +(width-1)*square,-square/2*(height-2)+i*square);
          type = "/layers/road_5.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[i][0] == "b") {
          QPointF pos1(-offset -square/2*width, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2),-square/2*(height-2)+i*square);
          type = "/layers/dot.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[i][width-1] == "b") {
          QPointF pos1(-offset -square/2*width +(width-1)*square, -square/2*height+i*square),
              pos2(-offset -square/2*(width-2) +(width-1)*square,-square/2*(height-2)+i*square);
          type = "/layers/dot.png";
          this->addTile(pos1, pos2, type, rotation);
        }

    }
  for (int j = 0; j < width; j++) {
      type = "/layers/";
      if (map[0][j] == "1" || map[0][j] == "2" || map[0][j] == "3" || map[0][j] == "4") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2));
          if (map[0][j] == "1") {
              type = "/layers/decor_1.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[0][j] == "2") {
              type = "/layers/decor_2.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[0][j] == "3") {
              type = "/layers/decor_3.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[0][j] == "4") {
              type = "/layers/tree.png";
              this->addTile(pos1, pos2, type, rotation);
            }
        }
      if (map[height-1][j] == "1" || map[height-1][j] == "2" || map[height-1][j] == "3"|| map[height-1][j] == "4") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height+(height-1)*square),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2)+(height-1)*square);
          if (map[height-1][j] == "1") {
              type = "/layers/decor_1.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[height-1][j] == "2") {
              type = "/layers/decor_2.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[height-1][j] == "3") {
              type = "/layers/decor_3.png";
              this->addTile(pos1, pos2, type, rotation);
            }
          if (map[height-1][j] == "4") {
              type = "/layers/tree.png";
              this->addTile(pos1, pos2, type, rotation);
            }
        }
      if (map[0][j] == "r") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2));
          type = "/layers/road_6.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[height-1][j] == "r") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height+(height-1)*square),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2)+(height-1)*square);
          type = "/layers/road_6.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[0][j] == "b") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2));
          type = "/layers/dot.png";
          this->addTile(pos1, pos2, type, rotation);
        }
      if (map[height-1][j] == "b") {
          QPointF pos1(-offset -square/2*width + j*square, -square/2*height+(height-1)*square),
              pos2(-offset -square/2*(width-2) + j*square,-square/2*(height-2)+(height-1)*square);
          type = "/layers/dot.png";
          this->addTile(pos1, pos2, type, rotation);
        }
    }


  addTile(basePos1, basePos2, "/layers/Base.png", 0);
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


void GameScene::setGameOptions(QVector<Wave> _waves, int _playerMoney) {
  playerMoney = _playerMoney;
  waves = _waves;
  if (!indicatorIsActive) {
      indicator = new Indicator();
      addItem(indicator);
      if ((start[waves[0].spawnPoint].x() + offset)/square + width/2 == 0.0)
        indicator->setPos(start[waves[0].spawnPoint].x()+25,start[waves[0].spawnPoint].y()-25);
      else
        indicator->setPos(start[waves[0].spawnPoint].x()-25,start[waves[0].spawnPoint].y()-25);
      indicatorAdded = true;
      indicatorIsActive = true;
    }
}


void GameScene::addInterface() {
  // List of Towers
  QPointF pos1(square*5, -square*5+0*square),
      pos2(square*75/8,-square*5+(0+1)*square);
  Interface *interface = new Interface(this, pos1, pos2, "Archer");
  this->addItem(interface);
  interfaces.push_back(interface);

  pos1 = QPointF(square*5, -square*5+1*square);
  pos2 = QPointF(square*75/8,-square*5+(1+1)*square);
  interface = new Interface(this, pos1, pos2, "Support");
  this->addItem(interface);
  interfaces.push_back(interface);

  pos1 = QPointF(square*5, -square*5+2*square);
  pos2 = QPointF(square*75/8,-square*5+(2+1)*square);
  interface = new Interface(this, pos1, pos2, "Mage");
  this->addItem(interface);
  interfaces.push_back(interface);

  pos1 = QPointF(square*5, -square*5+3*square);
  pos2 = QPointF(square*75/8,-square*5+(3+1)*square);
  interface = new Interface(this, pos1, pos2, "Artillery");
  this->addItem(interface);
  interfaces.push_back(interface);

  // Upgrade Menu
  pos1 = QPointF(square*5, -square*5+4*square);
  pos2 = QPointF(square*75/8,-square*5+6*square);
  interface = new Interface(this, pos1, pos2, "Upgrade");
  this->addItem(interface);
  interfaces.push_back(interface);

  // Info Menu
  pos1 = QPointF(square*5, -square*5+6*square);
  pos2 = QPointF(square*75/8,square*5);
  interface = new Interface(this, pos1, pos2, "Info");
  this->addItem(interface);
  interfaces.push_back(interface);
  // Game Info Menu
  pos1 = QPointF(-825,-510);
  pos2 = QPointF(-305,-465);
  gameInfo = new Interface(this, pos1, pos2, "Game");
  gameInfo->addGameInfo(this->playerHP, currentWave, playerMoney, this->waves.size());
  this->addItem(gameInfo);

}

void GameScene::addTile(QPointF pos1, QPointF pos2, QString type, int rotation) {
  Tile *tile = new Tile(this, pos1, pos2, backgroundTheme, type, rotation);
  this->addItem(tile);
}

void GameScene::addUnit(int _startPos, QString type) {
  Unit *unit = new Unit(this, _startPos, type, path[_startPos], interfaces);
  this->addItem(unit);
  units.push_back(unit);
  for (int i = 0; i < towers.size(); i++)
    towers[i]->updateUnits(units);
}

void GameScene::addTower(QPointF pos1, QPointF pos2, QString type, int price) {
  QList<QGraphicsItem*> items = this->items((pos1+pos2)/2);
  Tile *tile = nullptr;
  for (int i = 0; i < items.size(); i++)
    tile = static_cast<Tile*>(items[i]);
  if (!tile->hasTower) {
      tile->setOpacity(0.1);
      Tower *tower = new Tower(this, pos1, pos2, type, price, towers.size(), units, interfaces, this->map);

      if (type == "Support") {
          std::thread thread([tower]()
          {
              Signal sig;
              connect(&sig, &Signal::sig, tower, &Tower::spawnNPC);
              while (!tower->deleted) {
                  std::this_thread::sleep_for(std::chrono::milliseconds(1));
                  if (!tower->IsPaused)
                    emit sig.sig();
                }
            }
          );
          thread.detach();
          if (tower->deleted)
            thread.~thread();
        } else {
          std::thread thread([tower]()
          {
              Signal sig;
              connect(&sig, &Signal::sig, tower, &Tower::acquireTarget);
              while (!tower->deleted) {
                  std::this_thread::sleep_for(std::chrono::milliseconds(1));
                  if (!tower->IsPaused)
                    emit sig.sig();
                }
            }
          );
          thread.detach();
          if (tower->deleted)
            thread.~thread();
        }
      playerMoney -= interfaces[indexOfSelectedTower]->price;
      gameInfo->addGameInfo(playerHP, currentWave, playerMoney, waves.size());
      this->addItem(tower);
      towers.push_back(tower);
      tile->hasTower = true;
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

  if (playerMoney >= price) {
      playerMoney -= price;
      //  towers[index]->upgradeTower();
      interfaces[5]->typeOfEntity = "default";
      //      interfaces[5]->level = towers[index]->level;
      interfaces[5]->update();
      gameInfo->addGameInfo(playerHP, currentWave, playerMoney, waves.size());
      towers[index]->upgradeTower();
      //        towers[indexOfSelectedTower];
      interfaces[4]->showingUpgradeButton = false;
      interfaces[4]->showingRouteButton = false;
      interfaces[4]->update();
    }

}

void GameScene::sellCurrentTowerSlot()
{
  int index = interfaces[5]->currentTowerIndex;
  int price = interfaces[5]->sellPrice;
  playerMoney += price;
  QList<QGraphicsItem*> items = this->items((towers[index]->pos1+towers[index]->pos2)/2);
  Tile *tile = nullptr;
  for (int i = 0; i < items.size(); i++)
    tile = static_cast<Tile*>(items[i]);
  tile->hasTower = false;
  tile->setOpacity(1);
  towers[index]->~Tower();
  //  delete towers[index];
  if (index != towers.size() - 1) {
      for (int i = index; i < towers.size() - 1; i++) {
          towers[i+1]->index -=1;
          towers[i] = towers[i+1];
        }
    }
  towers.pop_back();

  interfaces[5]->typeOfEntity = "default";
  gameInfo->addGameInfo(playerHP, currentWave, playerMoney, waves.size());
  interfaces[5]->currentTowerIndex = 0;
  interfaces[5]->update();

  interfaces[4]->showingUpgradeButton = false;
  interfaces[4]->showingRouteButton = false;
  interfaces[4]->update();
}

void GameScene::changeRouteSlot()
{
  changingRoutePointScene = true;
  towers[interfaces[5]->currentTowerIndex]->attackArea->show();

}
void GameScene::paused()
{
  if (!IsPaused) {
      IsPaused = true;
      emit pauseSignal();
      emit showBackToMenuButton();
      grayBackGround = new QGraphicsRectItem();
      menu = new QGraphicsPixmapItem();
      grayBackGround->setRect(QRect(QPoint(-1000,-550),QPoint(1000,550)));
      grayBackGround->setBrush(Qt::SolidPattern);
      grayBackGround->setOpacity(0.4);
      if (!lost) {
          if (!victoryAchieved) {
              menu->setPixmap(QPixmap("../TowerDefense/images/Interface/menu.png"));
            }
          else {
//              emit showNextLevelButton();
              int completedOn;
              if (playerHP == 20)
                completedOn = 3;
              else if (playerHP > 10)
                completedOn = 2;
              else
                completedOn = 1;
              menu->setPixmap(QPixmap("../TowerDefense/images/Interface/Victory" + QString::number(completedOn) + "Stars.png"));
              QVector<QString> data;
              QFile file("../TowerDefense/Levels/Level_Completed");
              int i = 0;
              if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

              QTextStream out(&file);
              while (!out.atEnd()) {
                  QString line = out.readLine();

                  data.push_back(line);
                  i++;
                }
              file.close();
              if (data[level-1].toInt() <  completedOn)
                data.replace(level-1, QString::number(completedOn));
              if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
              QTextStream in(&file);
              for (int i = 0; i < data.size(); i++) {
                  in << data[i] << endl;
                }
              //              QByteArray blockOfData;
              //              i = 0;
              //              while (data[i] != "") {
              //                blockOfData.append(data[i]);
              //                i++;
              //              }
              file.close();
            }
        }
      else {
          menu->setPixmap(QPixmap("../TowerDefense/images/Interface/Defeat.png"));
          gameInfo->addGameInfo(0, currentWave, playerMoney, waves.size());
        }
      menu->setPos(-menu->pixmap().width()/2,-menu->pixmap().height()/2);
      addItem(grayBackGround);
      addItem(menu);
      for (int i = 0; i < towers.size(); i++)
        towers[i]->IsPaused = true;
    }
  else {
      IsPaused = false;
      emit pauseSignal();
      emit hideBackToMenuButton();
      for (int i = 0; i < towers.size(); i++)
        towers[i]->IsPaused = false;
      removeItem(menu);
      removeItem(grayBackGround);
      delete menu;
      delete grayBackGround;
    }
}

void GameScene::clearLevel()
{

  //  for (int i = 0; i < indicator.size(); i++) {
  if (indicatorIsActive) {
      indicator->~Indicator();
      //    delete indicator;
    }
  //    delete indicator[i];

  indicatorIsActive = false;

  //  indicator.clear();
  this->IsPaused = true;
  for(int i = 0; i < towers.size(); i++) {
      QList<QGraphicsItem*> items = this->items((towers[i]->pos1+towers[i]->pos2)/2);
      Tile *tile = nullptr;
      for (int j = 0; j < items.size(); j++)
        tile = static_cast<Tile*>(items[j]);
      tile->hasTower = false;
      tile->setOpacity(1);
      towers[i]->~Tower();
      //      removeItem(towers[i]);
      //      delete towers[i];
      //      delete tile;
    }
  towers.clear();
  for (int i = 0; i < units.size(); i++) {
      units[i]->~Unit();
      //      removeItem(units[i]);
      //    units[i]->~Unit();
    }
  units.clear();
  removeItem(menu);
  removeItem(grayBackGround);
  delete grayBackGround;
  delete menu;
  emit hideSellButton();
  emit hideRouteButton();
  emit hideUpgradeButton();
  emit hideBackToMenuButton();
}
void GameScene::spawnUnitSlot() {
  if (playerHP > 0) {

      if (currentWave < waves.size()) {
          if (waves[currentWave].numberOfUnits == 0) {
              //              indicatorIsActive = true;
              currentWave++;
              if (currentWave+1 < waves.size()) {
                  int bonusIncome = playerMoney / 100;
                  playerMoney += bonusIncome * 5;
                  gameInfo->addGameInfo(this->playerHP, currentWave, this->playerMoney, this->waves.size());
                }
              return;
            }
          if (indicatorIsActive && waves[currentWave].numberOfUnits != 0) {
              //              indicator->~Indicator();
//              removeItem(indicator);
//              delete indicator;
              indicator->~Indicator();
              indicatorAdded = false;
              indicatorIsActive = false;
            }
          if (!indicatorIsActive && waves[currentWave].numberOfUnits <= 3)  {
              if (currentWave+1 != waves.size() && !indicatorAdded) {
                  indicator = new Indicator();
                  addItem(indicator);
                  indicatorIsActive = true;
                  indicatorAdded = true;
                  if ((start[waves[currentWave+1].spawnPoint].x() + offset)/square + width/2 == 0.0)
                    indicator->setPos(start[waves[currentWave+1].spawnPoint].x()+25,start[waves[currentWave+1].spawnPoint].y()-25);
                  else
                    indicator->setPos(start[waves[currentWave+1].spawnPoint].x()-25,start[waves[currentWave+1].spawnPoint].y()-25);
                  //                  indicatorIsActive = true;
                }
            }
          this->addUnit(waves[currentWave].spawnPoint, waves[currentWave].typeOfUnits);
          waves[currentWave].numberOfUnits--;
        } else {
          gameInfo->addGameInfo(this->playerHP, waves.size()-1, this->playerMoney, waves.size());
          if (units.size() == 0) {
              victoryAchieved = true;
              paused();
            }

        }
    }

}

void GameScene::gameTimerSlot() {
  if (playerHP > 0) {
      for (int i = 0; i < 4; i++) {
          if (interfaces[i]->selectingMode) {
              interfaces[5]->selectingMode = true;
              interfaces[5]->typeOfEntity = "Tower";
              interfaces[5]->level = 1;
              selectedTower = interfaces[i]->typeOfTower;
              indexOfSelectedTower = i;
              interfaces[5]->typeOfTower = selectedTower;
              interfaces[5]->entityInfo(interfaces[i]->hp, interfaces[i]->dmg, 0, interfaces[i]->radius, interfaces[i]->attackSpeed, interfaces[i]->price, interfaces[i]->sellPrice);
              interfaces[5]->update();
              break;
            }
        }
      if (interfaces[4]->showingUpgradeButton) {
          if(towers[interfaces[5]->currentTowerIndex]->type != "Archer" && towers[interfaces[5]->currentTowerIndex]->type != "Musketeer" && towers[interfaces[5]->currentTowerIndex]->level != 3)
            emit showUpgradeButton();
          else
            if (towers[interfaces[5]->currentTowerIndex]->type == "Archer" && towers[interfaces[5]->currentTowerIndex]->level != 4)
              emit showUpgradeButton();
          emit showSellButton();
        }
      else {
          interfaces[4]->showingUpgradeButton = false;
          emit hideUpgradeButton();
          emit hideSellButton();
        }
      if (interfaces[4]->showingRouteButton)
        emit showRouteButton();
      else
        emit hideRouteButton();
      //    for(int k = 0; k < start.size(); k++) {
      for (int i = 0; i < units.size(); i++) {
          if(units[i]->currentPos >= units[i]->path.size()-1)
            units[i]->moveTo(units[i]->path.back());
          else if (units[i]->currentPos != units[i]->currentPos+1)
            units[i]->moveTo(units[i]->path[units[i]->currentPos]);

          if(units[i]->currentPos == units[i]->path.size() || units[i]->pos() == end || units[i]->hp <= 0) {
              if (units[i]->hp <= 0) {
                  playerMoney += units[i]->income;
                  units[i]->~Unit();
                  //                  removeItem(units[i]);
                }
              if (units[i]->currentPos == units[i]->path.size() || units[i]->pos() == end) {
                  playerHP -= units[i]->attackBaseValue;
                  units[i]->~Unit();
                  //                  removeItem(units[i]);
                }
              gameInfo->addGameInfo(this->playerHP, currentWave, this->playerMoney, this->waves.size());
              if (currentWave == waves.size())
                gameInfo->addGameInfo(this->playerHP, waves.size()-1, this->playerMoney, this->waves.size());
              this->update();
              units.erase(units.begin() + i);

              for (int t = 0; t < towers.size(); t++)
                towers[t]->updateUnits(units);
            }
        }
    } else {
      lost = true;
      paused();
    }

}


void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if(playerHP > 0) { // Если игрок ещё не проиграл
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
            for (int i = 0; i < towers.size(); i++)
              towers[i]->attackArea->setVisible(false);
            QPointF pos1(-square/2*width-offset +j*square, -square/2*height+i*square),
                pos2(-square/2*(width-2)-offset +j*square,-square/2*(height-2)+i*square);
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
                if (interfaces[5]->selectingMode && map[i][j] == 'b' && playerMoney >= interfaces[indexOfSelectedTower]->price)
                  addTower(pos1,pos2, selectedTower, interfaces[indexOfSelectedTower]->price);
                interfaces[5]->typeOfEntity = "default";
                interfaces[5]->selectingMode = false;
                interfaces[5]->update();
                for (int k = 0; k < 4; k++)
                  interfaces[k]->selectingMode = false;
                break;

              }
          }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key::Key_Escape && event->timestamp()-timeFromPauseToPause > 1001) {
      paused();
      timeFromPauseToPause = event->timestamp();
    }

}


void GameScene::makeWavePath() {
  const int WALL   = -1;
  const int BLANK  = -2;
  for (int current = 0; current < start.size(); current++) {
      std::vector<std::vector<int> > labyrinth (height, std::vector<int> (width));
      for(int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
          if (map[i][j] == 'b' || map[i][j] == '0' || map[i][j] == "1" || map[i][j] == "2" || map[i][j] == "3" || map[i][j] == "4")
            labyrinth[i][j] = WALL;
          else if (map[i][j] == 'r' || map[i][j] == 'e' || map[i][j] == 's')
            labyrinth[i][j] = BLANK;
      ///////
      QVector<QPointF> currentPath;
      size_t ay = start[current].y()/square + height/2,
          ax = (start[current].x() + offset)/square + width/2,
          by = end.y()/square + height/2,
          bx = (end.x()+offset)/square + width/2;
      int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
      int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
      size_t d, x, y, k;
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
          currentPath.push_front(QPointF(x*square -offset - square*(width-1)/2, y*square - (height-1) * square/2));                   // записываем ячейку (x, y) в путь
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
      currentPath.push_front(QPointF(ax*square -offset - square*(width-1)/2, ay*square - (height-1) * square/2));        // теперь px[0..len] и py[0..len] - координаты ячеек пути
      path.push_back(currentPath);
    }
}


