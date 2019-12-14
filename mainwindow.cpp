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
// this->setFixedSize(1920,1080);
  gameScene = new GameScene();
  ui->graphicsView->setScene(gameScene);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  size_t width = 8;
  std::vector<std::vector<QString> > p = /*(n, std::vector<int> (m));*/
  {
        {"0", "0", "0", "0", "0", "s", "0", "0"},
        {"s", "r", "b", "r", "r", "r", "0", "0"},
        {"0", "r", "b", "r", "b", "0", "0", "0"},
        {"0", "r", "b", "r", "0", "0", "b", "0"},
        {"0", "r", "b", "r", "b", "0", "r", "s"},
        {"0", "r", "r", "r", "b", "0", "r", "b"},
        {"0", "b", "b", "r", "0", "b", "r", "0"},
        {"0", "0", "b", "r", "b", "0", "r", "b"},
        {"0", "e", "r", "r", "r", "r", "r", "0"},
        {"0", "0", "0", "0", "0", "0", "0", "0"},

  };
  gameScene->fillMap(width, p);
  QVector<QVector<size_t> > numberOfUnitsToSpawn =
  {
       {100},
       {10, 10, 10},
       {20}
  };


  QString backgroundTheme = "1";
  // теперь можно заполнить двумерный массив (вектор векторов)
  int _playerMoney = 500;
  gameScene->setGameOptions(numberOfUnitsToSpawn, _playerMoney);
  gameScene->createMap(backgroundTheme); // и отрисовать карту с n*m тайлами(квадратами) причём каждый тайл является отдельным item'ом
  gameScene->addInterface();
  gameScene->makeWavePath();

  QPushButton *launchWave = new QPushButton(QIcon(QPixmap("../TowerDefense/images/change_route.png")), "Launch", ui->graphicsView);
  launchWave->setGeometry(100,100,100,100);

  QIcon icon(QPixmap("../TowerDefense/images/4.png"));
  QPushButton *upgradeButton = new QPushButton(icon, "Upgrade", ui->graphicsView);
  connect(gameScene, &GameScene::showUpgradeButton, upgradeButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideUpgradeButton, upgradeButton, &QPushButton::hide);
  connect(upgradeButton, &QPushButton::clicked, gameScene, &GameScene::upgradeCurrentTowerSlot);
  QPointF pos1(square*(width+1)/2, -square*(p.size())/2+4*square),
          pos2(square*(width+10)/2,-square*(p.size())/2+6*square);
  upgradeButton->setGeometry(/*gameScene->interfaces[4]->x()+pos1.x(), gameScene->interfaces[4]->x()+ pos2.y()*/1450, 480, 100, 100);

  QPushButton *changeRouteButton = new QPushButton(icon, "Change Route", ui->graphicsView);
  connect(gameScene, &GameScene::showRouteButton, changeRouteButton, &QPushButton::show);
  connect(gameScene, &GameScene::hideRouteButton, changeRouteButton, &QPushButton::hide);
  connect(changeRouteButton, &QPushButton::clicked, gameScene, &GameScene::changeRouteSlot);
  changeRouteButton->setGeometry(1600, 480, 100,100);



  timer = new QTimer();
  connect(timer, &QTimer::timeout, gameScene, &GameScene::gameTimerSlot);
  timer->start(1000/120);   connect(launchWave, &QPushButton::clicked, this, &MainWindow::launch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launch()
{
    if (!launched) {
        spawnTimer = new QTimer();
        connect(spawnTimer, &QTimer::timeout, gameScene, &GameScene::spawnUnitSlot);
        spawnTimer->start(1000);
        launched = true;
    } else {

    }
}





