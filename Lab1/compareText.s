SYSEXIT = 1;
EXIT_SUCCESS = 0;
STDOUT = 1
SYSWRITE = 4
SYSREAD = 3
STDIN = 0

.text
msg: .ascii "Write text (5): \n"
msg_len = . - msg

msg2: .ascii "Strings are different\n"
msg2_len = . - msg2

msg3: .ascii "Strings are equal\n"
msg3_len = . - msg3

newline: .ascii "\n"
newline_len = . - newline

key: .ascii "test"
key_len = . - key

.data
buf: .ascii "    "
buf_len = . - buf

.global _start
_start:

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $0, %eax

petla:
mov key(,%eax, 1), %bl
mov buf(,%eax, 1), %cl
cmp %bl, %cl
jne different
add $1, %eax
cmp $buf_len, %eax
jge equal

jmp petla

different:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg2, %ecx
mov $msg2_len, %edx
int $0x80
jmp end

equal:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg3, %ecx
mov $msg3_len, %edx
int $0x80

end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
