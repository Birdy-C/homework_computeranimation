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
#include <QGraphicsItemGroup>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include "points.h"
#include "line.h"

class MainScene:public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsScene Scene;
    class Points points;
    class Line line;

    QGraphicsItem *group_basic;//basic line & points
    QGraphicsItem *group_line;//Tween

    QGraphicsItem *group_inner_point;//basic line & points

    QGraphicsItem *group_character;//
    QGraphicsItem *character[8][2];//往返的
    bool char_index;
    bool char_index_before;

    QGraphicsItem *backpicture;

    QBrush brush_basic_point;
    QPen pen_basic_point;
    QPen pen_basic_line;
    QBrush brush_iner_point;
    QPen pen_iner_point;
    QPen pen_iner_line;

    bool newestTween;//whether the tween is the newest

    QTimer *timer_ch;
    QTimer *timer_mov;
    QTimer *timer_remov_character;

    int ch_flame;
    qreal mov_flame;
    double velocity;
    int vol_type;


    void calculate();
    void calculate_stand();
    void show_tween();
    void show_tween_point();

    int dense;
    QTime time;
    int time_record;




public:
    MainScene();
    ~MainScene();
    friend class MainWindow;
    void addPoint(int x,int y);
    void clearScene();

    void addTween();


    void startAnimation();

public slots:
    void next_ch_flame();
    void next_mov_flame();
    void remove_character();

};


#endif // MAINSCENE_H


