#ifndef ROBOTITEM_H
#define ROBOTITEM_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class RobotItem
{
    QList<QPoint> *path;
    QGraphicsPixmapItem *robot;

public:
    RobotItem(QList<QPoint> path, QGraphicsScene *scene, QGraphicsPixmapItem robot);
    void addToScene(
};

#endif // ROBOTITEM_H
