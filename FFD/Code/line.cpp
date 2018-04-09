//Birdy 17.11.23

#include "line.h"
#include <QSoundEffect>
Line::Line(int x1, int y1, QGraphicsScene *myscene):
    color1(255,249,110,200)
{
    scene = myscene;
    pointX = x1;
    pointY = y1;

    pen_point.setColor(color1);
    pen_point.setWidth(10);
    setObj();

    scene->addItem(pointObj1);

}


Line::~Line()
{
    delete pointObj1;
}


void Line::setObj()
{

    pointObj1=new QGraphicsEllipseItem
            (pointX-20,pointY-20,40,40);
    pointObj1->setPen(pen_point);

}



void Line::setpos(int x,int y)//index 0
{
    pointX = x,pointY = y;

    delete pointObj1;
    this->setObj();

    pointObj1->setPen(pen_point);
    pointObj1->setZValue(-1);
    scene->addItem(pointObj1);
}


int Line::getcollection(int x,int y)
{
    if(x>pointX-20&&x<pointX+20&&y>pointY-20&&y<pointY+20)
        return 0;

    return -1;
}

