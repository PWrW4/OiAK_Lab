SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

text: .ascii "asd"
text_len = . - text

.data

buff: .ascii "   "
buff_len = . - buff

.global _start
_start:

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buff, %ecx
mov $buff_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $buff, %ecx
mov $buff_len, %edx
int $0x80

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
