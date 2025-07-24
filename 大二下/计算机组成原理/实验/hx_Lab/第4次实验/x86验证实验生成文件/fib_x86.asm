.486
.model flat, stdcall

option casemap:none

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\gdi32.lib
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\masm32.lib

include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
include \masm32\include\windows.inc
include \masm32\include\msvcrt.inc
include \masm32\include\masm32.inc
include \masm32\macros\macros.asm

.data
    n dd 0
    a dd 0
    b dd 1
    i dd 1
    t dd 0

.code
start:
    mov eax, sval(input("Enter a number : "))
    mov n,eax

    print chr$("Fibonacci_number")
    print str$(0)
    print chr$(" is ")
    print str$(a)
    print chr$(" ",13,10)

    print chr$("Fibonacci_number")
    print str$(1)
    print chr$(" is ")
    print str$(b)
    print chr$(" ",13,10)

    mov ecx,n
    mov i,ecx
    dec i
    .while i
        mov eax,b
        mov t,eax
        mov eax,b
        add eax,a
        mov b,eax
        print chr$("Fibonacci_number")
        mov ecx,n
        sub ecx,i
        inc ecx
        print str$(ecx)
        print chr$(" is ")
        print str$(b)
        print chr$(" ",13,10)
        mov eax,t
        mov a,eax
        dec i
    .endw
    ret
end start