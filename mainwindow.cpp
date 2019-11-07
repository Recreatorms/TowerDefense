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
  this->resize(1280,720);

  background = new Background();
  ui->graphicsView->setScene(background->getScene());
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  size_t n = 5, m = 5;
  std::vector<std::vector<int> > p (n, std::vector<int>(m));
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      p[i][j] = 1;                // теперь можно заполнить двумерный массив (вектор векторов)

  background->fillMap(n,m,p);

  background->createMap(); // и отрисовать карту с n*m тайлами(квадратами) причём каждый тайл является отдельным item'ом

  unit = new Unit();
  background->getScene()->addItem(unit);
  timer = new QTimer();  // почти самая важная штука, иначе ничего не будет происходить
  connect(timer, &QTimer::timeout, unit, &Unit::gameTimerSlot);

  timer->start(1000/80); // это важно

}

MainWindow::~MainWindow()
{
  delete ui;
}




