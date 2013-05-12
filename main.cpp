#include "mainwindow.h"
#include "robotmap.h"
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDebug>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
       RobotMapPath one(0); /** Path for 1 robot */
       RobotMapPath two(0); /** Path for 2 robot */

       one.CreatePath();
       two.CreatePath();

       one.common_map(two);

       MainWindow w;
       w.show();
       return a.exec();
}
