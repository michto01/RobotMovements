#include "robotmap.h"

RobotMap::RobotMap() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<10;j++) {
            map[i][j]=0;
        }
    }
}

RobotMap::~RobotMap() {
}

int RobotMap::SetWidth(int x) {
    return 0;
}

int RobotMap::SetHeight(int x) {
    return 0;
}

void RobotMap::Draw() {
    for (int i=0;i<8;i++) {
        for (int j=0;j<10;j++)
            cout<<map[7-i][j]<<" ";
        cout<<endl;
    }
}

void RobotMap::wipe() {
    for (int i=0;i<8;i++)
        for (int j=0;j<10;j++)
            map[i][j]=0;
}


RobotMapPath::~RobotMapPath() {
}

int RobotMapPath::CreatePath() {
    srand((unsigned)time(NULL));
    int num_of_stepbacks = 0;

    while (1) {
        if(Step()==1) { //zaseknuti
            this->StepBack();
            num_of_stepbacks++;
            if (num_of_stepbacks==10) {//pokud se nemuze vymotat, zacne se znovu
                this->wipe(); //premazani pole
                if (robot) { //nastaveni puvodnich hodnot
                    map[0][0]=1;pozx=0;pozy=0;
                }
                else {map[7][0]=1;pozx=0;pozy=7;}
                num_of_stepbacks=0;
            }
        };
        if (pozx==9&&pozy==7&&robot)break; //dosazeni cile pro robota 1
        if (pozx==9&&pozy==0&&(!robot))break; //dosazeni cile pro robota 2
    }
    return 0;
}

int RobotMapPath::Step() {

    int direction = this->NextDirection();

    if (direction == 2) {
        this->map[pozy-1][pozx] = 2;
        this->pozy--;
    }
    if (direction == 4) {
        this->map[pozy][pozx-1]=4;
        this->pozx--;
    }
    if (direction == 6) {
        this->map[pozy][pozx+1]=6;
        this->pozx++;
    }
    if (direction == 8) {
        this->map[pozy+1][pozx]=8;
        this->pozy++;
    }
    if (direction == 0) {
        return 1;
    }

    this->baddir=direction;
    return 0;
}

void RobotMapPath::Write() {
    ofstream vyst_soub;

    if (robot) {
        vyst_soub.open("mapaklad.txt");

        for (int i=0;i<8;i++) {
            for (int j=0;j<10;j++) {
                vyst_soub << this->map[7-i][j] << " ";
            }
            vyst_soub << endl;
        }
    }
    else {
        vyst_soub.open("mapazap.txt");

        for (int i=0;i<8;i++) {
            for (int j=0;j<10;j++) {
                vyst_soub<< this->map[7-i][j] << " ";
            }
            vyst_soub << endl;
        }
    }
}

int RobotMapPath::StepBack() {
    stepbacking = 1;
    while(this->map[pozy][pozx] == this->baddir) {
        this->map[pozy][pozx] = 0;
        if(this->baddir == 2) {
            this->pozy++;
        }
        if(this->baddir == 4) {
            this->pozx++;
        }
        if(this->baddir == 6) {
            this->pozx--;
        }
        if(this->baddir == 8) {
            this->pozy--;
        }
    }
    return 0;
}

int RobotMapPath::LastDirection() {
    return 0;
}

int RobotMapPath::NextDirection() {
    bool l = false;
    bool r = false;
    bool u = false;
    bool d = false;
    int num_of_dir = 0;

    if (pozx-1>=0&&map[pozy][pozx-1]==0) {
        if ((map[pozy][pozx-2]==0||pozx-2<0)&&(map[pozy-1][pozx-1]==0||pozy-1<0)&&(map[pozy+1][pozx-1]==0||pozy+1>7)) {
            l=true;
            num_of_dir++;
        }
    }
    if (pozx+1<=9&&map[pozy][pozx+1]==0) {
        if ((map[pozy][pozx+2]==0||pozx+2>9)&&(map[pozy-1][pozx+1]==0||pozy-1<0)&&(map[pozy+1][pozx+1]==0||pozy+1>7)) {
            r=true;
            num_of_dir++;
        }
    }
    if (pozy-1>=0&&map[pozy-1][pozx]==0) {
        if ((map[pozy-2][pozx]==0||pozy-2<0)&&(map[pozy-1][pozx+1]==0||pozx+1>9)&&(map[pozy-1][pozx-1]==0||pozx-1<0)) {
            d=true;
            num_of_dir++;
        }
    }
    if (pozy+1<=7&&map[pozy+1][pozx]==0) {
        if ((map[pozy+2][pozx]==0||pozy+2>7)&&(map[pozy+1][pozx+1]==0||pozx+1>9)&&(map[pozy+1][pozx-1]==0||pozx-1<0)) {
            u=true;
            num_of_dir++;
        }
    }

    if (stepbacking) {
        if (baddir==2) {
            if (d) {
                d=false;
                num_of_dir--;
            }
        }
        if (baddir==4) {
            if (l) {
                l=false;
                num_of_dir--;
            }
        }
        if (baddir==6) {
            if (r) {
                r=false;
                num_of_dir--;
            }
        }
        if (baddir==8) {
            if (u) {
                u=false;
                num_of_dir--;
            }
        }
        if (num_of_dir==0) {
            baddir=map[pozy][pozx];
            StepBack();
        }
        stepbacking=0;
    }
    if (num_of_dir==0) {
        return 0;
    }

    int random=rand()%num_of_dir+1;

    if (random==1) {
        if (l) {
            return 4;
        }
        else if (r) {
            return 6;
        }
        else if (u) {
            return 8;
        }
        return 2;
    }
    if (random==2) {
        if (l) {
            if (r) {
                return 6;
            }
            else if (u) {
                return 8;
            }
            return 2;
        }
        else if (r) {
            if (u) {
                return 8;
            }
            return 2;
        }
        else return 2;
    }
    if (random==3) {
        if (l) {
            if (r) {
                if (u) {
                    return 8;
                }
                else return 2;
            }
            else  {
                return 2;
            }
        }
        else return 2;
    }
    if (random==4) {
        return 2;
    }
}

int RobotMapPath::common_map(RobotMapPath b) {
    int common[8][10];
    ofstream vyst_soub;

    for (int i=0;i<8;i++) {
        for (int j=0;j<10;j++) {
            if (map[i][j]>0&&b.map[i][j]==0) {
                common[i][j]=1;
            }
            if (map[i][j]==0&&b.map[i][j]>0) {
                common[i][j]=2;
            }
            if (map[i][j]>0&&b.map[i][j]>0) {
                common[i][j]=3;
            }
            if (map[i][j]==0&&b.map[i][j]==0) {
                common[i][j]=0;
            }
        }
    }

    vyst_soub.open("mapa.txt");

    for (int i=0;i<8;i++) {
        for (int j=0;j<10;j++) {
            vyst_soub<<common[7-i][j]<<" ";
        }
        vyst_soub<<endl;
    }

    return 0;
}
