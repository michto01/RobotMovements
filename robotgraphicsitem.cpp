#include "robotgraphicsitem.h"

RobotGraphicsItem::RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end) : QGraphicsPixmapItem(pixmap,parent) {
    this->path       = &path;
    this->end        = end;
    this->isFinished = false;
    this->actualPathPosition = this->path->begin();
    this->animateMovement();

    qDebug("RobotGraphicItem::Constructor : all setting applied");
}

void RobotGraphicsItem::calculatePosition(QPoint point) {
    this->actualPosition   = point;
    if(this->actualPosition.x() % 2 == 0)
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,this->actualPosition.y()*71);
    else
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,(this->actualPosition.y()*71)+35);
}

int RobotGraphicsItem::animation(QAnimationGroup &group) {
    for(this->actualPathPosition = this->path->begin(); this->actualPathPosition != this->path->end(); ++actualPathPosition) {
        (*actualPathPosition) = this->actualPathPosition;
        this->actualScenePosition = this->calculatePosition((*actualPosition));
        QPropertyAnimation *animation = new QPropertyAnimation(this, this->actualScenePosition);
        animation->setDuration(300);

    }
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
