#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sizeTable 2048
#define naWektorach 1


clock_t startTime;

void startCounter(){
    startTime = clock();
}

double stopCounter(){
    return ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
}

struct vec {
    float a;
    float b;
    float c;
    float d;
};

struct vec a[sizeTable];
struct vec b[sizeTable];
struct vec result1[sizeTable];
struct vec result2[sizeTable];
struct vec result3[sizeTable];
struct vec result4[sizeTable];

struct vec Sum(struct vec a,struct vec b){
asm( 
    "movaps %0, %%xmm0\n\t"
    "movaps %1, %%xmm1\n\t"
    "addps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (a)
   : "m" (b)
    );
    return a;
}

struct vec Sub(struct vec a,struct vec b){
asm( 
    "movaps %0, %%xmm0\n\t"
    "movaps %1, %%xmm1\n\t"
    "subps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (a)
   : "m" (b)
    );
    return a;
}

struct vec Div(struct vec a,struct vec b){
asm( 
    "movaps %0, %%xmm0\n\t"
    "movaps %1, %%xmm1\n\t"
    "divps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (a)
   : "m" (b)
    );
    return a;
}

struct vec Mul(struct vec a,struct vec b){
asm( 
    "movaps %0, %%xmm0\n\t"
    "movaps %1, %%xmm1\n\t"
    "mulps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (a)
   : "m" (b)
    );
    return a;
}

void makeRandNumb(){
    for(int i=0;i<sizeTable;i++){
        a[i].a = (float)(rand()%1000000)/100.0f;
        a[i].b = (float)(rand()%1000000)/100.0f;
        a[i].c = (float)(rand()%1000000)/100.0f;
        a[i].d = (float)(rand()%1000000)/100.0f;
        b[i].a = (float)(rand()%1000000)/100.0f;
        b[i].b = (float)(rand()%1000000)/100.0f;
        b[i].c = (float)(rand()%1000000)/100.0f;
        b[i].d = (float)(rand()%1000000)/100.0f;
    }
}

void NaWektorach(){
    double timeToShow;
    
    startCounter();
    for(int i=0;i<sizeTable;i++){
        result1[i] = Sum(a[i],b[i]);
    }
    timeToShow = stopCounter();

    printf("%lf \n",timeToShow);
}

int main(){
    srand(time(NULL));
    makeRandNumb();

    if(naWektorach){
        NaWektorach();
    }else{

    }



    
    return 0;
}


