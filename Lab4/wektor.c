#include <stdio.h>

struct vec {
    int a;
    int b;
    int c;
    int d;
};

struct vec Suma(struct vec a,struct vec b){
asm( 
    "movaps $0, %%xmm0"
    "movaps $1, %%xmm1"
    "addps %%xmm1, %%xmm0"
    "movaps %%xmm0, $0"
   : "=m" (&a)
   : "m" (&b)
    );
    return a;
}

int main(){
    struct  vec v1;
    struct  vec v2;
    printf("Podaj 4 liczby : ");
    scanf("%d%d%d%d",&v1.a,&v1.b,&v1.c,&v1.d);
    printf("Podaj 4 liczby : ");
    scanf("%d%d%d%d",&v2.a,&v2.b,&v2.c,&v2.d);
    v1 = Suma(v1,v2);
    printf("\n Suma = %d %d %d %d \n", v1.a, v1.b, v1.c, v1.d);
    //printf("\n Suma = %d \n", Suma(v1,v2).b);
    //printf("\n Suma = %d \n", Suma(v1,v2).c);
    //printf("\n Suma = %d \n", Suma(v1,v2).d);
    
    return 0;
}


