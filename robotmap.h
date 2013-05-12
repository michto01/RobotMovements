#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class RobotMap {

public:
    int map[8][10];
    RobotMap();
    ~RobotMap();
    int SetWidth(int x);
    int SetHeight(int x);
    void Draw();
    void wipe();
};

class RobotMapPath : public RobotMap {

private:
    int pozx;
    int pozy;
    int baddir;
    int ppozx;
    int ppozy;
    int robot;
    int stepbacking;

public:
    RobotMapPath(){
        pozx=0;
        pozy=0;
        baddir=0;
        map[0][0]=1;
    }
    RobotMapPath(int a){
        if (a) {
            map[0][0]=1;
            pozx=0;
            pozy=0;
            baddir=0;
            robot=1;
            stepbacking=0;
        }
        else {
            map[7][0]=1;
            pozx=0;
            pozy=7;
            baddir=0;
            robot=0;
            stepbacking=0;
        }
    }
    ~RobotMapPath();

     int CreatePath();
     int Step();
    void Write();
     int StepBack();
     int LastDirection();
     int NextDirection();
     int common_map(RobotMapPath b);

};

#endif // ROBOTMAP_H
