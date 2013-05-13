#ifndef ROBOTPATH_H
#define ROBOTPATH_H

#include "robotgridmatrix.h"
#include <algorithm>
#include <QPoint>
#include "map.h"

typedef struct _Robot {
    QPoint Pos;     /** Robot position */
       int Dir;     /** Directions: {up}(1), {down}{-1}, {left}(-2), {right}{2} */
       int PrevDir; /** Last taken direction */
       int ID;      /** Robot identification */
}Robot;

enum States {
       UP =  1,
     DOWN = -1,
     LEFT = -2,
    RIGHT =  2,

   SHARED =  3,

  DEFAULT = 0
};

class RobotPath
{
    QList<QPoint> *botOnePath;
    QList<QPoint> *botTwoPath;
    Map *map;
    int Maze[8][10];

public:
    RobotPath(RobotGridMatrix *Maze, QList<QPoint> botOnePath, QList<QPoint> botTwoPath);  /** Class constructor */
    RobotPath(Map maze, QList<QPoint> botOnePath, QList<QPoint> botTwoPath);
    void Movement(Robot& bot);
    ~RobotPath(); /** Class destructor */
    void FindDirection(Robot& BOT, int Elem); /** Methode to find next step */
    void MakeStep(Robot& BOT); /** Method to make a next step */
};

#endif // ROBOTPATH_H
