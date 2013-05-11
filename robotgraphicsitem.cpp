#include "robotgraphicsitem.h"

RobotGraphicsItem::RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end) : QGraphicsPixmapItem(pixmap,parent) {
    this->path       = &path;
    this->end        = end;
    this->isFinished = false;
    this->actualPathPosition = this->path->begin();
    this->animateMovement();

    qDebug("RobotGraphicItem::Constructor : all setting applied");
}

int RobotGraphicsItem::animateMovement(){
    if(!isFinished) {
        if(this->actualPathPosition < this->path->end()) {
            this->calculatePosition((*actualPathPosition));
            qDebug("Bad allocation");
            this->setPos(this->actualScenePosition);
            this->actualPathPosition++;
        }
        if(this->actualPosition == this->end) {
            this->isFinished = true;
            return 1;
        }
        else this->isFinished = false;
        return 0;
    }
    else return 1;

}

void RobotGraphicsItem::calculatePosition(QPoint point) {
    this->actualPosition   = point;
    if(this->actualPosition.x() % 2 == 0)
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,this->actualPosition.y()*71);
    else
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,(this->actualPosition.y()*71)+35);
}

RobotGraphicsItem::~RobotGraphicsItem()
{
}


RobotGraphicsObject::RobotGraphicsObject(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end): RobotGraphicsItem(pixmap,parent,path,end){
}

RobotGraphicsObject::~RobotGraphicsObject(){
}

void RobotGraphicsObject::animate(){
    this->animateMovement();
    return;
}
