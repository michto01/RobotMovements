#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtWebKitWidgets/QWebView>
#include <QWebSettings>
#include <QtWebKit>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QUrl>

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private slots:
    void on_actionClose_clicked();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
