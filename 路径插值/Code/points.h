#ifndef POINTS_H
#define POINTS_H

#include <QMessageBox>
#include <QDebug>



class Points
{
    friend class MainScene;
private:
    //以下从1开始存放，前后预留一位，在生成时候补齐
    int pointX[102];
    int pointY[102];
    int count;//the number of points on the scene

public:   
    Points();
    void calculateInit(double tension);//更新第一个和最后一个点
    bool addPoint(const int x, const int y);
    void changeGrain(int t);
    void changeTension(double t);
    void clear();
    void lastPoint(int &x,int &y);
    void getPoint(int index,int &x,int &y);
    int ret_count(){return count;}


};


#endif // POINTS_H
