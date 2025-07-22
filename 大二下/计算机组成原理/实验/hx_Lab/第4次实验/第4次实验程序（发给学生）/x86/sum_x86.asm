; x86（32位）汇编语言程序         sum_x86.asm          求累加和    sum = 1+2+...+n          

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
    n dd ?
    sum dd ?
    a dd 1
    b dd 0

.code
main:
        mov eax, sval(input("Input n= "))  		    ; 输入n，送eax
        mov n,eax                                     		    ; eax 保存到 n存储单元中
        mov ecx,n                                    		    ; ecx=n
        mov eax,a                                    		    ; eax=1
        mov ebx,b                                   		    ; ebx=0
sum_loop:
        add ebx,eax
        add eax,a
        cmp eax,ecx                                   		    ; 比较eax和ecx
        jg sum_stop 		              		    ; 大于则转sum_stop	
        jmp sum_loop
sum_stop:
        mov sum,ebx                                  		   ; 累加和结果（ebx）保存到sum存储单元中
        print chr$("Sum= ")
        print str$(sum)
        exit
end main