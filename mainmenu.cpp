#include "mainmenu.h"
LevelPreview::LevelPreview(QObject *parent, int _levelNumber, int &_currentLevel, int _completed) :
  QObject(parent), QGraphicsItem(), currentLevel(_currentLevel)
{
  levelNumber = _levelNumber+1;
//  currentLevel = levelNumber;
  completed = _completed;

}

LevelPreview::~LevelPreview()
{
}

QRectF LevelPreview::boundingRect() const {
  return QRectF(-87.5,-87.5,175,175);
}

void LevelPreview::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//  if (completed > 0) {
      emit levelSelected();
//    }
  this->scene()->update(scene()->sceneRect());
  currentLevel = levelNumber;

  Q_UNUSED(event)
}

void LevelPreview::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

  painter->drawPixmap(QRectF(-87.5,-87.5,175,175), QPixmap("../TowerDefense/images/Interface/EmptyTable.png"), QPixmap("../TowerDefense/images/Interface/EmptyTable.png").rect());
  sprite = QPixmap("../TowerDefense/Images/Interface/num_" + QString::number(levelNumber) + ".png");
  painter->drawPixmap(QRectF(QPointF(sprite.rect().topLeft().x() - 17,sprite.rect().topLeft().y()-60),QPointF(sprite.rect().bottomRight().x() - 17,sprite.rect().bottomRight().y()-60)), sprite, sprite.rect());
  sprite = QPixmap("../TowerDefense/images/Interface/star_" + QString::number(completed) + ".png");
  painter->drawPixmap(QRectF(-54,0,108,59.5), sprite, sprite.rect());
  Q_UNUSED(option)
  Q_UNUSED(widget)
}

//==============================================================================//

MainMenu::MainMenu()
{
  this->setSceneRect(QRectF(QPointF(-960,-540),QPointF(960,540)));
  //  emit showLevelSelectorButton();
}

MainMenu::~MainMenu()
{
  QList<QGraphicsItem*> itemsInScene = this->items();
  for (int i = 0; i < itemsInScene.size(); i++) {
      removeItem(itemsInScene[i]);
      delete itemsInScene[i];
    }
}

void MainMenu::showLevelSelectorSlot()
{
  //    emit hideLevelSelectorButton();
  emit showCloseLevelSelectorButton();
    selectedLevel = 0;
  QGraphicsPixmapItem *levelTable = new QGraphicsPixmapItem(QPixmap("../TowerDefense/images/Interface/LevelSelectTable.png"));
  levelTable->setPos(-levelTable->pixmap().width()/2, -levelTable->pixmap().height()/2);
  QVector<QString> data;
  QFile file("../TowerDefense/Levels/Level_Completed");
  int i = 0;
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QTextStream in(&file);
  while (!in.atEnd()) {
      QString line = in.readLine();
      data.push_back(line);
      i++;
    }
  file.close();
  int count = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) {
        LevelPreview *level = new LevelPreview(this, count, selectedLevel, data[count].toInt());
        level->setPos(QPointF(-levelTable->pixmap().width()/2  + 175*j+ 150,-levelTable->pixmap().height()/2+175*i + 300));
        addItem(level);
        connect(level, &LevelPreview::levelSelected, this, &MainMenu::levelSelected);
        count++;
      }
  selectingLevel = true;
  this->update(sceneRect());
}

void MainMenu::hideLevelSelectorSlot()
{
  QList<QGraphicsItem*> itemsInScene = this->items();
  for (int i = 0; i < itemsInScene.size(); i++) {
      removeItem(itemsInScene[i]);
      delete itemsInScene[i];
    }
  selectingLevel = false;
  selectedLevel = 0;
  this->update(sceneRect());
  emit showLevelSelectorButton();
}

void MainMenu::drawBackground(QPainter *painter, const QRectF &rect)
{
  QPixmap sprite = QPixmap("../TowerDefense/images/Interface/backgroundMenu.png");
  painter->drawPixmap(sceneRect(), sprite, sprite.rect());
  if (selectingLevel) {
      sprite = QPixmap("../TowerDefense/images/Interface/LevelSelectTable.png");
      painter->drawPixmap(QRectF(-966/2,-627/2,966,627), sprite, sprite.rect());
      sprite = QPixmap("../TowerDefense/images/Interface/header_levels.png");
      painter->drawPixmap(QRectF(-350,-270,394,162), sprite, sprite.rect());
      sprite = QPixmap("../TowerDefense/images/Interface/PreviewTable.png");
      painter->drawPixmap(QRectF(120,-270,296,534), sprite, sprite.rect());
    }
  if (selectedLevel != 0) {
      painter->setPen(Qt::white);
      painter->setFont(QFont("Comic Sans MS", 22, -1, false));
      painter->drawText(QPointF(220, 100), "Level " + QString::number(selectedLevel));
      sprite = QPixmap("../TowerDefense/images/Interface/Level_" + QString::number(selectedLevel) + "_Preview.png");
      painter->drawPixmap(QRectF(145,-200,250,250), sprite, sprite.rect());
    }
  Q_UNUSED(rect)
}

