#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDebug>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
       MainWindow w;
       w.show();
       return a.exec();
}
