#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rsautils.h"
#include "httpclient.h"

#include <QMessageBox>
#include <QFuture>
#include <QtConcurrent>


#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    HttpClient http;
    http.get("https://passport.baidu.com/v2/?login");
    QString str = http.get("https://passport.baidu.com/v2/api/?getapi&tpl=pp&apiver=v3");

    ui->textBrowser->setPlainText(str);
}

void MainWindow::on_actiongwa_triggered()
{
    QMessageBox msg(this);
    msg.setText("gwa!");
    msg.exec();
    ui->statusBar->showMessage("gwagwagwa!");

}
