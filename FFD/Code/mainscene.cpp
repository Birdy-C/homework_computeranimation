//Birdy 17.10.27
#include "mainscene.h"


MainScene::MainScene():active_num(-1),point_count(0)
{

    QPixmap pixmap1("E:/Code/animation_pro2/pic/10.png");
    backpicture = new QGraphicsPixmapItem(pixmap1);

    Scene.addItem(backpicture);
    PenBackline.setStyle(Qt::DotLine);
    PenBackline.setColor(QColor(50,50,50));

    group_line = new QGraphicsLineItem;
    Scene.addItem(group_line);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            line[i*3+j]= new class Line(300*i+100,300*j+100,&Scene);
    }
    for(int i=0;i<50;i++)
     {
        points[i]= new class Points(&Scene);

    }

    drawScene();

}


MainScene::~MainScene()
{
    delete backpicture;
    for(int i=0;i<9;i++)
    {
        delete line[i];
    }
}



void MainScene::addPoint(int x,int y)
{
    if(active_num == -1)
    {
        points[point_count]->addPoint(x,y);
        return;
    }
    else
    {
        line[active_num]->setpos(x,y);
        drawScene();
    }
}


void MainScene::finish()
{
    if(active_num == -1){
        if(points[point_count]->finish())
        {
            point_count++;
        }
    }
}


void MainScene::start(int x,int y)
{
    for(int i=0;i<9;i++)
     {
        int temp = line[i]->getcollection(x,y);
        if(temp == 0)
        {
            active_num = i;
            return;
        }

    }
    active_num = -1;
}



void MainScene::drawScene()
{
    calculate();
    clearScene();
    for(int m=0;m<10;m++)
    {    for (int i=0; i < 64;i++)
        {
            QGraphicsLineItem *temp_line = new QGraphicsLineItem(pointX[m][i],pointY[m][i],pointX[m][i+1],pointY[m][i+1],group_line);
            temp_line->setPen(PenBackline);

        }
    }
    for(int i=0;i<point_count;i++)
    {
        for(int j = 0; j< points[i]->count;j++)
        {
            double s = 1.*(points[i]->pointX[j]-100)/600;
            double t = 1.*(points[i]->pointY[j]-100)/600;
            double x = 0;
            double y = 0;
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                {
                    double Ber =Bernstein(j,s)* Bernstein(k,t);
                    x += Ber*line[j*3+k]->pointX;
                    y += Ber*line[j*3+k]->pointY;
                }
            points[i]->pointX_aft[j]=x;
            points[i]->pointY_aft[j]=y;
        }
         points[i]->draw();
    }

}


double MainScene::Bernstein(int t, double m )
{
    if( t<0 || t>2)
    {
        qDebug("MainScene::Bernstein::error input t");
        return 0;
    }
    if(t==0)
    {
        return (1-m)*(1-m);
    }
    if(t==1)
    {
        return 2*m*(1-m);
    }
    if(t==2)
    {
        return m*m;
    }
    qDebug("MainScene::Bernstein::error input t");
    return 0;

}

void MainScene::calculate()
{
    for(int m = 0; m < 5 ; m++)
    {
        for(int i=0;i<65;i++)
        {
            double s = 0.25*m;
            double t = 0./4 + 1./64*i;
            double x = 0;
            double y = 0;
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                {
                    double Ber =Bernstein(j,s)* Bernstein(k,t);
                    x += Ber*line[j*3+k]->pointX;
                    y += Ber*line[j*3+k]->pointY;
                }
            pointX[m][0+i]=x;
            pointY[m][0+i]=y;
        }
    }
    for(int m = 0; m < 5 ; m++)
    {
        for(int i=0;i<65;i++)
        {
            double s =0./4 + 1./64*i;
            double t = 0.25 * m ;
            double x = 0;
            double y = 0;
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                {
                    double Ber =Bernstein(j,s)* Bernstein(k,t);
                    x += Ber*line[j*3+k]->pointX;
                    y += Ber*line[j*3+k]->pointY;
                }
            pointX[m+5][0+i]=x;
            pointY[m+5][0+i]=y;
        }
    }
}


void MainScene::clearScene()
{

    QList<QGraphicsItem *>list_line = group_line->childItems();
    for ( int i=0; i!=list_line.size(); i++ )
    {
        Scene.removeItem(list_line.at(i));
    }


}
