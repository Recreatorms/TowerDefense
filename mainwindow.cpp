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
  this->setFixedSize(1920,1080);
  background = new Background();
  ui->graphicsView->setScene(background->getScene());
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  size_t n = 6, m = 6;
  std::vector<std::vector<int> > p = /*(n, std::vector<int> (m));*/
  {
        {0, 0, 0, 3, 1, 0},
        {2, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 0}
  };
//  // теперь можно заполнить двумерный массив (вектор векторов)
  background->fillMap(n,m,p);

  background->createMap(); // и отрисовать карту с n*m тайлами(квадратами) причём каждый тайл является отдельным item'ом
  background->makeChanges();

  background->setStartEndPos();
  background->makePath(background->start);
  background->addUnit();
  timer = new QTimer();  // почти самая важная штука, иначе ничего не будет происходить
  connect(timer, &QTimer::timeout, background, &Background::gameTimerSlot);

  timer->start(1000/80); // это важно

}

MainWindow::~MainWindow()
{
  delete ui;
}




