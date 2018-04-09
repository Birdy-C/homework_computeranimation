#ifndef LINE_H
#define LINE_H

#include <QDebug>
#include <QtMath>
class Line
{
    friend class MainScene;

    //For calcuate the Tween

    //Cardinal

    double Matrix[16];
    bool newestMatrix;//  True/False whether the scene has been changed


    //record the between
    int tweenX[10000];
    int tweenY[10000];
    qreal tweenTheta[10000];
    double length[100];   //the length of subline
    int count;

    int calculate_theta_single(int,int);
    void Matrix_line_init(double *p,const int *x);
    int get_pos(double *p,double u) const;
    double get_length(double *p,double u) const;

public:
    //calculate
    void initMatrix();

    void caluculateTween(const int x[], const int y[]);
    double calculateLength(const int x[], const int y[]);
    void caluculateTween_stand(const int x[], const int y[],double step);

    void addLastPoint(int x,int y);
    void changeGrain(int t);
    void changeTesion(double t);
    void clear();

    void calculate_theta();
    int grain;
    double tension;
    int cal_type;
    bool Type;// 0 normal \ 1 standardize
    int standard_type;



    Line();

};

#endif // LINE_H
