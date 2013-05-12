#ifndef MAP_H
#define MAP_H

#include <QtCore>
#include <QListIterator>
#include <QString>
#include <QPoint>
#include <QList>

#define CRSS QString(":/terrain/grounds.png")
#define PATH QString(":/terrain/green.png")
#define WALL QString(":/terrain/regular.png")

#define QPoint_UP    QPoint(0,-1)
#define QPoint_DOWN  QPoint(0,1)
#define QPoint_LEFT  QPoint(-1,0)
#define QPoint_RIGHT QPoint(1,0)

typedef struct _map {
  QPoint coords;
     int value;
 QString terrain;
}map;

class Map {
public:
    QList<map> maze;
             Map();
            ~Map();
       void addItem(QPoint p, int value);
       void addItem(QPoint p, int value, QString terrain);
    QString popTrrain(QPoint p);
        int popValue(QPoint p);
       void mapFromArray(int array[][10]);
};

#endif // MAP_H
