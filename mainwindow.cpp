#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QtCore>
#include <QtGui>

#include "instructionsdialog.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "mainwindow.h"

#include "robotgraphicsitem.h" /** Contains RobotGraphicsItem & RobotGraphicObject */
#include "robotgridmatrix.h"   /** Contains RobotGridMatrix */
#include "robotgriditem.h"     /** Contains RobotGridItem   */
#include "robotpath.h"         /** Contains RobotPath */
#include "robotmap.h"          /** Contains RobotPathMap & RobotMap */
#include "map.h"               /** Contains Map */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionRun_triggered() {

    QGraphicsScene *scene = new QGraphicsScene(this); /** Create new scene */
    QList<RobotGridItem*> grid;                       /** List holding the grid (graphical representation)*/
    QList<QPoint> path_1, path_2;                     /** Lists holding paths vectors */
    RobotGridMatrix Matrix(grid);                     /** Class for operating with grid */
    RobotMapPath one(1);                              /** Generation of path for 1 robot */
    RobotMapPath two(0);                              /** Generation of path for 2 robot */
    Map Maze;                                         /** Class to hold maze for algorithms */

    ui->areaPlot->setScene(scene);                          /* Set scene */
    ui->areaPlot->setRenderHint(QPainter::Antialiasing);    /* Add antialiasing */
    ui->areaPlot->setBackgroundBrush(QPixmap(":/terrain/background.png"));
    one.CreatePath();       /* Create 1. path */
    two.CreatePath();       /* Create 2. path */
    one.common_map(two);    /* Merge paths together */

    Maze.mapFromArray(one.common); /** Convert commnon map to condinate format */
    Matrix.MapToScene(Maze);       /** Calculate positions of tiles in scene */
    Matrix.AttachToScene(scene);   /** Attach tiles to scene (create graphic maze) */

    qDebug("CORNER::[0][0] => %d", Maze.popValue(QPoint(0,0)));
    qDebug("CORNER::[0][7] => %d", Maze.popValue(QPoint(0,7)));
    qDebug("CORNER::[9][7] => %d", Maze.popValue(QPoint(9,7)));
    qDebug("CORNER::[9][0] => %d", Maze.popValue(QPoint(9,0)));

    RobotPath(Maze, &path_1, &path_2);    /** Generate the paths vectors */
    qDebug("HIRE: %d", path_1.isEmpty());

    RobotGraphicsObject *bot = new RobotGraphicsObject(QPixmap(":/terrain/captain.png"),0, path_1, QPoint(0,7));
    RobotGraphicsObject *bot2 = new RobotGraphicsObject(QPixmap(":/terrain/monolith3.png"),0, path_2, QPoint(0,7));
    scene->addItem(bot);
    scene->addItem(bot2);

    QSequentialAnimationGroup *group1 = new QSequentialAnimationGroup;
    QListIterator<QPoint> PathIteration(path_1);
    PathIteration.next();
    while(PathIteration.hasNext()) {
        QPropertyAnimation *animation = new QPropertyAnimation(bot,"pos",this);
        animation->setStartValue(PathIteration.peekPrevious());
        animation->setEndValue(PathIteration.next());
        group1->addAnimation(animation);
    }

    QListIterator<QPoint> PathIteration2(path_2);
    PathIteration2.next();
    while(PathIteration2.hasNext()) {
        QPropertyAnimation *animation = new QPropertyAnimation(bot2,"pos",this);
        animation->setStartValue(PathIteration2.peekPrevious());
        animation->setEndValue(PathIteration2.next());
        group1->addAnimation(animation);
    }

    group1->start();

    scene->update();

    /*QPropertyAnimation animation(bot,"pos");
    animation.setDuration(10000);
    animation.setStartValue(QPoint(0,0));
    animation.setEndValue(QPoint(300,500));
    animation.start();*/

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
