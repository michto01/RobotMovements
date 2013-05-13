#include "robotpath.h"

RobotPath::RobotPath(RobotGridMatrix *Maze, QList<QPoint> botOnePath, QList<QPoint> botTwoPath){
    this->botOnePath = &botOnePath;
    this->botTwoPath = &botTwoPath;

    for(int r=0; r < 8; r++)
        for(int c=0; c < 10; c++)
            this->Maze[r][c] = Maze->Maze[r][c];
    //this->Maze = Maze->Maze;
    Robot bot1, bot2;
    {
        bot1.Pos     = QPoint(9,0);
        bot1.Dir     = DOWN;
        bot1.PrevDir = DEFAULT;
        this->botOnePath->append(bot1.Pos);
        qDebug("ACTUAL: Maze[%d][%d] {0}",bot1.Pos.x(),bot1.Pos.y());
    }
    {
        bot2.Pos     = QPoint(9,7);
        bot2.Dir     = UP;
        bot2.PrevDir = DEFAULT;
        this->botTwoPath->append(bot2.Pos);
    }

    int t = 1;
    while((bot1.Pos != QPoint(0,7))) {
        this->FindDirection(bot1, 1);
        this->MakeStep(bot1);
        qDebug("ACTUAL: Maze[%d][%d] {%d}",bot1.Pos.x(),bot1.Pos.y(),t);
        this->botOnePath->append(bot1.Pos);
        if(t > 20) break;
        t++;
    }
  /*
    while((bot2.Pos != QPoint(0,0))) {
    //for(int t; t < 10; t++) {
        bot2.Dir = this->FindDirection(bot2, BOT2);
        this->MakeStep(&bot2); qDebug("hire2 %d",t);
        this->botTwoPath->append(bot2.Pos);
    }*/
}

RobotPath::RobotPath(Map maze, QList<QPoint> botOnePath, QList<QPoint> botTwoPath) {
    this->botOnePath = &botOnePath;
    this->botTwoPath = &botTwoPath;
    this->map        = &maze;

    Robot bot1, bot2;
    {
        bot1.ID      = 2;
        bot1.Pos     = QPoint(9,0);
        bot1.Dir     = DOWN;
        bot1.PrevDir = DEFAULT;
        this->botOnePath->append(bot1.Pos);
        qDebug("ACTUAL: Maze[%d][%d] {0}",bot1.Pos.x(),bot1.Pos.y());
    }
    {
        bot2.ID      = 1;
        bot2.Pos     = QPoint(9,7);
        bot2.Dir     = UP;
        bot2.PrevDir = DEFAULT;
        this->botTwoPath->append(bot2.Pos);
    }
    int t = 0;
    while((bot1.Pos != QPoint(0,7))) {
        this->Movement(bot1);
        this->botOnePath->append(bot1.Pos);
        qDebug("ACTUAL1: MAZE[%d][%d] => %d",bot1.Pos.x(),bot1.Pos.y(),t);
        t++; if(t > 50) break;
    }
    t = 0;
    qDebug("");
    while((bot2.Pos != QPoint(0,0))) {
        this->Movement(bot2);
        this->botOnePath->append(bot2.Pos);
        qDebug("ACTUAL2: MAZE[%d][%d] => %d",bot2.Pos.x(),bot2.Pos.y(),t);
        t++; if(t > 50) break;
    }
}

void RobotPath::Movement(Robot &bot) {
    switch(bot.ID) {
        case 1: {
            if(this->map->popValue(QPoint_LEFT+bot.Pos) == bot.ID || this->map->popValue(QPoint_LEFT+bot.Pos) == SHARED) {
                if(bot.PrevDir != RIGHT) {
                    bot.PrevDir = bot.Dir = LEFT;
                    bot.Pos    += QPoint_LEFT;
                    return;
                }
            }
            if(this->map->popValue(QPoint_DOWN+bot.Pos) == bot.ID || this->map->popValue(QPoint_DOWN+bot.Pos) == SHARED) {
                if(bot.PrevDir != UP) {
                    bot.PrevDir = bot.Dir = DOWN;
                    bot.Pos    += QPoint_DOWN;
                    return;
                }
            }
            if(this->map->popValue(QPoint_UP+bot.Pos) == bot.ID || this->map->popValue(QPoint_UP+bot.Pos) == SHARED) {
                if(bot.PrevDir != DOWN) {
                    bot.PrevDir = bot.Dir = UP;
                    bot.Pos    += QPoint_UP;
                    return;
                }
            }
            if(this->map->popValue(QPoint_RIGHT+bot.Pos) == bot.ID || this->map->popValue(QPoint_RIGHT+bot.Pos) == SHARED) {
                if(bot.PrevDir != LEFT) {
                    bot.PrevDir = bot.Dir = RIGHT;
                    bot.Pos    += QPoint_RIGHT;
                    return;
                }
            }
        } break;
        case 2: {
            if(this->map->popValue(QPoint_LEFT+bot.Pos) == bot.ID || this->map->popValue(QPoint_LEFT+bot.Pos) == SHARED) {
                if(bot.PrevDir != RIGHT) {
                    bot.PrevDir = bot.Dir = LEFT;
                    bot.Pos    += QPoint_LEFT;
                    return;
                }
            }
            if(this->map->popValue(QPoint_UP+bot.Pos) == bot.ID || this->map->popValue(QPoint_UP+bot.Pos) == SHARED) {
                if(bot.PrevDir != DOWN) {
                    bot.PrevDir = bot.Dir = UP;
                    bot.Pos    += QPoint_UP;
                    return;
                }
            }
            if(this->map->popValue(QPoint_DOWN+bot.Pos) == bot.ID || this->map->popValue(QPoint_DOWN+bot.Pos) == SHARED) {
                if(bot.PrevDir != UP) {
                    bot.PrevDir = bot.Dir = DOWN;
                    bot.Pos    += QPoint_DOWN;
                    return;
                }
            }
            if(this->map->popValue(QPoint_RIGHT+bot.Pos) == bot.ID || this->map->popValue(QPoint_RIGHT+bot.Pos) == SHARED) {
                if(bot.PrevDir != LEFT) {
                    bot.PrevDir = bot.Dir = RIGHT;
                    bot.Pos    += QPoint_RIGHT;
                    return;
                }
            }
        } break;
    }
}

RobotPath::~RobotPath(){}

void RobotPath::FindDirection(Robot& BOT, int Elem){
    int x,y;
    x = BOT.Pos.x(); // position swap
    y = BOT.Pos.y(); // position swap

    switch(Elem) {
        case 1: {
                    if(this->Maze[x][y-1] == Elem || this->Maze[x][y-1] == SHARED) {
                        qDebug("LEFT: Maze[%d][%d] == %d",y-1,x,this->Maze[x][y-1]);
                        if(BOT.PrevDir != RIGHT) {
                            BOT.PrevDir = BOT.Dir;
                            BOT.Dir = LEFT;
                            return;
                        }
                    }
                    if(this->Maze[x+1][y] == Elem || this->Maze[x+1][y] == SHARED) {
                        qDebug("DOWN: Maze[%d][%d] == %d",y,x+1,this->Maze[x+1][y]);
                        if(BOT.PrevDir != UP) {
                           BOT.PrevDir = BOT.Dir;
                           BOT.Dir = DOWN;
                           return;
                        }
                    }
                    if(this->Maze[x-1][y] == Elem || this->Maze[x-1][y] == SHARED) {
                        qDebug("UP: Maze[%d][%d] == %d",x-1,y,this->Maze[x-1][y]);
                        if(BOT.PrevDir != DOWN) {
                            BOT.PrevDir = BOT.Dir;
                            BOT.Dir = UP;
                            return;
                        }

                    }
                    if(this->Maze[x][y+1] == Elem || this->Maze[x][y+1] == SHARED) {
                        qDebug("RIGHT: Maze[%d][%d] == %d",x,y+1,this->Maze[x][y+1]);
                        if(BOT.PrevDir != LEFT) {
                            BOT.PrevDir = BOT.Dir;
                            BOT.Dir = RIGHT;
                            return;
                        }
                    }
         }
    }

    //BOT.Dir = LEFT;
}

void RobotPath::MakeStep(Robot& BOT){
    switch(BOT.Dir){
        case    UP: BOT.Pos.rx()--; break;
        case  DOWN: BOT.Pos.rx()++; break;
        case  LEFT: BOT.Pos.ry()--; break;
        case RIGHT: BOT.Pos.ry()++; break;
    }
    BOT.Dir = DEFAULT;
}
