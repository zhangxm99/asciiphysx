#include <stdio.h>
#include <stdlib.h>
#include "iterationcalculation.h"
#define half_length 30 //half screen length
#define half_height 15  //half screen height

int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b; 
}

void coordinatechange(position* p,velocity* v,int Numbers){
    for(int i = 0;i < Numbers;i++){
        p[i].x = p[i].x + half_length - 1;
        p[i].y = half_height - p[i].y - 1;

        v[i].vy = -v[i].vy;
    }
}

void plot(position* p,int Numbers){
    int tmp[Numbers];
    for(int i = 0;i < Numbers;i++){
        if((int)p[i].x < 2*half_length&&(int)p[i].x > 0)
            tmp[i] = (int)(p[i].y)*half_length*2 + (int)(p[i].x);
        else
            tmp[i] = half_length*half_height*4;  //don not appear 
    }
    qsort(tmp,Numbers,sizeof(int),cmp);

    int count = 0;
    while(tmp[count] <= 0) count++;   //start from non-negtive position
    for(int i = 0;i < half_length*half_height*4;i++){
        if((i+1) % (half_length*2) != 0){
            if(i == tmp[count]){ count++; printf("@ ");}
            else printf("  ");
            fflush(stdout);
        }
        else{
            if(i == tmp[count]){count++; printf("@ ");}
            else puts("");
            fflush(stdout);
        }
    }
    printf("\e[1;1H\e[2J"); //clear screen
}
