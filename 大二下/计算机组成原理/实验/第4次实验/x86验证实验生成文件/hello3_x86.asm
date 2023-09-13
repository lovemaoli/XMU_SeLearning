.486                                    			; create 32 bit code
.model flat, stdcall                    		; 32 bit memory model
option casemap :none                    		; case sensitive 
include \masm32\include\windows.inc     	; always first
include \masm32\macros\macros.asm       	; MASM support macros
include \masm32\include\masm32.inc
include \masm32\include\gdi32.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\gdi32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.code                      		 		; Tell MASM where the code starts
start:                         		 	; The CODE entry point to the program
    print chr$("Hey, this actually works.",13,10)
    exit
end start                       			; Tell MASM where the program ends
