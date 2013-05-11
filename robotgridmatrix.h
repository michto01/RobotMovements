#ifndef ROBOTGRIDMATRIX_H
#define ROBOTGRIDMATRIX_H

#include "robotgriditem.h"
#include <QGraphicsScene>
#include <iostream>
#include <string>
#include "map.h"

class RobotGridMatrix
{
    QList<RobotGridItem*> *items;
public:
    int Maze[10][8];
    RobotGridMatrix(QList<RobotGridItem*> items);
    void ImportMaze(int maze[8][10]);
    void AttachToScene(QGraphicsScene *scene);
    void MapToScene(Map imp);
    ~RobotGridMatrix();
};

#endif // ROBOTGRIDMATRIX_H
