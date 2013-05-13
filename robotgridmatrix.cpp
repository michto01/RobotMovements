#include "robotgridmatrix.h"

#define PATH QString(":/terrain/grounds.png")
#define WALL QString(":/terrain/regular.png")


RobotGridMatrix::RobotGridMatrix(QList<RobotGridItem *> items){
 qDebug("RobotGridMatrix::RobotGridMatrix() => called...");
 this->items = &items;
 qDebug("RobotGridMatrix::RobotGridMatrix() => initialized without errors...");
}

void RobotGridMatrix::ImportMaze(int maze[8][10]){
    qDebug("RobotGridMatrix::ImportMaze()     => conversion initialized");
    for (int i = 0; i<8; i++) {
            for (int j = 0; j<10; j++) {
                switch(maze[i][j]) {
                    case 0: this->items->append(new RobotGridItem(WALL,0,QPoint(j,i)));this->Maze[i][j] = maze[i][j]; break;
                    case 1: this->items->append(new RobotGridItem(PATH,0,QPoint(j,i)));this->Maze[i][j] = maze[i][j]; break;
                    case 2: this->items->append(new RobotGridItem(PATH,0,QPoint(j,i)));this->Maze[i][j] = maze[i][j]; break;
                    case 3: this->items->append(new RobotGridItem(PATH,0,QPoint(j,i)));this->Maze[i][j] = maze[i][j]; break;
                }
            }
        }
    qDebug("RobotGridMatrix::ImportMaze()     => conversion success");
}

RobotGridMatrix::~RobotGridMatrix(){
}


void RobotGridMatrix::AttachToScene(QGraphicsScene *scene){
    QListIterator<RobotGridItem*> i(*items);
    while(i.hasNext()) scene->addItem(i.next());
}

void RobotGridMatrix::MapToScene(Map imp){
    QList<map>::Iterator actual;
    for(actual = imp.maze.begin(); actual != imp.maze.end(); ++actual){
        this->items->append(new RobotGridItem(imp.popTrrain((*actual).coords),0,(*actual).coords));
    }
}

