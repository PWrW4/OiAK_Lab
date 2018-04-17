#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//2048 = 4*512
//4096 = 4*1024
//8192 = 4*2048

//linuxik na pendrive -- done
//mierzenie czasu nie w funkcji -- done
//mierzenie wywołania czasu samych funkcji (bez for itd) -- done
//przekazywanie i obliczanie po 1 parametrze -- chyba bez sensu, wywolanie funkcji jest kosztowne i na pewnio wyjdzie dluzej, ale przez 4x wieksza ilosc wywolania funkcji

#define sizeTable 1024 
#define naWektorach 0
#define repeatNumber 10

clock_t startTime;
double timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv;

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
    
    for(int j=0;j<repeatNumber;j++){

        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            SumSIMD(a[i],b[i],&resultSum[i]);
            timeToShowSum += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
         

        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            DivSIMD(a[i],b[i],&resultDiv[i]);
            timeToShowDiv += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
         

        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            MulSIMD(a[i],b[i],&resultMul[i]);
            timeToShowMul += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        

        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            SubSIMD(a[i],b[i],&resultSub[i]);
            timeToShowSub += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }

    }

    timeToShowSum = timeToShowSum/(float)(repeatNumber*sizeTable);
    timeToShowDiv = timeToShowDiv/(float)(repeatNumber*sizeTable);
    timeToShowMul = timeToShowMul/(float)(repeatNumber*sizeTable);
    timeToShowSub = timeToShowSub/(float)(repeatNumber*sizeTable);

}

void SISD(){

    for(int j=0;j<repeatNumber;j++){
        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            SumSISD(a[i],b[i],&resultSum[i]);
            timeToShowSum += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        

        
        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            DivSISD(a[i],b[i],&resultDiv[i]);
            timeToShowDiv += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        

        
        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            MulSISD(a[i],b[i],&resultMul[i]);
            timeToShowMul += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        

        
        for(int i=0;i<sizeTable;i++){
            startTime = clock();
            SubSISD(a[i],b[i],&resultSub[i]);
            timeToShowSub += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        
    }

    timeToShowSum = timeToShowSum/(float)(repeatNumber*sizeTable);
    timeToShowDiv = timeToShowDiv/(float)(repeatNumber*sizeTable);
    timeToShowMul = timeToShowMul/(float)(repeatNumber*sizeTable);
    timeToShowSub = timeToShowSub/(float)(repeatNumber*sizeTable);

}

int main(){

    srand(time(NULL));
    makeRandNumb();

    if(naWektorach){
        printf("Typ obliczen: SIMD\n");
        SIMD();
        printf("Liczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n",(4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);


        	FILE *file;
			char str[4];
			char name[4+9] = {"SIMD_"};
			char end[4]={".txt"};

			sprintf(str, "%d", (4*sizeTable));
			strcat(name, str);
			//puts(name);
			strcat(name, end);
			//puts(name);

			if(file = fopen(name, "w"))
			{
				fprintf(file, "Typ obliczen: SIMD\nLiczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n", (4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);
			}
			else
			{
				printf("Wystąpił problem z otworzeniem pliku.\n");
			}


    }else{
        printf("Typ obliczen: SISD\n");
        SISD();
        printf("Liczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n",(4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);

            FILE *file;
			char str[4];
			char name[4+9] = {"SISD_"};
			char end[4]={".txt"};

			sprintf(str, "%d", (4*sizeTable));
			strcat(name, str);
			//puts(name);
			strcat(name, end);
			//puts(name);

			if(file = fopen(name, "w"))
			{
				fprintf(file, "Typ obliczen: SISD\nLiczba liczb: %d\nSredni czas [ms]: \n+ %lf \n- %lf \n* %lf \n/ %lf \n", (4*sizeTable),timeToShowSum,timeToShowSub,timeToShowMul,timeToShowDiv);
			}
			else
			{
				printf("Wystąpił problem z otworzeniem pliku.\n");
			}
    }



    
    return 0;
}


