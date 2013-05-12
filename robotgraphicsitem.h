#ifndef ROBOTGRAPHICSITEM_H
#define ROBOTGRAPHICSITEM_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QObject>
#include <QAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QSequentialAnimationGroup>

class RobotGraphicsItem : public QGraphicsPixmapItem  {

private:
    QList<QPoint> *path;
    QList<QPoint>::Iterator actualPathPosition;
    QPoint        actualPosition;
    QPoint        actualScenePosition;
    QPoint        end;
    QRectF        boundingRect();
    int           isFinished;

public:
    RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end);
    void calculatePosition(QPoint point);
    void animation(QSequentialAnimationGroup *group);
    ~RobotGraphicsItem();
};

class RobotGraphicsObject : public QObject, public RobotGraphicsItem {
    Q_OBJECT
    Q_PROPERTY (QPoint pos READ Pos WRITE setPos)
public slots:
    void animation();
public:
    RobotGraphicsObject(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> path, QPoint end);
    ~RobotGraphicsObject();
};

#endif // ROBOTGRAPHICSITEM_H
