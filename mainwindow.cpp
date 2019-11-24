#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <vector>
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
  QPushButton *changeRoute = new QPushButton(QIcon(QPixmap("../TowerDefense/images/change_route.png")),"", this);

  size_t width = 8;
  std::vector<std::vector<char> > p = /*(n, std::vector<int> (m));*/
  {
        {'b', 'b', 'b', 'b', 'b', 's', 'b', 'b'},
        {'s', 'r', 'b', 'r', 'r', 'r', 'b', 'b'},
        {'b', 'r', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'r', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'r', 'b', 'r', 'b', 'b', 'r', 's'},
        {'b', 'r', 'r', 'r', 'b', 'b', 'r', 'b'},
        {'b', 'b', 'b', 'r', 'b', 'b', 'r', 'b'},
        {'b', 'b', 'b', 'r', 'b', 'b', 'r', 'b'},
        {'b', 'e', 'r', 'r', 'r', 'r', 'r', 'b'},
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},

  };
  QVector<QVector<size_t> > numberOfUnitsToSpawn =
  {
       {1},
       {10, 10, 10},
       {20}
  };
  // теперь можно заполнить двумерный массив (вектор векторов)
  gameScene->fillMap(width, p);
  gameScene->createMap(); // и отрисовать карту с n*m тайлами(квадратами) причём каждый тайл является отдельным item'ом
  gameScene->addInterface();

  gameScene->setGameOptions(numberOfUnitsToSpawn);
  gameScene->makeWavePath();

  timer = new QTimer(); // почти самая важная штука, иначе ничего не будет происходить
  spawnTimer = new QTimer();
  connect(spawnTimer, &QTimer::timeout, gameScene, &GameScene::spawnUnit);
  connect(timer, &QTimer::timeout, gameScene, &GameScene::gameTimerSlot);
  timer->start(1000/120); // это важно
  spawnTimer->start(1000);


}

MainWindow::~MainWindow()
{
  delete ui;
}





