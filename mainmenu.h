#ifndef MAINMENU_H
#define MAINMENU_H
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTextStream>


class LevelPreview: public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  explicit LevelPreview(QObject *parent, int _levelNumber, int &_currentLevel, int _completed);
  ~LevelPreview() override;
  int levelNumber;
  int completed;
  QPixmap sprite;
  int &currentLevel;
signals:
  void levelSelected();
protected:
  QRectF boundingRect() const override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

//==============================================================================//

class MainMenu : public QGraphicsScene
{
  Q_OBJECT
public:
  MainMenu();
  ~MainMenu() override;
  int selectedLevel = 0;
  bool selectingLevel = false;
signals:
  void showLevelSelectorButton();
  void showCloseLevelSelectorButton();
  void levelSelected();
public slots:
  void showLevelSelectorSlot();
  void hideLevelSelectorSlot();
protected:
  void drawBackground(QPainter *painter, const QRectF &rect) override;
};


#endif // MAINMENU_H
