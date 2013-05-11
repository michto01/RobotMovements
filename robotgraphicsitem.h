#ifndef ROBOTGRAPHICSITEM_H
#define ROBOTGRAPHICSITEM_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QObject>
#include <QGraphicsPixmapItem>

class RobotGraphicsItem : public QGraphicsPixmapItem  {

private:
    QList<QPoint> *path;
    QList<QPoint>::Iterator actualPathPosition;
    QPoint        actualPosition;
    QPoint        actualScenePosition;
    QPoint        end;
    int           isFinished;

public:
    RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end);
    void calculatePosition(QPoint point);
    int animateMovement();
    ~RobotGraphicsItem();
};

class RobotGraphicsObject : public QObject, public RobotGraphicsItem {
    Q_OBJECT
public slots:
    void animate();
public:
    RobotGraphicsObject(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end);
    ~RobotGraphicsObject();
};

#endif // ROBOTGRAPHICSITEM_H
