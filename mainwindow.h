#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "background.h"
#include "towers.h"
#include "units.h"
#include "interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

public slots:
private:
  Ui::MainWindow * ui;
  Unit           * unit;
  QTimer         * timer;
  Background     * background;
 // Background *background;
};
#endif // MAINWINDOW_H
