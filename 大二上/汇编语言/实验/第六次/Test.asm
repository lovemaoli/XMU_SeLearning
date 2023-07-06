; asm文件注释格式为分号
; 定义程序模式
.386
.model            flat,stdcall
option            casemap    :none

; 包含必要头文件，基本每个win32 汇编程序都需要包含这几个

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
 sz   db '1 ',0
 DATA1  Db 7,5,3,2,6,9,1,8,4,0dh,0ah,'$'
 szLINE db 0ah,0dh,0
.code
START:	    MOV SI,8

           
Loop1:		
			
Loop2:			
	
     		MOV BP,0             ;排序后数据打印
			LEA EBX,DATA1	
 PRINT1:    LEA ecx,sz	
            MOV AL,[EBX]
            add al,'0'
            mov [ecx],al
            push offset sz
            call StdOut
	        ADD BP,1
			ADD EBX,1
			CMP BP,SI
			JLE PRINT1
END START