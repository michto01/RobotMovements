#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "instructionsdialog.h"
#include "robotpath.h"
#include "robotgriditem.h"
#include "robotgridmatrix.h"
#include "map.h"
#include <QMessageBox>
#include <QPixmap>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionRun_triggered() {

    int ib[8][10] = { {2,2,2,2,2,0,0,0,0,1},
                      {0,0,0,0,2,0,0,0,1,1},
                      {0,0,1,1,3,1,1,1,1,0},
                      {1,1,1,0,2,0,0,0,0,0},
                      {1,0,0,0,2,2,2,0,0,0},
                      {1,0,0,0,0,0,2,0,0,0},
                      {1,0,0,0,0,0,2,2,2,0},
                      {1,0,0,0,0,0,0,0,2,2}};

    QGraphicsScene *scene = new QGraphicsScene; ui->areaPlot->setScene(scene);

    QList<RobotGridItem*> grid;
    RobotGridMatrix Maze(grid);

    //Maze.ImportMaze(ib);

    Map grim;
    grim.mapFromArray(ib);
    Maze.MapToScene(grim);
    Maze.AttachToScene(scene);
    qDebug(">>> %d >>>", grim.popValue(QPoint(0,0)));
    qDebug(">>> %d >>>", grim.popValue(QPoint(0,1)));
    qDebug(">>> %d >>>", grim.popValue(QPoint(1,0)));
    qDebug(">>> %d >>>", grim.popValue(QPoint(9,0)));
    QList<QPoint> p1, p2;
    //RobotPath Xpath(&Maze,p1,p2);
    RobotPath(grim,p1,p2);
    QListIterator<QPoint> i(p1);
    while(i.hasNext()) qDebug() << i.next();

    qDebug() << "Action->run";
}

void MainWindow::on_actionReset_triggered() {
    ui->areaPlot->repaint();
    qDebug() << "Action->reset";
}

void MainWindow::on_actionGenerate_triggered() {qDebug() << "Action->generate";}

void MainWindow::on_actionImportAll_triggered() {qDebug() << "Action->ImportAll";}
void MainWindow::on_actionImportMap_triggered() {qDebug() << "Action->ImportMap";}

void MainWindow::on_actionExportCriticalPlaces_triggered() {qDebug() << "Action->ExportCriticalPlaces";}
void MainWindow::on_actionExportMap_triggered() {qDebug() << "Action->ExportMap";}
void MainWindow::on_actionExportMovements_triggered() {qDebug() << "Action->ExportMovements";}


void MainWindow::on_actionHelpAbout_triggered() {
    AboutDialog *about = new AboutDialog;
    about->setWindowTitle("About");
    about->show();
    qDebug() << "Action->HelpAbout";
}

void MainWindow::on_actionHelpInstructions_triggered(){
    InstructionsDialog *inst = new InstructionsDialog;
    inst->setWindowTitle("Instructions");
    inst->show();
    qDebug() << "Action->HelpInstructions";
}
