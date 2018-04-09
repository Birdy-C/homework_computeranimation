//Birdy 17.11.23
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QPixmap>
#include <QMovie>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this); // 设置ui
    ui->graphicsView->setScene(&myscene.Scene);

    set_UI();
    connect_signal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connect_signal()
{
    connect(ui->graphicsView,SIGNAL(addPoint(int,int)),this,SLOT(addPoint(int,int)));
    connect(ui->graphicsView,SIGNAL(resizeShape(qreal,qreal)),this,SLOT(resizeShape(qreal,qreal)));
    connect(ui->graphicsView,SIGNAL(finishtemp()),this,SLOT(finish()));
    connect(ui->graphicsView,SIGNAL(starttemp(int,int)),this,SLOT(start(int,int)));


}


void MainWindow::set_UI()
{

}


//======================================这里是一堆的槽==============

void MainWindow::addPoint(int x,int y)
{
    myscene.addPoint(x,y);
}


void MainWindow::resizeShape(qreal w,qreal h)
{
    myscene.Scene.setSceneRect(0, 0, w, h);
    myscene.backpicture->setPos(w-450,h-450);
}




void MainWindow::finish()
{
    myscene.finish();
}

void MainWindow::start(int x, int y)
{
    myscene.start(x,y);
}

