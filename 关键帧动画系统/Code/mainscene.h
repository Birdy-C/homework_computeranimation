//Birdy 2017.10.8

#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QList>
#include <QMainWindow>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QtMath>

#include <QGraphicsItemGroup>
#include <QDebug>
#include <QPixmap>
#include <QTimer>


class MainScene:public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsScene Scene;
    //以下从1开始存放，前后预留一位，在生成时候补齐
    int pointX[2][102];
    int pointY[2][102];

    int pointTweenX[64][102];
    int pointTweenY[64][102];
    int TweenIndex;


    int count[2];//the number of points on the scene
    QGraphicsItem *group_line;//Tweengroup_tween
    QGraphicsItem *group_tween;
    QPen pen[3];
    bool drawType;// start - false; finish - true
    bool tweenType;//line - false; vector line -true

    QTimer *timer;
    double calculate_theta_single(const int deltax,const int deltay);

    QGraphicsItem *backpicture;

public:
    void calculate();//更新第一个和最后一个点
    bool addPoint(const int x, const int y);
    void clear();
    void play();

    MainScene();
    ~MainScene();
    friend class MainWindow;


public slots:
    void next_flame();

};


#endif // MAINSCENE_H


