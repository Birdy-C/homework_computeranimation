//Birdy 17.10.10

#include "line.h"
#include <QtMath>
Line::Line():grain(16),tension(0.5),count(0),cal_type(0),standard_type(0)
{


}

//calculate
void Line::initMatrix()
{
    //if(newestMatrix)
    //    return;
    double *m = Matrix;
    double a1 = tension;
    switch (cal_type)
    {
    case 0:
        m[0]=-a1;   m[1]=2.-a1;  m[2]=a1-2.;   m[3]=a1;
        m[4]=2.*a1; m[5]=a1-3.;  m[6]=3.-2*a1; m[7]=-a1;
        m[8]=-a1;   m[9]=0.;     m[10]=a1;     m[11]=0.;
        m[12]=0.;   m[13]=1.;    m[14]=0.;     m[15]=0.;
    break;
    case 1:
    case 4:
        a1=0.5;
        m[0]=-a1;   m[1]=2.-a1;  m[2]=a1-2.;   m[3]=a1;
        m[4]=2.*a1; m[5]=a1-3.;  m[6]=3.-2*a1; m[7]=-a1;
        m[8]=-a1;   m[9]=0.;     m[10]=a1;     m[11]=0.;
        m[12]=0.;   m[13]=1.;    m[14]=0.;     m[15]=0.;
        break;

    case 2:
        m[0]=-1./6;  m[1]=0.5;   m[2]=-0.5;  m[3]=1./6;
        m[4]=0.5;   m[5]=-1;    m[6]=0.5;   m[7]=0;
        m[8]=-0.5;   m[9]=0;   m[10]=0.5;   m[11]=0;
        m[12]=1./6;   m[13]=4./6; m[14]=1./6;   m[15]=0;
        break;

    case 3:
        m[0]=-1;    m[1]=3;   m[2]=-3;  m[3]=1;
        m[4]=3;     m[5]=-6;  m[6]=3;   m[7]=0;
        m[8]=-3;    m[9]=3;   m[10]=0;   m[11]=0;
        m[12]=1;    m[13]=0; m[14]=0;   m[15]=0;
        break;
    }
    //newestMatrix = true;
}


void Line::clear()
{
    count = 0;
}


void Line::caluculateTween(const int *x,const int *y)
{
    if(!newestMatrix)
        initMatrix();
    double px[4],py[4];
    Matrix_line_init(&px[0], &x[0]);
    Matrix_line_init(&py[0], &y[0]);


    if(!Type)       //不经过标准化
    {
        double step = 1/(double)grain;
        double step_record = 0;

        for(int i = 0; i < grain ; i++)
        {
            tweenX[count+i] = get_pos(px,step_record);
            tweenY[count+i] = get_pos(py,step_record);
            qDebug("point:%d,%d",tweenX[count+i],tweenY[count+i]);
            step_record += step;
        }
        count = count + grain;

    }
    else
    {


    }

}


void Line::caluculateTween_stand(const int *x,const int *y,double record)
{
    initMatrix();
    double px[4],py[4];
    Matrix_line_init(&px[0], &x[0]);
    Matrix_line_init(&py[0], &y[0]);

    double step = 1/(double)grain/16;
    double step_record = 0;
    double tx,ty;
    double sum = 0;
    for(int i = 0; i < grain*16 ; i++)
    {
        tx = get_length(px,step_record);
        ty = get_length(py,step_record);

            double temp = sqrt(tx*tx+ty*ty);
            sum += temp;
            step_record += step;

            if(sum>record/step)
            {
                tweenX[count] = get_pos(px,step_record);
                tweenY[count++] = get_pos(py,step_record);
                sum = sum-record/step;
            }
    }
}



double Line::calculateLength(const int *x,const int *y)
{
    initMatrix();
    double px[4],py[4];
    Matrix_line_init(&px[0], &x[0]);
    Matrix_line_init(&py[0], &y[0]);
    double step = 1./(double)grain;
    double step_record = 0;
    double tx,ty;
    double sum = 0;
    for(int i = 0; i < grain ; i++)
    {
        tx = get_length(px,step_record);
        ty = get_length(py,step_record);

        double temp = sqrt(tx*tx+ty*ty);
            if(i ==0 || temp == grain)
            {
                 sum += temp;
            }
            else if(i%2)
            {
                sum += temp*2;
            }
            else
            {
                sum += temp*4;
            }

            step_record += step;
    }
    sum = sum*step/3;
    return sum;


}




void Line::Matrix_line_init(double *p,const int *x)
{
        p[0]=Matrix[0]*x[0] + Matrix[1]*x[1] + Matrix[2]*x[2] + Matrix[3]*x[3];
        p[1]=Matrix[4]*x[0] + Matrix[5]*x[1] + Matrix[6]*x[2] + Matrix[7]*x[3];
        p[2]=Matrix[8]*x[0] + Matrix[9]*x[1] + Matrix[10]*x[2] + Matrix[11]*x[3];
        p[3]=Matrix[12]*x[0] + Matrix[13]*x[1] + Matrix[14]*x[2] + Matrix[15]*x[3];

 }


int Line::get_pos(double *p,double u) const
{
    return p[3]+u*(p[2]+u*(p[1]+u*p[0]));
}

double Line::get_length(double *p,double u) const
{
    return p[2]+u*(2.*p[1]+3.*u*p[0]);
}


void Line::addLastPoint(int x,int y)
{
    tweenX[count] = x;
    tweenY[count] = y;
    count++;
}


// ================================================

int Line::calculate_theta_single(const int deltax,const int deltay)
{
    double angle;
    double length =sqrt(deltax*deltax+deltay*deltay);
    angle = asin(deltay/length);
    if(deltax<0)
        angle = 3.1415926-angle;

    return angle/3.1415926*180;
}


void Line::calculate_theta()
{
    if(count < 3)
        return;

    for(int i = 0 ; i < count ; i++)
    {
        tweenTheta[i] = calculate_theta_single(tweenX[i+1]-tweenX[i],tweenY[i+1]-tweenY[i]);
    }
    tweenTheta[count] = tweenTheta[count-1];
}


// ==================slot==========================
void Line::changeGrain(int t)
{
    grain = t;
    newestMatrix = false;
}


void Line::changeTesion(double t)
{
    tension = t;
    newestMatrix = false;
}
