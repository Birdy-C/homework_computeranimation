//Birdy 17.10.10
#include "mainscene.h"


MainScene::MainScene()
    :newestTween(true),ch_flame(0),mov_flame(0),char_index(true),char_index_before(true),
      dense(2),velocity(1),vol_type(0)

{
    group_basic = new QGraphicsLineItem;
    group_line = new QGraphicsLineItem;
    group_character = new QGraphicsLineItem;
    group_inner_point = new QGraphicsLineItem;

    timer_ch = new QTimer;
    timer_mov = new QTimer;
    timer_remov_character = new QTimer;



//==========================

    QColor color1(255,255,0,150);
    QColor color2(180,180,255,255);
    QColor color3(150,160,255,250);

    pen_basic_point.setColor(color1);
    pen_basic_point.setWidth(2);

    pen_basic_line.setColor(color1);
    pen_basic_line.setWidth(5);
    pen_basic_line.setStyle(Qt::DotLine);

    pen_iner_line.setColor(color2);
    pen_iner_line.setWidth(10);
    pen_iner_line.setCapStyle(Qt::RoundCap);

    pen_iner_point.setColor(color3);
    pen_iner_point.setWidth(2);


//====================

    QPixmap pixmap1("E:/Code/com_animation_experiment1/pic/10.png");
    backpicture = new QGraphicsPixmapItem(pixmap1);

    for(int i=0;i<8;i++)
    {
        QString path = "E:/Code/com_animation_experiment1/pic/ch";
        path +=('0'+i+1);
        path += ".png";
        QPixmap pixmap(path);
        character[i][0] = new QGraphicsPixmapItem(pixmap,group_character);

        QString path2 = "E:/Code/com_animation_experiment1/pic/ch1";
        path2 +=('0'+i+1);
        path2 += ".png";
        QPixmap pixmap2(path2);
        character[i][1] = new QGraphicsPixmapItem(pixmap2,group_character);


        character[i][0]->setPos(-220,-110);
        character[i][0]->setVisible(false);

        character[i][1]->setPos(-170,-110);
        character[i][1]->setVisible(false);

    }
    group_character->setScale(0.5);
    group_character->setVisible(false);

    Scene.addItem(backpicture);
   // Scene.addItem(group_basic);
    Scene.addItem(group_line);
    Scene.addItem(group_inner_point);
    Scene.addItem(group_basic);
    Scene.addItem(group_character);

    connect(timer_ch,SIGNAL(timeout()),this,SLOT(next_ch_flame()));
    connect(timer_mov,SIGNAL(timeout()),this,SLOT(next_mov_flame()));
    connect(timer_remov_character,SIGNAL(timeout()),this,SLOT(remove_character()));

}


MainScene::~MainScene()
{
    delete group_basic;
    delete group_line;
    delete group_character;


}



void MainScene::addPoint(int x,int y)
{


    //update class points
    int lastX,lastY;
    points.lastPoint(lastX,lastY);
    bool check = points.addPoint(x,y);
    if(!check)
    {
        return;
    }

    newestTween = false;

    QGraphicsEllipseItem *pointTemp = new QGraphicsEllipseItem(x-5,y-5,10,10,group_basic);

    pointTemp->setPen(pen_basic_point);
    pointTemp->setBrush(brush_basic_point);
    if(points.count == 2)
        return;
    QGraphicsLineItem *lineTemp = new QGraphicsLineItem(x,y,lastX,lastY,group_basic);
    lineTemp->setPen(pen_basic_line);

}




void MainScene::addTween()
{
    //因为想把计算的过程计时，所以角度的计算和位置的计算独立开来
    //还有就是这一步角度不直接影响显示所以扔后面单独计算
    line.clear();

    time.restart();
    if(line.Type==0)
        calculate();
    else
        calculate_stand();
    time_record = time.elapsed();

    show_tween();
    line.calculate_theta();
}




void MainScene::calculate()
{
    if(points.count < 3)
        return;

    if(line.cal_type==0||line.cal_type==1)
    {
        if(line.cal_type==0)
        {
            points.calculateInit(line.tension);
        }
        else
        {
            points.calculateInit(0.5);
        }
    for (int i=0;i <= points.ret_count()-3;i++)
    {
        line.caluculateTween(&points.pointX[i],&points.pointY[i]);
    }
    int lastX,lastY;
    points.lastPoint(lastX,lastY);
    line.addLastPoint(lastX,lastY);
    }

    if(line.cal_type==2)
    {
        for (int i=1;i <= points.ret_count()-4;i++)
        {
            line.caluculateTween(&points.pointX[i],&points.pointY[i]);
        }
        //line.addLastPoint(lastX,lastY);
    }

    if(line.cal_type==3)
    {
        for (int i=1;i <= points.ret_count()-4;i=i+3)
        {
            line.caluculateTween(&points.pointX[i],&points.pointY[i]);
        }
        int lastX,lastY;
        points.lastPoint(lastX,lastY);
        line.addLastPoint(lastX,lastY);
    }


}


void MainScene::calculate_stand()
{

    if(line.standard_type==0)
    {
        points.calculateInit(0.5);

        double sum = 0;

        for (int i=0;i <= points.ret_count()-3;i++)
        {
            sum += line.calculateLength(&points.pointX[i],&points.pointY[i]);
        }

        double step = sum/(points.ret_count()-3)/line.grain;


        line.addLastPoint(points.pointX[1],points.pointY[1]);

        for (int i=0;i <= points.ret_count()-3;i++)
        {
            line.caluculateTween_stand(&points.pointX[i],&points.pointY[i],step);
        }

        int lastX,lastY;
        points.lastPoint(lastX,lastY);
        line.addLastPoint(lastX,lastY);

    }

    if(line.standard_type==2)
    {
        double sum = 0;

        for (int i=0;i <= points.ret_count()-3;i++)
        {
            sum += line.calculateLength(&points.pointX[i],&points.pointY[i]);
        }

        double step = sum/(points.ret_count()-3)/line.grain;

        for (int i=0;i <= points.ret_count()-3;i++)
        {
           // line.caluculateTween_stand(&points.pointX[i],&points.pointY[i],step*4,4);
        }

    }

}


void MainScene::show_tween()
{
    QList<QGraphicsItem *>list_line = group_line->childItems();
    for ( int i=0; i!=list_line.size(); i++ )
    {
        Scene.removeItem(list_line.at(i));
    }


    for (int i=0; i < line.count-1;i++)
    {
         QGraphicsLineItem *temp_line = new QGraphicsLineItem(line.tweenX[i],line.tweenY[i],
                              line.tweenX[i+1],line.tweenY[i+1],group_line);
         QGraphicsLineItem *temp_line1 = new QGraphicsLineItem(line.tweenX[i],line.tweenY[i],
                                                              line.tweenX[i+1],line.tweenY[i+1],group_line);
         temp_line->setPen(pen_iner_line);
         temp_line1->setPen(pen_iner_point);

    }
    show_tween_point();
}




void MainScene::show_tween_point()
{

    QList<QGraphicsItem *>list_inner_point = group_inner_point->childItems();
    for ( int i=0; i!=list_inner_point.size(); i++ )
    {
        Scene.removeItem(list_inner_point.at(i));
    }


    int grain = line.grain;
    int step = grain/dense;
    for(int j=0;j<line.count;j=j+step)
    {
        QGraphicsEllipseItem *pointTemp =
                    new QGraphicsEllipseItem(line.tweenX[j]-5,line.tweenY[j]-5,10,10,group_inner_point);
            pointTemp->setPen(pen_iner_point);
    }


}




void MainScene::clearScene()
{

     points.clear();
     line.clear();

     QList<QGraphicsItem *>list_basic = group_basic->childItems();
     QList<QGraphicsItem *>list_line = group_line->childItems();
     QList<QGraphicsItem *>list_inner_point = group_inner_point->childItems();

     for ( int i=0; i!=list_basic.size(); i++ )
     {
         Scene.removeItem(list_basic.at(i));
     }

     for ( int i=0; i!=list_line.size(); i++ )
     {
         Scene.removeItem(list_line.at(i));
     }

     for ( int i=0; i!=list_inner_point.size(); i++ )
     {
         Scene.removeItem(list_inner_point.at(i));
     }


}



//============animation============

void MainScene::startAnimation()
{
    if(line.count == 0)
        return;

    mov_flame = 0;
    timer_ch->start (1);
    timer_mov->start (0);

    group_character->setVisible(true);

}



void MainScene::next_ch_flame()
{
    int flame_before = (ch_flame+7)%8;
    timer_ch->start(105);
    character[flame_before][0]->setVisible(false);
    character[flame_before][1]->setVisible(false);

    character[ch_flame][char_index]->setVisible(true);

    ch_flame++;
    if(8==ch_flame)
        ch_flame = 0;



}



void MainScene::next_mov_flame()
{
    switch(vol_type)
    {
    case 0:
         mov_flame += velocity;
        break;
    case 1:

        mov_flame += velocity*sin(mov_flame/line.count*3.1415926/2)+0.3;
        break;
    case 2:
        mov_flame += velocity*cos(mov_flame/line.count*3.1415926/2)+0.3;
        break;
    }


    int flame(mov_flame);


    if(line.count < mov_flame+1)
    {
        timer_remov_character->start (2000);
        timer_mov->stop();

    }
    else
    {
        timer_mov->start (100);
        double theta = line.tweenTheta[flame];
        group_character->setPos(line.tweenX[flame],line.tweenY[flame]);

       if(theta == 90 || theta == -90)
        {
           if(1==mov_flame)
           {
               group_character->setRotation(theta+180);
               if(theta==90)
               {
                    char_index= true;
               }
               else
               {
                    char_index= false;
               }
           }

        }

       else if( theta>90 || theta<-90 )
        {
            if( char_index_before== true)
            {

                if(true == char_index){}
                else
                {
                    char_index= true;
                    character[ch_flame][0]->setVisible(false);
                    group_character->setRotation(theta+180);
                    character[ch_flame][1]->setVisible(true);
                }
                group_character->setRotation(theta+180);
            }
            else
                char_index_before = true;


        }
        else
        {
            if( char_index_before== false)
            {
                if(false == char_index){}
                else
                {
                    char_index= false;
                    character[ch_flame][1]->setVisible(false);
                    group_character->setRotation(theta);
                    character[ch_flame][0]->setVisible(true);
                }
                group_character->setRotation(theta);
            }
            else
                char_index_before = false;


        }

    }

    next_ch_flame();
}



void MainScene::remove_character()
{

    int flame_before = (ch_flame+7)%8;
    timer_ch->stop();
    timer_remov_character->stop();
    character[flame_before][0]->setVisible(false);
    character[flame_before][1]->setVisible(false);

}
