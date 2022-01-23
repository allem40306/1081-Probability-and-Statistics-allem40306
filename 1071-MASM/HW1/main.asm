; .386

Include \masm32\include\Irvine32.inc
Includelib \masm32\lib\Irvine32.lib 
includelib \masm32\lib\Kernel32.lib
includelib \masm32\lib\User32.lib

.data
num DWORD 0
tmp DWORD 0
str_1 BYTE "Fibiacci Numbers by , Allen",0
str_2 BYTE "What's your name? ",0
str_3 BYTE "HI, ",0
str_4 BYTE "How many Fibonacci numbers should I display?",0
str_5 BYTE "Enter an integer in the range [1..47]: ",0
str_6 BYTE "That number was out of range, try again.",0
str_7 BYTE "   ",0
str_8 BYTE "Goodbye, ",0
N BYTE 10 DUP(?)
.code
main PROC
L1: ; print info  
    call Clrscr
    mov edx,OFFSET str_1
    call WriteString
    call Crlf
    mov edx,OFFSET str_2
    call WriteString
    mov edx,OFFSET N
    mov ecx,10
    call readString
    mov edx,OFFSET str_3
    call WriteString
    mov edx,OFFSET N
    call WriteString
    call Crlf
L2: ; chack range
    mov edx,OFFSET str_4
    call WriteString
    call Crlf
    mov edx,OFFSET str_5
    call WriteString
    call readint
    call Crlf
    cmp eax,1
    jl L3
    cmp eax,47
    jg L3
    mov ecx,eax
    mov num,0
    mov eax,0
    mov ebx,1
    jmp L4
L3: ; print error messenge
    mov edx,OFFSET str_6
    call WriteString
    call crlf
    jmp L2
L4: ; print fibonacci
    call pf
    call WriteDec
    mov tmp,eax
    mov eax,ebx
    add ebx,tmp
    inc num
    Loop L4
L5: ; print goodbye
    call crlf
    mov edx,OFFSET str_8
    call WriteString
    mov edx,OFFSET N
    call WriteString
    call Crlf
    exit
main ENDP

pf PROC uses eax ebx edx ; print 3 blank or wrap
La:
    xor edx,edx
    mov eax,num
    mov ebx,5
    div ebx
    cmp edx,0
    je Lb
    mov edx,OFFSET str_7
    call WriteString
    jmp Lc
Lb:
    cmp eax,0
    je Lc
    call Crlf
Lc:
    ret
pf ENDP

END main