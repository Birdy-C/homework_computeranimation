//Birdy 17.10.10

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
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(clearScene()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startAnimation()));

}


void MainWindow::set_UI()
{

    QMovie *movie = new QMovie("E:/Code/animation_pro3/com_animation_experiment3/pic/3.gif");
    ui->label_6->setMovie(movie);
    //connect(movie,SIGNAL(finished()),movie,SLOT(start()));
    movie->start();
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


void MainWindow::clearScene()
{
    myscene.clear();
}



void MainWindow::startAnimation()
{
    myscene.play();
}



//==================


void MainWindow::on_radioButton_7_clicked()
{
    myscene.drawType = false;
}

void MainWindow::on_radioButton_8_clicked()
{
    myscene.drawType = true;
}

void MainWindow::on_radioButton_4_clicked()
{
    myscene.tweenType = false;
}

void MainWindow::on_radioButton_5_clicked()
{
    myscene.tweenType = true;

}
