.code32

SYSEXIT = 1;
EXIT_SUCCESS = 0;
STDOUT = 1
SYSWRITE = 4
SYSREAD = 3
STDIN = 0

.text
msg: .ascii "Hello! \n"
msg_len = . - msg

.data

suma1:
.long 0xF001, 0xF100, 0x1012, 0x0000

suma2:
.long 0x1110, 0x1001, 0x10A0, 0x1111 

wynik:
.long 0x0000, 0x0000, 0x0000, 0x0000, 0x0000

wynik_len = . - wynik



.global _start
_start:

#liczba iteracji, czyli 3,2,1,0 - razem 4
mov $3, %edi

#puszujemy czyste flagi na stos, by za 1 razem nie było CF
clc
pushf

addloop:

#czyszczenie wszystkich flag, zeby adc nie uwzględniało złego przeniesienia
clc 

#popfc #pobranie flagi przeniesienia ze stosu
popf

#poprzesuwanie wartości
mov suma1(,%edi,4), %ax
mov suma2(,%edi,4), %bx

#dodawanko
adc %ax, %bx

#wynik! marsz do wyniku!
#mov %bx,wynik(,%edi,4)

push %bx

#zapisujemy flagi na stosik, by nam nie znikły
pushf

#porownanko
cmp $0 , %edi
jz carry

#i--
sub $1, %edi

jmp addloop


carry:
popf
mov $0,%ax
mov $0,%bx
adc %ax,%bx
push %bx
jmp endend

end:
mov $4, %edi

#pop %ecx

#mov $SYSWRITE, %eax
#mov $STDOUT, %ebx
#mov $wynik, %ecx
#mov $4, %edx
#int $0x80

#porownanko
cmp $0 , %edi
jz endend

#i--
sub $1, %edi

jmp end

endend:

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
