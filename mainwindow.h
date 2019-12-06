#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>
#include "mythread.h"
#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
public slots:
  void launch();
private:
  bool launched = false;
  Ui::MainWindow * ui;
  QTimer         * timer;
  QTimer         * spawnTimer;
  GameScene      * gameScene;
};
#endif // MAINWINDOW_H
