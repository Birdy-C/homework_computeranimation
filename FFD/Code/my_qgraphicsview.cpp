#include "my_qgraphicsview.h"

my_QGraphicsView::my_QGraphicsView(QWidget *parent):QGraphicsView(parent),pressed(false)
{

}


void my_QGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {      
       pressed = true;
       starttemp(event->x(),event->y());
       qDebug("mouse is pressed");
    }
}

void my_QGraphicsView::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button() == Qt::LeftButton)
    {
        pressed = false;
        finishtemp();
        qDebug("mouse is released");
    }
}


void my_QGraphicsView::mouseMoveEvent(QMouseEvent*event)
{
    if(pressed == true)
    {
        addPoint(event->x(),event->y());
        qDebug("my_QGraphicsView::get a point:(%d,%d)",event->x(),event->y());
    }
}



void my_QGraphicsView::resizeEvent(QResizeEvent * event)
{
        resizeShape(event->size().width(),event->size().height());
}



