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

odjemna:
.long 0x01111111, 0x11111B11, 0x12121212, 0x11110000

odjemnik:
.long 0x11100000, 0x10010A00, 0x000010A0, 0x11000011 

wynik:
.long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

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
mov odjemnik(,%edi,4), %eax
mov odjemna(,%edi,4), %ebx

#dodawanko
sbb %eax, %ebx

#wynik! marsz do wyniku!
#mov %ebx,wynik(,%edi,4)

push %ebx

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
mov $0,%eax
mov $0,%ebx
sbb %eax,%ebx
push %ebx
mov $4, %edi
jmp end

end:

pop %ecx

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
#mov $wynik, %ecx
mov $32, %edx
int $0x80

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
