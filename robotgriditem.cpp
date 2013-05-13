#include "robotgriditem.h"


RobotGridItem::RobotGridItem(const QPixmap &pixmap, QGraphicsItem *parent) : QGraphicsPixmapItem(pixmap, parent){
    qDebug("RobotGridItem::RobotGridItem() => called...");
    setCacheMode(NoCache);
    qDebug("RobotGridItem::RobotGridItem() => initialized without errors...");
}

RobotGridItem::RobotGridItem(const QPixmap &pixmap, QGraphicsItem *parent, QPoint Coord) : QGraphicsPixmapItem(pixmap,parent){
    qDebug("RobotGridItem::RobotGridItem() => called...");
    setCacheMode(NoCache);
    SetCoords(Coord);
    qDebug("RobotGridItem::RobotGridItem() => initialized without errors...");
}

void RobotGridItem::SetTerrain(QString terrain){
    this->setPixmap(terrain);
}

void RobotGridItem::SetPosition(QPoint position){
    this->setPos(position);
}

void RobotGridItem::SetCoords(QPoint coords){
    QPoint tmp;
    this->Coords   = coords;
    if(coords.x() % 2 == 0)
        this->Position = tmp = QPoint(coords.x()*54,coords.y()*71);
    else
        this->Position = tmp = QPoint(coords.x()*54,(coords.y()*71)+35);
    this->setPos(tmp);
}

RobotGridItem::~RobotGridItem(){}

