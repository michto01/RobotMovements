#include "map.h"

Map::Map() {
    qDebug("Map::Map()          => called...\nMap::Map()          => initialized without errors...");
}
Map::~Map() {}

void Map::addItem(QPoint p, int value){
    map tmp;
    tmp.coords = p;
    tmp.value = value;
    this->maze.append(tmp);
}

void Map::addItem(QPoint p, int value, QString terrain){
    map tmp;
    tmp.coords = p;
    tmp.value = value;
    tmp.terrain = terrain;
    this->maze.append(tmp);
}

QString Map::popTrrain(QPoint p){
   QList<map>::Iterator tmp;
   for(tmp = this->maze.begin(); tmp != this->maze.end();++tmp) {
       if((*tmp).coords == p) {
           return (*tmp).terrain;
       }
   }
   return NULL;
}

int Map::popValue(QPoint p){
    QList<map>::Iterator tmp;
    for(tmp = this->maze.begin(); tmp != this->maze.end(); ++tmp) {
        if((*tmp).coords == p) {
            return (*tmp).value;
        }
    }
    return -1;
}

void Map::mapFromArray(int array[8][10]){
    qDebug("Map::mapFromArray() => conversion initialization");
    QString Terrain;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 10; j++) {
            switch(array[i][j])
            {
                case 0: Terrain = WALL; break;
                case 3: Terrain = CRSS; break;
                case 2: Terrain = XATH; break;
                case 1: Terrain = PATH; break;

            };
                this->addItem(QPoint(j,i),array[i][j],Terrain);
        }
    }
    qDebug("Map::mapFromArray() => conversion success");
}
