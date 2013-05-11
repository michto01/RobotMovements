#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionRun_triggered();
    void on_actionGenerate_triggered();
    void on_actionReset_triggered();

    void on_actionImportMap_triggered();
    void on_actionImportAll_triggered();

    void on_actionExportMap_triggered();
    void on_actionExportMovements_triggered();
    void on_actionExportCriticalPlaces_triggered();

    void on_actionHelpAbout_triggered();
    void on_actionHelpInstructions_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
