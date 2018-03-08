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



.global _start
_start:

mov $4, %edx

addloop:
mov suma1(,%edx,4), %eax
mov suma2(,%edx,4), %ebx
pushl %eax
subl $1 , %edx

cmpl $0 , %edx
je end

jmp addloop

end:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80



mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
