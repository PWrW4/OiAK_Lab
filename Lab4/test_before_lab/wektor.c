// Kompilacja i linkowanie na systemie 64 bitowym 
//  gcc  -c sumuj64.c -o sumuj64.o
//  nasm -felf64 suma64.asm -o suma64.o
//  gcc sumuj64.o suma64.o -o suma64

#include <stdio.h>
extern int suma(int, int);
int main(){
   int a, b;
   printf("Podaj dwie liczby : ");
   scanf("%d%d",&a,&b);
   int c = suma(a, b);
   printf("\n Suma = %d \n", c);
   return 0;
}


