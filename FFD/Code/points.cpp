//Birdy 17.10.10
#include "points.h"

Points::Points(QGraphicsScene *mscene):count(0)
{
    scene = mscene;
    group_line = new QGraphicsEllipseItem;
    scene->addItem(group_line);



    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(QColor(180,180,255,200));

}

Points::~Points()
{
    delete group_line;
}


bool Points::addPoint(const int t_x,const int t_y)
{
    if(5000 == count)
    {
        QMessageBox::warning(0,QObject::tr("Sorry"),"Can't put in more than 100 points");
        return false;
    }

    if(count > 0)
    {
       QGraphicsLineItem *temp =  new QGraphicsLineItem(t_x,t_y,pointX[count-1],pointY[count-1],group_line);
       temp->setPen(pen);
    }
    pointX[count] = t_x;
    pointY[count] = t_y;

    pointX_aft[count] = t_x;
    pointY_aft[count] = t_y;
    count++;
    return true;

}



bool Points::finish()
{
    if(count == 1 )
    {
        count = 0;
        return false;
    }

}


void Points::draw()
{

     QList<QGraphicsItem *>list_line = group_line->childItems();
     for ( int i=0; i!=list_line.size(); i++ )
     {
         scene->removeItem(list_line.at(i));
     }

     for(int i=0; i<count-1; i++)
     {
          QGraphicsLineItem *temp = new QGraphicsLineItem(pointX_aft[i],pointY_aft[i],pointX_aft[i+1],pointY_aft[i+1],group_line);
          temp->setPen(pen);
     }
}


