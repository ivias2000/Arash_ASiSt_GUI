#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPoint(double x, double y);
    void ClearData();
    void plot();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y;
};
#endif // MAINWINDOW_H
