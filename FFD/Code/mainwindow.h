#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainscene.h"
#include "info.h"
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
    void finish();
    void start(int,int);

};

#endif // MAINWINDOW_H
