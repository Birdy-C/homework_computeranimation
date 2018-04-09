//Birdy 17.10.10
#define PI 3.141592
#include "mainscene.h"


MainScene::MainScene():drawType(false),tweenType(false)
{
    count[0]=0;
    count[1]=0;

    group_line = new QGraphicsLineItem;
    group_tween = new QGraphicsLineItem;
    Scene.addItem(group_line);
    Scene.addItem(group_tween);
    pen[0].setColor(QColor(180,180,255,255));
    pen[1].setColor(QColor(180,180,255,255));
    pen[2].setColor(QColor(180,180,255,255));
    pen[0].setWidth(2);

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(next_flame()));
    timer->stop();

    QPixmap pixmap1("E:/Code/animation_pro3/com_animation_experiment3/pic/10.png");
    backpicture = new QGraphicsPixmapItem(pixmap1);


}

MainScene::~MainScene()
{
    delete group_line;
    delete group_tween;

}


bool MainScene::addPoint(const int t_x,const int t_y)
{

    int count_temp = count[drawType];
    if(102 == count_temp)
    {
        QMessageBox::warning(0,QObject::tr("Sorry"),"Can't put in more than 100 points");
        return false;
    }
    pointX[drawType][count_temp] = t_x;
    pointY[drawType][count_temp] = t_y;
    count[drawType]++;

    QGraphicsEllipseItem *pointTemp = new QGraphicsEllipseItem(t_x-5,t_y-5,10,10,group_line);
    pointTemp->setPen(pen[0]);

    if(count[drawType] == 1)
        return true;

    QGraphicsLineItem *lineTemp = new QGraphicsLineItem(pointX[drawType][count_temp-1],pointY[drawType][count_temp-1],
            pointX[drawType][count_temp],pointY[drawType][count_temp],group_line);
    lineTemp->setPen(pen[0]);


    return true;
}


void MainScene::clear()
{
    count[0] = count[1] = 0;

    {
        QList<QGraphicsItem *> list_line = group_line->childItems();
        for ( int i=0; i!=list_line.size(); i++ )
        {
            Scene.removeItem(list_line.at(i));
        }
    }
    {
        QList<QGraphicsItem *> list_line = group_tween->childItems();
        for ( int i=0; i!=list_line.size(); i++ )
        {
            Scene.removeItem(list_line.at(i));
        }
    }
    timer->stop();
}


double MainScene::calculate_theta_single(const int deltax,const int deltay)
{
    double angle;
    double length =sqrt(deltax*deltax+deltay*deltay);
    angle = asin(deltay/length);
    if(deltax<0)
        angle = (PI-angle);

    return angle;
}


void MainScene::calculate()
{

    if(tweenType==false)
    {
        for(int i =0;i<64;i++)
        {
            for(int j=0;j<count[0];j++)
            {
                pointTweenX[i][j] = 1./64*i*pointX[1][j]+1./64*(64-i)*pointX[0][j];
                pointTweenY[i][j] = 1./64*i*pointY[1][j]+1./64*(64-i)*pointY[0][j];

            }
        }
    }
    else
    {
        for(int j=0;j<count[0];j++)
        {
            if(0==j)
            {
                for(int i =0;i<64;i++)
                {

                    pointTweenX[i][j] = 1./64*i*pointX[1][j]+1./64*(64-i)*pointX[0][j];
                    pointTweenY[i][j] = 1./64*i*pointY[1][j]+1./64*(64-i)*pointY[0][j];
                }
                continue;
            }

            double theta1 = calculate_theta_single(pointX[0][j]-pointX[0][j-1],pointY[0][j]-pointY[0][j-1]);
            double theta2 = calculate_theta_single(pointX[1][j]-pointX[1][j-1],pointY[1][j]-pointY[1][j-1]);
            double length1 = qSqrt(qPow(pointX[0][j]-pointX[0][j-1],2)+qPow(pointY[0][j]-pointY[0][j-1],2));
            double length2 = qSqrt(qPow(pointX[1][j]-pointX[1][j-1],2)+qPow(pointY[1][j]-pointY[1][j-1],2));

            if(theta1>theta2)
            {
                while(theta1-theta2>PI)
                    theta1 -= PI*2;
            }
            else
            {
                while(theta2-theta1>PI)
                    theta2 -= PI*2;
            }
            for(int i =0;i<64;i++)
            {

                double theta =  1./64*i*theta2 + 1./64*(64-i)*theta1;
                double length = 1./64*i*length2 + 1./64*(64-i)*length1;
                pointTweenX[i][j] = pointTweenX[i][j-1]+ length * qCos(theta);
                pointTweenY[i][j] = pointTweenY[i][j-1]+ length * qSin(theta);
            }
        }
    }



}


void MainScene::play()
{
    if(count[0]!=count[1])
    {
        QMessageBox::warning(0,QObject::tr("Sorry"),"Please enter same number of points");
        return;
    }
    calculate();
    TweenIndex = 0;
    timer->start(100);

}

void MainScene::next_flame()
{
    {
        QList<QGraphicsItem *> list_line = group_tween->childItems();
        for ( int i=0; i!=list_line.size(); i++ )
        {
            Scene.removeItem(list_line.at(i));
        }
    }
    if(TweenIndex==64)
        return;

    for(int i = 0; i< count[0];i++)
    {
        QGraphicsEllipseItem *pointTemp = new QGraphicsEllipseItem(pointTweenX[TweenIndex][i]-5,pointTweenY[TweenIndex][i]-5,10,10,group_tween);
        pointTemp->setPen(pen[2]);

        if(i == 0)
            continue;

        QGraphicsLineItem *lineTemp = new QGraphicsLineItem(pointTweenX[TweenIndex][i-1],pointTweenY[TweenIndex][i-1],
                pointTweenX[TweenIndex][i],pointTweenY[TweenIndex][i],group_tween);
        lineTemp->setPen(pen[2]);
    }

    TweenIndex++;

}


