#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "plot.h"

int main(void){
    //Initial status data collect
    int Numbers;
    printf("How much objects: ");
    scanf("%d",&Numbers);

    double mass[Numbers];
    position p[Numbers];
    velocity v[Numbers];
    acceleration a[Numbers];

    printf("Input this %d objects' initial status data\n",Numbers);
    puts("The Coordinate System are as follow");
    puts("     ↑ y    \n"
         "     |     \n"
         "-----|-----> x\n"
         "     |    ");
    puts("Input format is: \033[1mMASS\033[m,(\033[1mposition_x\033[m,\033[1mposition_y\033[m),(\033[1mvelocity_x\033[m,\033[1mvelocity_y\033[m)");

    for(int i = 0;i < Numbers;i++){
        int status = scanf("%lf,(%lf,%lf),(%lf,%lf)",&mass[i],&p[i].x,&p[i].y,&v[i].vx,&v[i].vy);
        if(status == 5) continue;
        else{
            puts("\033[1;30mSomething is wrong in your last input, please check and re-input\033[m");
            i--;
            while(getchar() != '\n') continue;
        }
    }

    coordinatechange(p,v,Numbers);  //change coordination


    //Start calculate
    int count = 0;
    while(1){
        CalculateAcceleration(p,mass,a,Numbers);

        for(int i = 0;i < Numbers;i++){
            CalculateVelocity(&v[i],&a[i]);
            CalculatePosition(&p[i],&v[i]);
        }
        float time = ++count*delt_t;
        printf("time: %fs\n",time);
        plot(p,Numbers);

        // for(int i = 0;i < Numbers;i++){
        //     printf("(%f,%f) ",p[i].x,p[i].y);
        // }
        // puts("");
        usleep(1000);
    }
}