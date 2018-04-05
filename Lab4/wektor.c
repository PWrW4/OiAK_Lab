#include <stdio.h>

struct vec {
    int a;
    int b;
    int c;
    int d;
};

struct vec Suma(struct vec a,struct vec b){
asm( 
    "add %%ebx, %%eax"
   : "=a" (a.a)
   : "b" (b.a)
    );
    return a;
}

int main(){
    struct vec v1;
    struct vec v2;
    v2.a = 4;
    v2.b = 1;
    v2.c = 1;
    v2.d = 1;
    printf("Podaj 4 liczby : ");
    scanf("%d%d%d%d",&v1.a,&v1.b,&v1.c,&v1.d);
    printf("\n Suma = %d \n", Suma(v1,v2).a);
    //printf("\n Suma = %d \n", Suma(v1,v2).b);
    //printf("\n Suma = %d \n", Suma(v1,v2).c);
    //printf("\n Suma = %d \n", Suma(v1,v2).d);
    
    return 0;
}


