#include "mainwindow.h"
#include "ui_mainwindow.h"

string send_ver(string first, string last);
void close_sock();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_send_clicked()
{
    QString Qstart = ui->ver1_lineEdit->text();
    QString Qfinal = ui->ver2_lineEdit->text();
    string start, final, path;
    start = Qstart.toStdString();
    final = Qfinal.toStdString();
    path = send_ver(start, final);
    ui->result_label->setText(QString::fromStdString(path));
}

