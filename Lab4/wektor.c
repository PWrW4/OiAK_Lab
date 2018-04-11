#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//2048 = 4*512
//4096 = 4*1024
//8192 = 4*2048

#define sizeTable 2048 
#define naWektorach 1
#define repeatNumber 10

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
struct vec resultSum[sizeTable];
struct vec resultSub[sizeTable];
struct vec resultMul[sizeTable];
struct vec resultDiv[sizeTable];

void Sum(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "addps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void Sub(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "subps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void Div(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "divps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void Mul(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "mulps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
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

void SIMD(){
    double timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv;
    
    for(int j=0;j<repeatNumber;j++){
        startCounter();
        for(int i=0;i<sizeTable;i++){
            Sum(a[i],b[i],&resultSum[i]);
        }
        timeToShowSum += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            Div(a[i],b[i],&resultDiv[i]);
        }
        timeToShowDiv += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            Mul(a[i],b[i],&resultMul[i]);
        }
        timeToShowMul += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            Sub(a[i],b[i],&resultSub[i]);
        }
        timeToShowSub += stopCounter();
    }

    timeToShowSum = timeToShowSum/(float)repeatNumber;
    timeToShowDiv = timeToShowDiv/(float)repeatNumber;
    timeToShowMul = timeToShowMul/(float)repeatNumber;
    timeToShowSub = timeToShowSub/(float)repeatNumber;

    printf("Liczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n",(4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);;
}

void SISD(){
    double timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv;

    printf("Liczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n",(4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);
}

int main(){
    srand(time(NULL));
    makeRandNumb();

    if(naWektorach){
        printf("Typ obliczen: SIMD\n");
        SIMD();
    }else{
        printf("Typ obliczen: SISD\n");
        SISD();
    }



    
    return 0;
}


