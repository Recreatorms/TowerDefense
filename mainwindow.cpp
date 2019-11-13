#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGraphicsView>
#include <QGraphicsItem>
#include <vector>

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->resize(1920,1080);
// this->setFixedSize(1920,1080);
  background = new Background();
  ui->graphicsView->setScene(background);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  size_t height = 10, width = 8;
  std::vector<std::vector<char> > p = /*(n, std::vector<int> (m));*/
  {
        {'b', 'b', 'b', 'b', 'b', 'r', 'b', 'b'},
        {'s', 'r', 'b', 'r', 'r', 'r', 'b', 'b'},
        {'b', 'r', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'r', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'r', 'r', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'b', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'b', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'b', 'b', 'r', 'b', 'b', 'b', 'b'},
        {'b', 'e', 'r', 'r', 'r', 'r', 'r', 'r'},
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},

  };
  size_t numberOfUnitsToSpawn = 10;
//  // теперь можно заполнить двумерный массив (вектор векторов)
  background->fillMap(height, width, p);
  background->createMap(); // и отрисовать карту с n*m тайлами(квадратами) причём каждый тайл является отдельным item'ом
  background->setGameOptions(numberOfUnitsToSpawn);
  background->addInterface();
  background->makeWavePath();
  timer = new QTimer(); // почти самая важная штука, иначе ничего не будет происходить
  spawnTimer = new QTimer();
  connect(spawnTimer, &QTimer::timeout, background, &Background::spawnUnit);
  connect(timer, &QTimer::timeout, background, &Background::gameTimerSlot);
  timer->start(1000/160); // это важно
  spawnTimer->start(500);


}

MainWindow::~MainWindow()
{
  delete ui;
}




