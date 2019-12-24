#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <vector>
extern void addUnit(QPointF _start, int startPos, QString type);

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->resize(1920,1080);
  this->setFixedSize(1920,1080);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);

  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  createMenu();


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::createMenu()
{
  menuScene = new MainMenu();
  ui->graphicsView->setScene(menuScene);

  QIcon icon1 = QPixmap("../TowerDefense/images/Buttons/button_play.png");
  levelSelectorButton = new QPushButton(icon1, "", ui->graphicsView);
  levelSelectorButton->setGeometry(this->geometry().center().x()-100, this->geometry().center().y()-100, 200, 200);
  levelSelectorButton->setIconSize(QSize(200,200));
  levelSelectorButton->setFlat(true);
//  levelSelectorButton->setAutoFillBackground(false);
  levelSelectorButton->show();
  connect(menuScene, &MainMenu::showLevelSelectorButton, levelSelectorButton, &QPushButton::show);
  connect(levelSelectorButton, &QPushButton::clicked, levelSelectorButton, &QPushButton::hide);
  connect(levelSelectorButton, &QPushButton::clicked, menuScene, &MainMenu::showLevelSelectorSlot);

  icon1 = QPixmap("../TowerDefense/images/Buttons/StartTheGame.png");
  startGameButton = new QPushButton(icon1, "", ui->graphicsView);
  startGameButton->setGeometry(this->geometry().center().x()+145, this->geometry().center().y()+125, 250, 102);
  startGameButton->setIconSize(QSize(250,102));
  startGameButton->hide();
  connect(menuScene, &MainMenu::levelSelected, startGameButton, &QPushButton::show);
  connect(menuScene, &MainMenu::showLevelSelectorButton, startGameButton, &QPushButton::hide);
  connect(startGameButton, &QPushButton::clicked, startGameButton, &QPushButton::hide);

  icon1 = QPixmap("../TowerDefense/images/Buttons/exitButton.png");
  exitButton = new QPushButton(icon1, "", ui->graphicsView);
  exitButton->setGeometry(this->geometry().center().x()-83, this->geometry().center().y()+300, 166, 100);
  exitButton->setIconSize(QSize(166,100));
  exitButton->show();
  connect(menuScene, &MainMenu::showLevelSelectorButton, exitButton, &QPushButton::show);
  connect(levelSelectorButton, &QPushButton::clicked, exitButton, &QPushButton::hide);
  connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

  icon1 = QPixmap("../TowerDefense/images/Buttons/CloseLevelSelector.png");
  closeLevelSelectorButton = new QPushButton(icon1, "", ui->graphicsView);
  closeLevelSelectorButton->setGeometry(this->geometry().center().x()+400, this->geometry().center().y()-350, 100, 100);
  closeLevelSelectorButton->setIconSize(QSize(100,100));
  closeLevelSelectorButton->hide();
  closeLevelSelectorButton->setFlat(true);
  connect(menuScene, &MainMenu::showCloseLevelSelectorButton, closeLevelSelectorButton, &QPushButton::show);
  connect(startGameButton, &QPushButton::clicked, closeLevelSelectorButton, &QPushButton::hide);
  connect(closeLevelSelectorButton, &QPushButton::clicked, closeLevelSelectorButton, &QPushButton::hide);
  connect(closeLevelSelectorButton, &QPushButton::clicked, menuScene, &MainMenu::hideLevelSelectorSlot);

  connect(startGameButton, &QPushButton::clicked, this, &MainWindow::switchScene);
}

void MainWindow::createLevel(int level)
{
  data.clear();
  QFile file("../TowerDefense/Levels/Level_" + QString::number(level));
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

  QString backgroundTheme = data[0];
  _playerMoney = data[1].toInt();
  height = data[2].toInt();
  width = data[3].toInt();

  QVector<QVector<QString> > map(height,QVector<QString>(width));
  QVector<QString> notOptimizedMap;

  for (int i = 4; i < height+4; i++)
    notOptimizedMap.push_back(data[i]);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      map[i][j].push_back(notOptimizedMap[i][j*2]);

  numberOfWaves = data[3+height+1].toInt();

  for (int i = 5+height; i < numberOfWaves*3+5+height; i+=3) {
      spawnPoint = data[i].toInt() - 1;
      numberOfUnits = data[i+1].toInt();
      typeOfUnitsInWave = data[i+2];
      Wave wave(spawnPoint, numberOfUnits, typeOfUnitsInWave);
      waves.push_back(wave);
    }

  gameScene->fillMap(width, map, level);
  gameScene->createMap(backgroundTheme);
  gameScene->setGameOptions(waves, _playerMoney);
  gameScene->addInterface();
  gameScene->makeWavePath();
  this->addGameButtons();
  map.clear();
  notOptimizedMap.clear();

  gameTimer = new QTimer();
  connect(gameTimer, &QTimer::timeout, gameScene, &GameScene::gameTimerSlot);
  gameTimer->start(5);
  //  QPushButton *button = new QPushButton(this);
  //  button->setGeometry(0,0,100,100);
  //  connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
  //  connect(gameScene,,timer, &QTimer::stop);
}

void MainWindow::addGameButtons()
{

  QIcon icon(QPixmap("../TowerDefense/images/Buttons/button_start.png"));
  launchWaveButton = new QPushButton(icon, "", ui->graphicsView);
  connect(launchWaveButton, &QPushButton::clicked, this, &MainWindow::launch);
  connect(launchWaveButton, &QPushButton::clicked, launchWaveButton, &QPushButton::hide);
  launchWaveButton->setIconSize(QSize(100,100));
  launchWaveButton->setGeometry(100,100,100,100);


  icon = QPixmap("../TowerDefense/images/Buttons/UpgradeButton.png");
  upgradeButton = new QPushButton(icon, "", ui->graphicsView);
  connect(gameScene, &GameScene::showUpgradeButton, upgradeButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideUpgradeButton, upgradeButton, &QPushButton::hide);
  connect(upgradeButton, &QPushButton::clicked, gameScene, &GameScene::upgradeCurrentTowerSlot);
  upgradeButton->hide();
  upgradeButton->setIconSize(QSize(100,100));
  int y = this->geometry().center().y() + (gameScene->interfaces[4]->pos1.y() + gameScene->interfaces[4]->pos2.y() - 100)/2;
  upgradeButton->setGeometry(this->geometry().center().x() +gameScene->interfaces[4]->pos1.x() + 40, y, 100, 100);
  icon = QPixmap("../TowerDefense/images/Buttons/RouteButton.png");

  changeRouteButton = new QPushButton(icon, "", ui->graphicsView);
  connect(gameScene, &GameScene::showRouteButton, changeRouteButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideRouteButton, changeRouteButton, &QPushButton::hide);
  connect(changeRouteButton, &QPushButton::clicked, gameScene, &GameScene::changeRouteSlot);
  changeRouteButton->hide();
  changeRouteButton->setIconSize(QSize(100,100));
  changeRouteButton->setGeometry(this->geometry().center().x() + (gameScene->interfaces[4]->pos1.x() + gameScene->interfaces[4]->pos2.x() - 100)/2, y, 100,100);

  icon = QPixmap("../TowerDefense/images/Buttons/SellButton.png");
  sellButton = new QPushButton(icon, "", ui->graphicsView);
  connect(gameScene, &GameScene::showSellButton, sellButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideSellButton, sellButton, &QPushButton::hide);
  sellButton->hide();
  connect(sellButton, &QPushButton::clicked, gameScene, &GameScene::sellCurrentTowerSlot);
  sellButton->setIconSize(QSize(100,100));
  sellButton->setGeometry(this->geometry().center().x() +gameScene->interfaces[4]->pos2.x() - 140, y, 100, 100);

  icon = QPixmap("../TowerDefense/images/Buttons/pauseButton.png");
  pauseButton = new QPushButton(icon, "", ui->graphicsView);
  pauseButton->setGeometry(60, 15, 75, 75);
  pauseButton->setIconSize(QSize(75,75));
  connect(gameScene, &GameScene::pauseSignal, this, &MainWindow::stopTimers);
  connect(pauseButton, &QPushButton::clicked, gameScene, &GameScene::paused);

  icon = QPixmap("../TowerDefense/images/Buttons/MainMenuButton.png");
  QPushButton *backToMenuButton = new QPushButton(icon, "", ui->graphicsView);
  backToMenuButton->setGeometry(this->geometry().center().x()-250, this->geometry().center().y()+40, 166, 100);
  backToMenuButton->setIconSize(QSize(166,100));
  backToMenuButton->hide();
  connect(gameScene, &GameScene::showBackToMenuButton, backToMenuButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideBackToMenuButton, backToMenuButton, &QPushButton::hide);
  connect(backToMenuButton, &QPushButton::clicked, this, &MainWindow::switchScene);
  icon = QPixmap("../TowerDefense/images/Buttons/RestartLevelButton.png");
  restartLevelButton = new QPushButton(icon, "", ui->graphicsView);
  restartLevelButton->setIconSize(QSize(166,100));
  restartLevelButton->setGeometry(this->geometry().center().x()-80, this->geometry().center().y()+40, 166, 100);
  restartLevelButton->hide();
  connect(gameScene, &GameScene::showBackToMenuButton, restartLevelButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideBackToMenuButton, restartLevelButton, &QPushButton::hide);
  connect(restartLevelButton, &QPushButton::clicked, this, &MainWindow::restartGame);

  icon = QPixmap("../TowerDefense/images/Buttons/NextLevelButton.png");
  nextLevelButton = new QPushButton(icon, "", ui->graphicsView);
  nextLevelButton->setGeometry(this->geometry().center().x() +90, this->geometry().center().y()+40, 166, 100);
  nextLevelButton->setIconSize(QSize(166,100));
  nextLevelButton->hide();
  connect(gameScene, &GameScene::showNextLevelButton, nextLevelButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideBackToMenuButton, nextLevelButton, &QPushButton::hide);
  connect(nextLevelButton, &QPushButton::clicked, this, &MainWindow::proceedToNextLevel);
}

void MainWindow::deleteGameButtons()
{
  launchWaveButton->~QPushButton();
  upgradeButton->~QPushButton();
  pauseButton->~QPushButton();
  restartLevelButton->~QPushButton();
  nextLevelButton->~QPushButton();
  gameTimer->~QTimer();
  if (launched)
    spawnTimer->~QTimer();
  //  backToMenuButton->deleteLater();
}

void MainWindow::deleteMenuButtons()
{
  levelSelectorButton->~QPushButton();
  exitButton->~QPushButton();
  startGameButton->~QPushButton();
}
void MainWindow::launch()
{
  if (!launched) {
      //      if (spawnTimer == nullptr)
      spawnTimer = new QTimer();
      connect(spawnTimer, &QTimer::timeout, gameScene, &GameScene::spawnUnitSlot);
      spawnTimer->start(1000);
      gameTimer->start(5);
      launched = true;
    }
}
void MainWindow::switchScene()
{
  if (ui->graphicsView->scene() == gameScene) {
      gameScene->clearLevel();
      launchWaveButton->hide();
      pauseButton->hide();
      gameScene->~GameScene();
      deleteGameButtons();
      stopped = false;
      launched = false;
      createMenu();
      menuScene->showLevelSelectorButton();
    }
  else if (ui->graphicsView->scene() == menuScene)
    {
      menuScene->~MainMenu();
      deleteMenuButtons();
      gameScene = new GameScene();
      ui->graphicsView->setScene(gameScene);
      waves.clear();
      createLevel(menuScene->selectedLevel);
      launchWaveButton->show();
      pauseButton->show();
    }
}



void MainWindow::restartGame()
{
  stopped = false;
  launched = false;
  gameScene->clearLevel();
  launchWaveButton->hide();
  pauseButton->hide();
  gameScene->~GameScene();
  deleteGameButtons();
  gameScene = new GameScene();
  ui->graphicsView->setScene(gameScene);
  waves.clear();
  createLevel(menuScene->selectedLevel);
  launchWaveButton->show();
  pauseButton->show();
}

void MainWindow::stopTimers()
{
  if (stopped) {
      launchWaveButton->show();
      stopped = false;
      gameTimer->start(5);
      if (launched)
        spawnTimer->start(1000);
      QIcon icon = QPixmap("../TowerDefense/images/Buttons/PauseButton.png");
      pauseButton->setIcon(icon);
      pauseButton->setIconSize(QSize(75,75));
      pauseButton->setGeometry(60, 15, 75, 75);
      pauseButton->show();
    } else {
      stopped = true;
      launchWaveButton->hide();
      gameTimer->stop();
      if (launched)
        spawnTimer->stop();
      if (gameScene->lost || gameScene->victoryAchieved) {
          pauseButton->hide();
          if (gameScene->victoryAchieved && menuScene->selectedLevel < 6)
            nextLevelButton->show();
        }
      QIcon icon = QPixmap("../TowerDefense/images/Buttons/BackToGameButton.png");
      pauseButton->setIcon(icon);
      pauseButton->setIconSize(QSize(166,100));
      pauseButton->setGeometry(this->geometry().center().x() +90, this->geometry().center().y()+40, 166, 100);

    }
}

void MainWindow::proceedToNextLevel()
{
  stopped = false;
  launched = false;
  gameScene->clearLevel();
  launchWaveButton->hide();
  pauseButton->hide();
  gameScene->~GameScene();
  deleteGameButtons();
  gameScene = new GameScene();
  ui->graphicsView->setScene(gameScene);
  waves.clear();
  menuScene->selectedLevel++;
  createLevel(menuScene->selectedLevel);
  launchWaveButton->show();
  pauseButton->show();
}






