#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct vec {
    float a;
    float b;
    float c;
    float d;
};

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

int main(){
    struct  vec v1;
    struct  vec v2;
    printf("Podaj 4 liczby : ");
    scanf("%f%f%f%f",&v1.a,&v1.b,&v1.c,&v1.d);
    printf("Podaj 4 liczby : ");
    scanf("%f%f%f%f",&v2.a,&v2.b,&v2.c,&v2.d);
    v1 = Sub(v1,v2);
    printf("\n Suma = %f %f %f %f \n", v1.a, v1.b, v1.c, v1.d);

    
    return 0;
}


