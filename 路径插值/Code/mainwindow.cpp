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
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(calculate()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startAnimation()));


}


void MainWindow::set_UI()
{

    QMovie *movie = new QMovie("E:/Code/com_animation_experiment1/pic/3.gif");
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
    myscene.clearScene();
}


void MainWindow::calculate()
{

}


void MainWindow::startAnimation()
{
    myscene.startAnimation();

}



//==================
void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    int index[4]={1,2,4,8};
    myscene.dense=index[value];
    myscene.show_tween_point();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    int index[4]={8,16,32,64};
    myscene.line.grain=index[value];
    myscene.addTween();
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    myscene.line.tension = arg1;
    myscene.addTween();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    myscene.velocity=arg1;
}

void MainWindow::on_radioButton_clicked()
{
    myscene.vol_type=0;
}

void MainWindow::on_radioButton_2_clicked()
{
    myscene.vol_type=1;
}

void MainWindow::on_radioButton_3_clicked()
{
    myscene.vol_type=2;
}

void MainWindow::on_radioButton_7_clicked()
{
    myscene.line.cal_type = 0;
}

void MainWindow::on_radioButton_8_clicked()
{
    myscene.line.cal_type = 1;
}

void MainWindow::on_radioButton_9_clicked()
{
    myscene.line.cal_type = 2;
}

void MainWindow::on_radioButton_10_clicked()
{
     myscene.line.cal_type = 3;
}

void MainWindow::on_radioButton_4_clicked()
{
    myscene.line.standard_type = 0;
}

void MainWindow::on_radioButton_5_clicked()
{
    myscene.line.standard_type = 1;
}

void MainWindow::on_radioButton_6_clicked()
{
    myscene.line.standard_type = 2;
}

void MainWindow::on_pushButton_4_clicked()
{
    myscene.line.Type = true;
    myscene.addTween();

    QString text= QString::number( myscene.time_record, 10);
    text+="ms";
    ui->label_12->setText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    myscene.line.Type = false;
    myscene.addTween();

    QString text= QString::number( myscene.time_record, 10);
    text+="ms";
    ui->label_3->setText(text);
}
