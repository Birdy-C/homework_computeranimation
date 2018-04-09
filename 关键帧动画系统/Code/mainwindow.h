#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainscene.h"
#include <QApplication>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    class MainScene myscene;
    void connect_signal();
    void set_UI();



public slots:
    void addPoint(int x,int y);
    void resizeShape(qreal w,qreal h);
    void clearScene();
    void startAnimation();


private slots:


    void on_radioButton_7_clicked();
    void on_radioButton_8_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
};

#endif // MAINWINDOW_H
