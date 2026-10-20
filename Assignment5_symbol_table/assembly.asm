
section .data
a   dd 4, 8
a1  db 'asdfasdfadsfasdfassdfasdfassdf', 10, 0
a2  dd 40, 83
a3  dd 4, 8
a4  db 'asdfasdfasdfasdfasdfasdfasdfas', 10, 0
a5  dd 40, 83
a6  dd 4, 8
a7  db 'asdfasdfasdfasdfasdfasdfasdfas', 10, 0
a8  dd 40, 83

section .text
global main

main:
    mov ebx, 123
    xor eax, eax
    add eax, ebx
    and eax, ebx
    sub eax, 5
    cmp eax, ebx
    inc eax
    dec ebx
    mul ebx
    div ebx

finish:

