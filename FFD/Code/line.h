
#ifndef LINE_H
#define LINE_H
#include "info.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QPixmap>

class Line
{
    friend class MainScene;

    int pointX;
    int pointY;

    QPen pen_point;
    QColor color1;

    QGraphicsEllipseItem *pointObj1;
    QGraphicsScene *scene;

    void setObj();

public:
    //calculate
    void setpos(int x,int y);//index 0/1
    int getcollection(int x,int y);
    Line(int x1, int y1, QGraphicsScene *myscene);
    ~Line();

};

#endif // LINE_H
