//Birdy 17.10.10
#include "points.h"

Points::Points():count(1)
{

}


bool Points::addPoint(const int t_x,const int t_y)
{
    if(102 == count)
    {
        QMessageBox::warning(0,QObject::tr("Sorry"),"Can't put in more than 100 points");
        return false;
    }
    pointX[count] = t_x;
    pointY[count] = t_y;
    count++;
    return true;
}


void Points::clear()
{
    count = 1;
}


void Points::lastPoint(int &x,int &y)
{
    if(0==count)
    {
        x = -1;
        y = -1;
        return;
    }

    x = pointX[count-1];
    y = pointY[count-1];
}


void Points::getPoint(int index,int &x,int &y)
{
    x = pointX[index];
    y = pointY[index];
}


void Points::calculateInit(double tension)
{
    double v;
    v = (2 * pointX[2] - pointX[1] - pointX[3])/2;
    pointX[0] = pointX[2] - v / tension ;

    v = (2 * pointX[count-2] - pointX[count-1] - pointX[count-3])/2;
    pointX[count] = pointX[count-2] - v / tension ;

    v = (2 * pointY[2] - pointY[1] - pointY[3])/2;
    pointY[0] = pointY[2] - v / tension ;

    v = (2 * pointY[count-2] - pointY[count-1] - pointY[count-3])/2;
    pointY[count] = pointY[count-2] - v / tension ;


}
