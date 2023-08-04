#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->lcdNumber_X->display(95);
    ui->lcdNumber_Y->display(55);
    ui->lcdNumber_Z->display(1255);
    addPoint(2.3,1.78);
    plot();
    //ui->lineEdit->setText(QString::number(45));
}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);

}

void MainWindow::ClearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->replot();
    ui->plot->update();
}


void MainWindow::on_pushButton_4_clicked()
{
    ClearData();
    plot();
}
