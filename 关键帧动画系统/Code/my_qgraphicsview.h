#ifndef MY_QGRAPHICSVIEW_H
#define MY_QGRAPHICSVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <qgraphicsview.h>

class my_QGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit my_QGraphicsView(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent * event);

signals:
    void addPoint(int x,int y);
    void resizeShape(qreal w,qreal h);

public slots:

};

#endif // MY_QGRAPHICSVIEW_H
