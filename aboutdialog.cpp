#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QtWebKit>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("qrc://Icons.qrc/files/about.html"));
    //ui->webView->
    ui->webView->show();
}

AboutDialog::~AboutDialog() {
    delete ui;
}

void AboutDialog::on_actionClose_clicked(){ this->close();}
