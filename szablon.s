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
buf: .ascii "     "
buf_len = . - buf

.global _start
_start:



mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
