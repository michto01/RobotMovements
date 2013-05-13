#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPixmap>

#include "instructionsdialog.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "mainwindow.h"

#include "robotgraphicsitem.h"
#include "robotgridmatrix.h"
#include "robotgriditem.h"
#include "robotpath.h"
#include "robotmap.h"
#include "map.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionRun_triggered() {

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->areaPlot->setScene(scene);
    ui->areaPlot->setRenderHint(QPainter::Antialiasing);

    QList<RobotGridItem*> grid;
    QList<QPoint> path_1, path_2;
    RobotGridMatrix Matrix(grid);
    RobotMapPath one(1); /** Path for 1 robot */
    RobotMapPath two(0); /** Path for 2 robot */
    Map Maze;

    one.CreatePath();
    two.CreatePath();
    one.common_map(two);

    Maze.mapFromArray(one.common);
    Matrix.MapToScene(Maze);
    Matrix.AttachToScene(scene);

    qDebug("CORNER::[0][0] => %d", Maze.popValue(QPoint(0,0)));
    qDebug("CORNER::[0][7] => %d", Maze.popValue(QPoint(0,7)));
    qDebug("CORNER::[9][7] => %d", Maze.popValue(QPoint(9,7)));
    qDebug("CORNER::[9][0] => %d", Maze.popValue(QPoint(9,0)));

    RobotPath(Maze, path_1, path_2);

    RobotGraphicsObject *bot = new RobotGraphicsObject(QPixmap(":/terrain/monolith3.png"),0,path_1,QPoint(0,7));
    scene->addItem(bot);

    qDebug() << "Action->run";

    /** IDEA BOX - STUFF TESTED, TESTING, DEPRE., UNUSED */

    //QListIterator<QPoint> i(path_1); while(i.hasNext()) qDebug() << i.next();
    //QSequentialAnimationGroup *Bot1Path1 = new QSequentialAnimationGroup;
    //bot->animation(Bot1Path1);
    /*
    int tmp[8][10] = {{2,2,2,2,2,0,0,0,0,1},
                      {0,0,0,0,2,0,0,0,1,1},
                      {0,0,1,1,3,1,1,1,1,0},
                      {1,1,1,0,2,0,0,0,0,0},
                      {1,0,0,0,2,2,2,0,0,0},
                      {1,0,0,0,0,0,2,0,0,0},
                      {1,0,0,0,0,0,2,2,2,0},
                      {1,0,0,0,0,0,0,0,2,2}};
    */
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
