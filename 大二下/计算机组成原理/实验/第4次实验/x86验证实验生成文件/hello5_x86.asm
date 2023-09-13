.486
.model flat, stdcall
option casemap: none 
include \masm32\include\msvcrt.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\kernel32.lib
 
.data
    szText db 'Hello World!', 0
 
.code
start:
    invoke crt_printf, addr szText
    invoke ExitProcess, 0
end start