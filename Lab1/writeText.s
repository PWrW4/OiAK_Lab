SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.text

msg1: .ascii "Write text(5): \n"
msg1_len = . - msg1

msg2: .ascii "Written text: "
msg2_len = . - msg2

msg3: .ascii "\n"
msg3_len = . - msg3

.data
buf: .ascii "     "
buf_len = . - buf

.global _start

_start:

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg1, %ecx
mov $msg1_len, %edx
int $0x80

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg2, %ecx
mov $msg2_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg3, %ecx
mov $msg3_len, %edx
int $0x80

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
