#ifndef INSTRUCTIONSDIALOG_H
#define INSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class InstructionsDialog;
}

class InstructionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InstructionsDialog(QWidget *parent = 0);
    ~InstructionsDialog();

private slots:
    void on_actionClose_clicked();

private:
    Ui::InstructionsDialog *ui;
};

#endif // INSTRUCTIONSDIALOG_H
