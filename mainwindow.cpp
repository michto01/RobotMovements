#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "instructionsdialog.h"
#include "robotpath.h"
#include "robotgriditem.h"
#include "robotgridmatrix.h"
#include "robotgraphicsitem.h"
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

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->areaPlot->setScene(scene);
    ui->areaPlot->setRenderHint(QPainter::Antialiasing);

    QList<RobotGridItem*> grid;
    QList<QPoint> path_1, path_2;

    RobotGridMatrix Matrix(grid);

    //Maze.ImportMaze(ib);

    Map Maze;
    Maze.mapFromArray(ib);
    Matrix.MapToScene(Maze);
    Matrix.AttachToScene(scene);
    qDebug(">>> %d >>>", Maze.popValue(QPoint(0,0)));
    qDebug(">>> %d >>>", Maze.popValue(QPoint(0,1)));
    qDebug(">>> %d >>>", Maze.popValue(QPoint(1,0)));
    qDebug(">>> %d >>>", Maze.popValue(QPoint(9,0)));


    RobotPath(Maze, path_1, path_2);
    //QListIterator<QPoint> i(path_1); while(i.hasNext()) qDebug() << i.next();
    RobotGraphicsObject *bot = new RobotGraphicsObject(QPixmap(":/terrain/monolith3.png"),0,path_1,QPoint(0,7));
    scene->addItem(bot);
    QSequentialAnimationGroup *Bot1Path1 = new QSequentialAnimationGroup;
    bot->animation(Bot1Path1);
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
