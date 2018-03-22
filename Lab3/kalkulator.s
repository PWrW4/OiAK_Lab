.code32

SYSEXIT = 1;
EXIT_SUCCESS = 0;
STDOUT = 1
SYSWRITE = 4
SYSREAD = 3
STDIN = 0

.data

zero: .float 0.0
plus: .float 3.7
minus: .float -2.3

.text
#msg: .ascii "Wojciech Wójcik - Hello! \n"
#msg_len = . - msg

.global _start
_start:

finit

fld plus
fdiv zero

fld minus
fdiv zero 

fld zero
fmul minus

fld zero
fmul plus

fld zero
fdiv zero





end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
