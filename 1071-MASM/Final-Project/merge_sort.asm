; .386

Include \masm32\include\Irvine32.inc
Includelib \masm32\lib\Irvine32.lib 
includelib \masm32\lib\Kernel32.lib
includelib \masm32\lib\User32.lib

.data
    buf DWORD 100 DUP(?)
    arr DWORD 100 DUP(?)
    n DWORD ?
    M DWORD ?
Carry MACRO Reg ;carry arr into buf
mov edx,[arr+4*Reg]
inc Reg
mov [buf+4*ecx],edx
ENDM

.code
main PROC
L1:
    call readInt

    ; check range
    cmp eax,0
    jle Quit
    cmp eax,100
    jg Quit
    ; store n
    mov n,eax
    ; scan array
    mov ecx,n
    mov edi,offset arr
sa: 
    call ReadInt
    mov DWORD PTR[edi],eax
    add edi,TYPE DWORD
    loop sa

    ; start recursive
    mov eax,0
    push eax
    mov eax,n
    push eax
    call MergeSort
    
    ; print array
    mov ecx,n
    mov ebx,0
pa: 
    mov eax,[arr+4*ebx]
    call WriteInt
    call WriteSpace
    inc ebx
    loop pa

    call Crlf
    loop L1
Quit:
main ENDP

writeSpace PROC uses eax
    mov al,' '
    call WriteChar
    ret
writeSpace ENDP

MergeSort PROC
    push ebp
    mov ebp,esp
    mov eax,[ebp+12] ; eax=L+1
    inc eax
    mov ebx,[ebp+8] ; ebx=R

    ; if(L+1)<=R return;
    cmp eax,ebx
    jge MQuit

    ; M=(L+R)>>1
    add ebx,[ebp+12]
    shr ebx,1
    push ebx

    ; MergeSort(L,M)
    mov eax,[ebp+12]
    push eax
    push ebx
    call MergeSort

    ; MergeSort(M,R)
    mov eax,[ebp+8]
    push ebx
    push eax
    call MergeSort

    ; set eax=i=L,ebx=j=M,ecx=k=L
    pop ebx ; push before recursive
    mov M,ebx
    mov eax,[ebp+12]
    mov ecx,[ebp+12]
M1:
    ; check if(i>=M)
    cmp eax,M
    jge M3
    ; check if(j>=R)
    cmp ebx,[ebp+8]
    jge M2
    
    ; cmp arr[i],arr[j]
    mov edx,[arr+4*eax] ;edx=arr[i]
    cmp edx,[arr+4*ebx]
    ; if(arr[i]>arr[j])
    jg M3
    ; else
M2:
    Carry eax ; buf[k] = arr[i++]
    jmp M4
M3:
    Carry ebx ; buf[k] = arr[j++]
M4:
    inc ecx ; k++
    ; if k==R break;
    cmp ecx,[ebp+8]
    jne M1

    ; ecx=R-L
    mov ecx,[ebp+8]
    sub ecx,[ebp+12]
    ; ebx=L
    mov ebx,[ebp+12]

RF: ; buf to arr 
    mov eax,[buf+4*ebx]
    mov [arr+4*ebx],eax
    ; call WriteInt
    inc ebx
    loop RF
    ; call Crlf
MQuit:
    mov esp,ebp
    pop ebp
    ret 8
MergeSort ENDP

END main