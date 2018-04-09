//Birdy 2017.11.23

#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "info.h"

#include <QList>
#include <QMainWindow>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QDebug>
#include <QPixmap>
#include "line.h"
#include "points.h"
#include "info.h"

class MainScene:public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsItem *backpicture;//后面那张小埋 不用管
    QGraphicsScene Scene;

    class Line *line[9];//九个点
    class Points *points[50];//我这里设置画的线条最多50条（然而没有溢出报错）
    int point_count;


    QGraphicsItem *group_line;//Tween
    int pointX[10][65];
    int pointY[10][65];
    double Bernstein(int t, double m );
    QPen PenBackline;

    int active_num;//widget 是-1 这个是用来判断点击事件 点到了什么东西 点到画布开始画图，点到弦的一端可以移动

public:

    MainScene();
    ~MainScene();
    friend class MainWindow;

    void drawScene();
    void calculate();
    //清屏
    void clearScene();

    //下面三个都是与鼠标有关的事件
    void addPoint(int x,int y);
    void finish();
    void start(int x ,int y);

};


#endif // MAINSCENE_H


