#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//2048 = 4*512
//4096 = 4*1024
//8192 = 4*2048

//linuxik na pendrive
//mierzenie czasu nie w funkcji
//mierzenie wywołania czasu samych funkcji (bez for itd)
//przekazywanie i obliczanie po 1 parametrze

#define sizeTable 8192 
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

//SIMD-------------------------------------------------
void SumSIMD(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "addps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void SubSIMD(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "subps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void DivSIMD(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "divps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

void MulSIMD(struct vec a,struct vec b,struct vec* res){
asm( 
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "mulps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*res)
   : "m" (a),"m" (b)
    );
}

//SISD-------------------------------------------------
void SumSISD(struct vec a,struct vec b,struct vec *res){
    
asm( 
    "fld %4\n\t"
    "fadd %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fadd %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fadd %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fadd %11\n\t"
    "fstp %3\n\t"
    
    


   :    "=m" (res->a), //0
        "=m" (res->b), //1
        "=m" (res->c), //2
        "=m" (res->d)  //3
   :    "m" (a.a), //4
        "m" (a.b), //5
        "m" (a.c), //6
        "m" (a.d), //7
        "m" (b.a), //8
        "m" (b.b), //9
        "m" (b.c), //10
        "m" (b.d) //11       
    );

}

void SubSISD(struct vec a,struct vec b,struct vec* res){

asm( 
    "fld %4\n\t"
    "fsub %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fsub %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fsub %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fsub %11\n\t"
    "fstp %3\n\t"
    
    


   :    "=m" (res->a), //0
        "=m" (res->b), //1
        "=m" (res->c), //2
        "=m" (res->d)  //3
   :    "m" (a.a), //4
        "m" (a.b), //5
        "m" (a.c), //6
        "m" (a.d), //7
        "m" (b.a), //8
        "m" (b.b), //9
        "m" (b.c), //10
        "m" (b.d) //11       
    );

}

void DivSISD(struct vec a,struct vec b,struct vec* res){

asm( 
    "fld %4\n\t"
    "fdiv %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fdiv %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fdiv %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fdiv %11\n\t"
    "fstp %3\n\t"
    
    


   :    "=m" (res->a), //0
        "=m" (res->b), //1
        "=m" (res->c), //2
        "=m" (res->d)  //3
   :    "m" (a.a), //4
        "m" (a.b), //5
        "m" (a.c), //6
        "m" (a.d), //7
        "m" (b.a), //8
        "m" (b.b), //9
        "m" (b.c), //10
        "m" (b.d) //11       
    ); 

}

void MulSISD(struct vec a,struct vec b,struct vec* res){

asm( 
    "fld %4\n\t"
    "fmul %8\n\t"
    "fstp %0\n\t"

    "fld %5\n\t"
    "fmul %7\n\t"
    "fstp %1\n\t"

    "fld %6\n\t"
    "fmul %10\n\t"
    "fstp %2\n\t"

    "fld %7\n\t"
    "fmul %11\n\t"
    "fstp %3\n\t"
    
    


   :    "=m" (res->a), //0
        "=m" (res->b), //1
        "=m" (res->c), //2
        "=m" (res->d)  //3
   :    "m" (a.a), //4
        "m" (a.b), //5
        "m" (a.c), //6
        "m" (a.d), //7
        "m" (b.a), //8
        "m" (b.b), //9
        "m" (b.c), //10
        "m" (b.d) //11       
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
            SumSIMD(a[i],b[i],&resultSum[i]);
        }
        timeToShowSum += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            DivSIMD(a[i],b[i],&resultDiv[i]);
        }
        timeToShowDiv += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            MulSIMD(a[i],b[i],&resultMul[i]);
        }
        timeToShowMul += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            SubSIMD(a[i],b[i],&resultSub[i]);
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

    for(int j=0;j<repeatNumber;j++){
        startCounter();
        for(int i=0;i<sizeTable;i++){
            SumSISD(a[i],b[i],&resultSum[i]);
        }
        timeToShowSum += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            DivSISD(a[i],b[i],&resultDiv[i]);
        }
        timeToShowDiv += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            MulSISD(a[i],b[i],&resultMul[i]);
        }
        timeToShowMul += stopCounter();

            startCounter();
        for(int i=0;i<sizeTable;i++){
            SubSISD(a[i],b[i],&resultSub[i]);
        }
        timeToShowSub += stopCounter();
    }

    timeToShowSum = timeToShowSum/(float)repeatNumber;
    timeToShowDiv = timeToShowDiv/(float)repeatNumber;
    timeToShowMul = timeToShowMul/(float)repeatNumber;
    timeToShowSub = timeToShowSub/(float)repeatNumber;

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


