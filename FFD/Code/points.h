//这个主要的画的
#ifndef POINTS_H
#define POINTS_H

#include "info.h"
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsItemGroup>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QPixmap>

class Points
{
    friend class MainScene;
private:
    int pointX[5000];
    int pointY[5000];
    int pointX_aft[5000];
    int pointY_aft[5000];
    int count;//the number of points on the scene


    QPen pen;
    QGraphicsEllipseItem *group_line;
    QGraphicsScene *scene;

public:   
    Points(QGraphicsScene *scene);
    ~Points();
    bool addPoint(const int x, const int y);
    bool finish();
    void draw();

};


#endif // POINTS_H
