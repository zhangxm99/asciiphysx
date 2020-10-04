#include "physicalquantity.h"
#include <math.h>
#include <stdio.h>
#define delt_t 0.01
#define Gvalue 6.67e-11

double Force(double M,double m,double r_sqr){
    return Gvalue*M*m/(r_sqr);
}

void CalculateAcceleration(position* p,double* mass,acceleration* a,int Numbers){
    double ai_x = 0;
    double ai_y = 0;
    for(int i = 0;i < Numbers;i++){
        double m1 = mass[i];
        for(int j = 0;j < Numbers;j++){
            if(j != i){
                double m_other = mass[j];
                double i_x = p[j].x - p[i].x;
                double i_y = p[j].y - p[i].y;
                double distance = sqrt(i_x*i_x + i_y*i_y);
                double sinx = i_y / distance;
                double cosx = i_x / distance;
                double F = Force(m1,m_other,distance*distance);    //Force formula
                ai_x += F*cosx/m1;
                ai_y += F*sinx/m1;
            }
        }
        a[i].ax = ai_x;
        a[i].ay = ai_y;
        ai_x = 0;
        ai_y = 0;
    }
}
void CalculateVelocity(velocity* v,acceleration* a){
    v->vx += a->ax * delt_t;
    v->vy += a->ay * delt_t;
}
void CalculatePosition(position* p,velocity* v){
    p->x += v->vx * delt_t;
    p->y += v->vy * delt_t;
}
