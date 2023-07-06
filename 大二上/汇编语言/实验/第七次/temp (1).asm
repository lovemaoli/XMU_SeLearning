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
includelib \masm32\lib\debug.lib

include \masm32\include\debug.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
include \masm32\include\windows.inc
include \masm32\include\msvcrt.inc
include \masm32\include\masm32.inc
include \masm32\macros\macros.asm
.data
    ORIGINNUM DD 0
    REMAINDER DD 0
    QUOTIENT DD 0
    PRODUCT DD 0
.code

START:	    
            MOV ECX,100
LOOP1:      INC ECX         ;执行除法
            ;PrintDec  ECX
            CMP ECX,10000   
            JZ  DONE
            MOV ORIGINNUM,ECX
            MOV ESI,0

LOOP2:      





CONLOOP2:   
            

CONLOOP1:   


DONE:       
            PrintText "Over"
END START