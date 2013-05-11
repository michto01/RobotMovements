#ifndef ROBOTGRIDITEM_H
#define ROBOTGRIDITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QPoint>
#include <QtCore>

class RobotGridItem : public QGraphicsPixmapItem {

private:
    QPoint  Coords;   /** The coordinates used in algorithms */
    QPoint  Position; /** The position of the Item calculated in regards to QGraphicView */
    QString Terrain;  /** String spec. the terrain */
public:
    RobotGridItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);
    RobotGridItem(const QPixmap &pixmap, QGraphicsItem *parent, QPoint Coord);
    void SetTerrain(QString terrain);
    void SetPosition(QPoint position);
    void SetCoords(QPoint coords);
    ~RobotGridItem();
    
};

#endif // ROBOTGRIDITEM_H
