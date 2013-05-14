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
    QPoint        actualPosition;
    QPoint        actualScenePosition;
    QPoint        end;
    QRectF        boundingRect();
    int           isFinished;

public:
    QList<QPoint>& path;

public:
    RobotGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> &path, QPoint end);
    void calculatePosition(QPoint point);
    //void animation(QSequentialAnimationGroup *group);
    QPoint takeFirstPathItem();
    QPoint getActualPosition();
    QPoint getScenePosition();

    void setActualPosition(QPoint terget);
    ~RobotGraphicsItem();
};

class RobotGraphicsObject : public QObject, public RobotGraphicsItem {
    Q_OBJECT
    Q_PROPERTY(QPoint pos READ getPosition WRITE setPosition)

private:
    QPropertyAnimation posAnimation;

public slots:
    void animationFinished();
    QPoint getPosition();
    void setPosition(QPoint target);
public:
    RobotGraphicsObject(const QPixmap &pixmap, QGraphicsItem *parent, QList<QPoint> &path, QPoint end);
    ~RobotGraphicsObject();
    void animation(QPoint start, QPoint end);
    QPropertyAnimation getAnimation();
};

#endif // ROBOTGRAPHICSITEM_H
