#include "my_qgraphicsview.h"

my_QGraphicsView::my_QGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}


void my_QGraphicsView::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        qDebug("my_QGraphicsView::get a point:(%d,%d)",event->x(),event->y());
        addPoint(event->x(),event->y());
    }
}


void my_QGraphicsView::resizeEvent(QResizeEvent * event)
{
        resizeShape(event->size().width(),event->size().height());
}

