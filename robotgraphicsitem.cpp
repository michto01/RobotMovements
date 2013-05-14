#include "robotgraphicsitem.h"

RobotGraphicsItem::RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> &path, QPoint end) : QGraphicsPixmapItem(pixmap,parent), path(path) {
    qDebug("RobotGraphicsItem::RobotGraohicsItem() => called...");
    this->path = path;

    this->actualPosition     = this->path.takeFirst();
    this->calculatePosition(this->actualPosition);

    this->end                = end;
    this->isFinished         = false;
    this->actualPathPosition = this->path.begin();
    qDebug("RobotGraphicsItem::RobotGraohicsItem() => finished...");
}

void RobotGraphicsItem::calculatePosition(QPoint point) {
    this->actualPosition   = point;
    if(this->actualPosition.x() % 2 == 0)
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,this->actualPosition.y()*71);
    else
        this->actualScenePosition = QPoint(this->actualPosition.x()*54,(this->actualPosition.y()*71)+35);
}

QPoint RobotGraphicsItem::takeFirstPathItem() {
    return this->path.takeFirst();
}

QPoint RobotGraphicsItem::getActualPosition() {
    return this->actualPosition;
}

QPoint RobotGraphicsItem::getScenePosition() {
    return this->actualScenePosition;
}

void RobotGraphicsItem::setActualPosition(QPoint terget) {
    this->actualPosition = terget;
}

RobotGraphicsItem::~RobotGraphicsItem()
{
}


RobotGraphicsObject::RobotGraphicsObject(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> &path, QPoint end): RobotGraphicsItem(pixmap,parent,path,end){
    qDebug("RobotGraphicsObject::RobotGraohicsObject() => called...");
    this->posAnimation.setPropertyName("pos");
    this->posAnimation.setTargetObject(this);
    this->connect(&posAnimation, SIGNAL(finished()), SLOT(animationFinished()));
    //this->animationFinished();
    //this->posAnimation.start();
    qDebug("RobotGraphicsObject::RobotGraohicsObject() => initialized without errors...");
}

RobotGraphicsObject::~RobotGraphicsObject(){
}

void RobotGraphicsObject::animationFinished() {
   if(!this->path.isEmpty()) {
        qDebug("RobotGraphicsObject::animationFinished() => called...");
        this->posAnimation.setStartValue(this->getPosition());
        qDebug("{%d}{%d}", this->getPosition().x(),this->getPosition().y());
        QPoint tmp = this->path.takeFirst();
        this->setPosition(tmp);
        this->calculatePosition(tmp);
        this->posAnimation.setEndValue(this->getPosition());
        qDebug("{%d}{%d}", this->getPosition().x(),this->getPosition().y());
        this->posAnimation.start();
        qDebug("RobotGraphicsObject::animationFinished() => running the animation...");
    }
}

QPoint RobotGraphicsObject::getPosition() {
    return this->getActualPosition();
}


void RobotGraphicsObject::setPosition(QPoint target) {
    this->setActualPosition(target);
    this->calculatePosition(target);
    this->setPos(this->getPosition());
}
