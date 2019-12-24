#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include <QFile>
#include <QDataStream>
#include "mythread.h"
#include "mainmenu.h"
#include "gamescene.h"
#include <QResizeEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void createMenu();
  void createLevel(int level);
  void addGameButtons();
  void deleteGameButtons();
  void deleteMenuButtons();
  void switchScene();
public slots:
  void launch();
  void restartGame();
  void stopTimers();
  void proceedToNextLevel();
private:
  bool launched = false;
  bool stopped = false;
  QVector<QString> data;
  int height,
      width;
  int _playerMoney;
  QVector<Wave> waves;
  int numberOfWaves;
  int spawnPoint;
  int numberOfUnits;  QString typeOfUnitsInWave;

  QPushButton *pauseButton,
              *launchWaveButton,
              *upgradeButton,
              *sellButton,
              *changeRouteButton,
              *backToMenuButton,
              *restartLevelButton,
              *nextLevelButton,

              *levelSelectorButton,
              *startGameButton,
              *exitButton,
              *closeLevelSelectorButton;
  Ui::MainWindow * ui;
  QTimer         * gameTimer;
  QTimer         * spawnTimer;
  MainMenu       * menuScene;
  GameScene      * gameScene;
};
#endif // MAINWINDOW_H
