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
.long 0xF0010000, 0xF1000000, 0x00001012, 0x00000000

suma2:
.long 0x11100000, 0x10010000, 0x000010A0, 0x11000011 

wynik:
.long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010000

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
mov suma1(,%edi,4), %eax
mov suma2(,%edi,4), %ebx

#dodawanko
adc %eax, %ebx

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
adc %eax,%ebx
push %ebx
jmp end

end:
mov $4, %edi

#pop %ecx

#mov %ecx,wynik(,%edi,4)

#mov $SYSWRITE, %eax
#mov $STDOUT, %ebx
#mov $wynik, %ecx
#mov $32, %edx
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
