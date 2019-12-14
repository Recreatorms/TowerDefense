#include "tile.h"

Tile::Tile(QObject *parent, QPointF _pos1, QPointF _pos2, QString _backgroundTheme, QString _type, int rotation) :
           QObject(parent), QGraphicsItem()
{
    pos1 = _pos1;
    pos2 = _pos2;
    QPointF center = this->boundingRect().center();
    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(rotation);
    t.translate(-center.x(), -center.y());
    setTransform(t);
    setPos(pos1);
    backgroundTheme = _backgroundTheme;
    type = _type;
}

Tile::~Tile()
{

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (hasTower)
      return;
    else if (towerSelected)
      hasTower = true;
}

QRectF Tile::boundingRect() const {
    return QRectF(0,0,100,100);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    spriteImage = new QPixmap("../TowerDefense/images/Map/game_background_" + backgroundTheme + type);
    if (type == "/layers/road_1.png") {
        painter->drawPixmap(QRect(0,0,100,100), *spriteImage, spriteImage->rect());
//        painter->setCompositionMode(QPainter::CompositionMode_DestinationOver);
//        spriteImage = new QPixmap("../TowerDefense/images/Map/game_background_" + backgroundTheme + "/layers/road_6.png");
//        painter->drawPixmap(QRectF(0,50,100,100), *spriteImage, spriteImage->rect());
//        spriteImage = new QPixmap("../TowerDefense/images/Map/game_background_" + backgroundTheme + "/layers/road_5.png");
//        painter->drawPixmap(QRectF(50,0,100,150), *spriteImage, spriteImage->rect());
      }
      else {
        //if (type != "/layers/dot.png")
           //  painter->setCompositionMode(QPainter::CompositionMode_DestinationOver);
          painter->drawPixmap(QRectF(0,0,100,100), *spriteImage, spriteImage->rect());
    }
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


