#include "instructionsdialog.h"
#include "ui_instructionsdialog.h"

InstructionsDialog::InstructionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionsDialog)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("qrc://Icons.qrc/files/instructions.html"));
    ui->webView->show();
}

InstructionsDialog::~InstructionsDialog()
{
    delete ui;
}

void InstructionsDialog::on_actionClose_clicked(){ this->close();}
